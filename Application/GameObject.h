#pragma once

/*
=============
GameObject
=============
*/

class GameObject
{
public:
	GameObject();
	virtual ~GameObject() = 0;

	virtual void Update(const float dt) = 0;
	virtual void Render() = 0;

	void SetWire(bool isWire) { m_isWire = isWire; }
	virtual void SetScale(Vector3 scale) { m_scale = scale; }
	virtual void SetRotation(Vector3 rotation) { m_rotation = rotation; }
	virtual void SetPosition(Vector3 pos) { m_position = pos; }
	Vector3 GetPosition() { return m_position; }
	bool IsWire() { return m_isWire; }
	virtual IT_BaseObject* GetMyObject() { return nullptr; };

private:
	Vector3 m_scale = Vector3(1.0f);
	Vector3 m_rotation = Vector3(0.0f);
	Vector3 m_position = Vector3(0.0f);
	bool m_isWire = false;
};

