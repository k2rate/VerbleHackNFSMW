#pragma once

#include "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include/d3dx9.h"

namespace d3dresloader
{
	void __cdecl texture(UINT Width, UINT Height, const char FileName[64], LPDIRECT3DTEXTURE9* ppTexOut);
	void __cdecl font(UINT Width, UINT Height, UINT Weight, const char NameStr[64], LPD3DXFONT *ppFontOut);
	void __cdecl sprite(LPD3DXSPRITE *ppSpriteOut);
}