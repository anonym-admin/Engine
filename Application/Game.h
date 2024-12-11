#pragma once

/*
=======
Game
=======
*/

class Application;
class Actor;
struct DL_LIST;

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
	DL_LIST* m_headActorListNode = nullptr;
	DL_LIST* m_tailActorListNode = nullptr;
	uint32 m_fps = 0;
};

