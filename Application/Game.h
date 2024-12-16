#pragma once

/*
=======
Game
=======
*/

class Application;
class Camera;
class TextUI;
class CharacterObject_01;
class CoordinateObject;
class Actor;

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
	bool InitCamera();
	bool InitActorLists();
	bool InitCharacters();
	void Update(uint64 curTick);
	void UpdateMousePicking();
	void Render();
	void CleanCamera();
	void CleanActorLists();
	void CleanCharacters();
	Actor* IntersectActor(float ndcX, float ndcY, Vector3* prevPos, float* prevRatio);

private:
	Application* m_app = nullptr;
	IT_Renderer* m_renderer = nullptr;
	uint32 m_screenWidth = 0;
	uint32 m_screenHeight = 0;
	uint32 m_fps = 0;
	// Text UI
	TextUI* m_textUI = nullptr;
	// Camera
	Camera* m_camera = nullptr;
	// Actor Container.
	HashTable* m_htActors = nullptr;
	MESH_GROUP_HANDLE* m_cube = nullptr;
	// Character.
	CharacterObject_01* m_character_01 = nullptr;
	// CoordinateObject
	CoordinateObject* m_coordObj = nullptr;

};

