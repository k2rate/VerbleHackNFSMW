#pragma once

#include <Windows.h>
#include <Process.h>
#include <time.h>
#include <stdio.h>

#include "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include/d3dx9.h"
#include "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include/d3d9.h"


#pragma comment(lib,"C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x86/d3dx9.lib")
#pragma comment(lib,"C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x86/d3d9.lib")

#define Thread(x) _beginthread(x,0,0);
//CreateThread(0,0,(LPTHREAD_START_ROUTINE)x,0,0,0);

struct verble_loop_ex {
	void(*start_address);
	DWORD parameter;
};

namespace core
{
	void AddLoop(void*);
	void AddLoopEx(verble_loop_ex*);
	void AddMouseLoop(void*);
	void AddMouseLoopEx(verble_loop_ex*);
	void AddDirectX9Loop(void*);
	void AddDirectX9LoopEx(verble_loop_ex*);
	void FreeLoop(void*);
	void FreeLoopEx(verble_loop_ex*);
	void FreeMouseLoop(void*);
	void FreeMouseLoopEx(verble_loop_ex*);
	void FreeDirectX9Loop(void*);
	void FreeDirectX9LoopEx(verble_loop_ex*);

	void Initializing();

	namespace font
	{
		extern ID3DXFont *small_size, *medium_size, *big_size;

		namespace constdata
		{
			constexpr char configFilePath[] = "verblehack\\core\\font\\Memory.ini";
			constexpr char fontFilePath[] = "verblehack\\core\\font\\font.ttf";
			constexpr char defaultName[] = "Tahoma";
			constexpr char configBasicBlockName[] = "main";
		}

		VOID Initializing(IDirect3DDevice9 *pDev);
	}

	namespace cursor
	{
		extern D3DXVECTOR3 pos;

		bool __fastcall in_object_prop(D3DXVECTOR3* pos, float size);
		bool __fastcall in_object(D3DXVECTOR3* pos, float x, float y);

		VOID Draw(IDirect3DDevice9 *dev);
		VOID Initializing(IDirect3DDevice9 *pDev);
	}

	namespace d3d9hook
	{
		VOID BreakPresent();
		VOID UnBreakPresent();
		VOID FunctionForFuckGetOffDeviceOfPresent(IDirect3DDevice9 *pInDev);
		VOID GetDevice(IDirect3DDevice9 **ppOutDev);
		VOID SetStartAddress(void(*startAddress)(IDirect3DDevice9*));
		VOID Start();
	}
	
	namespace texture
	{
		namespace constdata
		{
			constexpr char freecolorPath[] = "verblehack\\textures\\freecolor.png";
		}
	}

	constexpr float xdefres = 1920.0;
	constexpr float ydefres = 1080.0;

	extern float xm;
	extern float ym;

	extern float res_x;
	extern float res_y;
}

void ErrorMessage(const char *_text);
void ErrorMessageWithLastError(const char *_text);
void ErrorMessageWithHexValue(const char *_text, DWORD HexValue);

#define _RECT(left,top,right,bottom){left,top,right,bottom}
struct BGRA { BYTE b, g, r, a; };

VOID MyD3DXSimpleFillTexture(IDirect3DTexture9 *pTex, D3DCOLOR Color);
VOID MyD3DXSimpleFillTextureWithShadow(IDirect3DTexture9 *pTex, D3DCOLOR Color, BYTE ShadowStrenght);
VOID MyD3DXBorderTexture(IDirect3DTexture9 *pTex, D3DCOLOR Color, DWORD BorderSize);
VOID MyD3DXBorderTextureWithShadow(IDirect3DTexture9 *pTex, D3DCOLOR Color, DWORD BorderSize, BYTE ShadowStrenght);
VOID MyD3DXFillTextureRect(IDirect3DTexture9 *pTex, D3DCOLOR Color, RECT *pRect);
VOID MyD3DXFillTextureRectWithShadow(IDirect3DTexture9 *pTex, D3DCOLOR Color, RECT *pRect, BYTE ShadowStrenght);
VOID MyD3DXFillTextureAlpha(IDirect3DTexture9 *pTex, BYTE Alpha);
VOID MyD3DXFillTextureNoAlpha(IDirect3DTexture9 *pTex, D3DCOLOR ColorRGB);

ID3DXSprite* MyD3DXCreateSprite(LPDIRECT3DDEVICE9 pDevice);

IDirect3DTexture9* MyD3DXCreateTexture(LPDIRECT3DDEVICE9 pDevice, UINT Width, UINT Height, UINT MipLevels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool);
IDirect3DTexture9* MyD3DXCreateTextureFromFileEx(LPDIRECT3DDEVICE9 pDevice, LPCSTR pSrcFile, UINT Width, UINT Height, UINT MipLevels,
	DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, DWORD Filter, DWORD MipFilter,
	D3DCOLOR ColorKey, D3DXIMAGE_INFO* pSrcInfo, PALETTEENTRY* Palette);

ID3DXFont* MyD3DXCreateFont(LPDIRECT3DDEVICE9 pDevice, INT Height, UINT Width, UINT Weight, UINT MipLevels,
	BOOL Italic, DWORD CharSet, DWORD OutputPrecision, DWORD Quality, DWORD PitchAndFamily, LPCSTR pFaceName);

VOID MyGDIBorderedTexture(IDirect3DTexture9 *pTex, DWORD BorderSize, COLORREF Color, COLORREF BorderColor);
