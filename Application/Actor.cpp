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

    //for (uint32 i = 0; i < m_cube->numMeshes; i++)
    //{
    //    for (uint32 j = 0; j < m_cube->meshes[i].numVertices; j++)
    //    {
    //        printf("%f %f %f\n", m_cube->meshes[i].vertices[j].position.x, m_cube->meshes[i].vertices[j].position.y, m_cube->meshes[i].vertices[j].position.z);
    //    }
    //}

    //for (uint32 i = 0; i < m_cube->numMeshes; i++)
    //{
    //    for (uint32 j = 0; j < m_cube->meshes[i].numIndices; j++)
    //    {
    //        printf("%d ", m_cube->meshes[i].indices[j]);
    //    }
    //    printf("\n");
    //}

    m_meshObj = m_renderer->CreateMeshObject();
    m_texture0 = m_renderer->CreateTextureFromFile(L"../../Assets/WoodCrate01.dds");
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
    m_renderer->DestroyTexture(m_texture0);
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
