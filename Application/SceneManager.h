#pragma once

enum SCENE_TYPE
{
	SCENE_TYPE_HOME,
	SCENE_TYPE_NUM,
};

/*
==============
SceneManager
==============
*/

class Game;
class Scene;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	bool Initialize(Game* gmae, uint32 maxNumScene);
	void Update(const float dt);
	void Render();

	void SetCurrentScene(SCENE_TYPE type) { m_curScene = m_sceneGraph[type]; }
	Scene* GetCurrentScene() { return m_curScene; }

private:
	void CleanUp();

private:
	Scene** m_sceneGraph = nullptr;
	Scene* m_curScene = nullptr;
	uint32 m_numScene = 0;
	uint32 m_maxNumScene = 0;
};

