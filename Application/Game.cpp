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
	level->AddUI(textUI);
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



