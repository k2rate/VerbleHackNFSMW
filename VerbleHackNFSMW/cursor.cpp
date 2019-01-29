#include "core.h"

#pragma comment(lib,"C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x86/d3dx9.lib")

using namespace core;

POINT posBuffer;
D3DXVECTOR3 cursor::pos;

LPDIRECT3DTEXTURE9 cursorTex;
LPD3DXSPRITE cursorSprite;

VOID cursor::Draw(IDirect3DDevice9 *dev)
{
	GetCursorPos(&posBuffer);
	pos.x = posBuffer.x;
	pos.y = posBuffer.y;
	
	cursorSprite->Begin(D3DXSPRITE_ALPHABLEND);
	cursorSprite->Draw(cursorTex, 0, 0, &pos, 0xFFFFFFFF);
	cursorSprite->End();
}

VOID cursor::Initializing(IDirect3DDevice9 *pDev)
{
	cursorSprite = MyD3DXCreateSprite(pDev);
	cursorTex = MyD3DXCreateTextureFromFileEx(pDev, "verblehack\\cursor.png", 25 * xm, 25 * ym, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL);
}

bool __fastcall cursor::in_object_prop(D3DXVECTOR3* vectorpos, float size) {
	if (pos.x > vectorpos->x && pos.x < vectorpos->x + size && pos.y > vectorpos->y && pos.y < vectorpos->y + size)
		return true;
	return false;
}
bool __fastcall cursor::in_object(D3DXVECTOR3* vectorpos, float x, float y) {
	if (pos.x > vectorpos->x && pos.x < vectorpos->x + x && pos.y > vectorpos->y && pos.y < vectorpos->y + y)
		return true;
	return false;
}