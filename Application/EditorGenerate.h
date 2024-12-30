#pragma once

#include "Editor.h"

/*
===============
EditorGenerate
===============
*/

class EditorGenerate : public Editor
{
public:
	EditorGenerate();
	virtual ~EditorGenerate();

	bool Initialize(Game* game);
	virtual void BeginEditor();
	virtual void EndEditor();
	virtual void Update(const float dt);
	virtual void Render();

private:
	void CleanUp();
	void CreateBuilding();

private:
	Game* m_game = nullptr;
	Scene* m_curScene = nullptr;
	IT_EngineCore* m_engineCore = nullptr;
	IT_TextUI* m_textUI = nullptr;
	Vector3 m_sceneCamPos = Vector3(0.0f);
	Vector3 m_sceneCamDir = Vector3(0.0f, 0.0f, 1.0f);
	Vector3 m_wltPos = Vector3(0.0f);
	Vector3 m_wrbPos = Vector3(0.0f);
};

