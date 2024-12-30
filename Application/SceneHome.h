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
	SceneHome();
	virtual ~SceneHome();

	bool Initialize(Game* gmae);
	void BeginScene();
	void EndScene();
	virtual void Update(const float dt) override;
	virtual void Render() override;

private:
	void CleanUp();
	void UpdateCameraRotation();
	void UpdateInput(const float dt);

private:
	Game* m_game = nullptr;
	IT_EngineCore* m_engineCore = nullptr;
	IT_Terrain* m_terrain = nullptr;
};

