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

    return true;
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
}

void Game::Render()
{
}
