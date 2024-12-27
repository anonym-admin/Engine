#include "pch.h"
#include "Monster.h"

/*
==========
Monster
==========
*/

Monster::Monster()
{
}

Monster::~Monster()
{
    CleanUp();
}

bool Monster::Initialize(IT_EngineCore* engineCore)
{
    m_engineCore = engineCore;

    void* actor = m_engineCore->GetActor(0);
    m_characterObj = m_engineCore->CreateCharacterObject(actor, 1);

    return true;
}

void Monster::Update(const float dt)
{
    m_engineCore->UpdateMousePicking(m_characterObj);
}

void Monster::Render()
{
    m_engineCore->RenderCharacterObject(m_characterObj, IsWire());
}

void Monster::SetScale(Vector3 scale)
{
    GameObject::SetScale(scale);
    m_characterObj->SetScale(scale.x, scale.y, scale.z);
}

void Monster::SetRotation(Vector3 rotation)
{
    GameObject::SetRotation(rotation);
    m_characterObj->SetRotation(rotation.x, rotation.y, rotation.z);
}

void Monster::SetPosition(Vector3 pos)
{
    GameObject::SetPosition(pos);
    m_characterObj->SetPosition(pos);
}

void Monster::CleanUp()
{
    if (m_characterObj)
    {
        m_characterObj->Release();
        m_characterObj = nullptr;
    }
}
