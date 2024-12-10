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

bool Actor::Initialize(IT_Renderer* renderer)
{
    m_renderer = renderer;

    m_triangle = GeometryGenerator::MakeSquare();
    m_meshObj = m_renderer->CreateMeshObject();
    m_meshObj->CreateMeshBuffers(m_triangle);

    return true;
}

void Actor::CleanUp()
{
    if (m_meshObj)
    {
        m_meshObj->Release();
    }

    GeometryGenerator::DestroyGeometry(m_triangle);
}

void Actor::Update()
{
}

void Actor::Render()
{
    m_renderer->RenderMeshObject(m_meshObj);
}
