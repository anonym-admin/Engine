#include "pch.h"
#include "TextUI.h"
#include "Actor.h"

TextUI::TextUI()
{
}

TextUI::~TextUI()
{
	CleanUp();
}

bool TextUI::Initialize(IT_Renderer* renderer, uint32 width, uint32 height, uint32 renderPosX, uint32 renderPosY, float scaleX, float scaleY, float depthZ, const wchar_t* fontFamilyName, float fontSize, RECT* sample)
{
	// Set the font object.
	m_renderer = renderer;

	m_actor = new Actor;
	ACTOR_HANDLE actorHandle = {};
	actorHandle.type = ACTOR_TYPE::SPRITE_OBJ;
	actorHandle.sprite.width = width;
	actorHandle.sprite.height = height;
	actorHandle.sprite.renderPosX = renderPosX;
	actorHandle.sprite.renderPosY = renderPosY;
	actorHandle.sprite.scaleX = scaleX;
	actorHandle.sprite.scaleY = scaleY;
	actorHandle.sprite.depthZ = depthZ;
	actorHandle.sprite.sample = sample;

	m_actorHandle = actorHandle;
	m_actor->Initialize(renderer, &m_actorHandle);

	m_fontObj = m_renderer->CreateFontObject(fontFamilyName, 12);
	m_texture = m_renderer->CreateDynamicTexture(width, height, "Font");
	m_img = (uint8*)malloc(width * height * 4);

	return true;

}

void TextUI::Update(const wchar_t* contents)
{
	uint32 strLen = static_cast<uint32>(wcslen(contents));
	int32 texWidth = 0;
	int32 texHeight = 0;

	if (wcscmp(m_contents, contents))
	{
		memset(m_img, 0, m_actorHandle.sprite.width * m_actorHandle.sprite.height * 4);
		m_renderer->WriteTextToBitmap(m_img, m_actorHandle.sprite.width, m_actorHandle.sprite.height, m_actorHandle.sprite.width * 4, &texWidth, &texHeight, m_fontObj, contents, strLen, FONT_COLOR_TYPE::SPRING_GREEN);
		m_renderer->UpdateTextureWidthImage(m_texture, m_img, m_actorHandle.sprite.width, m_actorHandle.sprite.height);
		m_actor->SetTexture(m_texture);
		wcscpy_s(m_contents, contents);
	}
}

void TextUI::Render()
{
	// ====================
	// WWARNING!!!
	// ====================
	// 같은 sprite obj 에 대해서 멀티쓰레드 렌더링을 시도할 경우 플리커링 현상이 발생한다.
	m_actor->Render();
}

void TextUI::CleanUp()
{
	if (m_img)
	{
		free(m_img);
		m_img = nullptr;
	}
	if (m_texture)
	{
		m_renderer->DestroyTexture(m_texture);
		m_texture = nullptr;
	}
	if (m_fontObj)
	{
		m_renderer->DestroyFontObject(m_fontObj);
		m_fontObj = nullptr;
	}
	if (m_actor)
	{
		delete m_actor;
		m_actor = nullptr;
	}
}
