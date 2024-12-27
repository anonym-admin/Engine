#pragma once

#include "GameObject.h"

/*
========
Wall
========
*/

class Wall : public GameObject
{
public:
	Wall();
	~Wall();

	bool Initialize(IT_EngineCore* engineCore);
	virtual void Update(const float dt) override;
	virtual void Render() override;

	virtual void SetScale(Vector3 scale) override;
	virtual void SetRotation(Vector3 rotation) override;
	virtual void SetPosition(Vector3 pos) override;
	IT_BuildingObject* GetMyObject() { return m_buildingObj; }

private:
	void CleanUp();

private:
	IT_EngineCore* m_engineCore = nullptr;
	IT_BuildingObject* m_buildingObj = nullptr;
};

