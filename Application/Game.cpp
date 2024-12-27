#include "pch.h"
#include "Game.h"
#include "Application.h"
#include "Player.h"
#include "SceneManager.h"

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
	CleanUpGame();
}

bool Game::InitGame(Application* app)
{
	m_app = app;
	m_engineCore = app->GetEngineCore();
	m_renderer = m_engineCore->GetRenderer();

	RECT rect = {};
	GetClientRect(m_app->GetHwnd(), &rect);
	m_screenWidth = rect.right - rect.left;
	m_screenHeight = rect.bottom - rect.top;

	// Initialize scene.
	m_sceneManager = new SceneManager;
	m_sceneManager->Initialize(this, 8);

	return true;
}

void Game::CleanUpGame()
{
	if (m_sceneManager)
	{
		delete m_sceneManager;
		m_sceneManager = nullptr;
	}
}

void Game::RunGame()
{
	m_engineCore->BeginGameLogic();
	Update(m_engineCore->GetDeltaTime());
	m_engineCore->EndGameLogic();

	m_renderer->BeginRender();
	Render();
	m_renderer->EndRender();
	m_renderer->Present();
}

void Game::Update(const float dt)
{
	m_sceneManager->Update(dt);
}

void Game::Render()
{
	m_sceneManager->Render();
}



