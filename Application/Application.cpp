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

bool Application::Initialize()
{
	if (!InitWindow())
	{
		return false;
	}
	if (!InitModule())
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
		int32 keyCode = wParam;
		if (keyCode == VK_ESCAPE)
		{
			::PostQuitMessage(998);
		}
	}
	break;
	case WM_KEYUP:
	{
	}
	break;
	case WM_MOUSEMOVE:
	{
	}
	break;
	case WM_LBUTTONDOWN:
	{
	}
	break;
	case WM_LBUTTONUP:
	{
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

	return true;
}

bool Application::InitModule()
{
	m_rendererDll = ::LoadLibrary(L"./RendererD3D12.dll");
	if (!m_rendererDll)
	{
		__debugbreak();
	}
	Dll_CreateInstance CreateInstance = (Dll_CreateInstance)::GetProcAddress(m_rendererDll, "Dll_CreateInstance");
	CreateInstance(reinterpret_cast<void**>(&m_renderer));
	if (!m_renderer->Initialize(m_hwnd))
	{
		return false;
	}
	return true;
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
