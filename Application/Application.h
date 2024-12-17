#pragma once

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

	inline IT_EngineCore* GetEngineCore() { return m_engineCore; }
	inline HWND GetHwnd() { return m_hwnd; }
	inline uint32 GetMousePosX() { return m_mousePosX; }
	inline uint32 GetMousePosY() { return m_mousePosY; }
	inline float GetNdcMousePosX() { return m_ndcMousePosX; }
	inline float GetNdcMousePosY() { return m_ndcMousePosY; }
	inline bool IsLeftBtnDown() { return m_mouseLeftButton; }
	inline bool IsRightBtnDown() { return m_mouseRightButton; }

private:
	bool InitWindow();
	bool InitEngine(bool enableDebugLayer, bool enableGBV);
	void UpdateMouse();
	void CleanWindow();
	void CleanEngine();

private:
	HWND m_hwnd = nullptr;
	HMODULE m_engineCoreDll = nullptr;
	IT_EngineCore* m_engineCore = nullptr;
	Game* m_game = nullptr;
	uint32 m_screenWidth = 0;
	uint32 m_screenHeight = 0;
	uint32 m_mousePosX = 0;
	uint32 m_mousePosY = 0;
	float m_ndcMousePosX = 0.0f;
	float m_ndcMousePosY = 0.0f;
	bool m_mouseLeftButton = false;
	bool m_mouseRightButton = false;
	bool m_fpv = false; // First person view.
};

