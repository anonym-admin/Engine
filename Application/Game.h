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
	void Update();
	void Render();

private:
	Application* m_app = nullptr;
	Actor* m_actor = nullptr;
};

