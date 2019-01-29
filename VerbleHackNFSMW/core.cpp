#include "core.h"

#pragma comment(lib,"C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x86/d3dx9.lib")

using namespace core;

void *pvl[64]; DWORD pvl_count = 0;
verble_loop_ex *pvlex[64]; DWORD pvlex_count = 0;
void *pmvl[64]; DWORD pmvl_count = 0;
verble_loop_ex *pmvlex[64]; DWORD pmvlex_count = 0;
void *pd9vl[64]; DWORD pd9vl_count = 0;
verble_loop_ex *pd9vlex[64]; DWORD pd9vlex_count = 0;

void core::AddLoop(void *_pvl) { pvl[pvl_count] = _pvl; pvl_count++; }
void core::FreeLoop(void *_pvl) {
	for (register DWORD i = 0; i < pvl_count; i++) {
		if (pvl[i] == _pvl) {
			pvl_count--; pvl[i] = pvl[pvl_count];
			return;
		}
	}
}
void core::AddLoopEx(verble_loop_ex *_pvlex) { pvlex[pvlex_count] = _pvlex; pvlex_count++; }
void core::FreeLoopEx(verble_loop_ex *_pvlex) {
	for (register DWORD i = 0; i < pvlex_count; i++) {
		if (pvlex[i] == _pvlex) {
			pvlex_count--; pvlex[i] = pvlex[pvlex_count];
			return;
		}
	}
}
void LoopProcess(void*) {
	while (true) 
	{
		for (register DWORD i = pvl_count; i != 0; i--) { ((void(*)())pvl[i-1])(); }
		for (register DWORD i = pvlex_count; i != 0; i--) { ((void(*)(DWORD))pvlex[i-1]->start_address)(pvlex[i-1]->parameter); }
		Sleep(5);
	}
}
void core::AddMouseLoop(void *_pmvl) { pmvl[pmvl_count] = _pmvl; pmvl_count++; }
void core::FreeMouseLoop(void *_pmvl) {
	for (register DWORD i = 0; i < pmvl_count; i++) {
		if (pmvl[i] == _pmvl) {
			pmvl_count--; pmvl[i] = pmvl[pmvl_count];
			return;
		}
	}
}
void core::AddMouseLoopEx(verble_loop_ex *_pmvlex) { pmvlex[pmvlex_count] = _pmvlex; pmvlex_count++; }
void core::FreeMouseLoopEx(verble_loop_ex *_pmvlex) {
	for (register DWORD i = 0; i < pmvlex_count; i++) {
		if (pmvlex[i] == _pmvlex) {
			pmvlex_count--; pmvlex[i] = pmvlex[pmvlex_count];
			return;
		}
	}
}
void MouseLoopProcess(void*) {
	while (true) {
		if (GetAsyncKeyState(VK_LBUTTON)) {
			for (register DWORD i = 0; i < pmvl_count; i++) { ((void(*)())pmvl[i])(); }
			for (register DWORD i = 0; i < pmvlex_count; i++) { ((void(*)(DWORD))pmvlex[i]->start_address)(pmvlex[i]->parameter); }
		} Sleep(5);
	}
}
void core::AddDirectX9Loop(void *_pd9vl) { pd9vl[pd9vl_count] = _pd9vl; pd9vl_count++; }
void core::FreeDirectX9Loop(void *_pd9vl) {
	for (register DWORD i = 0; i < pd9vl_count; i++) {
		if (pd9vl[i] == _pd9vl) {
			pd9vl_count--; pd9vl[i] = pd9vl[pd9vl_count];
			return;
		}
	}
}
void core::AddDirectX9LoopEx(verble_loop_ex *_pd9vlex) { pd9vlex[pd9vlex_count] = _pd9vlex; pd9vlex_count++; }
void core::FreeDirectX9LoopEx(verble_loop_ex *_pd9vlex) {
	for (register DWORD i = 0; i < pd9vlex_count; i++) {
		if (pd9vlex[i] == _pd9vlex) {
			pd9vlex_count--; pd9vlex[i] = pd9vlex[pd9vlex_count];
			return;
		}
	}
}
void DirectX9LoopProcess(IDirect3DDevice9 *dev) {
	for (register DWORD i = 0; i < pd9vl_count; i++) { ((void(*)(IDirect3DDevice9*))pd9vl[i])(dev); }
	for (register DWORD i = 0; i < pd9vlex_count; i++) { ((void(*)(IDirect3DDevice9*, DWORD))pd9vlex[i]->start_address)(dev, pd9vlex[i]->parameter);  }
	if ((pd9vl_count + pd9vlex_count) != 0) { cursor::Draw(dev); }
}

float core::xm = 0, core::ym = 0,
core::res_x = 0, core::res_y = 0;


void __cdecl core::Initializing()
{
	res_x = (float)GetSystemMetrics(SM_CXSCREEN), res_y = (float)GetSystemMetrics(SM_CYSCREEN);
	float y_prop = core::xdefres / core::ydefres;
	xm = res_x / core::xdefres, ym = (res_x / y_prop) / core::ydefres;
	
	float scale = 0.0f;
	char string_ret[50];
	GetPrivateProfileStringA("main", "scale", 0, string_ret, 50, "verblehack/core/scale.ini");
	scale = atof(string_ret);
	xm *= scale;
	ym *= scale;

	d3d9hook::SetStartAddress(DirectX9LoopProcess);
	d3d9hook::Start();

	IDirect3DDevice9 *pDev;
	d3d9hook::GetDevice(&pDev);
	d3d9hook::BreakPresent();

	cursor::Initializing(pDev);
	font::Initializing(pDev);

	d3d9hook::UnBreakPresent();

	Thread(LoopProcess);
	Thread(MouseLoopProcess);
}