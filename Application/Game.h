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
	Game();
	~Game();

	bool InitGame(Application* app);
	void RunGame();

private:
	void Update();
	void Render();

private:
	Application* m_app = nullptr;
};

