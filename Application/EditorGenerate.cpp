#include "pch.h"
#include "EditorGenerate.h"
#include "Game.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Wall.h"

/*
===============
EditorGenerate
===============
*/

EditorGenerate::EditorGenerate()
{
}

EditorGenerate::~EditorGenerate()
{
    CleanUp();
}

bool EditorGenerate::Initialize(Game* game)
{
	m_game = game;
	m_engineCore = game->GetEngineCore();

	const uint32 screenWidth = m_game->GetScreenWidth();
	const uint32 screenHeight = m_game->GetScreenHeight();
	const uint32 offset = 10;

	m_textUI = m_engineCore->CreateTextUI(256, 32, screenWidth - 128, offset, 1.0f, 1.0f, 0.0f, L"Consolas", 14);

	return true;
}

void EditorGenerate::BeginEditor()
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

void EditorGenerate::EndEditor()
{
	m_engineCore->SetCameraPosition(m_sceneCamPos);
	m_engineCore->SetCameraDirection(m_sceneCamDir);
}

void EditorGenerate::Update(const float dt)
{
	IT_Renderer* renderer = m_engineCore->GetRenderer();

	wchar_t buf[256] = {};
	swprintf_s(buf, L"Edit Mode Generate");
	m_engineCore->WriteTextToUI(m_textUI, buf, FONT_COLOR_TYPE::WHITE);

	DirectX::SimpleMath::Plane xzPlane = DirectX::SimpleMath::Plane(Vector3(0.0f, 1.0f, 0.0f), 0); // This plane is (y = 0) xz plane.
	
	// Create building object.
	if (m_engineCore->LButtonDown())
	{
		m_wltPos = renderer->GetWorldPos(xzPlane, m_engineCore->GetNdcX(), m_engineCore->GetNdcY());
	}
	if (m_engineCore->LButtonUp())
	{
		m_wrbPos = renderer->GetWorldPos(xzPlane, m_engineCore->GetNdcX(), m_engineCore->GetNdcY());
		if (abs(m_wltPos.x - m_wrbPos.x) <= 1e-5f)
		{
			return;
		}

		CreateBuilding();

		m_wltPos = m_wrbPos;
	}
}

void EditorGenerate::Render()
{
	m_engineCore->RenderTextUI(m_textUI);
}

void EditorGenerate::CleanUp()
{
	if (m_textUI)
	{
		m_textUI->Release();
		m_textUI = nullptr;
	}
}

void EditorGenerate::CreateBuilding()
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
