#include "core.h"

bool stop_present = false;
bool is_stopped = false;

void(*present_call)(IDirect3DDevice9*);

typedef HRESULT(__stdcall *PRESENT9)(IDirect3DDevice9*, CONST RECT*, CONST RECT*, HWND, CONST RGNDATA*);
PRESENT9 present_ptr;
BYTE present_code_fragment[5] /* first 5 original bytes in present */, 
present_code_jmp[5] /* first 5 my bytes in present */;

typedef HRESULT(__stdcall *RESET9)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
RESET9 reset_ptr;
BYTE reset_code_fragment[5] /* first 5 original bytes in reset */,
reset_code_jmp[5] /* first 5 my bytes in reset */;

using namespace core;


#pragma region Present

HRESULT __stdcall hkPresent(IDirect3DDevice9* dev, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion)
{
	BYTE* codeDest = (BYTE*)present_ptr;

	*(BYTE*)(codeDest + 0) = *(BYTE*)(present_code_fragment + 0);
	*(DWORD*)(codeDest + 1) = *(DWORD*)(present_code_fragment + 1);
	
	present_call(dev);
	
	HRESULT hr = present_ptr(dev, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);

	if (stop_present) {
		is_stopped = true;
		while (stop_present) {
			Sleep(5);
		} is_stopped = false;
	}
	
	*(BYTE*)(codeDest + 0) = *(BYTE*)(present_code_jmp + 0);
	*(DWORD*)(codeDest + 1) = *(DWORD*)(present_code_jmp + 1);

	return hr;
}

void HookPresent()
{
	*(BYTE *)(present_code_jmp + 0x0) = 0xE9;
	*(DWORD*)(present_code_jmp + 0x1) = (DWORD)hkPresent - (DWORD)present_ptr - 5;

	DWORD saved_protection;
	VirtualProtect(present_ptr, 8, PAGE_EXECUTE_READWRITE, &saved_protection);

	memcpy(present_code_fragment, present_ptr, 5);
	memcpy(present_ptr, present_code_jmp, 5);
}

VOID d3d9hook::BreakPresent() {
	stop_present = true;
	while (is_stopped == false)
		Sleep(5); 
}

VOID d3d9hook::UnBreakPresent() {
	stop_present = false;
	while (is_stopped == true)
		Sleep(5);
}

IDirect3DDevice9 **ppDevBuffer = NULL;
void(*old_present_call)(IDirect3DDevice9*);

VOID d3d9hook::FunctionForFuckGetOffDeviceOfPresent(IDirect3DDevice9 *pInDev) {
	*ppDevBuffer = pInDev;
	present_call = old_present_call;
}

VOID d3d9hook::GetDevice(IDirect3DDevice9 **ppOutDev) {
	ppDevBuffer = ppOutDev;
	old_present_call = present_call;
	present_call = FunctionForFuckGetOffDeviceOfPresent;
	while (present_call == FunctionForFuckGetOffDeviceOfPresent) 
		Sleep(5);
}

#pragma endregion

#pragma region Reset
HRESULT __stdcall hkReset(IDirect3DDevice9* dev, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	return 0;
}

void HookReset()
{
	*(BYTE *)(reset_code_jmp + 0x0) = 0xE9;
	*(DWORD*)(reset_code_jmp + 0x1) = (DWORD)hkReset - (DWORD)reset_ptr - 5;

	DWORD saved_protection;
	VirtualProtect(reset_ptr, 8, PAGE_EXECUTE_READWRITE, &saved_protection);

	memcpy(reset_code_fragment, reset_ptr, 5);
	memcpy(reset_ptr, reset_code_jmp, 5);
}
#pragma endregion

void GetDeviceData()
{
	HRESULT hr;

	IDirect3D9* d3d9_t = Direct3DCreate9(D3D_SDK_VERSION); // _t - temp
	if (d3d9_t == NULL) 
	{ 
		ErrorMessage("Direct3DCreate9 in d3d9hook returned NULL\n" 
			"1) try install directx\n"
			"2) try install c++ libraries 2005-2017 x86 - x64\n"
			"3) remove d3d9.dll in game folder"); 
	}

	D3DDISPLAYMODE dm;
	hr = d3d9_t->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &dm);
	if (FAILED(hr)) { 
		ErrorMessage("IDirect3D9::GetAdapterDisplayMode FAILED :("); 
	}

	D3DPRESENT_PARAMETERS pp;
	ZeroMemory(&pp, sizeof(pp));
	pp.BackBufferFormat = dm.Format;
	pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	pp.Windowed = TRUE;

	HWND hWnd = CreateWindow("STATIC", ".", 0, 0, 0, 0, 0, 0, 0, 0, 0);
	if (hWnd == NULL) { 
		ErrorMessage("CreateWindow returned NULL, pzdc"); 
	}

	IDirect3DDevice9* dev_t;
	hr = d3d9_t->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &pp, &dev_t);
	if (FAILED(hr)) { 
		ErrorMessage("IDirect3D9::CreateDevice FAILED :("); 
	}
	DWORD* vtablePtr = *(DWORD**)dev_t;
	if (vtablePtr == nullptr) { 
		ErrorMessage("vtablePtr == nullptr :("); 
	}
	
	present_ptr = (PRESENT9)vtablePtr[17];
	reset_ptr = (RESET9)vtablePtr[16];

	dev_t->Release();
	d3d9_t->Release();

	DestroyWindow(hWnd);
}

void d3d9hook::SetStartAddress(void(*startAddress)(IDirect3DDevice9*)) 
{ 
	present_call = startAddress; 
}

void d3d9hook::Start() 
{ 
	GetDeviceData(); 
	HookPresent(); 
	HookReset();
}