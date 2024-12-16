#include "pch.h"
#include "Application.h"
#include "Game.h"

Application* GApplication;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

/*
================================
Dll function prototype typedef
================================
*/
typedef void (*Dll_CreateInstance)(void** inst);

/*
=============
Application
=============
*/

Application::Application()
{
	GApplication = this;
}

Application::~Application()
{
	CleanUp();
}

bool Application::Initialize(bool enableDebugLayer, bool enableGBV)
{
	srand(static_cast<uint32>(time(nullptr)));

	if (!InitWindow())
	{
		return false;
	}
	if (!InitModule(enableDebugLayer, enableGBV))
	{
		return false;
	}

	m_game = new Game;
	if (!m_game->InitGame(this))
	{
		return false;
	}

	return true;
}

void Application::CleanUp()
{
	if (m_game)
	{
		m_game->CleanUpGame();
		delete m_game;
		m_game = nullptr;
	}

	CleanUpModule();
	CleanUpWindow();
}

int32 Application::RunApplication()
{
	MSG msg = { };
	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			m_game->RunGame();
		}
	}

	return (int32)msg.wParam;
}

LRESULT Application::MemberWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_SIZE:
		{
			int32 width = LOWORD(lParam);  // Macro to get the low-order word.
			int32 height = HIWORD(lParam); // Macro to get the high-order word.
		}
		break;
		case WM_KEYDOWN:
		{
			int32 keyCode = (int32)wParam;
			if (keyCode == VK_ESCAPE)
			{
				::PostQuitMessage(998);
			}
			if (keyCode == 'F') // First person view.
			{
				m_fpv = !m_fpv;
			}
		}
		break;
		case WM_KEYUP:
		{
		}
		break;
		case WM_MOUSEMOVE:
		{
			int32 posX = LOWORD(lParam);
			int32 posY = HIWORD(lParam);

			m_mousePosX = posX;
			m_mousePosY = posY;

			UpdateMouse();
		}
		break;
		case WM_LBUTTONDOWN:
		{
			m_mouseLeftButton = true;
		}
		break;
		case WM_LBUTTONUP:
		{
			m_mouseLeftButton = false;
		}
		break;
		case WM_RBUTTONDOWN:
		{
			m_mouseRightButton = true;
		}
		break;
		case WM_RBUTTONUP:
		{
			m_mouseRightButton = false;
		}
		break;
		case WM_DESTROY:
		{
			::PostQuitMessage(999);
		}
		break;
		}
	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

bool Application::InitWindow()
{
	const wchar_t className[] = L"Window Application";
	const wchar_t windowName[] = L"AnonymouseEngine Prototype";

	WNDCLASS wc = { };

	wc.lpfnWndProc = WndProc;
	wc.hInstance = ::GetModuleHandle(nullptr);
	wc.lpszClassName = className;
	RegisterClass(&wc);

	m_hwnd = ::CreateWindowEx(0, className, windowName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, wc.hInstance, NULL);

	::ShowWindow(m_hwnd, SW_SHOW);

	RECT rt = {};
	::GetClientRect(m_hwnd, &rt);
	m_screenWidth = static_cast<uint32>(rt.right - rt.left);
	m_screenHeight = static_cast<uint32>(rt.bottom - rt.top);

	return true;
}

bool Application::InitModule(bool enableDebugLayer, bool enableGBV)
{
	m_rendererDll = ::LoadLibrary(L"./RendererD3D12.dll");
	if (!m_rendererDll)
	{
		__debugbreak();
	}
	Dll_CreateInstance CreateInstance = (Dll_CreateInstance)::GetProcAddress(m_rendererDll, "Dll_CreateInstance");
	CreateInstance(reinterpret_cast<void**>(&m_renderer));
	if (!m_renderer->Initialize(m_hwnd, enableDebugLayer, enableGBV))
	{
		return false;
	}
	return true;
}

void Application::UpdateMouse()
{
	if (m_fpv)
	{
		float ndcX = static_cast<float>(m_mousePosX) / m_screenWidth * 2.0f - 1.0f;
		float ndcY = static_cast<float>(m_mousePosY) / m_screenHeight * -2.0f + 1.0f;

		ndcX = F_Clamp(ndcX, -1.0f, 1.0f);
		ndcY = F_Clamp(ndcY, -1.0f, 1.0f);

		m_ndcMousePosX = ndcX;
		m_ndcMousePosY = ndcY;
	}
}

void Application::CleanUpWindow()
{
	if (m_hwnd)
	{
		::DestroyWindow(m_hwnd);
	}
}

void Application::CleanUpModule()
{
	if (m_renderer)
	{
		m_renderer->Release();
		m_renderer = nullptr;
	}
	if (m_rendererDll)
	{
		::FreeLibrary(m_rendererDll);
	}
}

/*
=========
WndProc
=========
*/

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return GApplication->MemberWndProc(hwnd, msg, wParam, lParam);
}
