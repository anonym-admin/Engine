#include "pch.h"
#include "Game.h"
#include "Application.h"

/*
=======
Game
=======
*/

Game::Game()
{
}

Game::~Game()
{
}

bool Game::InitGame(Application* app)
{
	m_app = app;
	m_engineCore = app->GetEngineCore();

	RECT rect = {};
	GetClientRect(m_app->GetHwnd(), &rect);
	m_screenWidth = rect.right - rect.left;
	m_screenHeight = rect.bottom - rect.top;
	
	return true;
}

void Game::CleanUpGame()
{
}

void Game::RunGame()
{
	static uint32 fps = 0;
	static uint64 prevTickCount = 0;
	fps++;

	uint64 curTickCount = ::GetTickCount64();

	m_engineCore->Tick();

	if (curTickCount - prevTickCount > 1000)
	{
		m_fps = fps;
		fps = 0;
		prevTickCount = curTickCount;
	}
}

void Game::Update(uint64 curTick)
{
	static uint64 prevTickCount = curTick;

	// 16ms 마다 한번씩 업데이트
	// 1s 에는 60번 업데이트
	if (curTick - prevTickCount < 16)
	{
		return;
	}
	prevTickCount = curTick;

	// Mouse Picking.
	// UpdateMousePicking();

	//// Update text.
	//uint32 cmdListCount = m_renderer->GetCmdListCount();
	//wchar_t buf[36] = {};
	//swprintf_s(buf, L"fps: %d cmdList: %d", m_fps, cmdListCount);
	//m_textUI->Update(buf);
}

void Game::UpdateMousePicking()
{
	//static Vector3 prevPos = Vector3(0.0f);
	//static float prevRatio = 0.0f;
	//static Actor* selected = nullptr;
	//bool leftBtn = m_app->IsLeftBtnDown();
	//bool rightBtn = m_app->IsRightBtnDown();
	//float ndcX = m_app->GetNdcMousePosX();
	//float ndcY = m_app->GetNdcMousePosY();

	//if (m_app->IsLeftBtnDown() || m_app->IsRightBtnDown())
	//{
	//	if (!selected)
	//	{
	//		Actor* actor = IntersectActor(ndcX, ndcY, &prevPos, &prevRatio);
	//		if (actor)
	//		{
	//			selected = actor;
	//		}
	//	}
	//	else
	//	{
	//		if (leftBtn || rightBtn)
	//		{
	//			if (leftBtn) // Move
	//			{
	//				Vector3 curPos = Vector3(0.0f);
	//				m_renderer->MousePickingAfterMoveObject(ndcX, ndcY, &curPos, prevRatio);
	//				float moveLen = (curPos - prevPos).Length();

	//				if (moveLen >= 1e-5)
	//				{
	//					selected->MovePosition(curPos - prevPos);
	//					prevPos = curPos;
	//				}
	//			}
	//			else // Rotation
	//			{
	//			}
	//		}
	//	}
	//}
	//else
	//{
	//	selected = nullptr;
	//}
}

void* Game::IntersectActor(float ndcX, float ndcY, Vector3* prevPos, float* prevRatio)
{
	//float hitDist = 0.0f;
	//DL_LIST* cur = m_headActorListNode;
	//while (cur != nullptr)
	//{
	//	Actor* actor = reinterpret_cast<Actor*>(cur);
	//	DirectX::BoundingBox boundingBox = actor->GetBoundingBox();
	//	bool pick = m_renderer->MousePicking(boundingBox, ndcX, ndcY, prevPos, &hitDist, prevRatio);
	//	if (pick)
	//	{
	//		return actor;
	//	}
	//	cur = cur->next;
	//}
	return nullptr;
}


