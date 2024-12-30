#include "pch.h"
#include "SceneHome.h"
#include "Game.h"
#include "Player.h"
#include "Monster.h"
#include "Wall.h"

/*
==============
SceneHome
==============
*/

SceneHome::SceneHome()
{
}

SceneHome::~SceneHome()
{
	CleanUp();
}

bool SceneHome::Initialize(Game* game)
{
	m_game = game;
	m_engineCore = game->GetEngineCore();

	return true;
}

void SceneHome::BeginScene()
{
	// System info.
	m_sysInfoUI = m_engineCore->CreateTextUI(m_game->GetScreenWidth(), m_game->GetScreenHeight() / 16, 10, 10, 1.0f, 1.0f, 0.0f, L"Consolas", 14);

	// Terrain.
	m_terrain = m_engineCore->CreateTerrain(100.0f, nullptr);

	Vector3 playerPos = Vector3(0.0f, 0.0f, -1.0f);
	Vector3 camPos = playerPos - Vector3(0.0f, 0.0f, 5.0f);
	Vector3 camDir = Vector3(0.0f, 0.0f, 1.0f);
	SetCameraPos(camPos);
	SetCameraDir(camDir);

	m_engineCore->SetCameraPosition(camPos);
	m_engineCore->SetCameraDirection(camDir);

	// Game object.
	Player* player = new Player;
	player->Initialize(m_engineCore);
	player->SetPosition(playerPos);
	AddGameObject(OBJ_TYPE_PLAYER, player);

	//Wall* wall = new Wall;
	//wall->Initialize(m_engineCore, GetNumGameObject(OBJ_TYPE_WALL));
	//wall->SetScale(Vector3(1.0f, 1.0f, 0.5f));
	//wall->SetPosition(Vector3(0.0f, 0.0f, 2.0f));
	//AddGameObject(OBJ_TYPE_WALL, wall);
}

void SceneHome::EndScene()
{
}

void SceneHome::Update(const float dt)
{
	Vector3 camPos = m_engineCore->GetCameraPosition();
	Vector3 camDir = m_engineCore->GetCameraDirection();
	wchar_t buf[256] = {};
	swprintf_s(buf, L"fps:%d dt:%lf cam pos:[%lf %lf %lf] cam dir:[%lf %lf %lf]", m_engineCore->GetFps(), m_engineCore->GetDeltaTime(), camPos.x, camPos.y, camPos.z, camDir.x, camDir.y, camDir.z);
	m_engineCore->WriteTextToUI(m_sysInfoUI, buf, FONT_COLOR_TYPE::SPRING_GREEN);

	float height = 0.0f;
	float collisionRadius = 1.0f;
	for (uint32 i = 0; i < OBJ_TYPE_NUM; i++)
	{
		uint32 numGameObj = GetNumGameObject(GAME_OBJ_TYPE(i));
		for (uint32 j = 0; j < numGameObj; j++)
		{
			GameObject* (*gameObj)[Scene::MAX_NUM_GAME_OBJ] = GetGameObject();
			if (gameObj[i][j])
			{
				Vector3 curPos = gameObj[i][j]->GetPosition();

				m_terrain->IntersectObject(gameObj[i][j]->GetMyObject(), &height);

				printf("%lf\n", height);

				gameObj[i][j]->SetPosition(Vector3(curPos.x, height + 1.0f, curPos.z));
				gameObj[i][j]->Update(dt);
			}
		}
	}

	GameObject* (*gameObj)[Scene::MAX_NUM_GAME_OBJ] = GetGameObject();
	const float yaw = m_engineCore->GetNdcX() * DirectX::XM_PI;
	const float pitch = m_engineCore->GetNdcY() * DirectX::XM_PI;
	const Vector3 playerPos = gameObj[OBJ_TYPE_PLAYER][0]->GetPosition();
	
	Vector3 newCamPos = Vector3(0.0f, 0.0f, -5.0f);
	Vector3 newCamDir = Vector3(0.0f, 0.0f, 1.0f);
	newCamPos = Vector3::Transform(newCamPos, Matrix::CreateRotationY(yaw));
	newCamDir = Vector3::Transform(newCamDir, Matrix::CreateRotationY(yaw));
	newCamPos = newCamPos + playerPos;

	m_engineCore->SetCameraPosition(newCamPos);
	m_engineCore->SetCameraDirection(newCamDir);

	camPos = m_engineCore->GetCameraPosition();
	camDir = m_engineCore->GetCameraDirection();

	Vector3 curPos = gameObj[OBJ_TYPE_PLAYER][0]->GetPosition();

	if (m_engineCore->KeyboardHold(KEY_INPUT_W))
	{
		camPos += camDir * 1.0f * dt;
		curPos += camDir * 1.0f * dt;
	}
	
	m_engineCore->SetCameraPosition(camPos);
	gameObj[OBJ_TYPE_PLAYER][0]->SetPosition(curPos);
}

void SceneHome::Render()
{
	m_engineCore->RenderTextUI(m_sysInfoUI);

	m_engineCore->RenderTerrain(m_terrain);

	for (uint32 i = 0; i < OBJ_TYPE_NUM; i++)
	{
		uint32 numGameObj = GetNumGameObject(GAME_OBJ_TYPE(i));
		for (uint32 j = 0; j < numGameObj; j++)
		{
			GameObject* (*gameObj)[Scene::MAX_NUM_GAME_OBJ] = GetGameObject();
			if (gameObj[i][j])
			{
				gameObj[i][j]->SetWire(true);
				gameObj[i][j]->Render();
			}
		}
	}
}

void SceneHome::CleanUp()
{
	for (uint32 i = 0; i < OBJ_TYPE_NUM; i++)
	{
		uint32 numGameObj = GetNumGameObject(GAME_OBJ_TYPE(i));
		for (uint32 j = 0; j < numGameObj; j++)
		{
			GameObject* (*gameObj)[Scene::MAX_NUM_GAME_OBJ] = GetGameObject();
			if (gameObj[i][j])
			{
				delete gameObj[i][j];
				gameObj[i][j] = nullptr;
			}
		}
	}
	if (m_terrain)
	{
		m_terrain->Release();
		m_terrain = nullptr;
	}
	if (m_sysInfoUI)
	{
		m_sysInfoUI->Release();
		m_sysInfoUI = nullptr;
	}
}
