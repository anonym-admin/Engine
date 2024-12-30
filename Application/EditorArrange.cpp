#include "pch.h"
#include "EditorArrange.h"
#include "Game.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Wall.h"

/*
===============
EditorArrange
===============
*/

EditorArrange::EditorArrange()
{
}

EditorArrange::~EditorArrange()
{
	CleanUp();
}

bool EditorArrange::Initialize(Game* game)
{
	m_game = game;
	m_engineCore = game->GetEngineCore();

	const uint32 screenWidth = m_game->GetScreenWidth();
	const uint32 screenHeight = m_game->GetScreenHeight();
	const uint32 offset = 10;

	m_textUI = m_engineCore->CreateTextUI(256, 32, screenWidth - 128, offset, 1.0f, 1.0f, 0.0f, L"Consolas", 14);

	return true;
}

void EditorArrange::BeginEditor()
{
	m_engineCore = m_game->GetEngineCore();
	SceneManager* sceneManger = m_game->GetSceneManager();
	m_curScene = sceneManger->GetCurrentScene();

	m_sceneCamPos = m_curScene->GetCameraPos();
	m_sceneCamDir = m_curScene->GetCameraDir();
}

void EditorArrange::EndEditor()
{
}

void EditorArrange::Update(const float dt)
{
	IT_Renderer* renderer = m_engineCore->GetRenderer();

	wchar_t buf[256] = {};
	swprintf_s(buf, L"Edit Mode Arrangement");
	m_engineCore->WriteTextToUI(m_textUI, buf, FONT_COLOR_TYPE::WHITE);

	UpdateMousePicking();
}

void EditorArrange::Render()
{
	m_engineCore->RenderTextUI(m_textUI);
}

void EditorArrange::CleanUp()
{
	if (m_textUI)
	{
		m_textUI->Release();
		m_textUI = nullptr;
	}
}

GameObject* EditorArrange::IsSelectedObject()
{
	GameObject* (*gameObj)[Scene::MAX_NUM_GAME_OBJ] = m_curScene->GetGameObject();
	uint32 numWall = m_curScene->GetNumGameObject(GAME_OBJ_TYPE::OBJ_TYPE_WALL);

	Wall* wall = nullptr;
	for (uint32 i = 0; i < numWall; i++)
	{
		if (gameObj[OBJ_TYPE_WALL][i])
		{
			Wall* wall = reinterpret_cast<Wall*>(gameObj[OBJ_TYPE_WALL][i]);
			if (m_engineCore->MousePicking(wall->GetMyObject()))
			{
				return wall;
			}
		}
	}
	return wall;
}

bool EditorArrange::UpdateMousePicking()
{
	static GameObject* selected = nullptr;

	if (m_engineCore->LButtonDown() || m_engineCore->RButtonDown())
	{
		if (!selected)
		{
			selected = IsSelectedObject();

			if (selected)
			{
				Wall* wall = reinterpret_cast<Wall*>(selected);
				wall->IsDrawMeshBoundingBox();
			}
		}
		else
		{

		}
	}
	else
	{
		selected = nullptr;
	}

	return selected ? true : false;
}
