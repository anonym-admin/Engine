#pragma once

/*
==========
Scene
==========
*/

class GameObject;

class Scene
{
public:
	static const uint32 MAX_NUM_GAME_OBJ = 2048;

	Scene();
	virtual ~Scene() = 0;

	bool Initialize();
	virtual void BeginScene() = 0;
	virtual void EndScene() = 0;
	virtual void Update(const float dt) = 0;
	virtual void Render() = 0;
	void AddGameObject(GAME_OBJ_TYPE type, GameObject* gameObj) { m_gameObjList[type][m_numGameObjList[type]++] = gameObj; }
	void SetName(const wchar_t* name);
	void SetCameraPos(Vector3 camPos);
	void SetCameraDir(Vector3 camDir);
	GameObject* (*GetGameObject())[MAX_NUM_GAME_OBJ] { return m_gameObjList; }
	uint32 GetNumGameObject(GAME_OBJ_TYPE type) { return m_numGameObjList[type]; }
	const wchar_t* GetName();
	Vector3 GetCameraPos() { return m_camPos; }
	Vector3 GetCameraDir() { return m_camDir; }

private:
	void CleanUp();

private:
	GameObject* m_gameObjList[OBJ_TYPE_NUM][MAX_NUM_GAME_OBJ] = {};
	uint32 m_numGameObjList[OBJ_TYPE_NUM] = {};
	wchar_t m_sceneName[32] = {};
	Vector3 m_camPos = Vector3(0.0f);
	Vector3 m_camDir = Vector3(0.0f, 0.0f, 1.0f);
};

