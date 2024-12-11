#include "pch.h"
#include "GeometryGenerator.h"

/*
===================
Geometry Generator
===================
*/

MESH_GROUP_HANDLE* GeometryGenerator::MakeTriagle()
{
	MESH_GROUP_HANDLE* meshGroup = new MESH_GROUP_HANDLE;

	uint32 numMeshes = 1;
	meshGroup->meshes = new MeshData[numMeshes];
	meshGroup->numMeshes = numMeshes;

	// src
	MeshData* srcData = new MeshData[numMeshes];
	srcData->numVertices = 3;
	srcData->numIndices = 3;
	srcData->vertices = new Vertex[srcData->numVertices];
	srcData->indices = new uint32[srcData->numIndices];

	srcData->vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
	srcData->vertices[1].position = Vector3(0.0f, 0.5f, 0.0f);
	srcData->vertices[2].position = Vector3(0.5f, -0.5f, 0.0f);
	srcData->vertices[0].normal = Vector3(0.0f, -1.0f, 0.0f);
	srcData->vertices[1].normal = Vector3(0.0f, -1.0f, 0.0f);
	srcData->vertices[2].normal = Vector3(0.0f, -1.0f, 0.0f);
	srcData->vertices[0].texCoord = Vector2(0.0f, 1.0f);
	srcData->vertices[1].texCoord = Vector2(0.5f, 0.5f);
	srcData->vertices[2].texCoord = Vector2(1.0f, 1.0f);

	srcData->indices[0] = 0;
	srcData->indices[1] = 1;
	srcData->indices[2] = 2;

	MeshData* destData = meshGroup->meshes;
	memcpy(destData, srcData, sizeof(MeshData) * meshGroup->numMeshes);

	delete[] srcData;
	srcData = nullptr;

	return meshGroup;
}

MESH_GROUP_HANDLE* GeometryGenerator::MakeSquare()
{
	MESH_GROUP_HANDLE* meshGroup = new MESH_GROUP_HANDLE;
	uint32 numMeshes = 1;
	meshGroup->meshes = new MeshData[numMeshes];
	meshGroup->numMeshes = numMeshes;

	// src
	MeshData* srcData = new MeshData[numMeshes];
	srcData->numVertices = 4;
	srcData->numIndices = 6;
	srcData->vertices = new Vertex[srcData->numVertices];
	srcData->indices = new uint32[srcData->numIndices];

	srcData->vertices[0].position = Vector3(-1.0f, 1.0f, 0.0f);
	srcData->vertices[1].position = Vector3(1.0f, 1.0f, 0.0f);
	srcData->vertices[2].position = Vector3(1.0f, -1.0f, 0.0f);
	srcData->vertices[3].position = Vector3(-1.0f, -1.0f, 0.0f);
	srcData->vertices[0].normal = Vector3(0.0f, 0.0f, -1.0f);
	srcData->vertices[1].normal = Vector3(0.0f, 0.0f, -1.0f);
	srcData->vertices[2].normal = Vector3(0.0f, 0.0f, -1.0f);
	srcData->vertices[3].normal = Vector3(0.0f, 0.0f, -1.0f);
	srcData->vertices[0].texCoord = Vector2(0.0f, 0.0f);
	srcData->vertices[1].texCoord = Vector2(1.0f, 0.0f);
	srcData->vertices[2].texCoord = Vector2(1.0f, 1.0f);
	srcData->vertices[3].texCoord = Vector2(0.0f, 1.0f);

	srcData->indices[0] = 0;
	srcData->indices[1] = 1;
	srcData->indices[2] = 2;
	srcData->indices[3] = 0;
	srcData->indices[4] = 2;
	srcData->indices[5] = 3;

	MeshData* destData = meshGroup->meshes;
	memcpy(destData, srcData, sizeof(MeshData) * meshGroup->numMeshes);

	delete[] srcData;
	srcData = nullptr;

	return meshGroup;
}

MESH_GROUP_HANDLE* GeometryGenerator::MakeCube()
{
	MESH_GROUP_HANDLE* meshGroup = new MESH_GROUP_HANDLE;
	uint32 numMeshes = 6;
	meshGroup->meshes = new MeshData[numMeshes];
	meshGroup->numMeshes = numMeshes;

	// src
	MeshData* srcData = new MeshData[numMeshes];
	for (uint32 i = 0; i < numMeshes; i++)
	{
		srcData[i].numVertices = 4;
		srcData[i].numIndices = 6;
		srcData[i].vertices = new Vertex[srcData[i].numVertices];
		srcData[i].indices = new uint32[srcData[i].numIndices];
	}

	// À­¸é
	srcData[0].vertices[0].position = Vector3(-1.0f, 1.0f, -1.0f);
	srcData[0].vertices[1].position = Vector3(-1.0f, 1.0f, 1.0f);
	srcData[0].vertices[2].position = Vector3(1.0f, 1.0f, 1.0f);
	srcData[0].vertices[3].position = Vector3(1.0f, 1.0f, -1.0f);
	srcData[0].vertices[0].normal = Vector3(0.0f, 1.0f, 0.0f);
	srcData[0].vertices[1].normal = Vector3(0.0f, 1.0f, 0.0f);
	srcData[0].vertices[2].normal = Vector3(0.0f, 1.0f, 0.0f);
	srcData[0].vertices[3].normal = Vector3(0.0f, 1.0f, 0.0f);
	srcData[0].vertices[0].texCoord = Vector2(0.0f, 0.0f);
	srcData[0].vertices[1].texCoord = Vector2(1.0f, 0.0f);
	srcData[0].vertices[2].texCoord = Vector2(1.0f, 1.0f);
	srcData[0].vertices[3].texCoord = Vector2(0.0f, 1.0f);
	// ¾Æ·§¸é
	srcData[1].vertices[0].position = Vector3(-1.0f, -1.0f, -1.0f);
	srcData[1].vertices[1].position = Vector3(1.0f, -1.0f, -1.0f);
	srcData[1].vertices[2].position = Vector3(1.0f, -1.0f, 1.0f);
	srcData[1].vertices[3].position = Vector3(-1.0f, -1.0f, 1.0f);
	srcData[1].vertices[0].normal = Vector3(0.0f, -1.0f, 0.0f);
	srcData[1].vertices[1].normal = Vector3(0.0f, -1.0f, 0.0f);
	srcData[1].vertices[2].normal = Vector3(0.0f, -1.0f, 0.0f);
	srcData[1].vertices[3].normal = Vector3(0.0f, -1.0f, 0.0f);
	srcData[1].vertices[0].texCoord = Vector2(0.0f, 0.0f);
	srcData[1].vertices[1].texCoord = Vector2(1.0f, 0.0f);
	srcData[1].vertices[2].texCoord = Vector2(1.0f, 1.0f);
	srcData[1].vertices[3].texCoord = Vector2(0.0f, 1.0f);
	// ¾Õ¸é
	srcData[2].vertices[0].position = Vector3(-1.0f, -1.0f, -1.0f);
	srcData[2].vertices[1].position = Vector3(-1.0f, 1.0f, -1.0f);
	srcData[2].vertices[2].position = Vector3(1.0f, 1.0f, -1.0f);
	srcData[2].vertices[3].position = Vector3(1.0f, -1.0f, -1.0f);
	srcData[2].vertices[0].normal = Vector3(0.0f, 0.0f, -1.0f);
	srcData[2].vertices[1].normal = Vector3(0.0f, 0.0f, -1.0f);
	srcData[2].vertices[2].normal = Vector3(0.0f, 0.0f, -1.0f);
	srcData[2].vertices[3].normal = Vector3(0.0f, 0.0f, -1.0f);
	srcData[2].vertices[0].texCoord = Vector2(0.0f, 0.0f);
	srcData[2].vertices[1].texCoord = Vector2(1.0f, 0.0f);
	srcData[2].vertices[2].texCoord = Vector2(1.0f, 1.0f);
	srcData[2].vertices[3].texCoord = Vector2(0.0f, 1.0f);
	// µÞ¸é
	srcData[3].vertices[0].position = Vector3(-1.0f, -1.0f, 1.0f);
	srcData[3].vertices[1].position = Vector3(1.0f, -1.0f, 1.0f);
	srcData[3].vertices[2].position = Vector3(1.0f, 1.0f, 1.0f);
	srcData[3].vertices[3].position = Vector3(-1.0f, 1.0f, 1.0f);
	srcData[3].vertices[0].normal = Vector3(0.0f, 0.0f, 1.0f);
	srcData[3].vertices[1].normal = Vector3(0.0f, 0.0f, 1.0f);
	srcData[3].vertices[2].normal = Vector3(0.0f, 0.0f, 1.0f);
	srcData[3].vertices[3].normal = Vector3(0.0f, 0.0f, 1.0f);
	srcData[3].vertices[0].texCoord = Vector2(0.0f, 0.0f);
	srcData[3].vertices[1].texCoord = Vector2(1.0f, 0.0f);
	srcData[3].vertices[2].texCoord = Vector2(1.0f, 1.0f);
	srcData[3].vertices[3].texCoord = Vector2(0.0f, 1.0f);
	// ¿ÞÂÊ
	srcData[4].vertices[0].position = Vector3(-1.0f, -1.0f, 1.0f);
	srcData[4].vertices[1].position = Vector3(-1.0f, 1.0f, 1.0f);
	srcData[4].vertices[2].position = Vector3(-1.0f, 1.0f, -1.0f);
	srcData[4].vertices[3].position = Vector3(-1.0f, -1.0f, -1.0f);
	srcData[4].vertices[0].normal = Vector3(-1.0f, 0.0f, 0.0f);
	srcData[4].vertices[1].normal = Vector3(-1.0f, 0.0f, 0.0f);
	srcData[4].vertices[2].normal = Vector3(-1.0f, 0.0f, 0.0f);
	srcData[4].vertices[3].normal = Vector3(-1.0f, 0.0f, 0.0f);
	srcData[4].vertices[0].texCoord = Vector2(0.0f, 0.0f);
	srcData[4].vertices[1].texCoord = Vector2(1.0f, 0.0f);
	srcData[4].vertices[2].texCoord = Vector2(1.0f, 1.0f);
	srcData[4].vertices[3].texCoord = Vector2(0.0f, 1.0f);
	// ¿À¸¥ÂÊ
	srcData[5].vertices[0].position = Vector3(1.0f, -1.0f, 1.0f);
	srcData[5].vertices[1].position = Vector3(1.0f, -1.0f, -1.0f);
	srcData[5].vertices[2].position = Vector3(1.0f, 1.0f, -1.0f);
	srcData[5].vertices[3].position = Vector3(1.0f, 1.0f, 1.0f);
	srcData[5].vertices[0].normal = Vector3(1.0f, 0.0f, 0.0f);
	srcData[5].vertices[1].normal = Vector3(1.0f, 0.0f, 0.0f);
	srcData[5].vertices[2].normal = Vector3(1.0f, 0.0f, 0.0f);
	srcData[5].vertices[3].normal = Vector3(1.0f, 0.0f, 0.0f);
	srcData[5].vertices[0].texCoord = Vector2(0.0f, 0.0f);
	srcData[5].vertices[1].texCoord = Vector2(1.0f, 0.0f);
	srcData[5].vertices[2].texCoord = Vector2(1.0f, 1.0f);
	srcData[5].vertices[3].texCoord = Vector2(0.0f, 1.0f);

	uint32 idx = 0;
	srcData[0].indices[idx++] = 0; srcData[0].indices[idx++] = 1; srcData[0].indices[idx++] = 2; srcData[0].indices[idx++] = 0; srcData[0].indices[idx++] = 2; srcData[0].indices[idx++] = 3;
	idx = 0;
	srcData[1].indices[idx++] = 0; srcData[1].indices[idx++] = 1; srcData[1].indices[idx++] = 2; srcData[1].indices[idx++] = 0; srcData[1].indices[idx++] = 2; srcData[1].indices[idx++] = 3;
	idx = 0;
	srcData[2].indices[idx++] = 0; srcData[2].indices[idx++] = 1; srcData[2].indices[idx++] = 2; srcData[2].indices[idx++] = 0; srcData[2].indices[idx++] = 2; srcData[2].indices[idx++] = 3;
	idx = 0;
	srcData[3].indices[idx++] = 0; srcData[3].indices[idx++] = 1; srcData[3].indices[idx++] = 2; srcData[3].indices[idx++] = 0; srcData[3].indices[idx++] = 2; srcData[3].indices[idx++] = 3;
	idx = 0;
	srcData[4].indices[idx++] = 0; srcData[4].indices[idx++] = 1; srcData[4].indices[idx++] = 2; srcData[4].indices[idx++] = 0; srcData[4].indices[idx++] = 2; srcData[4].indices[idx++] = 3;
	idx = 0;
	srcData[5].indices[idx++] = 0; srcData[5].indices[idx++] = 1; srcData[5].indices[idx++] = 2; srcData[5].indices[idx++] = 0; srcData[5].indices[idx++] = 2; srcData[5].indices[idx++] = 3;

	MeshData* destData = meshGroup->meshes;

	for (uint32 i = 0; i < numMeshes; i++)
	{
		memcpy(destData + i, srcData + i, sizeof(MeshData));
	}

	delete[] srcData;
	srcData = nullptr;

	return meshGroup;
}

void GeometryGenerator::DestroyGeometry(MESH_GROUP_HANDLE* mgHandle)
{
	if (mgHandle)
	{
		MeshData* meshes = mgHandle->meshes;
		if (meshes)
		{
			for (uint32 i = 0; i < mgHandle->numMeshes; i++)
			{
				Vertex* vertices = meshes[i].vertices;
				uint32* indices = meshes[i].indices;
				if (vertices)
				{
					delete[] vertices;
				}
				if (indices)
				{
					delete[] indices;
				}
			}
			delete[] meshes;
		}
		delete mgHandle;
	}
}
