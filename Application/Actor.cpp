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

    m_cube = GeometryGenerator::MakeCube();
    m_meshObj = m_renderer->CreateMeshObject();
    m_meshObj->CreateMeshBuffers(m_cube);
    m_meshObj->SetTransform(m_transform);

    return true;
}

void Actor::CleanUp()
{
    if (m_meshObj)
    {
        m_meshObj->Release();
    }

    GeometryGenerator::DestroyGeometry(m_cube);
}

void Actor::Update()
{
    static float dt = 0.0f;
    dt += 1.0f / 1000.0f;

    m_transform = Matrix::CreateRotationY(dt);
}

void Actor::Render()
{
    m_renderer->RenderMeshObject(m_meshObj, m_transform);
}

void Actor::SetPosition(Vector3 pos)
{
    m_pos = pos;
    m_transform = Matrix::CreateTranslation(pos);
    m_meshObj->SetTransform(m_transform);
}
