#include "pch.h"
#include "Game.h"
#include "Application.h"
#include "GeometryGenerator.h"
#include "Actor.h"
#include "Camera.h"
#include "TextUI.h"
#include "CharacterObject_01.h"
#include "CoordinateObject.h"

/*
=======
Game
=======
*/

Game::Game()
{
}

Game::~Game()
{
}

bool Game::InitGame(Application* app)
{
	m_app = app;
	m_renderer = app->GetRenderer();

	RECT rect = {};
	GetClientRect(m_app->GetHwnd(), &rect);
	m_screenWidth = rect.right - rect.left;
	m_screenHeight = rect.bottom - rect.top;

	// Initialize the camera.
	InitCamera();
	// Initialize the actor lists.
	InitActorLists();
	// Initialize the character.
	InitCharacters();
	// Initialize the text ui.
	m_textUI = new TextUI;
	m_textUI->Initialize(m_renderer, 256, 64, m_screenWidth - 256, 0, 1.0f, 1.0f, 0.0f, L"Consolas", 14);
	// Create the coordinate object.
	m_coordObj = new CoordinateObject;
	m_coordObj->Initialize(m_renderer);

	return true;
}

void Game::CleanUpGame()
{
	if (m_coordObj)
	{
		delete m_coordObj;
		m_coordObj = nullptr;
	}
	if (m_textUI)
	{
		delete m_textUI;
		m_textUI = nullptr;
	}
	CleanCharacters();
	CleanActorLists();
	CleanCamera();
}

void Game::RunGame()
{
	static uint32 fps = 0;
	static uint64 prevTickCount = 0;
	fps++;

	uint64 curTickCount = ::GetTickCount64();
	Update(curTickCount);

	m_renderer->BeginRender();

	Render();

	m_renderer->EndRender();

	m_renderer->Present();

	if (curTickCount - prevTickCount > 1000)
	{
		m_fps = fps;
		fps = 0;
		prevTickCount = curTickCount;

		wchar_t buf[36] = {};
		swprintf_s(buf, L"fps: %d", m_fps);
		::SetWindowText(m_app->GetHwnd(), buf);
	}
}

bool Game::InitCamera()
{
	// Set camera position.
	Vector3 camPos = Vector3(0.0f, 0.0f, -2.0f);
	Vector3 camDir = Vector3(0.0f, 0.0f, 1.0f);
	m_camera = new Camera;
	m_camera->Initialize(m_app, camPos, camDir);

	return true;
}

bool Game::InitActorLists()
{
	// Initialize actor container.
	m_htActors = HT_CreateHashTable(MAX_ACTOR_NUM);

	const float cubeScale = 0.2f;
	m_cube = GeometryGenerator::MakeCube(cubeScale);

	const wchar_t* basePath = L"../../Assets/";
	const wchar_t* textureFilenames[] = 
	{
		L"tex_00.dds",
		L"tex_01.dds",
		L"tex_02.dds",
		L"tex_03.dds",
		L"tex_04.dds",
		L"tex_05.dds",
	};

	for (uint32 i = 0; i < m_cube->numMeshes; i++)
	{
		wchar_t filePath[256] = {};
		wcscat_s(filePath, basePath);
		wcscat_s(filePath, textureFilenames[i]);

		wcscpy_s(m_cube->meshes[i].textureFileaname, 256, filePath);
	}

	Actor* actor = new Actor;
	ACTOR_HANDLE actorHandle = {};
	actorHandle.type = ACTOR_TYPE::MESH_OBJ;
	actorHandle.mesh.pos = Vector3(0.0f, 0.0f, 1.0f);
	actorHandle.mesh.scale = Vector3(1.0f);
	actorHandle.mesh.geometry = m_cube;
	actor->Initialize(m_renderer, &actorHandle);
	
	HT_Insert(m_htActors, (void*)L"Box", actor);

	return true;
}

bool Game::InitCharacters()
{
	Actor* actor = reinterpret_cast<Actor*>(HT_Find(m_htActors, (void*)L"Box"));
	
	m_character_01 = new CharacterObject_01;
	m_character_01->Initialize();
	m_character_01->SetActor(actor);

	return true;
}

void Game::Update(uint64 curTick)
{
	static uint64 prevTickCount = curTick;

	// 16ms 마다 한번씩 업데이트
	// 1s 에는 60번 업데이트
	if (curTick - prevTickCount < 16)
	{
		return;
	}
	prevTickCount = curTick;

	// Mouse Picking.
	// UpdateMousePicking();

	// Update camera.
	m_camera->Update();

	// Update text.
	uint32 cmdListCount = m_renderer->GetCmdListCount();
	wchar_t buf[36] = {};
	swprintf_s(buf, L"fps: %d cmdList: %d", m_fps, cmdListCount);
	m_textUI->Update(buf);
}

void Game::UpdateMousePicking()
{
	static Vector3 prevPos = Vector3(0.0f);
	static float prevRatio = 0.0f;
	static Actor* selected = nullptr;
	bool leftBtn = m_app->IsLeftBtnDown();
	bool rightBtn = m_app->IsRightBtnDown();
	float ndcX = m_app->GetNdcMousePosX();
	float ndcY = m_app->GetNdcMousePosY();

	if (m_app->IsLeftBtnDown() || m_app->IsRightBtnDown())
	{
		if (!selected)
		{
			Actor* actor = IntersectActor(ndcX, ndcY, &prevPos, &prevRatio);
			if (actor)
			{
				selected = actor;
			}
		}
		else
		{
			if (leftBtn || rightBtn)
			{
				if (leftBtn) // Move
				{
					Vector3 curPos = Vector3(0.0f);
					m_renderer->MousePickingAfterMoveObject(ndcX, ndcY, &curPos, prevRatio);
					float moveLen = (curPos - prevPos).Length();

					if (moveLen >= 1e-5)
					{
						selected->MovePosition(curPos - prevPos);
						prevPos = curPos;
					}
				}
				else // Rotation
				{
				}
			}
		}
	}
	else
	{
		selected = nullptr;
	}
}

Actor* Game::IntersectActor(float ndcX, float ndcY, Vector3* prevPos, float* prevRatio)
{
	//float hitDist = 0.0f;
	//DL_LIST* cur = m_headActorListNode;
	//while (cur != nullptr)
	//{
	//	Actor* actor = reinterpret_cast<Actor*>(cur);
	//	DirectX::BoundingBox boundingBox = actor->GetBoundingBox();
	//	bool pick = m_renderer->MousePicking(boundingBox, ndcX, ndcY, prevPos, &hitDist, prevRatio);
	//	if (pick)
	//	{
	//		return actor;
	//	}
	//	cur = cur->next;
	//}
	return nullptr;
}

void Game::Render()
{
	// Render character.
	m_character_01->Render();

	// Render text.
	m_textUI->Render();

	// Render Coordinate object.
	m_coordObj->Render();
}

void Game::CleanCamera()
{
	if (m_camera)
	{
		delete m_camera;
		m_camera = nullptr;
	}
}

void Game::CleanActorLists()
{
	for (uint32 i = 0; i < m_htActors->tableSize; i++)
	{
		DL_LIST* cur = m_htActors->headList[i];
		while (cur != nullptr)
		{
			DL_LIST* next = cur->next;
			Bucket* bucket = reinterpret_cast<Bucket*>(cur);
			Actor* actor = reinterpret_cast<Actor*>(bucket->value);

			if (actor)
			{
				delete actor;
				actor = nullptr;
			}

			cur = next;
		}
	}

	if (m_htActors)
	{
		HT_DestroyHashTable(m_htActors);
	}

	if (m_cube)
	{
		GeometryGenerator::DestroyGeometry(m_cube);
		m_cube = nullptr;
	}
}

void Game::CleanCharacters()
{
	if (m_character_01)
	{
		delete m_character_01;
		m_character_01 = nullptr;
	}
}
