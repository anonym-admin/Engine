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

	void SetPosition(Vector3 pos);
	void MovePosition(Vector3 deltaPos);
	inline DirectX::BoundingBox GetBoundingBox() { return m_boundingBox; }

	DL_LIST actorLink;

private:
	IT_Renderer* m_renderer = nullptr;	
	MESH_GROUP_HANDLE* m_cube = nullptr;
	IT_MeshObject* m_meshObj = nullptr;
	Matrix m_transform = Matrix();
	Vector3 m_pos = Vector3(0.0f);
	void* m_texture0 = nullptr;
	float m_dt = 0.0f;

	DirectX::BoundingBox m_boundingBox = {};
};

