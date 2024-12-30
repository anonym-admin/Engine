#pragma once

#include "Editor.h"

/*
===============
EditorArrange
===============
*/

class Game;
class Scene;

class EditorArrange : public Editor
{
public:
	EditorArrange();
	virtual ~EditorArrange();

	bool Initialize(Game* game);
	virtual void BeginEditor();
	virtual void EndEditor();
	virtual void Update(const float dt);
	virtual void Render();

private:
	void CleanUp();
	GameObject* IsSelectedObject();
	bool UpdateMousePicking();

private:
	Game* m_game = nullptr;
	Scene* m_curScene = nullptr;
	IT_EngineCore* m_engineCore = nullptr;
	IT_TextUI* m_textUI = nullptr;
	Vector3 m_sceneCamPos = Vector3(0.0f);
	Vector3 m_sceneCamDir = Vector3(0.0f, 0.0f, 1.0f);
};

