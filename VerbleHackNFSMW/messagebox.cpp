#include "core.h"
#include "menu.h"

#include <string>

#include "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include/d3dx9.h"
#pragma comment(lib,"C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x86/d3dx9.lib")

namespace messagebox
{
	void Draw(LPDIRECT3DDEVICE9);
	void Proc();
	void LMBProc();
	void Init(IDirect3DDevice9 *pDev);
	void CreateGetValue(void* valueptr, const char* title, v_type valuetype, bool usecall);
	void Terminate();
}

using namespace std;

char msbx_title[50];
string msbx_outtext;
bool ActiveMessageBox = false;

LPDIRECT3DTEXTURE9 msbx_cursor_tex;
D3DXVECTOR3 msbx_cursor_pos;

LPD3DXSPRITE msbx_spr;

D3DCOLOR Color = D3DXCOLOR(0,0,0,255), BColor = D3DXCOLOR(255, 0, 0, 255), FontColor = D3DXCOLOR(255,255,255, 255), trFontColor = D3DXCOLOR(200, 200, 200, 200);

D3DCOLOR col_onmouse = D3DCOLOR_ARGB(235, 40, 40, 40);

D3DXVECTOR3 MessageBoxPos;
D3DXVECTOR3 msbx_outtext_Pos;

D3DXVECTOR3 msbx_buttonok_pos;
D3DXVECTOR3 msbx_buttoncancel_pos;

LPDIRECT3DTEXTURE9 MessageBoxTex;

LPDIRECT3DTEXTURE9 msbx_OutT_Tex;

LPDIRECT3DTEXTURE9 msbx_button_tex;

LPD3DXFONT msbx_titlefont;
LPD3DXFONT msbx_buttonfont;
LPD3DXFONT msbx_outfont;

RECT msbx_rect_titlefont;
RECT msbx_rect_outfont;

RECT msbx_buttonok_rect;
RECT msbx_buttoncancel_rect;

bool g_msbx_textcrutch;

constexpr int messageboxsizeX = 350;
constexpr int messageboxsizeY = 90;
constexpr int msbx_outtext_sizeX = 300;
constexpr int msbx_outtext_sizeY = 25;
constexpr int msbx_button_sizeX = 50;
constexpr int msbx_button_sizeY = 18;

constexpr float msbx_outtext_menuoffsetX = 41;
constexpr float msbx_outtext_menuoffsetY = 30;

constexpr float msbx_outtext_yoffset = 30.0f;

#define bt_ok 0
#define bt_cancel 1

bool mouse_in_button = false, mb_mouse_in_button = false;
unsigned char button_type;

void* pthisvalue;

void set_char_value() { *(char*)pthisvalue = (char)atoi(msbx_outtext.c_str()); }
void set_short_value() { *(short*)pthisvalue = (short)atoi(msbx_outtext.c_str()); }
void set_int_value() { *(int*)pthisvalue = atoi(msbx_outtext.c_str()); }
void set_float_value() { *(float*)pthisvalue = (float)atof(msbx_outtext.c_str()); }
void set_double_value() { *(double*)pthisvalue = atof(msbx_outtext.c_str()); }
void set_str_value() { strcpy((char*)pthisvalue, (char*)msbx_outtext.c_str()); }

void* setvalue_func[6] = { set_char_value,set_short_value, set_int_value,set_float_value,set_double_value,set_str_value };

void set_char_callvalue() { ((void(*)(char))pthisvalue)((char)atoi(msbx_outtext.c_str())); }
void set_short_callvalue() { ((void(*)(short))pthisvalue)((short)atoi(msbx_outtext.c_str())); }
void set_int_callvalue() { ((void(*)(int))pthisvalue)(atoi(msbx_outtext.c_str())); }
void set_float_callvalue() { ((void(*)(float))pthisvalue)((float)atof(msbx_outtext.c_str())); }
void set_double_callvalue() { ((void(*)(double))pthisvalue)(atof(msbx_outtext.c_str())); }
void set_str_callvalue() { ((void(*)(...))pthisvalue)(msbx_outtext.c_str()); }

void* setvalue_callfunc[6] = { set_char_callvalue,set_short_callvalue, set_int_callvalue,set_float_callvalue,set_double_callvalue,set_str_callvalue };

void(*thissetvalue_func)();

inline void msbx_outtext_setdefaultpos()
{
	msbx_outtext_Pos.x = MessageBoxPos.x + msbx_outtext_menuoffsetX;
	msbx_outtext_Pos.y = MessageBoxPos.y + msbx_outtext_menuoffsetY;

	msbx_rect_outfont.left = msbx_outtext_Pos.x + 3.0f;
	msbx_rect_outfont.top = msbx_outtext_Pos.y + 2.0f;

	msbx_rect_outfont.right = msbx_outtext_Pos.x + msbx_outtext_sizeX;
	msbx_rect_outfont.bottom = msbx_outtext_Pos.y + msbx_outtext_sizeY;
}

inline void msbx_setdefaultpos()
{
	MessageBoxPos.x = (GetSystemMetrics(SM_CXSCREEN) / 2) - (messageboxsizeX / 2);
	MessageBoxPos.y = (GetSystemMetrics(SM_CYSCREEN) / 2) - (messageboxsizeY / 2);

	msbx_rect_titlefont.left = MessageBoxPos.x + 1.0f;
	msbx_rect_titlefont.right = msbx_rect_titlefont.left + messageboxsizeX;
	msbx_rect_titlefont.top = MessageBoxPos.y + 1.0f;
	msbx_rect_titlefont.bottom = msbx_rect_titlefont.top + 20.0f;

	msbx_buttonok_pos.x = MessageBoxPos.x + 235;
	msbx_buttonok_pos.y = MessageBoxPos.y + 65;

	msbx_buttoncancel_pos.x = MessageBoxPos.x + 290;
	msbx_buttoncancel_pos.y = MessageBoxPos.y + 65;

	msbx_buttonok_rect.left = msbx_buttonok_pos.x + 1.0f;
	msbx_buttonok_rect.right = msbx_buttonok_rect.left + msbx_button_sizeX;
	msbx_buttonok_rect.top = msbx_buttonok_pos.y + 1.0f;
	msbx_buttonok_rect.bottom = msbx_buttonok_rect.top + msbx_button_sizeY;

	msbx_buttoncancel_rect.left = msbx_buttoncancel_pos.x + 1.0f;
	msbx_buttoncancel_rect.right = msbx_buttoncancel_rect.left + msbx_button_sizeX;
	msbx_buttoncancel_rect.top = msbx_buttoncancel_pos.y + 1.0f;
	msbx_buttoncancel_rect.bottom = msbx_buttoncancel_rect.top + msbx_button_sizeY;

	msbx_outtext_setdefaultpos();
}

void messagebox::CreateGetValue(void* valueptr, const char* title, v_type valuetype, bool usecall)
{
	if (ActiveMessageBox) {
		Terminate();
	}

	strcpy(msbx_title, title);
	pthisvalue = valueptr;

	usecall ? thissetvalue_func = (void(*)())setvalue_callfunc[valuetype] : thissetvalue_func = (void(*)())setvalue_func[valuetype];

	g_msbx_textcrutch = true;

	core::AddDirectX9Loop(Draw);
	core::AddMouseLoop(LMBProc);
	core::AddLoop(Proc);
	 
	ActiveMessageBox = true;
}

void messagebox::Terminate()
{
	core::FreeMouseLoop(LMBProc);
	core::FreeLoop(Proc);
	core::FreeDirectX9Loop(Draw);

	mouse_in_button = false;
	ActiveMessageBox = false;
}

void messagebox::Draw(LPDIRECT3DDEVICE9)
{
	msbx_spr->Begin(D3DXSPRITE_ALPHABLEND);

	msbx_spr->Draw(MessageBoxTex, 0, 0, &MessageBoxPos, 0xFFFFFFFF);
	msbx_titlefont->DrawTextA(msbx_spr, msbx_title, -1, &msbx_rect_titlefont, 0, FontColor);

	msbx_spr->Draw(msbx_OutT_Tex, 0, 0, &msbx_outtext_Pos, 0xFFFFFFFF);
	msbx_outfont->DrawTextA(msbx_spr, msbx_outtext.c_str(), -1, &msbx_rect_outfont, 0, FontColor);

	mb_mouse_in_button = false;

	if (core::cursor::in_object(&msbx_buttonok_pos, msbx_button_sizeX, msbx_button_sizeY))
	{
		mb_mouse_in_button = true;
		button_type = bt_ok;
		msbx_spr->Draw(msbx_button_tex, 0, 0, &msbx_buttonok_pos, 0xAAFFFFFF);
	}
	else
	{
		msbx_spr->Draw(msbx_button_tex, 0, 0, &msbx_buttonok_pos, 0xFFFFFFFF);
	}
	msbx_buttonfont->DrawTextA(msbx_spr, "Accept", -1, &msbx_buttonok_rect, 0, FontColor);

	if (core::cursor::in_object(&msbx_buttoncancel_pos, msbx_button_sizeX, msbx_button_sizeY))
	{
		mb_mouse_in_button = true;
		button_type = bt_cancel;
		msbx_spr->Draw(msbx_button_tex, 0, 0, &msbx_buttoncancel_pos, 0xAAFFFFFF);
	}
	else
	{
		msbx_spr->Draw(msbx_button_tex, 0, 0, &msbx_buttoncancel_pos, 0xFFFFFFFF);
	}
	msbx_buttonfont->DrawTextA(msbx_spr, "Cancel", -1, &msbx_buttoncancel_rect, 0, FontColor);

	mouse_in_button = mb_mouse_in_button;

	msbx_spr->End();
}

inline void msbx_writetext_proc();
inline void msbx_writetext_proc_caps();

inline void msbx_textout_crutch()
{
	for (int i = 0; i < 0xFF; i++)
		GetAsyncKeyState(i);
}

void messagebox::LMBProc()
{
	if (mouse_in_button)
	{
		switch (button_type)
		{
		case bt_ok:
			thissetvalue_func();
			break;
		case bt_cancel:
			messagebox::Terminate();
			break;
		}
	}
}

void messagebox::Proc()
{
	if (g_msbx_textcrutch) {
		msbx_textout_crutch();
		g_msbx_textcrutch = false;
	} GetKeyState(VK_CAPITAL) ? msbx_writetext_proc_caps() : msbx_writetext_proc();
}

void messagebox::Init(IDirect3DDevice9 *pDev)
{
	msbx_spr = MyD3DXCreateSprite(pDev);

	MessageBoxTex = MyD3DXCreateTexture(pDev, messageboxsizeX, messageboxsizeY, D3DX_DEFAULT, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED);
	msbx_OutT_Tex = MyD3DXCreateTexture(pDev, msbx_outtext_sizeX, msbx_outtext_sizeY, D3DX_DEFAULT, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED);
	msbx_button_tex = MyD3DXCreateTexture(pDev, msbx_button_sizeX, msbx_button_sizeY, D3DX_DEFAULT, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED);

	MyD3DXSimpleFillTexture(MessageBoxTex, D3DCOLOR_ARGB(220, 0, 0, 0));
	MyD3DXBorderTextureWithShadow(MessageBoxTex, D3DCOLOR_ARGB(255, 220, 0, 0), 2, 85);
	MyD3DXSimpleFillTexture(msbx_OutT_Tex, D3DCOLOR_ARGB(220, 0, 0, 0));
	MyD3DXBorderTextureWithShadow(msbx_OutT_Tex, D3DCOLOR_ARGB(255, 220, 0, 0), 2, 85);
	MyD3DXSimpleFillTexture(msbx_button_tex, D3DCOLOR_ARGB(220, 0, 0, 0));
	MyD3DXBorderTextureWithShadow(msbx_button_tex, D3DCOLOR_ARGB(255, 220, 0, 0), 2, 85);

	msbx_titlefont = MyD3DXCreateFont(pDev, 20, 8, 0, 0, 0, RUSSIAN_CHARSET, 0, 0, 0 | FF_DONTCARE, "Consolas");
	msbx_outfont = MyD3DXCreateFont(pDev, 20, 8, 0, 0, 0, RUSSIAN_CHARSET, 0, 0, 0 | FF_DONTCARE, "Consolas");
	msbx_buttonfont = MyD3DXCreateFont(pDev, 16, 6, 0, 0, 0, RUSSIAN_CHARSET, 0, 0, 0 | FF_DONTCARE, "Consolas");

	msbx_setdefaultpos();
}

void __fastcall TextPop(int VirtualKey) {
	if (GetAsyncKeyState(VirtualKey)) {
		if (msbx_outtext.length() != 0) { msbx_outtext.pop_back(); }
		for (int i = 0; i < 30 && GetAsyncKeyState(VirtualKey); i++) { Sleep(10); }
		while (GetAsyncKeyState(VirtualKey)) { if (msbx_outtext.length() != 0) { msbx_outtext.pop_back(); Sleep(25); } }
	}
}

void __fastcall TextPress(int VirtualKey, char AddSymbol) {
	if (GetAsyncKeyState(VirtualKey)) {
		msbx_outtext += AddSymbol;
		for (int i = 0; i < 30 && GetAsyncKeyState(VirtualKey); i++) { Sleep(10); }
		while (GetAsyncKeyState(VirtualKey)) { msbx_outtext += AddSymbol; Sleep(25); }
	}
}

inline void msbx_writetext_proc()
{
	TextPop(VK_BACK);
	TextPress(VK_SPACE, ' ');
	TextPress(0x30, '0');
	TextPress(0x31, '1');
	TextPress(0x32, '2');
	TextPress(0x33, '3');
	TextPress(0x34, '4');
	TextPress(0x35, '5');
	TextPress(0x36, '6');
	TextPress(0x37, '7');
	TextPress(0x38, '8');
	TextPress(0x39, '9');
	TextPress(0x41, 'a');
	TextPress(0x42, 'b');
	TextPress(0x43, 'c');
	TextPress(0x44, 'd');
	TextPress(0x45, 'e');
	TextPress(0x46, 'f');
	TextPress(0x47, 'g');
	TextPress(0x48, 'h');
	TextPress(0x49, 'i');
	TextPress(0x4A, 'j');
	TextPress(0x4B, 'k');
	TextPress(0x4C, 'l');
	TextPress(0x4D, 'm');
	TextPress(0x4E, 'n');
	TextPress(0x4F, 'o');
	TextPress(0x50, 'p');
	TextPress(0x51, 'q');
	TextPress(0x52, 'r');
	TextPress(0x53, 's');
	TextPress(0x54, 't');
	TextPress(0x55, 'u');
	TextPress(0x56, 'v');
	TextPress(0x57, 'w');
	TextPress(0x58, 'x');
	TextPress(0x59, 'y');
	TextPress(0x5A, 'z');
	TextPress(VK_SUBTRACT, '-');
	TextPress(VK_OEM_MINUS, '-');
	TextPress(VK_OEM_PERIOD, '.');
	TextPress(VK_OEM_2, '.');
	TextPress(VK_OEM_4, '[');
	TextPress(VK_OEM_5, '|');
	TextPress(VK_OEM_6, ']');
}

inline void msbx_writetext_proc_caps()
{
	TextPop(VK_BACK);
	TextPress(VK_SPACE, ' ');
	TextPress(0x30, '0');
	TextPress(0x31, '1');
	TextPress(0x32, '2');
	TextPress(0x33, '3');
	TextPress(0x34, '4');
	TextPress(0x35, '5');
	TextPress(0x36, '6');
	TextPress(0x37, '7');
	TextPress(0x38, '8');
	TextPress(0x39, '9');
	TextPress(0x41, 'A');
	TextPress(0x42, 'B');
	TextPress(0x43, 'C');
	TextPress(0x44, 'D');
	TextPress(0x45, 'E');
	TextPress(0x46, 'F');
	TextPress(0x47, 'G');
	TextPress(0x48, 'H');
	TextPress(0x49, 'I');
	TextPress(0x4A, 'J');
	TextPress(0x4B, 'K');
	TextPress(0x4C, 'L');
	TextPress(0x4D, 'M');
	TextPress(0x4E, 'N');
	TextPress(0x4F, 'O');
	TextPress(0x50, 'P');
	TextPress(0x51, 'Q');
	TextPress(0x52, 'R');
	TextPress(0x53, 'S');
	TextPress(0x54, 'T');
	TextPress(0x55, 'U');
	TextPress(0x56, 'V');
	TextPress(0x57, 'W');
	TextPress(0x58, 'X');
	TextPress(0x59, 'Y');
	TextPress(0x5A, 'Z');
	TextPress(VK_SUBTRACT, '-');
	TextPress(VK_OEM_MINUS, '-');
	TextPress(VK_OEM_PERIOD, '.');
	TextPress(VK_OEM_2, '.');
	TextPress(VK_OEM_4, '[');
	TextPress(VK_OEM_5, '|');
	TextPress(VK_OEM_6, ']');
}