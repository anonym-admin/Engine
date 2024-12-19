#pragma once

#ifdef _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#include <crtdbg.h>
	#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

// run time lib.
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

// my lib.
#include "../../Common/MeshData.h"
#include "../../Common/EngineType.h"
#include "../../CommonLib/CommonLib/LinkedList.h"
#include "../../CommonLib/CommonLib/HashTable.h"
#include "../../CommonLib/CommonLib/GenericUtils.h"
#include "../../Interface/IT_EngineCore.h"




