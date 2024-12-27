#pragma once

#include "Scene.h"

/*
==============
SceneHome
==============
*/

class Game;
class GameObject;

class SceneHome : public Scene
{
public:
	static const uint32 MAX_NUM_GAME_OBJ = 2048;

	SceneHome();
	virtual ~SceneHome();

	bool Initialize(Game* gmae);
	void BeginScene();
	void EndScene();
	virtual void Update(const float dt) override;
	virtual void Render() override;

private:
	void CleanUp();

private:
	Game* m_game = nullptr;
	IT_EngineCore* m_engineCore = nullptr;
	IT_TextUI* m_sysInfoUI = nullptr;
	IT_Terrain* m_terrain = nullptr;
	GameObject* m_gameObjList[OBJ_TYPE_NUM][MAX_NUM_GAME_OBJ] = {};
	uint32 m_numGameObjList[OBJ_TYPE_NUM] = {};
};

