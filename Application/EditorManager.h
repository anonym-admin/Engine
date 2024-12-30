#pragma once

/*
====================
EditorManager
====================
*/

class Game;
class Editor;

class EditorManager
{
public:
	EditorManager();
	~EditorManager();

	bool Initialize(Game* game, uint32 maxNumEditor);
	void Update(const float dt);
	void Render();

	void SetCurrentEditor(EDITOR_TYPE type);
	Editor* GetCurrentEditor() { return m_curEditor; }

private:
	void CleanUp();

private:
	Editor** m_editorList = nullptr;
	Editor* m_curEditor = nullptr;
	uint32 m_numEditor = 0;
	uint32 m_maxNumEditor = 0;
};

