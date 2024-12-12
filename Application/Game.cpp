#include "pch.h"
#include "Game.h"
#include "Application.h"
#include "GeometryGenerator.h"
#include "Actor.h"
#include "LinkedList.h"

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

    // Create the mesh object.
    m_cube = GeometryGenerator::MakeCube();
    const wchar_t* basePath = L"../../Assets/";
    const wchar_t* textureFilenames[] = {
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

    m_meshObj = m_renderer->CreateMeshObject();
    m_meshObj->CreateMeshBuffers(m_cube);
    m_transform0 = Matrix::CreateTranslation(Vector3(-2.0f, 0.0f, 0.0f));
    m_transform1 = Matrix::CreateTranslation(Vector3(2.0f, 0.0f, 0.0f));

    // Set the font object.
    m_fontTexWidth = 256;
    m_fontTexHeight = 256;
    m_fontObj = m_renderer->CreateFontObject(L"Consolas", 18);
    m_fontTexture = m_renderer->CreateDynamicTexture(m_fontTexWidth, m_fontTexHeight);
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
    m_dynamicTexture = m_renderer->CreateDynamicTexture(m_imageWidth, m_imageHeight);
    m_spriteObj = m_renderer->CreateSpriteObject();

    return true;
}

void Game::CleanUpGame()
{
    if (m_spriteObj)
    {
        m_spriteObj->Release();
        m_spriteObj = nullptr;
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
    }
    if (m_fontObj)
    {
        m_renderer->DestroyFontObject(m_fontObj);
    }
    if (m_meshObj)
    {
        m_meshObj->Release();
        m_meshObj = nullptr;
    }
    if (m_cube)
    {
        GeometryGenerator::DestroyGeometry(m_cube);
        m_cube = nullptr;
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
    m_renderer->RenderMeshObject(m_meshObj, m_transform1);
    m_renderer->RenderMeshObject(m_meshObj, m_transform0);

    m_renderer->RenderSpriteObjectWithTexture(m_spriteObj, 300, 300, 1.0f, 1.0f, 1.0f, nullptr, m_fontTexture);
    m_renderer->RenderSpriteObjectWithTexture(m_spriteObj, 100, 100, 0.5f, 0.5f, 1.0f, nullptr, m_dynamicTexture);
}
