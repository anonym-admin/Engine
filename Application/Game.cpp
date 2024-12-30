#include "pch.h"
#include "Game.h"
#include "Application.h"
#include "Player.h"
#include "SceneManager.h"
#include "Editor.h"

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

#if defined(EDITOR_MODE)
	m_editor = new Editor;
	m_editor->Initialize(this);
#endif

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
#if defined(EDITOR_MODE)
	if (m_editor)
	{
		delete m_editor;
		m_editor = nullptr;
	}
#endif
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
	// F12 Button => Editor On/Off
	if (m_engineCore->KeyboardDown(KEY_INPUT_F12))
	{
		m_isEditorMode = !m_isEditorMode;
	}
	// Editor mode On
	if (m_isEditorMode)
	{
		if (m_isEidtorModeFirst)
		{
			m_editor->BeginEditor();
			m_isEidtorModeFirst = false;
		}
		m_editor->Update(dt);
	}
	else
	{
		if (!m_isEidtorModeFirst)
		{
			m_editor->EndEditor();
			m_isEidtorModeFirst = true;
		}
	}

	// Update scene.
	if (!m_isEditorMode)
	{
		m_sceneManager->Update(dt);
	}

}

void Game::Render()
{
	if (m_isEditorMode)
	{
		m_editor->Render();
	}

	m_sceneManager->Render();
}



