#include "pch.h"
#include "Wall.h"

/*
========
Wall
========
*/

Wall::Wall()
{
}

Wall::~Wall()
{
    CleanUp();
}

bool Wall::Initialize(IT_EngineCore* engineCore, uint32 ctxIndex)
{
    m_engineCore = engineCore;

    void* actor = m_engineCore->GetActor(1);
    m_buildingObj = m_engineCore->CreateBuildingObject(actor, ctxIndex);

    return false;
}

void Wall::Update(const float dt)
{
}

void Wall::Render()
{
    m_engineCore->RenderBuildingObject(m_buildingObj, false, m_drawMeshBoundingBox);
}

void Wall::SetScale(Vector3 scale)
{
    GameObject::SetScale(scale);
    m_buildingObj->SetScale(scale.x, scale.y, scale.z);
}

void Wall::SetRotation(Vector3 rotation)
{
    GameObject::SetRotation(rotation);
    m_buildingObj->SetRotation(rotation.x, rotation.y, rotation.z);
}

void Wall::SetPosition(Vector3 pos)
{
    GameObject::SetPosition(pos);
    m_buildingObj->SetPosition(pos);
}

void Wall::UpdateMousePicking()
{
    m_engineCore->UpdateMousePicking(m_buildingObj);
}

void Wall::IsDrawMeshBoundingBox()
{
    m_drawMeshBoundingBox = !m_drawMeshBoundingBox;
}

void Wall::CleanUp()
{
    if (m_buildingObj)
    {
        m_buildingObj->Release();
        m_buildingObj = nullptr;
    }
}
