#include "pch.h"
#include "CoordinateObject.h"
#include "Actor.h"

/*
=================
CoordinateObject
=================
*/

CoordinateObject::CoordinateObject()
{
}

CoordinateObject::~CoordinateObject()
{
	CleanUp();
}

bool CoordinateObject::Initialize(IT_Renderer* renderer)
{
	m_renderer = renderer;

	// Create the line object.
	m_lineData = new LineData;
	m_lineData->numVertices = 6;
	m_lineData->vertices = new LineVertex[6];

	m_lineData->vertices[0].position = Vector3(0.0f, 0.0f, 0.0f);
	m_lineData->vertices[1].position = Vector3(0.0f, 1.0f, 0.0f);
	m_lineData->vertices[2].position = Vector3(0.0f, 0.0f, 0.0f);
	m_lineData->vertices[3].position = Vector3(1.0f, 0.0f, 0.0f);
	m_lineData->vertices[4].position = Vector3(0.0f, 0.0f, 0.0f);
	m_lineData->vertices[5].position = Vector3(0.0f, 0.0f, 1.0f);
	m_lineData->vertices[0].color = Vector3(1.0f, 0.0f, 1.0f);
	m_lineData->vertices[1].color = Vector3(1.0f, 0.0f, 1.0f);
	m_lineData->vertices[2].color = Vector3(0.0f, 1.0f, 0.0f);
	m_lineData->vertices[3].color = Vector3(0.0f, 1.0f, 0.0f);
	m_lineData->vertices[4].color = Vector3(1.0f, 0.0f, 0.0f);
	m_lineData->vertices[5].color = Vector3(1.0f, 0.0f, 0.0f);

	ACTOR_HANDLE actorHandle = {};
	actorHandle.type = ACTOR_TYPE::LINE_OBJ;
	actorHandle.line.lineData = m_lineData;

	m_actor = new Actor;
	m_actor->Initialize(renderer, &actorHandle);

	return true;
}

void CoordinateObject::Update()
{
}

void CoordinateObject::Render()
{
	m_actor->Render();
}

void CoordinateObject::CleanUp()
{
	if (m_actor)
	{
		delete m_actor;
		m_actor = nullptr;
	}
	if (m_lineData)
	{
		if (m_lineData->vertices)
		{
			delete[] m_lineData->vertices;
			m_lineData->vertices = nullptr;
		}

		delete m_lineData;
		m_lineData = nullptr;
	}
}
