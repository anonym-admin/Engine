#pragma once

/*
=======
Game
=======
*/

class Application;
class Actor;

class Game
{
public:
	Game();
	~Game();

	bool InitGame(Application* app);
	void CleanUpGame();
	void RunGame();

private:
	void Update(uint64 curTick);
	void Render();

private:
	Application* m_app = nullptr;
	Actor* m_actor = nullptr;

	uint32 m_fps = 0;
};

