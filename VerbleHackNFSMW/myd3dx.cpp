#include "core.h"
#include "dllmain.h"

VOID MyD3DXSimpleFillTexture(IDirect3DTexture9 *pTex, D3DCOLOR Color)
{
	D3DSURFACE_DESC desc;
	pTex->GetLevelDesc(0, &desc);
	DWORD pixelCount = desc.Width * desc.Height;
	
	D3DLOCKED_RECT lr;
	pTex->LockRect(0, &lr, 0, D3DLOCK_DONOTWAIT);

	DWORD *pByte = (DWORD*)lr.pBits;

	for (register DWORD i = 0; i < pixelCount; i++) {
		pByte[i] = Color;
	}

	pTex->UnlockRect(0);
}
VOID MyD3DXSimpleFillTextureWithShadow(IDirect3DTexture9 *pTex, D3DCOLOR Color, BYTE ShadowStrenght)
{
	D3DSURFACE_DESC desc;
	pTex->GetLevelDesc(0, &desc);
	DWORD pixelCount = desc.Width * desc.Height;

	D3DLOCKED_RECT lr;
	pTex->LockRect(0, &lr, 0, D3DLOCK_DONOTWAIT);

	DWORD *pByte = (DWORD*)lr.pBits;

	for (register DWORD i = 0; i < pixelCount; i++) {
		pByte[i] = Color;
	}

	constexpr DWORD BorderSize = 1;

	// UP
	for (DWORD y = 0; y < BorderSize; y++) {
		for (DWORD x = 0; x < desc.Width; x++) {
			BGRA *pDest = (BGRA*)&pByte[y * desc.Width + x];
			pDest->a >= ShadowStrenght ? pDest->a -= ShadowStrenght : pDest->a = 0;
			pDest->r >= ShadowStrenght ? pDest->r -= ShadowStrenght : pDest->r = 0;
			pDest->g >= ShadowStrenght ? pDest->g -= ShadowStrenght : pDest->g = 0;
			pDest->b >= ShadowStrenght ? pDest->b -= ShadowStrenght : pDest->b = 0;
		}
	}
	// LEFT 
	for (DWORD y = 0; y < desc.Height; y++) {
		for (DWORD x = 0; x < BorderSize; x++) {
			BGRA *pDest = (BGRA*)&pByte[y * desc.Width + x];
			pDest->a >= ShadowStrenght ? pDest->a -= ShadowStrenght : pDest->a = 0;
			pDest->r >= ShadowStrenght ? pDest->r -= ShadowStrenght : pDest->r = 0;
			pDest->g >= ShadowStrenght ? pDest->g -= ShadowStrenght : pDest->g = 0;
			pDest->b >= ShadowStrenght ? pDest->b -= ShadowStrenght : pDest->b = 0;
		}
	}
	// DOWN
	for (DWORD y = desc.Height - BorderSize; y < desc.Height; y++) {
		for (DWORD x = 0; x < desc.Width; x++) {
			BGRA *pDest = (BGRA*)&pByte[y * desc.Width + x];
			pDest->a >= ShadowStrenght ? pDest->a -= ShadowStrenght : pDest->a = 0;
			pDest->r >= ShadowStrenght ? pDest->r -= ShadowStrenght : pDest->r = 0;
			pDest->g >= ShadowStrenght ? pDest->g -= ShadowStrenght : pDest->g = 0;
			pDest->b >= ShadowStrenght ? pDest->b -= ShadowStrenght : pDest->b = 0;
		}
	}
	// RIGHT
	for (DWORD y = 0; y < desc.Height; y++) {
		for (DWORD x = desc.Width - BorderSize; x < desc.Width; x++) {
			BGRA *pDest = (BGRA*)&pByte[y * desc.Width + x];
			pDest->a >= ShadowStrenght ? pDest->a -= ShadowStrenght : pDest->a = 0;
			pDest->r >= ShadowStrenght ? pDest->r -= ShadowStrenght : pDest->r = 0;
			pDest->g >= ShadowStrenght ? pDest->g -= ShadowStrenght : pDest->g = 0;
			pDest->b >= ShadowStrenght ? pDest->b -= ShadowStrenght : pDest->b = 0;
		}
	}



	pTex->UnlockRect(0);
}
VOID MyD3DXBorderTexture(IDirect3DTexture9 *pTex, D3DCOLOR Color, DWORD BorderSize)
{
	D3DSURFACE_DESC desc;
	pTex->GetLevelDesc(0, &desc);
	DWORD pixelCount = desc.Width * desc.Height;

	D3DLOCKED_RECT lr;
	pTex->LockRect(0, &lr, 0, D3DLOCK_DONOTWAIT);

	DWORD *pByte = (DWORD*)lr.pBits;

	// UP
	for (DWORD y = 0; y < BorderSize; y++) {
		for (DWORD x = 0; x < desc.Width; x++) {
			pByte[y * desc.Width + x] = Color;
		}
	}
	// LEFT 
	for (DWORD y = 0; y < desc.Height; y++) {
		for (DWORD x = 0; x < BorderSize; x++) {
			pByte[y * desc.Width + x] = Color;
		}
	}
	// DOWN
	for (DWORD y = desc.Height - BorderSize; y < desc.Height; y++) {
		for (DWORD x = 0; x < desc.Width; x++) {
			pByte[y * desc.Width + x] = Color;
		}
	}
	// RIGHT
	for (DWORD y = 0; y < desc.Height; y++) {
		for (DWORD x = desc.Width - BorderSize; x < desc.Width; x++) {
			pByte[y * desc.Width + x] = Color;
		}
	}

	pTex->UnlockRect(0);
}
VOID MyD3DXBorderTextureWithShadow(IDirect3DTexture9 *pTex, D3DCOLOR Color, DWORD BorderSize, BYTE ShadowStrenght)
{
	if (BorderSize < 1) return;

	D3DSURFACE_DESC desc;
	pTex->GetLevelDesc(0, &desc);

	D3DLOCKED_RECT lr;
	pTex->LockRect(0, &lr, 0, D3DLOCK_DONOTWAIT);

	DWORD *pByte = (DWORD*)lr.pBits;

	// UP
	for (DWORD y = 0; y < BorderSize; y++) {
		for (DWORD x = 0; x < desc.Width; x++) {
			pByte[y * desc.Width + x] = Color;
		}
	}
	// LEFT 
	for (DWORD y = 0; y < desc.Height; y++) {
		for (DWORD x = 0; x < BorderSize; x++) {
			pByte[y * desc.Width + x] = Color;
		}
	}
	// DOWN
	for (DWORD y = desc.Height - BorderSize; y < desc.Height; y++) {
		for (DWORD x = 0; x < desc.Width; x++) {
			pByte[y * desc.Width + x] = Color;
		}
	}
	// RIGHT
	for (DWORD y = 0; y < desc.Height; y++) {
		for (DWORD x = desc.Width - BorderSize; x < desc.Width; x++) {
			pByte[y * desc.Width + x] = Color;
		}
	}

	// UP
	for (DWORD y = BorderSize - 1; y < BorderSize; y++) {
		for (DWORD x = BorderSize - 1; x < desc.Width - BorderSize; x++) {
			BGRA *pDest = (BGRA*)&pByte[y * desc.Width + x];
			pDest->a >= ShadowStrenght ? pDest->a -= ShadowStrenght : pDest->a = 0;
			pDest->r >= ShadowStrenght ? pDest->r -= ShadowStrenght : pDest->r = 0;
			pDest->g >= ShadowStrenght ? pDest->g -= ShadowStrenght : pDest->g = 0;
			pDest->b >= ShadowStrenght ? pDest->b -= ShadowStrenght : pDest->b = 0;
		}
	}

	// LEFT 
	for (DWORD y = BorderSize; y < desc.Height - BorderSize; y++) {
		for (DWORD x = BorderSize - 1; x < BorderSize; x++) {
			BGRA *pDest = (BGRA*)&pByte[y * desc.Width + x];
			pDest->a >= ShadowStrenght ? pDest->a -= ShadowStrenght : pDest->a = 0;
			pDest->r >= ShadowStrenght ? pDest->r -= ShadowStrenght : pDest->r = 0;
			pDest->g >= ShadowStrenght ? pDest->g -= ShadowStrenght : pDest->g = 0;
			pDest->b >= ShadowStrenght ? pDest->b -= ShadowStrenght : pDest->b = 0;
		}
	}

	// DOWN
	for (DWORD y = desc.Height - BorderSize; y < desc.Height - BorderSize + 1; y++) {
		for (DWORD x = BorderSize - 1; x < desc.Width - BorderSize + 1; x++) {
			BGRA *pDest = (BGRA*)&pByte[y * desc.Width + x];
			pDest->a >= ShadowStrenght ? pDest->a -= ShadowStrenght : pDest->a = 0;
			pDest->r >= ShadowStrenght ? pDest->r -= ShadowStrenght : pDest->r = 0;
			pDest->g >= ShadowStrenght ? pDest->g -= ShadowStrenght : pDest->g = 0;
			pDest->b >= ShadowStrenght ? pDest->b -= ShadowStrenght : pDest->b = 0;
		}
	}

	// RIGHT
	for (DWORD y = 0 + BorderSize - 1; y < desc.Height - BorderSize; y++) {
		for (DWORD x = desc.Width - BorderSize; x < desc.Width - BorderSize + 1; x++) {
			BGRA *pDest = (BGRA*)&pByte[y * desc.Width + x];
			pDest->a >= ShadowStrenght ? pDest->a -= ShadowStrenght : pDest->a = 0;
			pDest->r >= ShadowStrenght ? pDest->r -= ShadowStrenght : pDest->r = 0;
			pDest->g >= ShadowStrenght ? pDest->g -= ShadowStrenght : pDest->g = 0;
			pDest->b >= ShadowStrenght ? pDest->b -= ShadowStrenght : pDest->b = 0;
		}
	}

	pTex->UnlockRect(0);
}
VOID MyD3DXFillTextureRect(IDirect3DTexture9 *pTex, D3DCOLOR Color, RECT *pRect)
{
	D3DSURFACE_DESC desc;
	pTex->GetLevelDesc(0, &desc);
	
	/*
	
	*/
	if (pRect->right > desc.Width || pRect->bottom > desc.Height)
		ErrorMessage("MyD3DXFillTextureRect && (pRect->right > desc.Width || pRect->bottom > desc.Height) wtf :(");

	D3DLOCKED_RECT lr;
	pTex->LockRect(0, &lr, 0, D3DLOCK_DONOTWAIT);

	DWORD *pByte = (DWORD*)lr.pBits;

	for (DWORD y = pRect->top; y < pRect->bottom; y++) {
		for (DWORD x = pRect->left; x < pRect->right; x++) {
			pByte[y * desc.Width + x] = Color;
		}
	}

	pTex->UnlockRect(0);
}
VOID MyD3DXFillTextureRectWithShadow(IDirect3DTexture9 *pTex, D3DCOLOR Color, RECT *pRect, BYTE ShadowStrenght)
{
	D3DSURFACE_DESC desc;
	pTex->GetLevelDesc(0, &desc);

	if (pRect->right > desc.Width || pRect->bottom > desc.Height)
		ErrorMessage("MyD3DXFillTextureRect && (pRect->right > desc.Width || pRect->bottom > desc.Height) wtf :(");

	D3DLOCKED_RECT lr;
	pTex->LockRect(0, &lr, 0, D3DLOCK_DONOTWAIT);

	DWORD *pByte = (DWORD*)lr.pBits;

	for (DWORD y = pRect->top; y < pRect->bottom; y++) {
		for (DWORD x = pRect->left; x < pRect->right; x++) {
			pByte[y * desc.Width + x] = Color;
		}
	}

	constexpr DWORD BorderSize = 1;

	// UP
	for (DWORD y = pRect->top; y < pRect->top + BorderSize; y++) {
		for (DWORD x = pRect->left; x < pRect->right; x++) {
			BGRA *pDest = (BGRA*)&pByte[y * desc.Width + x];
			pDest->a >= ShadowStrenght ? pDest->a -= ShadowStrenght : pDest->a = 0;
			pDest->r >= ShadowStrenght ? pDest->r -= ShadowStrenght : pDest->r = 0;
			pDest->g >= ShadowStrenght ? pDest->g -= ShadowStrenght : pDest->g = 0;
			pDest->b >= ShadowStrenght ? pDest->b -= ShadowStrenght : pDest->b = 0;
		}
	}
	// LEFT 
	for (DWORD y = pRect->top; y < pRect->bottom; y++) {
		for (DWORD x = pRect->left; x < pRect->left + BorderSize; x++) {
			BGRA *pDest = (BGRA*)&pByte[y * desc.Width + x];
			pDest->a >= ShadowStrenght ? pDest->a -= ShadowStrenght : pDest->a = 0;
			pDest->r >= ShadowStrenght ? pDest->r -= ShadowStrenght : pDest->r = 0;
			pDest->g >= ShadowStrenght ? pDest->g -= ShadowStrenght : pDest->g = 0;
			pDest->b >= ShadowStrenght ? pDest->b -= ShadowStrenght : pDest->b = 0;
		}
	}
	// DOWN
	for (DWORD y = pRect->bottom - BorderSize; y < pRect->bottom; y++) {
		for (DWORD x = pRect->left; x < pRect->right; x++) {
			BGRA *pDest = (BGRA*)&pByte[y * desc.Width + x];
			pDest->a >= ShadowStrenght ? pDest->a -= ShadowStrenght : pDest->a = 0;
			pDest->r >= ShadowStrenght ? pDest->r -= ShadowStrenght : pDest->r = 0;
			pDest->g >= ShadowStrenght ? pDest->g -= ShadowStrenght : pDest->g = 0;
			pDest->b >= ShadowStrenght ? pDest->b -= ShadowStrenght : pDest->b = 0;
		}
	}
	// RIGHT
	for (DWORD y = pRect->top; y < pRect->bottom; y++) {
		for (DWORD x = pRect->right - BorderSize; x < pRect->right; x++) {
			BGRA *pDest = (BGRA*)&pByte[y * desc.Width + x];
			pDest->a >= ShadowStrenght ? pDest->a -= ShadowStrenght : pDest->a = 0;
			pDest->r >= ShadowStrenght ? pDest->r -= ShadowStrenght : pDest->r = 0;
			pDest->g >= ShadowStrenght ? pDest->g -= ShadowStrenght : pDest->g = 0;
			pDest->b >= ShadowStrenght ? pDest->b -= ShadowStrenght : pDest->b = 0;
		}
	}

	pTex->UnlockRect(0);
}
VOID MyD3DXFillTextureAlpha(IDirect3DTexture9 *pTex, BYTE Alpha)
{
	D3DSURFACE_DESC desc;
	pTex->GetLevelDesc(0, &desc);
	DWORD pixelCount = desc.Width * desc.Height;

	D3DLOCKED_RECT lr;
	pTex->LockRect(0, &lr, 0, D3DLOCK_DONOTWAIT);

	DWORD *pByte = (DWORD*)lr.pBits;

	struct BGRA {
		BYTE b, g, r, a;
	} this_color;

	for (register DWORD i = 0; i < pixelCount; i++) {
		this_color = *(BGRA*)&pByte[i];
		this_color.a = Alpha;
		*(BGRA*)&pByte[i] = this_color;
	}

	pTex->UnlockRect(0);
}
VOID MyD3DXFillTextureNoAlpha(IDirect3DTexture9 *pTex, D3DCOLOR ColorRGB)
{
	D3DSURFACE_DESC desc;
	pTex->GetLevelDesc(0, &desc);
	DWORD pixelCount = desc.Width * desc.Height;

	D3DLOCKED_RECT lr;
	pTex->LockRect(0, &lr, 0, D3DLOCK_DONOTWAIT);

	DWORD *pByte = (DWORD*)lr.pBits;

	struct BGRA {
		BYTE b, g, r, a;
	} this_color;

	for (register DWORD i = 0; i < pixelCount; i++) {
		this_color.a = ((BGRA*)&pByte[i])->a;
		pByte[i] = ColorRGB;
		((BGRA*)&pByte[i])->a = this_color.a;
	}

	pTex->UnlockRect(0);
}

ID3DXSprite* MyD3DXCreateSprite(LPDIRECT3DDEVICE9 pDevice)
{
	ID3DXSprite *sprite;
	HRESULT hr = D3DXCreateSprite(pDevice, &sprite);
	if (FAILED(hr))
		ErrorMessageWithHexValue("D3DXCreateSprite FAILED, HRESULT == ", hr);
	else
		RegisterIUnknown(sprite);
	return sprite;
}
IDirect3DTexture9* MyD3DXCreateTexture(LPDIRECT3DDEVICE9 pDevice, UINT Width, UINT Height, UINT MipLevels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool)
{
	IDirect3DTexture9 *texture;
	HRESULT hr = D3DXCreateTexture(pDevice, Width, Height, MipLevels, Usage, Format, Pool, &texture);
	if (FAILED(hr))
		ErrorMessageWithHexValue("D3DXCreateTexture FAILED, HRESULT == ", hr);
	else
		RegisterIUnknown(texture);
	return texture;
}
IDirect3DTexture9* MyD3DXCreateTextureFromFileEx(LPDIRECT3DDEVICE9 pDevice, LPCSTR pSrcFile, UINT Width, UINT Height, UINT MipLevels,
	DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, DWORD Filter, DWORD MipFilter,
	D3DCOLOR ColorKey, D3DXIMAGE_INFO* pSrcInfo, PALETTEENTRY* Palette)
{
	IDirect3DTexture9 *texture;
	HRESULT hr = D3DXCreateTextureFromFileEx(pDevice, pSrcFile, Width, Height, MipLevels,
		Usage, Format, Pool, Filter, MipFilter, ColorKey, pSrcInfo, Palette, &texture);
	if (FAILED(hr)) {
		char text[256]; sprintf(text, "D3DXCreateTextureFromFileEx FAILED :(\n HRESULT == 0x%X, path - %s", hr, pSrcFile);
		ErrorMessage(text); } 
	else {
		RegisterIUnknown(texture); }
	return texture;
}
ID3DXFont* MyD3DXCreateFont(LPDIRECT3DDEVICE9 pDevice, INT Height, UINT Width, UINT Weight, UINT MipLevels, 
	BOOL Italic, DWORD CharSet, DWORD OutputPrecision, DWORD Quality, DWORD PitchAndFamily, LPCSTR pFaceName)
{
	ID3DXFont *font;
	HRESULT hr = D3DXCreateFont(pDevice, Height, Width, Weight, MipLevels, Italic, CharSet, OutputPrecision, Quality, PitchAndFamily, pFaceName, &font);
	if (FAILED(hr))
		ErrorMessageWithHexValue("D3DXCreateFont FAILED, HRESULT == ", hr);
	else
		RegisterIUnknown(font);
	return font;
}

VOID MyGDIBorderedTexture(IDirect3DTexture9 *pTex, DWORD BorderSize, COLORREF Color, COLORREF BorderColor)
{
	IDirect3DSurface9 *surface;
	pTex->GetSurfaceLevel(0, &surface);

	D3DSURFACE_DESC desc;
	surface->GetDesc(&desc);

	HDC hdc;
	surface->GetDC(&hdc);

	HPEN hFill = CreatePen(PS_SOLID, desc.Height * 1.5f, Color);
	HPEN hBord = CreatePen(PS_SOLID, BorderSize * 2, BorderColor);

	SelectObject(hdc, hFill);

	MoveToEx(hdc, desc.Height / 2, desc.Height / 2, 0);
	LineTo(hdc, desc.Width - desc.Height / 2, desc.Height / 2);

	SelectObject(hdc, hBord);

	MoveToEx(hdc, 0, 0, 0);

	LineTo(hdc, desc.Width, 0);
	LineTo(hdc, desc.Width, desc.Height);
	LineTo(hdc, 0, desc.Height);
	LineTo(hdc, 0, 0);

	surface->ReleaseDC(hdc);

	SelectObject(hdc, GetStockObject(BLACK_PEN));

	DeleteObject(hFill);
	DeleteObject(hBord);
}