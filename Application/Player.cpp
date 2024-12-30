#include "pch.h"
#include "Player.h"

/*
========
Player
========
*/

Player::Player()
{
}

Player::~Player()
{
	CleanUp();
}

bool Player::Initialize(IT_EngineCore* engineCore)
{
	m_engineCore = engineCore;

	void* actor = m_engineCore->GetActor(0);
	m_characterObj = m_engineCore->CreateCharacterObject(actor, 0);

	return true;
}

void Player::Update(const float dt)
{
	// m_engineCore->UpdateMousePicking(m_characterObj);
}

void Player::Render()
{
	m_engineCore->RenderCharacterObject(m_characterObj, IsWire());
}

void Player::SetScale(Vector3 scale)
{
	GameObject::SetScale(scale);
	m_characterObj->SetScale(scale.x, scale.y, scale.z);
}

void Player::SetRotation(Vector3 rotation)
{
	GameObject::SetRotation(rotation);
	m_characterObj->SetRotation(rotation.x, rotation.y, rotation.z);
}

void Player::SetPosition(Vector3 pos)
{
	GameObject::SetPosition(pos);
	m_characterObj->SetPosition(pos);
}

void Player::CleanUp()
{
	if (m_characterObj)
	{
		m_characterObj->Release();
		m_characterObj = nullptr;
	}
}
