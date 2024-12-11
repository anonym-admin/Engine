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
    IT_Renderer* renderer = app->GetRenderer();

    m_app = app;

    // Set camera position.
    renderer->SetCameraPos(0.0f, 0.0f, -5.0f);

    // Set actors.
    for (uint32 i = 0; i < 20; i++)
    {
        Actor* actor = new Actor;
        actor->Initialize(renderer);
        actor->SetPosition(Vector3(-10.0f + i * 5.0f, 0.0f, 0.0f));

        DL_InsertBack(&m_headActorListNode, &m_tailActorListNode, &actor->actorLink);
    }

    return true;
}

void Game::CleanUpGame()
{
    DL_LIST* curActorListNode = m_headActorListNode;
    while (curActorListNode != nullptr)
    {
        DL_LIST* delNextNode = curActorListNode->next;
        DL_Delete(&m_headActorListNode, &m_tailActorListNode, curActorListNode);
        Actor* actor = reinterpret_cast<Actor*>(curActorListNode);
        delete actor;
        curActorListNode = delNextNode;
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
    DL_LIST* curActorListNode = m_headActorListNode;
    while (curActorListNode != nullptr)
    {
        Actor* actor = reinterpret_cast<Actor*>(curActorListNode);
        actor->Update();
        curActorListNode = curActorListNode->next;
    }
}

void Game::Render()
{
    DL_LIST* curActorListNode = m_headActorListNode;
    while (curActorListNode != nullptr)
    {
        Actor* actor = reinterpret_cast<Actor*>(curActorListNode);
        actor->Render();
        curActorListNode = curActorListNode->next;
    }
}
