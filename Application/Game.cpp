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
    m_app = app;

    IT_Renderer* renderer = m_app->GetRenderer();

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

    Update();

    renderer->BeginRender();
    Render();
    renderer->EndRender();

    renderer->Present();
}

void Game::Update()
{
    m_actor->Update();
}

void Game::Render()
{
    m_actor->Render();
}
