#pragma once

/*
===================
Geometry Generator
===================
*/

class GeometryGenerator
{
public:
	static MESH_GROUP_HANDLE* MakeTriagle();
	static MESH_GROUP_HANDLE* MakeSquare(const float scale = 1.0f);
	static MESH_GROUP_HANDLE* MakeCube(const float scale = 1.0f);

	static void DestroyGeometry(MESH_GROUP_HANDLE* mgHandle);
};

