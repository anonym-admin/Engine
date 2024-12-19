#include "pch.h"
#include "Game.h"
#include "Application.h"

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
	m_engineCore = app->GetEngineCore();

	RECT rect = {};
	GetClientRect(m_app->GetHwnd(), &rect);
	m_screenWidth = rect.right - rect.left;
	m_screenHeight = rect.bottom - rect.top;

	// Create world.
	IT_World* world = m_engineCore->CreateWorld(L"WORLD_01");
	m_engineCore->AddWorld(world);
	// Create Level.
	IT_Level* level = m_engineCore->CreateLevel(L"LEVEL_01");
	world->AddLevel(level);
	// Create Game Object.
	IT_TextUI* textUI = m_engineCore->CreateTextUI(256, 64, 100, 100, 1.0f, 1.0f, 0.0f, L"Consolas", 14, nullptr);
	level->AddGmaeObject(textUI, GAME_OBJ_TYPE::UI);
	m_textUI = textUI;

	IT_CoordinateObject* coordObj = m_engineCore->CreateCoordinateObject();
	level->AddGmaeObject(coordObj, GAME_OBJ_TYPE::COORDINATE);

	world->SetCurrentLevel();
	world->BeginWorld();
	
	return true;
}

void Game::CleanUpGame()
{
}

void Game::RunGame()
{
	// Update text.
	wchar_t buf[36] = {};
	swprintf_s(buf, L"fps: %d dt: %f", m_engineCore->GetFps(), m_engineCore->GetDeltaTime());
	m_textUI->WriteText(buf);

	m_engineCore->Tick();
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

	//// Update text.
	//uint32 cmdListCount = m_renderer->GetCmdListCount();
	//wchar_t buf[36] = {};
	//swprintf_s(buf, L"fps: %d cmdList: %d", m_fps, cmdListCount);
	//m_textUI->Update(buf);
}

void Game::UpdateMousePicking()
{
	//static Vector3 prevPos = Vector3(0.0f);
	//static float prevRatio = 0.0f;
	//static Actor* selected = nullptr;
	//bool leftBtn = m_app->IsLeftBtnDown();
	//bool rightBtn = m_app->IsRightBtnDown();
	//float ndcX = m_app->GetNdcMousePosX();
	//float ndcY = m_app->GetNdcMousePosY();

	//if (m_app->IsLeftBtnDown() || m_app->IsRightBtnDown())
	//{
	//	if (!selected)
	//	{
	//		Actor* actor = IntersectActor(ndcX, ndcY, &prevPos, &prevRatio);
	//		if (actor)
	//		{
	//			selected = actor;
	//		}
	//	}
	//	else
	//	{
	//		if (leftBtn || rightBtn)
	//		{
	//			if (leftBtn) // Move
	//			{
	//				Vector3 curPos = Vector3(0.0f);
	//				m_renderer->MousePickingAfterMoveObject(ndcX, ndcY, &curPos, prevRatio);
	//				float moveLen = (curPos - prevPos).Length();

	//				if (moveLen >= 1e-5)
	//				{
	//					selected->MovePosition(curPos - prevPos);
	//					prevPos = curPos;
	//				}
	//			}
	//			else // Rotation
	//			{
	//			}
	//		}
	//	}
	//}
	//else
	//{
	//	selected = nullptr;
	//}
}

void* Game::IntersectActor(float ndcX, float ndcY, Vector3* prevPos, float* prevRatio)
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


