#include "pch.h"
#include "Game.h"
#include "Application.h"
#include "GeometryGenerator.h"
#include "Actor.h"

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
	m_renderer = app->GetRenderer();

	m_app = app;

	RECT rect = {};
	GetClientRect(m_app->GetHwnd(), &rect);
	m_screenWidth = rect.right - rect.left;
	m_screenHeight = rect.bottom - rect.top;

	// Set camera position.
	m_renderer->SetCameraPos(0.0f, 0.0f, -5.0f);

	//// Set the mesh object.
	//m_square = GeometryGenerator::MakeSquare();
	//m_tiledTexture = m_renderer->CreateTiledTexture(256, 256, 32, 32);
	//m_meshObj = m_renderer->CreateMeshObject();
	//m_meshObj->CreateMeshBuffers(m_square);
	//m_meshObj->SetTexture(m_tiledTexture);
	//m_meshObj->SetTransform(Matrix::Identity);

	// Set the actors.
	const uint32 NUM_ACTORS = 20;
	for (uint32 i = 0; i < NUM_ACTORS; i++)
	{
	    Actor* actor = new Actor;
	    actor->Initialize(m_renderer);
	    
	    float x = static_cast<float>((rand() % 21) - 10);
	    float y = static_cast<float>((rand() % 21) - 10);
	    float z = static_cast<float>((rand() % 21) - 10);

	    actor->SetPosition(Vector3(x, y, z));

	    DL_InsertBack(&m_headActorListNode, &m_tailActorListNode, &actor->actorLink);
	}

	// Set the font object.
	m_fontTexWidth = 256;
	m_fontTexHeight = 64;
	m_fontObj = m_renderer->CreateFontObject(L"Consolas", 12);
	m_fontTexture = m_renderer->CreateDynamicTexture(m_fontTexWidth, m_fontTexHeight, "font");
	m_fontImage = (uint8*)malloc(m_fontTexWidth * m_fontTexHeight * 4);

	// Create the sprite.
	m_imageWidth = 512;
	m_imageHeight = 256;
	m_image = (uint8*)malloc(m_imageWidth * m_imageHeight * 4);
	uint32* dest = reinterpret_cast<uint32*>(m_image);
	for (uint32 y = 0; y < m_imageHeight; y++)
	{
		for (uint32 x = 0; x < m_imageWidth; x++)
		{
			dest[x + m_imageWidth * y] = 0xff0000ff; // red
		}
	}
	m_dynamicTexture = m_renderer->CreateDynamicTexture(m_imageWidth, m_imageHeight, "gradation");
	m_spriteObj0 = m_renderer->CreateSpriteObject();
	m_spriteObj1 = m_renderer->CreateSpriteObject();

	// Create the line object.
	m_lineObj = m_renderer->CreateLineObject();
	m_lineData = new LineData;
	m_lineData->numVertices = 6;
	m_lineData->vertices = new LineVertex[6];
	
	m_lineData->vertices[0].position = Vector3(0.0f, 0.0f, 0.0f);
	m_lineData->vertices[1].position = Vector3(0.0f, 1.0f, 0.0f);
	m_lineData->vertices[2].position = Vector3(0.0f, 0.0f, 0.0f);
	m_lineData->vertices[3].position = Vector3(1.0f, 0.0f, 0.0f);
	m_lineData->vertices[4].position = Vector3(0.0f, 0.0f, 0.0f);
	m_lineData->vertices[5].position = Vector3(0.0f, 0.0f, 1.0f);
	m_lineData->vertices[0].color = Vector3(1.0f, 0.0f, 1.0f);
	m_lineData->vertices[1].color = Vector3(1.0f, 0.0f, 1.0f);
	m_lineData->vertices[2].color = Vector3(0.0f, 1.0f, 0.0f);
	m_lineData->vertices[3].color = Vector3(0.0f, 1.0f, 0.0f);
	m_lineData->vertices[4].color = Vector3(1.0f, 0.0f, 0.0f);
	m_lineData->vertices[5].color = Vector3(1.0f, 0.0f, 0.0f);

	m_lineObj->CreateLineBuffers(m_lineData);

	return true;
}

void Game::CleanUpGame()
{
	if (m_lineData)
	{
		if (m_lineData->vertices)
		{
			delete[] m_lineData->vertices;
			m_lineData->vertices = nullptr;
		}
		delete m_lineData;
	}
	if (m_lineObj)
	{
		m_lineObj->Release();
		m_lineObj = nullptr;
	}
	if (m_spriteObj1)
	{
		m_spriteObj1->Release();
		m_spriteObj1 = nullptr;
	}
	if (m_spriteObj0)
	{
		m_spriteObj0->Release();
		m_spriteObj0 = nullptr;
	}
	if (m_dynamicTexture)
	{
		m_renderer->DestroyTexture(m_dynamicTexture);
		m_dynamicTexture = nullptr;
	}
	if (m_image)
	{
		free(m_image);
		m_image = nullptr;
	}
	if (m_fontImage)
	{
		free(m_fontImage);
		m_fontImage = nullptr;
	}
	if (m_fontTexture)
	{
		m_renderer->DestroyTexture(m_fontTexture);
		m_fontTexture = nullptr;
	}
	if (m_fontObj)
	{
		m_renderer->DestroyFontObject(m_fontObj);
		m_fontObj = nullptr;
	}
	if (m_meshObj)
	{
		m_meshObj->Release();
		m_meshObj = nullptr;
	}
	if (m_tiledTexture)
	{
		m_renderer->DestroyTexture(m_tiledTexture);
		m_tiledTexture = nullptr;
	}
	if (m_square)
	{
		GeometryGenerator::DestroyGeometry(m_square);
		m_square = nullptr;
	}
	DL_LIST* cur = m_headActorListNode;
	while (cur != nullptr)
	{
		DL_LIST* next = cur->next;
		Actor* actor = reinterpret_cast<Actor*>(cur);
		DL_Delete(&m_headActorListNode, &m_tailActorListNode, cur);
		delete actor;
		cur = next;
	}
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

	UpdateMousePicking();

	// Update actors.
	DL_LIST* cur = m_headActorListNode;
	while (cur != nullptr)
	{
		Actor* actor = reinterpret_cast<Actor*>(cur);
		actor->Update();
		cur = cur->next;
	}

	// Update text.
	uint32 cmdListCount = m_renderer->GetCmdListCount();
	wchar_t buf[36] = {};
	swprintf_s(buf, L"fps: %d cmdList: %d", m_fps, cmdListCount);
	uint32 strLen = static_cast<uint32>(wcslen(buf));
	int32 texWidth = 0;
	int32 texHeight = 0;

	if (wcscmp(m_gameText, buf))
	{
		memset(m_fontImage, 0, m_fontTexWidth * m_fontTexHeight * 4);
		m_renderer->WriteTextToBitmap(m_fontImage, m_fontTexWidth, m_fontTexHeight, m_fontTexWidth * 4, &texWidth, &texHeight, m_fontObj, buf, strLen, FONT_COLOR_TYPE::SPRING_GREEN);
		m_renderer->UpdateTextureWidthImage(m_fontTexture, m_fontImage, m_fontTexWidth, m_fontTexHeight);
		wcscpy_s(m_gameText, buf);
	}

	// Update dynamic gradation texture.
	static uint32 count = 0;
	static uint32 tileColorR = 0;
	static uint32 tileColorG = 0;
	static uint32 tileColorB = 0;

	const uint32 tileWidth = 16;
	const uint32 tileHeight = 16;

	uint32 tileCountX = m_imageWidth / tileWidth;
	uint32 tileCountY = m_imageHeight / tileHeight;

	if (count >= tileCountX * tileCountY)
	{
		count = 0;
	}

	uint32 tileX = count % tileCountX;
	uint32 tileY = count / tileCountX;

	uint32 startX = tileX * tileWidth;
	uint32 startY = tileY * tileHeight;

	uint32 r = tileColorR;
	uint32 g = tileColorG;
	uint32 b = tileColorB;

	uint32* dest = reinterpret_cast<uint32*>(m_image);
	for (uint32 y = 0; y < 16; y++)
	{
		for (uint32 x = 0; x < 16; x++)
		{
			if (startX + x >= m_imageWidth)
			{
				__debugbreak();
			}
			if (startY + y >= m_imageHeight)
			{
				__debugbreak();
			}

			dest[(startX + x) + m_imageWidth * (startY + y)] = 0xff000000 | (b << 16) | (g << 8) | r;
		}
	}

	count++;
	tileColorR += 8;
	if (tileColorR > 255)
	{
		tileColorR = 0;
		tileColorG += 8;
	}
	if (tileColorG > 255)
	{
		tileColorG = 0;
		tileColorB += 8;
	}
	if (tileColorB > 255)
	{
		tileColorB = 0;
	}

	if (m_dynamicTexture)
	{
		m_renderer->UpdateTextureWidthImage(m_dynamicTexture, m_image, m_imageWidth, m_imageHeight);
	}
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
	float hitDist = 0.0f;
	DL_LIST* cur = m_headActorListNode;
	while (cur != nullptr)
	{
		Actor* actor = reinterpret_cast<Actor*>(cur);
		DirectX::BoundingBox boundingBox = actor->GetBoundingBox();
		bool pick = m_renderer->MousePicking(boundingBox, ndcX, ndcY, prevPos, &hitDist, prevRatio);
		if (pick)
		{
			return actor;
		}
		cur = cur->next;
	}
	return nullptr;
}

void Game::Render()
{
	// Render the mesh object.
	// m_renderer->RenderMeshObject(m_meshObj, Matrix::Identity);

	// Render actors.
	DL_LIST* cur = m_headActorListNode;
	while (cur != nullptr)
	{
		Actor* actor = reinterpret_cast<Actor*>(cur);
		actor->Render();
		cur = cur->next;
	}

	// Render text.
	// ====================
	// WWARNING!!!
	// ====================
	// 같은 sprite obj 에 대해서 멀티쓰레드 렌더링을 시도할 경우 플리커링 현상이 발생한다.
	uint32 offset = 10;
	uint32 posX = m_screenWidth - m_fontTexWidth - offset;
	uint32 posY = offset;
	m_renderer->RenderSpriteObjectWithTexture(m_spriteObj0, posX, posY, 1.0f, 1.0f, 0.0f, nullptr, m_fontTexture, "text");
	// Render dynamic gradation texture.
	m_renderer->RenderSpriteObjectWithTexture(m_spriteObj1, 100, 100, 0.5f, 0.5f, 0.0f, nullptr, m_dynamicTexture, "gradation");
	// Render line object.
	m_renderer->RenderLineObject(m_lineObj, Matrix());
}
