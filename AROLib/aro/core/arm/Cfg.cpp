#include <aro/core/arm/Cfg.hpp>

//Defines the entry point for the DLL application.
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	   case DLL_PROCESS_DETACH:
	   case DLL_PROCESS_ATTACH:
	   case DLL_THREAD_ATTACH:
	   case DLL_THREAD_DETACH:
		break;
	}

	return TRUE;
}
