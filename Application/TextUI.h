#pragma once

/*
===========
TextUI
===========
*/

class Actor;

class TextUI
{
public:
	TextUI();
	~TextUI();

	bool Initialize(IT_Renderer* renderer, uint32 width, uint32 height, uint32 renderPosX, uint32 renderPosY, float scaleX, float scaleY, float depthZ, const wchar_t* fontFamilyName, float fontSize, RECT* sample = nullptr);
	void Update(const wchar_t* contents);
	void Render();

private:
	void CleanUp();

private:
	IT_Renderer* m_renderer = nullptr;
	void* m_fontObj = nullptr;
	uint8* m_img = nullptr;
	wchar_t m_contents[256] = {};
	void* m_texture = nullptr;
	Actor* m_actor = nullptr;
	ACTOR_HANDLE m_actorHandle = {};
};

