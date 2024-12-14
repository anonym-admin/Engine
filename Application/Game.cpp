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
	const uint32 NUM_ACTORS = 200;
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
	m_fontTexHeight = 256;
	m_fontObj = m_renderer->CreateFontObject(L"Consolas", 18);
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

	return true;
}

void Game::CleanUpGame()
{
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

	// Update actors.
	DL_LIST* cur = m_headActorListNode;
	while (cur != nullptr)
	{
		Actor* actor = reinterpret_cast<Actor*>(cur);
		actor->Update();
		cur = cur->next;
	}

	// Update text.
	wchar_t buf[36] = {};
	swprintf_s(buf, L"fps: %d", m_fps);
	uint32 strLen = static_cast<uint32>(wcslen(buf));
	int32 texWidth = 0;
	int32 texHeight = 0;

	if (wcscmp(m_gameText, buf))
	{
		memset(m_fontImage, 0, m_fontTexWidth * m_fontTexHeight * 4);
		m_renderer->WriteTextToBitmap(m_fontImage, m_fontTexWidth, m_fontTexHeight, m_fontTexWidth * 4, &texWidth, &texHeight, m_fontObj, buf, strLen);
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
	m_renderer->RenderSpriteObjectWithTexture(m_spriteObj0, 300, 300, 1.0f, 1.0f, 0.0f, nullptr, m_fontTexture, "text");
	// Render dynamic gradation texture.
	m_renderer->RenderSpriteObjectWithTexture(m_spriteObj1, 100, 100, 0.5f, 0.5f, 0.0f, nullptr, m_dynamicTexture, "gradation");
}
