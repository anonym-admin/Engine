#include "pch.h"
#include "EditorManager.h"
#include "EditorArrange.h"
#include "EditorGenerate.h"

/*
====================
EditorManager
====================
*/

EditorManager::EditorManager()
{
}

EditorManager::~EditorManager()
{
	CleanUp();
}

bool EditorManager::Initialize(Game* game, uint32 maxNumEditor)
{
	m_maxNumEditor = maxNumEditor;
	m_editorList = new Editor * [maxNumEditor];

	EditorArrange* editorArrange = new EditorArrange;
	editorArrange->Initialize(game);
	m_editorList[m_numEditor++] = editorArrange;

	EditorGenerate* editGenerate = new EditorGenerate;
	editGenerate->Initialize(game);
	m_editorList[m_numEditor++] = editGenerate;

	m_curEditor = editorArrange;

	return true;
}

void EditorManager::Update(const float dt)
{
	if (!m_curEditor)
	{
		__debugbreak();
	}

	m_curEditor->Update(dt);
}

void EditorManager::Render()
{
	if (!m_curEditor)
	{
		__debugbreak();
	}

	m_curEditor->Render();
}

void EditorManager::SetCurrentEditor(EDITOR_TYPE type)
{
	m_curEditor->EndEditor();

	m_curEditor = m_editorList[type - 1];

	m_curEditor->BeginEditor();
}

void EditorManager::CleanUp()
{
	if (m_editorList)
	{
		for (uint32 i = 0; i < m_numEditor; i++)
		{
			if (m_editorList[i])
			{
				delete m_editorList[i];
				m_editorList[i] = nullptr;
			}
		}
		delete[] m_editorList;
		m_editorList = nullptr;
	}
}
