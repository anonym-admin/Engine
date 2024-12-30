#pragma once

/*
==================
CameraController
==================
*/

class EngineCore;
class Camera;

class CameraController
{
public:
	CameraController();
	~CameraController();

	bool Initialize(EngineCore* engineCore);
	void Update(const float dt);
	void SetCurrentCameraMode(CAMERA_CONTROL_TYPE type);
	Vector3 GetCurrentCameraModePosition();

private:
	void CleanUp();

private:
	Camera* m_cameraModeList[CAMERA_CONTROL_TYPE_NUM] = {};
	Camera* m_curCamera = nullptr;
	Camera* m_prevCamera = nullptr;

	Vector3 m_fpsCamPosition = Vector3(0.0f, 0.0f, -2.0f);
	Vector3 m_fpsCamDir = Vector3(0.0f, 0.0f, 1.0f);

	Vector3 m_editModeCamPosition = Vector3(0.0f, 10.0f, 0.0f);
	Vector3 m_editModeCamDir = Vector3(0.0f, -1.0f, 0.0f);

	Vector3 m_prevPosition;
	Vector3 m_curPosition;
};

