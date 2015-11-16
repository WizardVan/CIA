// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"



inline IBaseVerify::~IBaseVerify() {}
typedef char* (*_NxModule_GetType)();
typedef IBaseVerify* (*_NxVerify_GetInterface)();
IBaseVerify* pCV;
_NxModule_GetType NxModule_GetType;
_NxVerify_GetInterface NxVerify_GetInterface;



BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		HMODULE hVDLL;
		hVDLL = LoadLibrary(TEXT("NxVerify.dll"));
		if (hVDLL == NULL)return FALSE;
		NxModule_GetType = (_NxModule_GetType)GetProcAddress(hVDLL, "NxModule_GetType");
		if (NxModule_GetType == NULL)return FALSE;
		NxVerify_GetInterface = (_NxVerify_GetInterface)GetProcAddress(hVDLL, "NxVerify_GetInterface");
		if (NxVerify_GetInterface == NULL)return FALSE;
		//printf("0x%08X\n", GetProcAddress(hVDLL, "des2key"));
		pCV = NxVerify_GetInterface();
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

