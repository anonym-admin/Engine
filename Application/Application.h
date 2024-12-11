#pragma once

#include "../../Interface/IT_Renderer.h"

/*
=============
Application
=============
*/

class Game;

class Application
{
public:
	Application();
	~Application();

	bool Initialize(bool enableDebugLayer, bool enableGBV);
	void CleanUp();
	int32 RunApplication();
	LRESULT CALLBACK MemberWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	inline IT_Renderer* GetRenderer() { return m_renderer; }
	inline HWND GetHwnd() { return m_hwnd; }

private:
	bool InitWindow();
	bool InitModule(bool enableDebugLayer, bool enableGBV);
	void CleanUpWindow();
	void CleanUpModule();

private:
	HWND m_hwnd = nullptr;
	HMODULE m_rendererDll = nullptr;
	IT_Renderer* m_renderer = nullptr;
	Game* m_game = nullptr;
};

