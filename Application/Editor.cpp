#include "pch.h"
#include "Editor.h"
#include "Game.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Wall.h"

/*
========
Editor
========
*/

Editor::Editor()
{
}

Editor::~Editor()
{
	CleanUp();
}

bool Editor::Initialize(Game* game)
{
	m_game = game;
	m_engineCore = game->GetEngineCore();

	const uint32 screenWidth = m_game->GetScreenWidth();
	const uint32 screenHeight = m_game->GetScreenHeight();
	const uint32 offset = 10;
	m_textUI = m_engineCore->CreateTextUI(256, 32, screenWidth - 128, offset, 1.0f, 1.0f, 0.0f, L"Consolas", 14);

	return true;
}

void Editor::BeginEditor()
{
	m_engineCore = m_game->GetEngineCore();
	SceneManager* sceneManger = m_game->GetSceneManager();
	m_curScene = sceneManger->GetCurrentScene();

	m_sceneCamPos = m_curScene->GetCameraPos();
	m_sceneCamDir = m_curScene->GetCameraDir();

	// Set camera position.
	Vector3 camPos = Vector3(0.0f, 10.0f, 0.0f);
	Vector3 camDir = Vector3(0.0f, -1.0f, 0.0f);
	m_engineCore->SetCameraPosition(camPos);
	m_engineCore->SetCameraDirection(camDir);
	m_engineCore->DisalbeFPV();
}

void Editor::EndEditor()
{
	m_engineCore->SetCameraPosition(m_sceneCamPos);
	m_engineCore->SetCameraDirection(m_sceneCamDir);
}

void Editor::Update(const float dt)
{
	IT_Renderer* renderer = m_engineCore->GetRenderer();

	wchar_t buf[256] = {};
	swprintf_s(buf, L"Edit mode");
	m_engineCore->WriteTextToUI(m_textUI, buf, FONT_COLOR_TYPE::WHITE);

	if (m_engineCore->KeyboardDown(KEY_INPUT_B))
	{
		Wall* wall = new Wall;
		wall->Initialize(m_engineCore, m_curScene->GetNumGameObject(OBJ_TYPE_WALL));
		wall->SetPosition(Vector3(-2.0f, 2.0f, 1.0f));
		m_curScene->AddGameObject(OBJ_TYPE_WALL, wall);
	}

	DirectX::SimpleMath::Plane plane = DirectX::SimpleMath::Plane(Vector3(0.0f, 1.0f, 0.0f), 0);

	m_isPicking = UpdateMousePicking();

	if (m_isPicking)
	{
		return;
	}


}

void Editor::Render()
{
	m_engineCore->RenderTextUI(m_textUI);
}

void Editor::CleanUp()
{
	if (m_textUI)
	{
		m_textUI->Release();
		m_textUI = nullptr;
	}
}

void Editor::CreateBuilding()
{
	// World 좌표로의 변환이 필요하다.
	const float scaleX = abs(m_wltPos.x - m_wrbPos.x);
	const float scaleZ = abs(m_wltPos.z - m_wrbPos.z);

	const float centerX = (m_wltPos.x + m_wrbPos.x) * 0.5f;
	const float centerZ = (m_wltPos.z + m_wrbPos.z) * 0.5f;

	Vector3 scale = Vector3(scaleX, 3.0f, scaleZ);
	Vector3 position = Vector3(centerX, 0.0f, centerZ);

	Wall* wall = new Wall;
	wall->Initialize(m_engineCore, m_curScene->GetNumGameObject(OBJ_TYPE_WALL));
	wall->SetScale(scale);
	wall->SetPosition(position);
	m_curScene->AddGameObject(OBJ_TYPE_WALL, wall);
}

GameObject* Editor::IsSelectedObject()
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

bool Editor::UpdateMousePicking()
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
