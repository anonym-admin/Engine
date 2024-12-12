#pragma once

#ifdef _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#include <crtdbg.h>
	#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#include <stdio.h>
#include <windows.h>





#include "../../Common/MeshData.h"
#include "LinkedList.h"