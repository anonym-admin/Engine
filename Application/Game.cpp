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
    IT_Renderer* renderer = app->GetRenderer();

    m_app = app;

    // Set camera position.
    renderer->SetCameraPos(0.0f, 0.0f, -5.0f);

    // Set actors.
    m_actor = new Actor;
    m_actor->Initialize(renderer);

    return true;
}

void Game::CleanUpGame()
{
    if (m_actor)
    {
        delete m_actor;
        m_actor = nullptr;
    }
}

void Game::RunGame()
{
    IT_Renderer* renderer = m_app->GetRenderer();

    static uint32 fps = 0;
    static uint64 prevTickCount = 0;
    fps++;

    uint64 curTickCount = ::GetTickCount64();
    Update(curTickCount);

    renderer->BeginRender();
    Render();
    renderer->EndRender();

    renderer->Present();

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
    m_actor->Update();
}

void Game::Render()
{
    m_actor->Render();
}
