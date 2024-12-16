#pragma once

/*
=======
Game
=======
*/

class Application;
class Actor;
interface IT_Renderer;
interface IT_MeshObject;
interface IT_SpriteObject;
interface IT_LineObject;

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
	void UpdateMousePicking();
	Actor* IntersectActor(float ndcX, float ndcY, Vector3* prevPos, float* prevRatio);
	void Render();

private:
	Application* m_app = nullptr;
	IT_Renderer* m_renderer = nullptr;
	uint32 m_screenWidth = 0;
	uint32 m_screenHeight = 0;
	uint32 m_fps = 0;
	// Mesh object.
	IT_MeshObject* m_meshObj = nullptr;
	void* m_tiledTexture = nullptr;
	MESH_GROUP_HANDLE* m_square = nullptr;

	// Actor
	DL_LIST* m_headActorListNode = nullptr;
	DL_LIST* m_tailActorListNode = nullptr;
	
	// Sprite
	IT_SpriteObject* m_spriteObj0 = nullptr;
	IT_SpriteObject* m_spriteObj1 = nullptr;
	uint32 m_imageWidth = 0;
	uint32 m_imageHeight = 0;
	uint8* m_image = nullptr;
	void* m_dynamicTexture = nullptr;
	// Font
	uint32 m_fontTexWidth = 256;
	uint32 m_fontTexHeight = 256;
	void* m_fontObj = nullptr;
	void* m_fontTexture = nullptr;
	uint8* m_fontImage = nullptr;

	wchar_t m_gameText[256] = {};
	// Line
	IT_LineObject* m_lineObj = nullptr;
	LineData* m_lineData = nullptr;
};

