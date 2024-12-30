#pragma once

/*
=======
Game
=======
*/

class Application;
class Player;
class SceneManager;
class Editor;

class Game
{
public:
	Game();
	~Game();

	bool InitGame(Application* app);
	void RunGame();

	IT_EngineCore* GetEngineCore() { return m_engineCore; }
	SceneManager* GetSceneManager() { return m_sceneManager; }
	uint32 GetScreenWidth() { return m_screenWidth; }
	uint32 GetScreenHeight() { return m_screenHeight; }

private:
	void CleanUpGame();
	void Update(const float dt);
	void Render();

private:
	Application* m_app = nullptr;
	IT_EngineCore* m_engineCore = nullptr;
	IT_Renderer* m_renderer = nullptr;
	uint32 m_screenWidth = 0;
	uint32 m_screenHeight = 0;
	uint32 m_fps = 0;

	SceneManager* m_sceneManager = nullptr;
	uint64 m_prevTickCount = 0;

	Editor* m_editor = nullptr;
	bool m_isEditorMode = false;
	bool m_isEidtorModeFirst = true;
};

