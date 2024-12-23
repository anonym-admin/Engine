#include "pch.h"
#include "Game.h"
#include "Application.h"
#include "Player.h"

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
	{
		IT_World* world = m_engineCore->CreateWorld(L"WORLD_01");
		m_engineCore->AddWorld(world);

		// Create Level.
		{
			IT_Level* levelInGame = m_engineCore->CreateLevelInGame(L"LEVEL_INGAME");
			world->AddLevel(levelInGame);

			// Create Game Object.
			{
				IT_TextUI* textUI = m_engineCore->CreateTextUI(256, 64, 100, 100, 1.0f, 1.0f, 0.0f, L"Consolas", 14, nullptr);
				levelInGame->AddUI(textUI);
				m_textUI = textUI;
			}

			{
				Player* player = new Player;
				player->Initialize(m_engineCore, levelInGame, this);
				m_player = player;
			}
		}

		{
			IT_Level* levelLoading = m_engineCore->CreateLevelLoading(L"LEVEL_LOADING");
			world->AddLevel(levelLoading);
		}

		world->SetCurrentLevel(1);
		world->BeginWorld();

		m_world = world;
	}
	
	return true;
}

void Game::CleanUpGame()
{
	if (m_player)
	{
		delete m_player;
		m_player = nullptr;
	}
}

void Game::RunGame()
{
	static float accTime = 0.0f;

	if (accTime >= 0.016f)
	{
		if (m_engineCore->KeyDown(KEY_INPUT_M))
		{
			m_world->SetCurrentLevel(0);
			m_world->BeginWorld();
		}
	}

	m_engineCore->Tick(accTime);

	if (accTime >= 0.016f)
	{
		accTime = 0.0f;
	}

	accTime += m_engineCore->GetDeltaTime();
}



