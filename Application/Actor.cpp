#include "pch.h"
#include "Actor.h"
#include "Game.h"
#include "GeometryGenerator.h"
#include "../../Interface/IT_Renderer.h"

/*
=======
Actor
=======
*/

Actor::Actor()
{
}

Actor::~Actor()
{
	CleanUp();
}

bool Actor::Initialize(IT_Renderer* renderer, ACTOR_HANDLE* actorHandle)
{
	m_renderer = renderer;

	memcpy(&m_actorHandle, actorHandle, sizeof(ACTOR_HANDLE));

	switch (m_actorHandle.type)
	{
	case ACTOR_TYPE::MESH_OBJ:
	{
		IT_MeshObject* meshObj = nullptr;

		m_geometry = m_actorHandle.mesh.geometry;
		meshObj = m_renderer->CreateMeshObject();
		meshObj->CreateMeshBuffers(m_geometry);
		meshObj->SetTransform(m_transform);
		m_boundingBox = DirectX::BoundingBox(m_position, m_actorHandle.mesh.scale);

		m_renderObj = meshObj;

		SetPosition(m_actorHandle.mesh.pos);
	}
	break;
	case ACTOR_TYPE::SPRITE_OBJ:
	{
		IT_SpriteObject* spriteObj = nullptr;

		spriteObj = m_renderer->CreateSpriteObject();

		m_renderObj = spriteObj;
	}
	break;
	case ACTOR_TYPE::LINE_OBJ:
	{
		IT_LineObject* lineObj = nullptr;

		lineObj = m_renderer->CreateLineObject();
		lineObj->CreateLineBuffers(m_actorHandle.line.lineData);

		m_renderObj = lineObj;
	}
	break;
	default:
	{
		__debugbreak();
	}
	break;
	}

	return true;
}

void Actor::CleanUp()
{
	if (m_renderObj)
	{
		IUnknown* obj = reinterpret_cast<IUnknown*>(m_renderObj);
		obj->Release();

		m_renderObj = nullptr;
	}
}

void Actor::Update()
{
}

void Actor::Render()
{
	switch (m_actorHandle.type)
	{
	case ACTOR_TYPE::MESH_OBJ:
	{
		IT_MeshObject* meshObj = reinterpret_cast<IT_MeshObject*>(m_renderObj);
		m_renderer->RenderMeshObject(meshObj, m_transform);
	}
	break;
	case ACTOR_TYPE::SPRITE_OBJ:
	{
		IT_SpriteObject* spriteObj = reinterpret_cast<IT_SpriteObject*>(m_renderObj);
		if (m_texture)
		{
			m_renderer->RenderSpriteObjectWithTexture(spriteObj, m_actorHandle.sprite.renderPosX, m_actorHandle.sprite.renderPosY, m_actorHandle.sprite.scaleX, m_actorHandle.sprite.scaleY, m_actorHandle.sprite.depthZ, m_actorHandle.sprite.sample, m_texture, "Text");
		}
	}
	break;
	case ACTOR_TYPE::LINE_OBJ:
	{
		IT_LineObject* lineObj = reinterpret_cast<IT_LineObject*>(m_renderObj);
		m_renderer->RenderLineObject(lineObj, m_transform);
	}
	break;
	default:
	{
		__debugbreak();
	}
	break;
	}
}

void Actor::SetTexture(void* texHandle)
{
	if (ACTOR_TYPE::SPRITE_OBJ != m_actorHandle.type)
	{
		__debugbreak();
	}

	m_texture = texHandle;
}

void Actor::SetPosition(Vector3 pos)
{
	if (ACTOR_TYPE::MESH_OBJ != m_actorHandle.type && ACTOR_TYPE::LINE_OBJ != m_actorHandle.type)
	{
		__debugbreak();
	}

	IT_MeshObject* obj = reinterpret_cast<IT_MeshObject*>(m_renderObj);

	m_position = pos;
	obj->SetTransform(Matrix::CreateTranslation(m_position));
}

void Actor::MovePosition(Vector3 deltaPos)
{
	if (ACTOR_TYPE::MESH_OBJ != m_actorHandle.type && ACTOR_TYPE::LINE_OBJ != m_actorHandle.type)
	{
		__debugbreak();
	}

	Vector3 translation = m_transform.Translation();
	SetPosition(translation + deltaPos);
}
