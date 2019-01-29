#pragma once

#include <Windows.h>

void RegisterIUnknown(IUnknown *iu);

namespace dllresource
{
	extern HMODULE Module;
	extern DWORD ThreadId;
	extern IUnknown* ReleaseData[256];
}