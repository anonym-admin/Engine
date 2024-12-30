#include "pch.h"
#include "CameraController.h"

/*
==================
CameraController
==================
*/

CameraController::CameraController()
{
}

CameraController::~CameraController()
{
    CleanUp();
}

bool CameraController::Initialize(EngineCore* engineCore)
{
    Camera* cam = new Camera;
    cam->Initialize(engineCore);
    cam->EnableFpv();
    m_cameraModeList[FPS_MODE] = cam;

    cam = new Camera;
    cam->Initialize(engineCore);
    cam->DisalbeFpv();
    m_cameraModeList[EDIT_MODE] = cam;

    m_curCamera = m_cameraModeList[FPS_MODE];
    m_curCamera->SetPosition(m_fpsCamPosition);
    m_curCamera->SetDirection(m_fpsCamDir);

    return true;
}

void CameraController::Update(const float dt)
{
    m_curCamera->Update(dt);
}

void CameraController::SetCurrentCameraMode(CAMERA_CONTROL_TYPE type)
{
    if (FPS_MODE == type)
    {
        m_editModeCamPosition = m_curCamera->GetPosition();
        
        m_curCamera = m_cameraModeList[type];
        m_curCamera->SetPosition(m_fpsCamPosition);
        m_curCamera->SetDirection(m_fpsCamDir);
    }
    else
    {
        m_fpsCamPosition = m_curCamera->GetPosition();

        m_curCamera = m_cameraModeList[type];
        m_curCamera->SetPosition(m_editModeCamPosition);
        m_curCamera->SetDirection(m_editModeCamDir);
    }
}

Vector3 CameraController::GetCurrentCameraModePosition()
{
    return m_curCamera->GetPosition();
}

void CameraController::CleanUp()
{
    for (uint32 i = 0; i < CAMERA_CONTROL_TYPE_NUM; i++)
    {
        if (m_cameraModeList[i])
        {
            delete m_cameraModeList[i];
            m_cameraModeList[i] = nullptr;
        }
    }
}
