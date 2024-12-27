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

const wchar_t* Scene::GetName()
{
    return m_sceneName;
}

void Scene::CleanUp()
{
}
