#include "pch.h"
#include "Game.h"
#include "Application.h"
#include "Player.h"
#include "SceneManager.h"
#include "EditorManager.h"
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
	m_editorManager = new EditorManager;
	m_editorManager->Initialize(this, 2);
	memset(m_isEidtorModeFirst, true, EDITOR_TYPE_NUM);
	m_prevEditorMode = EDITOR_TYPE_NUM;
#endif

	// Initialize scene.
	m_sceneManager = new SceneManager;
	m_sceneManager->Initialize(this, 8);

	// System info.
	m_sysInfoUI = m_engineCore->CreateTextUI(m_screenWidth, m_screenWidth / 16, 10, 10, 1.0f, 1.0f, 0.0f, L"Consolas", 14);

	return true;
}

void Game::CleanUpGame()
{
	if (m_sysInfoUI)
	{
		m_sysInfoUI->Release();
		m_sysInfoUI = nullptr;
	}
	if (m_sceneManager)
	{
		delete m_sceneManager;
		m_sceneManager = nullptr;
	}
#if defined(EDITOR_MODE)
	if (m_editorManager)
	{
		delete m_editorManager;
		m_editorManager = nullptr;
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
	Vector3 camPos = m_engineCore->GetCameraPosition();
	Vector3 camDir = m_engineCore->GetCameraDirection();
	wchar_t buf[256] = {};
	swprintf_s(buf, L"fps:%d dt:%lf cam pos:[%lf %lf %lf] cam dir:[%lf %lf %lf]", m_engineCore->GetFps(), m_engineCore->GetDeltaTime(), camPos.x, camPos.y, camPos.z, camDir.x, camDir.y, camDir.z);
	m_engineCore->WriteTextToUI(m_sysInfoUI, buf, FONT_COLOR_TYPE::SPRING_GREEN);

	// F12 Button => Editor On/Off
	if (m_engineCore->KeyboardDown(KEY_INPUT_F12))
	{
		m_curEidtorMode = static_cast<EDITOR_TYPE>((m_curEidtorMode + 1) % EDITOR_TYPE_NUM);
	}

	// Editor mode On
	static Editor* editor = nullptr;
	if (EDITOR_TYPE_NONE != m_curEidtorMode && m_prevEditorMode == m_curEidtorMode)
	{
		if (m_isEidtorModeFirst[m_curEidtorMode])
		{
			m_editorManager->SetCurrentEditor(m_curEidtorMode);
			editor = m_editorManager->GetCurrentEditor();
			m_isEidtorModeFirst[m_curEidtorMode] = false;
		}
		m_editorManager->Update(dt);
	}
	else
	{
		if (!m_isEidtorModeFirst[m_curEidtorMode])
		{
			editor->EndEditor();
			m_isEidtorModeFirst[m_curEidtorMode] = true;
		}
		m_prevEditorMode = m_curEidtorMode;
	}

	// Update scene.
	if (EDITOR_TYPE_NONE == m_curEidtorMode)
	{
		m_sceneManager->Update(dt);
	}

}

void Game::Render()
{
	m_engineCore->RenderTextUI(m_sysInfoUI);

	if (EDITOR_TYPE_NONE != m_curEidtorMode)
	{
		m_editorManager->Render();
	}

	m_sceneManager->Render();
}



