#pragma once

/*
===================
CharacterObject_01
Rename later
===================
*/

class Actor;

class CharacterObject_01
{
public:
	CharacterObject_01();
	~CharacterObject_01();

	bool Initialize();
	void Update();
	void Render();

	inline void SetActor(Actor* actor) { m_actor = actor; }
	inline Actor* GetActor() { return m_actor; }

private:
	void CleanUp();

private:
	Actor* m_actor = nullptr;
};

