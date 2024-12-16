#pragma once

/*
=================
CoordinateObject
=================
*/

class Actor;

class CoordinateObject
{
public:
	CoordinateObject();
	~CoordinateObject();

	bool Initialize(IT_Renderer* renderer);
	void Update();
	void Render();
	
private:
	void CleanUp();

private:
	IT_Renderer* m_renderer = nullptr;
	Actor* m_actor = nullptr;
	LineData* m_lineData = nullptr;
};

