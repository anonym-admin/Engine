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

    const wchar_t* basePath = L"../../Assets/";
    const wchar_t* textureFilenames[] = {
        L"tex_00.dds",
        L"tex_01.dds",
        L"tex_02.dds",
        L"tex_03.dds",
        L"tex_04.dds",
        L"tex_05.dds",
    };

    for (uint32 i = 0; i < m_cube->numMeshes; i++)
    {
        wchar_t filePath[256] = {};
        wcscat_s(filePath, basePath);
        wcscat_s(filePath, textureFilenames[i]);

        wcscpy_s(m_cube->meshes[i].textureFileaname, 256, filePath);
    }

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
    m_dt += 1.0f / 1000.0f;

    Vector3 translation = m_transform.Translation();

    m_transform = Matrix::CreateRotationY(m_dt) * Matrix::CreateTranslation(translation);
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
