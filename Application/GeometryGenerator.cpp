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
	uint32 numMeshes = 1;
	meshGroup->meshes = new MeshData[numMeshes];
	meshGroup->numMeshes = numMeshes;

	// src
	MeshData* srcData = new MeshData[numMeshes];
	srcData->numVertices = 24;
	srcData->numIndices = 36;
	srcData->vertices = new Vertex[srcData->numVertices];
	srcData->indices = new uint32[srcData->numIndices];

	// À­¸é
	srcData->vertices[0].position = Vector3(-1.0f, 1.0f, -1.0f);
	srcData->vertices[1].position = Vector3(-1.0f, 1.0f, 1.0f);
	srcData->vertices[2].position = Vector3(1.0f, 1.0f, 1.0f);
	srcData->vertices[3].position = Vector3(1.0f, 1.0f, -1.0f);
	srcData->vertices[0].normal = Vector3(0.0f, 1.0f, 0.0f);
	srcData->vertices[1].normal = Vector3(0.0f, 1.0f, 0.0f);
	srcData->vertices[2].normal = Vector3(0.0f, 1.0f, 0.0f);
	srcData->vertices[3].normal = Vector3(0.0f, 1.0f, 0.0f);
	srcData->vertices[0].texCoord = Vector2(0.0f, 0.0f);
	srcData->vertices[1].texCoord = Vector2(1.0f, 0.0f);
	srcData->vertices[2].texCoord = Vector2(1.0f, 1.0f);
	srcData->vertices[3].texCoord = Vector2(0.0f, 1.0f);
	// ¾Æ·§¸é
	srcData->vertices[4].position = Vector3(-1.0f, -1.0f, -1.0f);
	srcData->vertices[5].position = Vector3(1.0f, -1.0f, -1.0f);
	srcData->vertices[6].position = Vector3(1.0f, -1.0f, 1.0f);
	srcData->vertices[7].position = Vector3(-1.0f, -1.0f, 1.0f);
	srcData->vertices[4].normal = Vector3(0.0f, -1.0f, 0.0f);
	srcData->vertices[5].normal = Vector3(0.0f, -1.0f, 0.0f);
	srcData->vertices[6].normal = Vector3(0.0f, -1.0f, 0.0f);
	srcData->vertices[7].normal = Vector3(0.0f, -1.0f, 0.0f);
	srcData->vertices[4].texCoord = Vector2(0.0f, 0.0f);
	srcData->vertices[5].texCoord = Vector2(1.0f, 0.0f);
	srcData->vertices[6].texCoord = Vector2(1.0f, 1.0f);
	srcData->vertices[7].texCoord = Vector2(0.0f, 1.0f);
	// ¾Õ¸é
	srcData->vertices[8].position = Vector3(-1.0f, -1.0f, -1.0f);
	srcData->vertices[9].position = Vector3(-1.0f, 1.0f, -1.0f);
	srcData->vertices[10].position = Vector3(1.0f, 1.0f, -1.0f);
	srcData->vertices[11].position = Vector3(1.0f, -1.0f, -1.0f);
	srcData->vertices[8].normal = Vector3(0.0f, 0.0f, -1.0f);
	srcData->vertices[9].normal = Vector3(0.0f, 0.0f, -1.0f);
	srcData->vertices[10].normal = Vector3(0.0f, 0.0f, -1.0f);
	srcData->vertices[11].normal = Vector3(0.0f, 0.0f, -1.0f);
	srcData->vertices[8].texCoord = Vector2(0.0f, 0.0f);
	srcData->vertices[9].texCoord = Vector2(1.0f, 0.0f);
	srcData->vertices[10].texCoord = Vector2(1.0f, 1.0f);
	srcData->vertices[11].texCoord = Vector2(0.0f, 1.0f);
	// µÞ¸é
	srcData->vertices[12].position = Vector3(-1.0f, -1.0f, 1.0f);
	srcData->vertices[13].position = Vector3(1.0f, -1.0f, 1.0f);
	srcData->vertices[14].position = Vector3(1.0f, 1.0f, 1.0f);
	srcData->vertices[15].position = Vector3(-1.0f, 1.0f, 1.0f);
	srcData->vertices[12].normal = Vector3(0.0f, 0.0f, 1.0f);
	srcData->vertices[13].normal = Vector3(0.0f, 0.0f, 1.0f);
	srcData->vertices[14].normal = Vector3(0.0f, 0.0f, 1.0f);
	srcData->vertices[15].normal = Vector3(0.0f, 0.0f, 1.0f);
	srcData->vertices[12].texCoord = Vector2(0.0f, 0.0f);
	srcData->vertices[13].texCoord = Vector2(1.0f, 0.0f);
	srcData->vertices[14].texCoord = Vector2(1.0f, 1.0f);
	srcData->vertices[15].texCoord = Vector2(0.0f, 1.0f);
	// ¿ÞÂÊ
	srcData->vertices[16].position = Vector3(-1.0f, -1.0f, 1.0f);
	srcData->vertices[17].position = Vector3(-1.0f, 1.0f, 1.0f);
	srcData->vertices[18].position = Vector3(-1.0f, 1.0f, -1.0f);
	srcData->vertices[19].position = Vector3(-1.0f, -1.0f, -1.0f);
	srcData->vertices[16].normal = Vector3(-1.0f, 0.0f, 0.0f);
	srcData->vertices[17].normal = Vector3(-1.0f, 0.0f, 0.0f);
	srcData->vertices[18].normal = Vector3(-1.0f, 0.0f, 0.0f);
	srcData->vertices[19].normal = Vector3(-1.0f, 0.0f, 0.0f);
	srcData->vertices[16].texCoord = Vector2(0.0f, 0.0f);
	srcData->vertices[17].texCoord = Vector2(1.0f, 0.0f);
	srcData->vertices[18].texCoord = Vector2(1.0f, 1.0f);
	srcData->vertices[19].texCoord = Vector2(0.0f, 1.0f);
	// ¿À¸¥ÂÊ
	srcData->vertices[20].position = Vector3(1.0f, -1.0f, 1.0f);
	srcData->vertices[21].position = Vector3(1.0f, -1.0f, -1.0f);
	srcData->vertices[22].position = Vector3(1.0f, 1.0f, -1.0f);
	srcData->vertices[23].position = Vector3(1.0f, 1.0f, 1.0f);
	srcData->vertices[20].normal = Vector3(1.0f, 0.0f, 0.0f);
	srcData->vertices[21].normal = Vector3(1.0f, 0.0f, 0.0f);
	srcData->vertices[22].normal = Vector3(1.0f, 0.0f, 0.0f);
	srcData->vertices[23].normal = Vector3(1.0f, 0.0f, 0.0f);
	srcData->vertices[20].texCoord = Vector2(0.0f, 0.0f);
	srcData->vertices[21].texCoord = Vector2(1.0f, 0.0f);
	srcData->vertices[22].texCoord = Vector2(1.0f, 1.0f);
	srcData->vertices[23].texCoord = Vector2(0.0f, 1.0f);

	uint32 idx = 0;
	srcData->indices[idx++] = 0; srcData->indices[idx++] = 1; srcData->indices[idx++] = 2; srcData->indices[idx++] = 0; srcData->indices[idx++] = 2; srcData->indices[idx++] = 3;
	srcData->indices[idx++] = 4; srcData->indices[idx++] = 5; srcData->indices[idx++] = 6; srcData->indices[idx++] = 4; srcData->indices[idx++] = 6; srcData->indices[idx++] = 7;
	srcData->indices[idx++] = 8; srcData->indices[idx++] = 9; srcData->indices[idx++] = 10; srcData->indices[idx++] = 8; srcData->indices[idx++] = 10; srcData->indices[idx++] = 11;
	srcData->indices[idx++] = 12; srcData->indices[idx++] = 13; srcData->indices[idx++] = 14; srcData->indices[idx++] = 12; srcData->indices[idx++] = 14; srcData->indices[idx++] = 15;
	srcData->indices[idx++] = 16; srcData->indices[idx++] = 17; srcData->indices[idx++] = 18; srcData->indices[idx++] = 16; srcData->indices[idx++] = 18; srcData->indices[idx++] = 19;
	srcData->indices[idx++] = 20; srcData->indices[idx++] = 21; srcData->indices[idx++] = 22; srcData->indices[idx++] = 20; srcData->indices[idx++] = 22; srcData->indices[idx++] = 23;

	MeshData* destData = meshGroup->meshes;
	memcpy(destData, srcData, sizeof(MeshData)* meshGroup->numMeshes);

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
