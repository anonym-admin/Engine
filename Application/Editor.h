#pragma once

/*
========
Editor
========
*/

class Game;
class Scene;
class SceneManger;
class GameObject;

class Editor
{
public:
	Editor();
	~Editor();

	bool Initialize(Game* game);
	void BeginEditor();
	void EndEditor();
	void Update(const float dt);
	void Render();

private:
	void CleanUp();
	void CreateBuilding();
	GameObject* IsSelectedObject();
	bool UpdateMousePicking();

private:
	Game* m_game = nullptr;
	IT_EngineCore* m_engineCore = nullptr;
	IT_TextUI* m_textUI = nullptr;
	Scene* m_curScene = nullptr;
	Vector3 m_sceneCamPos = Vector3(0.0f);
	Vector3 m_sceneCamDir = Vector3(0.0f, 0.0f, 1.0f);



	float m_ltPosX = 0.0f;
	float m_ltPosY = 0.0f;
	float m_rbPosX = 0.0f;
	float m_rbPosY = 0.0f;


	Vector3 m_wltPos = Vector3(0.0f);
	Vector3 m_wrbPos = Vector3(0.0f);


	bool m_isPicking = false;
};

