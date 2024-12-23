#pragma once

/*
========
Player
========
*/

class Game;
interface IT_EngineCore;

class Player
{
public:
	bool Initialize(IT_EngineCore* engineCore, IT_Level* curLevel, Game* game);
	void Tick();

private:
	void CleanUp();

private:
	uint32 m_refCount = 1;
	IT_GeometryObject* m_geoObj = nullptr;
	Vector3 m_position = Vector3(0.0f);
};

