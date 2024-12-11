#include "pch.h"
#include "Application.h"

extern "C" { __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001; }
// D3D12 Agility SDK Runtime
extern "C" { __declspec(dllexport) extern const UINT D3D12SDKVersion = 614; }
#if defined(_M_AMD64)
extern "C" { __declspec(dllexport) extern const char* D3D12SDKPath = u8".\\D3D12\\"; }
#endif

/*
==============
Main entry
==============
*/

int main(int argc, char* argv[])
{
#ifdef _DEBUG
	int32 flags = _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF;
	_CrtSetDbgFlag(flags);
#endif

	Application* app = new Application;
	if (!app->Initialize(true, true)) // app->Initialize(false, false)
	{
		return -1;
	}

	int32 exitCode = app->RunApplication(); // success return code : 999
	app->CleanUp();
	delete app;

#ifdef _DEBUG
	_ASSERT(_CrtCheckMemory());
#endif

	return exitCode;
}
