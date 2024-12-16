#include "pch.h"
#include "CharacterObject_01.h"
#include "Actor.h"

CharacterObject_01::CharacterObject_01()
{
}

CharacterObject_01::~CharacterObject_01()
{
    CleanUp();
}

bool CharacterObject_01::Initialize()
{
    return true;
}

void CharacterObject_01::Update()
{
    m_actor->Update();
}

void CharacterObject_01::Render()
{
    m_actor->Render();
}

void CharacterObject_01::CleanUp()
{
    
}
