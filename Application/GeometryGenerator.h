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
	static MESH_GROUP_HANDLE* MakeSquare();
	static MESH_GROUP_HANDLE* MakeCube();

	static void DestroyGeometry(MESH_GROUP_HANDLE* mgHandle);
};

