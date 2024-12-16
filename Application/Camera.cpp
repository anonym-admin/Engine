#include "pch.h"
#include "Camera.h"
#include "Application.h"

/*
=========
Camera
=========
*/

Camera::Camera()
{
}

Camera::~Camera()
{
    CleanUp();
}

bool Camera::Initialize(Application* app, Vector3 pos, Vector3 dir)
{
    m_app = app;

	IT_Renderer* renderer = m_app->GetRenderer();

	renderer->SetCameraPos(pos);
	renderer->SetCameraRot(dir);

    return true;
}

void Camera::Update()
{
	IT_Renderer* renderer = m_app->GetRenderer();

	// Rotate
	const float yaw = m_app->GetNdcMousePosX() * DirectX::XM_2PI;
	const float pitch = -m_app->GetNdcMousePosY() * DirectX::XM_PI;
	renderer->SetCameraRot(yaw, pitch, 0.0f);

	// Move
	if (GetAsyncKeyState('W') & 0x8000)
	{
		renderer->MoveFrontCamera(1.0f / 30.0f);
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		renderer->MoveRightCamera(1.0f / 30.0f);
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		renderer->MoveFrontCamera(-1.0f / 30.0f);
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		renderer->MoveRightCamera(-1.0f / 30.0f);
	}
	if (GetAsyncKeyState('Q') & 0x8000)
	{
		renderer->MoveUpCamera(1.0f / 30.0f);
	}
	if (GetAsyncKeyState('E') & 0x8000)
	{
		renderer->MoveUpCamera(-1.0f / 30.0f);
	}
}

void Camera::CleanUp()
{
}

