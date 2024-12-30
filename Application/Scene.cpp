#include "pch.h"
#include "Scene.h"

/*
==========
Scene
==========
*/

Scene::Scene()
{
}

Scene::~Scene()
{
    CleanUp();
}

bool Scene::Initialize()
{
    return true;
}

void Scene::Update(const float dt)
{
     //
}

void Scene::Render()
{
    //
}

void Scene::SetName(const wchar_t* name)
{
    wcscpy_s(m_sceneName, name);
}

void Scene::SetCameraPos(Vector3 camPos)
{
    m_camPos = camPos;
}

void Scene::SetCameraDir(Vector3 camDir)
{
    m_camDir = camDir;
}

const wchar_t* Scene::GetName()
{
    return m_sceneName;
}

void Scene::CleanUp()
{
}
