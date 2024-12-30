#pragma once

#include "GameObject.h"

/*
========
Player
========
*/

class Player : public GameObject
{
public:
	Player();
	~Player();

	bool Initialize(IT_EngineCore* engineCore);
	virtual void Update(const float dt) override;
	virtual void Render() override;

	virtual void SetScale(Vector3 scale) override;
	virtual void SetRotation(Vector3 rotation) override;
	virtual void SetPosition(Vector3 pos) override;
	IT_CharacterObject* GetCharacterObject() { return m_characterObj; }

private:
	void CleanUp();

private:
	IT_EngineCore* m_engineCore = nullptr;
	IT_CharacterObject* m_characterObj = nullptr;
	float m_moveSpeed = 1.0f;
};

