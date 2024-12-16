#pragma once

#include "../../Common/Type.h"
#include "../../Common/MeshData.h"

/*
===========
EngineType
===========
*/

enum class ACTOR_TYPE
{
	MESH_OBJ,
	SPRITE_OBJ,
	LINE_OBJ,
};

struct ACTOR_MESH_HANDLE
{
	MESH_GROUP_HANDLE* geometry = nullptr;
	Vector3 pos = Vector3(0.0f);
	Vector3 scale = Vector3(0.0f);
};

struct ACTOR_SPRITE_HANDLE
{
	uint32 width = 0;
	uint32 height = 0;
	uint32 renderPosX = 0; 
	uint32 renderPosY = 0; 
	float scaleX = 1.0f;
	float scaleY = 1.0f;
	float depthZ = 0.0f;
	RECT* sample = nullptr;
};

struct ACTOR_LINE_HANDLE
{
	LineData* lineData = nullptr;
};

struct ACTOR_HANDLE
{
	ACTOR_TYPE type;
	union
	{
		ACTOR_MESH_HANDLE mesh;
		ACTOR_SPRITE_HANDLE sprite;
		ACTOR_LINE_HANDLE line;
	};
};