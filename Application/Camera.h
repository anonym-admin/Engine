#pragma once

/*
=========
Camera
=========
*/

class Application;

class Camera
{
public:
	Camera();
	~Camera();

	bool Initialize(Application* app, Vector3 pos, Vector3 dir);
	void Update();
	
private:
	void CleanUp();

private:
	Application* m_app = nullptr;
	Vector3 m_pos = Vector3(0.0f);
	Vector3 m_dir = Vector3(0.0f);
};

