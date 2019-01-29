#include "menu.h"
#include "messagebox.h"

using namespace core;

void b_prototype::DrawRect(ID3DXSprite * sprite)
{
	sprite->Draw(tex, NULL, NULL, &pos, 0xFFFFFFFF);
	font->DrawText(sprite, text, -1, &text_rect, DT_NOCLIP, 0xFFFFFFFF);
}
bool b_prototype::OnMouseRect()
{
	return cursor::in_object(&pos, tex_size_x, tex_size_y);
}
b_prototype::b_prototype(const char * text, D3DXVECTOR2 pos, IDirect3DTexture9 *tex, ID3DXFont *font)
{
	this->pos.x = pos.x;
	this->pos.y = pos.y;
	this->text_rect.left = pos.x + 5.0f * core::xm;
	this->text_rect.top = pos.y + text_y_bias * core::ym;
	this->tex = tex; 
	this->font = font; 
	this->text = text;

	b_type = b_type_prototype;
	this->pos.z = 0.0f;

	D3DSURFACE_DESC desc; 
	this->tex->GetLevelDesc(0, &desc);
	tex_size_x = desc.Width; 
	tex_size_y = desc.Height;
}

b_button::b_button(const char *text, D3DXVECTOR2 pos, IDirect3DTexture9 *tex, ID3DXFont *font, void(*function)())
	: b_prototype(text, pos, tex, font)
{
	this->b_type = b_type_button;
	this->call = function;
}
void b_boolean::Draw(ID3DXSprite *sprite)
{
	DrawRect(sprite);
	sprite->Draw(is_active ? active_checkbox_tex : checkbox_tex, NULL, NULL, &checkbox_pos, 0xFFFFFFFF);
}
void b_boolean::ClickProc()
{
	is_active = !is_active;
	function(is_active);
}

b_boolean::b_boolean(const char * text, D3DXVECTOR2 pos, IDirect3DTexture9 *tex, ID3DXFont *font,
	IDirect3DTexture9 *checkbox_tex, IDirect3DTexture9 *active_checkbox_tex, void(*function)(bool))
	:b_prototype(text, pos, tex, font)
{
	D3DSURFACE_DESC checkbox_tex_desc;
	checkbox_tex->GetLevelDesc(0, &checkbox_tex_desc);

	this->b_type = b_type_boolean;
	this->checkbox_tex = checkbox_tex;
	this->active_checkbox_tex = active_checkbox_tex;
	this->checkbox_pos = { pos.x + tex_size_x - checkbox_tex_desc.Width - 5.0f,pos.y + (tex_size_y / 2 - checkbox_tex_desc.Height / 2),0.0f };
	this->function = function;
	is_active = false;
}

void b_value::Process()
{
	Update();
}
void b_value::Update()
{
	switch (this->value_type)
	{
	case v_type_byte:
		if (use_call_to_get_value) sprintf(value_text, "%u", ((unsigned char(*)())get_value_addr)());
		else sprintf(value_text, "%u", *(unsigned char*)get_value_addr);
		return;
	case v_type_short:
		if (use_call_to_get_value) sprintf(value_text, "%d", ((short(*)())get_value_addr)());
		else sprintf(value_text, "%d", *(short*)get_value_addr);
		return;
	case v_type_long:
		if (use_call_to_get_value) sprintf(value_text, "%d", ((int(*)())get_value_addr)());
		else sprintf(value_text, "%d", *(int*)get_value_addr);
		return;
	case v_type_float:
		if (use_call_to_get_value) sprintf(value_text, "%f", ((float(*)())get_value_addr)());
		else sprintf(value_text, "%f", *(float*)get_value_addr);
		return;
	}
}
b_value::b_value(LPCSTR text, D3DXVECTOR2 pos, IDirect3DTexture9 *tex, ID3DXFont *font,
	IDirect3DTexture9 *button_tex, ID3DXFont *button_font, IDirect3DTexture9 *plus_tex, IDirect3DTexture9 *minus_tex, v_type value_type, bool use_call_to_get_value, bool use_call_to_set_value, void*get_value_addr, void*set_value_addr)
	:b_prototype(text, pos, tex, font)
{
	D3DSURFACE_DESC button_tex_desc;
	button_tex->GetLevelDesc(0, &button_tex_desc);

	this->b_type = b_type_value;
	this->button_tex = button_tex;
	this->button_pos = { pos.x + tex_size_x - button_tex_desc.Width - 5.0f * core::xm,pos.y + (tex_size_y / 2 - button_tex_desc.Height / 2),0.0f };
	
	this->use_call_to_set_value = use_call_to_set_value;
	this->use_call_to_get_value = use_call_to_get_value;

	this->get_value_addr = get_value_addr;
	this->set_value_addr = set_value_addr;

	this->value_type = value_type;
	this->button_font = button_font;

	this->value_text_rect = _RECT((LONG)(button_pos.x - 140.0f * core::xm), (LONG)((button_pos.y + (button_size_y / 5)) - 5.0f * core::ym), 0, 0);
	strcpy(value_text, "0");

	this->plus_tex = plus_tex;
	this->minus_tex = minus_tex;

	button_tex_size_x = button_tex_desc.Width;
	button_tex_size_y = button_tex_desc.Height;

	plus_tex->GetLevelDesc(0, &button_tex_desc);
	plus_tex_size_x = button_tex_desc.Width;
	plus_tex_size_y = button_tex_desc.Height;

	minus_tex->GetLevelDesc(0, &button_tex_desc);
	minus_tex_size_x = button_tex_desc.Width;
	minus_tex_size_y = button_tex_desc.Height;
	
	minus_pos.x = button_pos.x - minus_tex_size_x - 2.0f * core::xm;
	minus_pos.y = pos.y + (tex_size_y / 2) - (minus_tex_size_y / 2);
	minus_pos.z = 0;
	plus_pos.x = minus_pos.x - plus_tex_size_x - 2.0f * core::xm;
	plus_pos.y = pos.y + (tex_size_y / 2) - (minus_tex_size_y / 2);
	plus_pos.z = 0;
}
void b_value::Draw(ID3DXSprite *sprite)
{
	DrawRect(sprite);
	button_font->DrawText(sprite, value_text, -1, &value_text_rect, DT_NOCLIP, 0xFFFFFFFF);
	sprite->Draw(button_tex, 0, 0, &button_pos, 0xFFFFFFFF);
	sprite->Draw(plus_tex, 0, 0, &plus_pos, 0xFFFFFFFF);
	sprite->Draw(minus_tex, 0, 0, &minus_pos, 0xFFFFFFFF);
}
void b_value::ClickProc()
{
	if (cursor::in_object(&button_pos, button_tex_size_x, button_tex_size_y)) {
		messagebox::CreateGetValue(this->set_value_addr, this->text, this->value_type, this->use_call_to_set_value);
	}
	else
	{
		constexpr int click_wait_max_count = 45;
		static int click_wait_count = 0;
	reclick:
		if (cursor::in_object(&plus_pos, plus_tex_size_x, plus_tex_size_y))
		{
			if (use_call_to_set_value)
			{
				if (use_call_to_get_value)
				{
					switch (value_type)
					{
					case v_type_byte:
						((void(*)(byte))set_value_addr)(((byte(*)())get_value_addr)() + 1); break;
					case v_type_short:
						((void(*)(short))set_value_addr)(((short(*)())get_value_addr)() + 1); break;
					case v_type_long:
						((void(*)(long))set_value_addr)(((long(*)())get_value_addr)() + 1); break;
					case v_type_float:
						((void(*)(float))set_value_addr)(((float(*)())get_value_addr)() + 0.1f); break;
					}
				}
				else
				{
					switch (value_type)
					{
					case v_type_byte:
						((void(*)(byte))set_value_addr)(*(byte*)get_value_addr + 1); break;
					case v_type_short:
						((void(*)(short))set_value_addr)(*(short*)get_value_addr + 1); break;
					case v_type_long:
						((void(*)(int))set_value_addr)(*(int*)get_value_addr + 1); break;
					case v_type_float:
						((void(*)(float))set_value_addr)(*(float*)get_value_addr + 0.1f); break;
					}
				}
			}
			else
			{
				if (use_call_to_get_value)
				{
					switch (value_type)
					{
					case v_type_byte:
						*(byte*)set_value_addr = ((byte(*)())get_value_addr)() + 1; break;
					case v_type_short:
						*(short*)set_value_addr = ((short(*)())get_value_addr)() + 1; break;
					case v_type_long:
						*(int*)set_value_addr = ((int(*)())get_value_addr)() + 1; break;
					case v_type_float:
						*(float*)set_value_addr = ((float(*)())get_value_addr)() + 0.1f; break;
					}
				}
				else
				{
					switch (value_type)
					{
					case v_type_byte:
						*(byte*)set_value_addr = *(byte*)get_value_addr + 1; break;
					case v_type_short:
						*(short*)set_value_addr = *(short*)get_value_addr + 1; break;
					case v_type_long:
						*(int*)set_value_addr = *(int*)get_value_addr + 1; break;
					case v_type_float:
						*(float*)set_value_addr = *(float*)get_value_addr + 0.1f; break;
					}
				}
			}
		}
		else if (cursor::in_object(&minus_pos, minus_tex_size_x, minus_tex_size_y))
		{
			if (use_call_to_set_value)
			{
				if (use_call_to_get_value)
				{
					switch (value_type)
					{
					case v_type_byte:
						((void(*)(byte))set_value_addr)(((byte(*)())get_value_addr)() - 1); break;
					case v_type_short:
						((void(*)(short))set_value_addr)(((short(*)())get_value_addr)() - 1); break;
					case v_type_long:
						((void(*)(long))set_value_addr)(((long(*)())get_value_addr)() - 1); break;
					case v_type_float:
						((void(*)(float))set_value_addr)(((float(*)())get_value_addr)() - 0.1f); break;
					}
				}
				else
				{
					switch (value_type)
					{
					case v_type_byte:
						((void(*)(byte))set_value_addr)(*(byte*)get_value_addr - 1); break;
					case v_type_short:
						((void(*)(short))set_value_addr)(*(short*)get_value_addr - 1); break;
					case v_type_long:
						((void(*)(int))set_value_addr)(*(int*)get_value_addr - 1); break;
					case v_type_float:
						((void(*)(float))set_value_addr)(*(float*)get_value_addr - 1.0f); break;
					}
				}
			}
			else
			{
				if (use_call_to_get_value)
				{
					switch (value_type)
					{
					case v_type_byte:
						*(byte*)set_value_addr = ((byte(*)())get_value_addr)() - 1; break;
					case v_type_short:
						*(short*)set_value_addr = ((short(*)())get_value_addr)() - 1; break;
					case v_type_long:
						*(int*)set_value_addr = ((int(*)())get_value_addr)() - 1; break;
					case v_type_float:
						*(float*)set_value_addr = ((float(*)())get_value_addr)() - 0.1f; break;
					}
				}
				else
				{
					switch (value_type)
					{
					case v_type_byte:
						*(byte*)set_value_addr = *(byte*)get_value_addr - 1; break;
					case v_type_short:
						*(short*)set_value_addr = *(short*)get_value_addr - 1; break;
					case v_type_long:
						*(int*)set_value_addr = *(int*)get_value_addr - 1; break;
					case v_type_float:
						*(float*)set_value_addr = *(float*)get_value_addr - 0.1f; break;
					}
				}
			}
		}


		while (GetAsyncKeyState(0x1)) { Sleep(10); if (click_wait_count == click_wait_max_count) { goto reclick; } else { click_wait_count++; } };
		click_wait_count = 0;
	}
}

void b_section::DrawChilds(ID3DXSprite *sprite)
{
	for (DWORD i = 0; i < buttons_count; i++)
	{
		button[i]->Draw(sprite);
		if (button[i]->b_type == b_type_section)
		{
			if (button[i] == opened_section)
			{
				sprite->Draw(((b_section*)button[i])->triangle1_tex, 0, 0, &((b_section*)button[i])->triangle1_pos, 0xFFFFFFFF);
			}
			else
			{
				sprite->Draw(((b_section*)button[i])->triangle2_tex, 0, 0, &((b_section*)button[i])->triangle2_pos, 0xFFFFFFFF);
			}
		}
	}

	if (opened_section)
	{
		opened_section->DrawChilds(sprite);
	}
}
void b_section::LMBChildsProc()
{
	for (DWORD i = 0; i < buttons_count; i++)
	{
		if (button[i]->OnMouseRect())
		{
			if (button[i]->b_type == b_type_section)
			{
				if (opened_section == (b_section *)button[i])
				{
					opened_section = 0;
				}
				else
				{
					opened_section = (b_section *)button[i];
				}
			}
			else
			{
				button[i]->ClickProc();
			}
			return;
		}
	}

	if (opened_section)
	{
		opened_section->LMBChildsProc();
	}
}
void b_section::ProcessChilds()
{
	for (DWORD i = 0; i < buttons_count; i++)
	{
		button[i]->Process();
	}

	if (opened_section)
	{
		opened_section->ProcessChilds();
	}
}
void b_section::CalculateNextPos(D3DXVECTOR2 *out)
{
	out->x = pos.x + tex_size_x + button_x_bias * core::xm;
	out->y = buttons_count != 0 ? button[buttons_count - 1]->tex_size_y + button[buttons_count - 1]->pos.y + button_y_bias * core::ym : pos.y;
}
b_button *b_section::CreateButtonFunction(const char *text, IDirect3DTexture9 *tex, ID3DXFont *font, void(*function)())
{
	D3DXVECTOR2 position;
	CalculateNextPos(&position);

	b_button *b = new b_button(text, position, tex, font, function);

	button[buttons_count] = b;
	buttons_count++;

	return b;
}
b_boolean *b_section::CreateBooleanFunction(const char *text, IDirect3DTexture9 *tex, ID3DXFont *font,
	IDirect3DTexture9 *checkbox_tex, IDirect3DTexture9 *active_checkbox_tex, void(*function)(bool))
{
	D3DXVECTOR2 position;
	CalculateNextPos(&position);

	b_boolean *b = new b_boolean(text, position, tex, font, checkbox_tex, active_checkbox_tex, function);

	button[buttons_count] = b;
	buttons_count++;

	return b;
}
b_value *b_section::CreateValueFunction(LPCSTR text, IDirect3DTexture9 *tex, ID3DXFont *font,
	IDirect3DTexture9 *button_tex, ID3DXFont *button_font, IDirect3DTexture9 *plus_tex, IDirect3DTexture9 *minus_tex, v_type v_type, bool use_call_to_get_value, bool use_call_to_set_value, void*get_value_addr, void*set_value_addr)
{
	D3DXVECTOR2 position;
	CalculateNextPos(&position);

	b_value *b = new b_value(text, position, tex, font, button_tex, button_font, plus_tex, minus_tex, v_type, use_call_to_get_value, use_call_to_set_value, get_value_addr, set_value_addr);

	button[buttons_count] = b;
	buttons_count++;

	return b;
}
b_section *b_section::CreateSection(const char * text, IDirect3DTexture9 * tex, ID3DXFont * font, IDirect3DTexture9 *tr1_tex, IDirect3DTexture9 *tr2_tex, DWORD buttons_page_size)
{
	D3DXVECTOR2 position;
	CalculateNextPos(&position);

	b_section *b = new b_section(text, position, tex, font, tr1_tex, tr2_tex, buttons_page_size);

	this->button[this->buttons_count] = b;
	this->buttons_count++;

	return b;
}
b_section::b_section(const char * text, D3DXVECTOR2 pos, IDirect3DTexture9 * tex, ID3DXFont * font, IDirect3DTexture9 *tr1_tex, IDirect3DTexture9 *tr2_tex, DWORD buttons_page_size)
	: b_prototype(text, pos, tex, font)
{
	this->b_type = b_type_section;
	opened_section = nullptr;
	buttons_count = 0;
	button = (buttons_page_size != 0) ? (new b_prototype*[buttons_page_size]) : (nullptr);
	triangle1_tex = tr1_tex;
	triangle2_tex = tr2_tex;

	if (!tr1_tex || !tr2_tex) { return; }

	triangle1_pos.z = 0.0f;
	triangle2_pos.z = 0.0f;

	D3DSURFACE_DESC desc;
	triangle1_tex->GetLevelDesc(0, &desc);

	triangle1_pos.x = this->pos.x + tex_size_x - desc.Width - 4.0f;
	triangle1_pos.y = this->pos.y + (tex_size_y / 2) - (desc.Height / 2);

	triangle2_tex->GetLevelDesc(0, &desc);

	triangle2_pos.x = this->pos.x + tex_size_x - desc.Width - 4.0f;
	triangle2_pos.y = this->pos.y + (tex_size_y / 2) - (desc.Height / 2);
}

void Menu::CalculateNextPos(D3DXVECTOR2 *out)
{
	out->x = pos.x;
	out->y = button_y_bias * core::ym + (buttons_count != 0 ? button[buttons_count - 1]->tex_size_y + button[buttons_count - 1]->pos.y: tex_size_y + pos.y);
}
void Menu::Open()
{
	if (!is_open)
	{
		core::AddLoopEx(&process_loop);
		core::AddDirectX9LoopEx(&direct_loop);
		core::AddMouseLoopEx(&lmb_loop);
		is_open = true;
	}
}
void Menu::Close()
{
	if (is_open)
	{
		core::FreeLoopEx(&process_loop);
		core::FreeDirectX9LoopEx(&direct_loop);
		core::FreeMouseLoopEx(&lmb_loop);
		is_open = false;
	}
}
void Menu::BeginProcess()
{
	ProcessChilds();
}
void Menu::BeginDraw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	Draw(sprite);
	DrawChilds(sprite);

	sprite->End();
}
void Menu::BeginLMBProcess()
{
	LMBChildsProc();
	while (GetAsyncKeyState(0x1)) { Sleep(5); }
}
void Menu::BeginCloseOpenProcess()
{
	if (GetAsyncKeyState(vk_code))
	{
		is_open ? Close() : Open();
		while (GetAsyncKeyState(vk_code)) { Sleep(5); }
	}
}

void MenuProcess(Menu *obj) { obj->BeginProcess(); }
void MenuDirectProcess(IDirect3DDevice9 *dev, Menu *obj) { obj->BeginDraw(); }
void MenuLMBProcess(Menu *obj) { obj->BeginLMBProcess(); }
void MenuCloseOpenProcess(Menu *obj) { obj->BeginCloseOpenProcess(); }

Menu::Menu(const char * text, D3DXVECTOR2 pos, IDirect3DTexture9 * tex, ID3DXFont * font, DWORD buttons_page_size, ID3DXSprite * sprite, int vk_code)
	: b_section(text, pos, tex, font, 0, 0, buttons_page_size)
{
	this->sprite = sprite;
	this->vk_code = vk_code;
	this->is_open = false;

	process_loop.start_address = MenuProcess;
	direct_loop.start_address = MenuDirectProcess;
	lmb_loop.start_address = MenuLMBProcess;
	close_open_loop.start_address = MenuCloseOpenProcess;

	process_loop.parameter = (DWORD)this;
	direct_loop.parameter = (DWORD)this;
	lmb_loop.parameter = (DWORD)this;
	close_open_loop.parameter = (DWORD)this;
	
	core::AddLoopEx(&close_open_loop);
}

/* --- menu.cpp structure ---
// b_prototype methods
// b_button methods
// b_boolean methods 
// b_value methods
// b_section methods
// Menu methods
*/

/* --- menu.cpp class code procedure ---
// 1) Methods
// 2) Extra functions
// 3) Constructors
*/