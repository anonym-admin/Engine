#pragma once

/*
=======
Actor
=======
*/

class Game;
struct MESH_GROUP_HANDLE;
interface IT_Renderer;
interface IT_MeshObject;

class Actor
{
public:
	Actor();
	~Actor();

	bool Initialize(IT_Renderer* renderer);
	void CleanUp();
	void Update();
	void Render();

private:
	IT_Renderer* m_renderer = nullptr;	
	MESH_GROUP_HANDLE* m_triangle = nullptr;
	IT_MeshObject* m_meshObj = nullptr;
};

