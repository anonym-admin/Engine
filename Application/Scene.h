#pragma once

/*
==========
Scene
==========
*/

class Scene
{
public:
	Scene();
	virtual ~Scene() = 0;

	bool Initialize();
	virtual void BeginScene() = 0;
	virtual void EndScene() = 0;
	virtual void Update(const float dt) = 0;
	virtual void Render() = 0;
	void SetName(const wchar_t* name);
	const wchar_t* GetName();

private:
	void CleanUp();

private:
	wchar_t m_sceneName[32] = {};
};

