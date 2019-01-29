#pragma once

#include "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include/d3dx9.h"

namespace messagebox
{
	void Draw(LPDIRECT3DDEVICE9);
	void Proc();
	void LMBProc();
	void Init(IDirect3DDevice9 *pDev);
	void CreateGetValue(void* valueptr, const char* title, v_type valuetype, bool usecall);
	void Terminate();
}