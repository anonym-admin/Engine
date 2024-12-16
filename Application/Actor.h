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

	bool Initialize(IT_Renderer* renderer, ACTOR_HANDLE* actorHandle);
	void Update();
	void Render();

	void SetTexture(void* texHandle);
	void SetPosition(Vector3 pos);
	void MovePosition(Vector3 deltaPos);
	inline DirectX::BoundingBox GetBoundingBox() { return m_boundingBox; }
	inline Vector3 GetPosition() { return m_position; }

	DL_LIST actorLink = {};

private:
	void CleanUp();

protected:
	IT_Renderer* m_renderer = nullptr;
	void* m_renderObj = nullptr;
	ACTOR_HANDLE m_actorHandle = {};
	// Mesh
	MESH_GROUP_HANDLE* m_geometry = nullptr;
	Matrix m_transform = Matrix();
	Vector3 m_position = Vector3(0.0f);
	DirectX::BoundingBox m_boundingBox = {};
	DirectX::BoundingSphere m_boundingSphere = {};
	// Sprite
	void* m_texture = nullptr;
};

