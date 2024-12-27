#include "pch.h"
#include "SceneManager.h"
#include "SceneHome.h"

/*
==============
SceneManager
==============
*/


SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
    CleanUp();
}

bool SceneManager::Initialize(Game* gmae, uint32 maxNumScene)
{
    m_maxNumScene = maxNumScene;
    m_sceneGraph = new Scene * [maxNumScene];

    SceneHome* sceneHome = new SceneHome;
    sceneHome->Initialize(gmae);
    m_sceneGraph[m_numScene++] = sceneHome;

    m_curScene = sceneHome;
    m_curScene->BeginScene();

    return true;
}

void SceneManager::Update(const float dt)
{
    if (!m_curScene)
    {
        __debugbreak();
    }

    m_curScene->Update(dt);
}

void SceneManager::Render()
{
    if (!m_curScene)
    {
        __debugbreak();
    }

    m_curScene->Render();
}

void SceneManager::CleanUp()
{
    if (m_sceneGraph)
    {
        for (uint32 i = 0; i < m_numScene; i++)
        {
            if (m_sceneGraph[i])
            {
                delete m_sceneGraph[i];
                m_sceneGraph[i] = nullptr;
            }
        }
        delete[] m_sceneGraph;
        m_sceneGraph = nullptr;
    }
}
