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
	m_terrain = m_engineCore->CreateTerrain(50.0f, nullptr);

	// Game object.
	Player* player = new Player;
	player->Initialize(m_engineCore);
	player->SetPosition(Vector3(-2.0f, 0.0f, 0.0f));
	m_gameObjList[OBJ_TYPE_PLAYER][m_numGameObjList[OBJ_TYPE_PLAYER]++] = player;

	Monster* monster = new Monster;
	monster->Initialize(m_engineCore);
	monster->SetPosition(Vector3(2.0f, 0.0f, 0.0f));
	m_gameObjList[OBJ_TYPE_MONSTER][m_numGameObjList[OBJ_TYPE_MONSTER]++] = monster;

	Wall* wall = new Wall;
	wall->Initialize(m_engineCore);
	wall->SetScale(Vector3(1.0f, 1.0f, 0.5f));
	wall->SetPosition(Vector3(0.0f, 0.0f, 2.0f));
	m_gameObjList[OBJ_TYPE_WALL][m_numGameObjList[OBJ_TYPE_WALL]++] = wall;
}

void SceneHome::EndScene()
{
}

void SceneHome::Update(const float dt)
{
	Vector3 camPos = m_engineCore->GetCameraPos();
	wchar_t buf[256] = {};
	swprintf_s(buf, L"fps:%d dt:%lf cam:[%.2lf,%.2lf,%.2lf]", m_engineCore->GetFps(), m_engineCore->GetDeltaTime(), camPos.x, camPos.y, camPos.z);

	m_engineCore->WriteTextToUI(m_sysInfoUI, buf, FONT_COLOR_TYPE::SPRING_GREEN);

	float height = 0.0f;
	float collisionRadius = 1.0f;
	for (uint32 i = 0; i < OBJ_TYPE_NUM; i++)
	{
		for (uint32 j = 0; j < m_numGameObjList[i]; j++)
		{
			if (m_gameObjList[i][j])
			{
				m_gameObjList[i][j]->Update(dt);
			}
		}
	}
}

void SceneHome::Render()
{
	m_engineCore->RenderTextUI(m_sysInfoUI);

	m_engineCore->RenderTerrain(m_terrain);

	for (uint32 i = 0; i < OBJ_TYPE_NUM; i++)
	{
		for (uint32 j = 0; j < m_numGameObjList[i]; j++)
		{
			if (m_gameObjList[i][j])
			{
				m_gameObjList[i][j]->Render();
			}
		}
	}
}

void SceneHome::CleanUp()
{
	for (uint32 i = 0; i < OBJ_TYPE_NUM; i++)
	{
		for (uint32 j = 0; j < m_numGameObjList[i]; j++)
		{
			if (m_gameObjList[i][j])
			{
				delete m_gameObjList[i][j];
				m_gameObjList[i][j] = nullptr;
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
