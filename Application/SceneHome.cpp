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
				//gameObj[i][j]->SetPosition(Vector3(curPos.x, height + 1.0f, curPos.z));
				gameObj[i][j]->Update(dt);
			}
		}
	}

	UpdateCameraRotation();
	UpdateInput(dt);
}

void SceneHome::Render()
{
	// m_engineCore->RenderTerrain(m_terrain);

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
}

void SceneHome::UpdateCameraRotation()
{
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

	SetCameraPos(newCamPos);
	SetCameraDir(newCamDir);
}

void SceneHome::UpdateInput(const float dt)
{
	const float moveSpeed = 1.5f;

	GameObject* (*gameObj)[Scene::MAX_NUM_GAME_OBJ] = GetGameObject();

	Vector3 camPos = m_engineCore->GetCameraPosition();
	Vector3 camDir = m_engineCore->GetCameraDirection();
	Vector3 camUp = Vector3(0.0f, 1.0f, 0.0f);
	Vector3 camRight = camUp.Cross(camDir);
	Vector3 curPos = gameObj[OBJ_TYPE_PLAYER][0]->GetPosition();

	if (m_engineCore->KeyboardHold(KEY_INPUT_W))
	{
		camPos += camDir * moveSpeed * dt;
		curPos += camDir * moveSpeed * dt;
	}
	if (m_engineCore->KeyboardHold(KEY_INPUT_S))
	{
		camPos -= camDir * moveSpeed * dt;
		curPos -= camDir * moveSpeed * dt;
	}
	if (m_engineCore->KeyboardHold(KEY_INPUT_D))
	{
		camPos += camRight * moveSpeed * dt;
		curPos += camRight * moveSpeed * dt;
	}
	if (m_engineCore->KeyboardHold(KEY_INPUT_A))
	{
		camPos -= camRight * moveSpeed * dt;
		curPos -= camRight * moveSpeed * dt;
	}

	SetCameraPos(camPos);
	m_engineCore->SetCameraPosition(camPos);
	gameObj[OBJ_TYPE_PLAYER][0]->SetPosition(curPos);
}
