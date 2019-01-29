#include "dllmain.h"
#include "core.h"

HMODULE dllresource::Module;
DWORD dllresource::ThreadId;
IUnknown* dllresource::ReleaseData[256];

void RegisterIUnknown(IUnknown *iu)
{
	static byte iu_count = 0;
	dllresource::ReleaseData[iu_count] = iu;
	iu_count++;
}

void __cdecl initializing(); // from functions.cpp

void InitializingVerblehack(void *lpParam)
{
	core::Initializing();
	initializing();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwParam, LPVOID lpReserved)
{
	switch (dwParam)
	{
	case DLL_PROCESS_DETACH:
		
		for (int i = 0; i < 256; i++)
		{
			if (dllresource::ReleaseData[i] != nullptr)
			{
				dllresource::ReleaseData[i]->Release();
			}
			else
			{
				break;
			}
		}
		
		break;
	case DLL_PROCESS_ATTACH:

		dllresource::Module = hModule;
		dllresource::ThreadId = GetCurrentThreadId();

		ZeroMemory(dllresource::ReleaseData, sizeof(dllresource::ReleaseData));
		
		Thread(InitializingVerblehack);
	
		break;
	case DLL_THREAD_ATTACH:
		
		break;
	case DLL_THREAD_DETACH:
		
		break;
	}

	return TRUE;
}