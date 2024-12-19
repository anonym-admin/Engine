#pragma once

/*
=======
Game
=======
*/

class Application;

class Game
{
public:
	static const uint32 MAX_ACTOR_NUM = 128;

	Game();
	~Game();

	bool InitGame(Application* app);
	void CleanUpGame();
	void RunGame();

private:
	void Update(uint64 curTick);
	void UpdateMousePicking();
	void Render();
	void* IntersectActor(float ndcX, float ndcY, Vector3* prevPos, float* prevRatio);

private:
	Application* m_app = nullptr;
	IT_EngineCore* m_engineCore = nullptr;
	uint32 m_screenWidth = 0;
	uint32 m_screenHeight = 0;
	uint32 m_fps = 0;
	IT_TextUI* m_textUI = nullptr;
	IT_GeometryObject* m_geometryObj = nullptr;
};

