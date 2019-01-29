#pragma once
#include "core.h"

enum b_type { b_type_prototype, b_type_section, b_type_boolean, b_type_value, b_type_button };
enum v_type { v_type_byte = 0, v_type_short = 1, v_type_long = 2, v_type_float = 3 };

class b_prototype
{
public:
	b_prototype(const char * text, D3DXVECTOR2 pos, IDirect3DTexture9 *tex, ID3DXFont *font);

	virtual void DrawRect(ID3DXSprite *sprite);
	virtual bool OnMouseRect();

	virtual void ClickProc() {};
	virtual void Process() {};
	virtual void Draw(ID3DXSprite *sprite) { DrawRect(sprite); };

	D3DXVECTOR3 pos;
	IDirect3DTexture9 *tex;
	ID3DXFont *font;
	DWORD tex_size_x, tex_size_y;
	const char *text;
	RECT text_rect;
	b_type b_type;
};
class b_boolean : public b_prototype
{
public:
	b_boolean(const char * text, D3DXVECTOR2 pos, IDirect3DTexture9 *tex, ID3DXFont *font,
		IDirect3DTexture9 *checkbox_tex, IDirect3DTexture9 *active_checkbox_tex, void(*function)(bool));

	virtual void Draw(ID3DXSprite *sprite);
	virtual void ClickProc();

	IDirect3DTexture9 *checkbox_tex, *active_checkbox_tex;
	D3DXVECTOR3 checkbox_pos;
	bool is_active;
	void(*function)(bool);
};
class b_value : public b_prototype
{
public:
	b_value(LPCSTR text, D3DXVECTOR2 pos, IDirect3DTexture9 *tex, ID3DXFont *font,
		IDirect3DTexture9 *button_tex, ID3DXFont *button_font, IDirect3DTexture9 *plus_tex, IDirect3DTexture9 *minus_tex, v_type value_type, bool use_call_to_get_value, bool use_call_to_set_value, void*get_value_addr, void*set_value_addr);

	virtual void Process();
	virtual void Draw(ID3DXSprite *sprite);
	virtual void ClickProc();

	void Update();

	IDirect3DTexture9 *button_tex;
	D3DXVECTOR3 button_pos;
	DWORD button_tex_size_x, button_tex_size_y;
	IDirect3DTexture9 *plus_tex,*minus_tex;
	D3DXVECTOR3 plus_pos, minus_pos;
	DWORD plus_tex_size_x, plus_tex_size_y, minus_tex_size_x, minus_tex_size_y;
	v_type value_type;
	ID3DXFont *button_font;
	RECT value_text_rect;
	char value_text[60];
	bool use_call_to_get_value, use_call_to_set_value;
	void *get_value_addr, *set_value_addr;
};
class b_button : public b_prototype
{
public:
	b_button(const char *text, D3DXVECTOR2 pos, IDirect3DTexture9 *tex, ID3DXFont *font, void(function)());

	virtual void ClickProc() { call(); };
	void(*call)();
};
class b_section : public b_prototype
{
public:
	b_section(const char * text, D3DXVECTOR2 pos, IDirect3DTexture9 *tex, ID3DXFont *font, IDirect3DTexture9 *tr1_tex, IDirect3DTexture9 *tr2_tex, DWORD buttons_page_size);

	void DrawChilds(ID3DXSprite *sprite);
	void LMBChildsProc();
	void ProcessChilds();

	virtual void CalculateNextPos(D3DXVECTOR2 *out);

	b_section *CreateSection(const char * text, IDirect3DTexture9 * tex, ID3DXFont * font, IDirect3DTexture9 *tr1_tex, IDirect3DTexture9 *tr2_tex, DWORD buttons_page_size);
	b_boolean *CreateBooleanFunction(const char *text, IDirect3DTexture9 *tex, ID3DXFont *font,
		IDirect3DTexture9 *checkbox_tex, IDirect3DTexture9 *active_checkbox_tex, void(*function)(bool));
	b_value *CreateValueFunction(LPCSTR text, IDirect3DTexture9 *tex, ID3DXFont *font,
		IDirect3DTexture9 *button_tex, ID3DXFont *button_font, IDirect3DTexture9 *plus_tex, IDirect3DTexture9 *minus_tex, v_type v_type, bool use_call_to_get_value, bool use_call_to_set_value, void*get_value_addr, void*set_value_addr);
	b_button *CreateButtonFunction(const char *text, IDirect3DTexture9 *tex, ID3DXFont *font, void(*function)());

	IDirect3DTexture9 *triangle1_tex, *triangle2_tex;
	D3DXVECTOR3 triangle1_pos, triangle2_pos;
	b_section * opened_section;
	b_prototype ** button;
	DWORD buttons_count;
};
class Menu : public b_section
{
public:
	Menu(const char * text, D3DXVECTOR2 pos, IDirect3DTexture9 * tex, ID3DXFont * font, DWORD buttons_page_size, ID3DXSprite * sprite, int vk_code);

	void BeginProcess();
	void BeginDraw();
	void BeginLMBProcess();
	void BeginCloseOpenProcess();

	void Close();
	void Open();

	virtual void CalculateNextPos(D3DXVECTOR2 *out);

	ID3DXSprite *sprite;

	verble_loop_ex process_loop, direct_loop, lmb_loop, close_open_loop;
	int vk_code;
	bool is_open;
};

constexpr float button_x_bias = 5.0f;
constexpr float button_y_bias = 4.5f;
constexpr float text_x_bias = 5.5f;
constexpr float text_y_bias = 2.0f;
constexpr DWORD section_size_x = 180;
constexpr DWORD section_size_y = 28;
constexpr UINT button_size_x = 350;
constexpr UINT button_size_y = 28;
constexpr DWORD title_size_x = section_size_x + button_size_x + button_x_bias;
constexpr DWORD title_size_y = 25;