#include "menu.h"
#include "messagebox.h"

using namespace menu;
using namespace buttons;

s_simple * opened_section;

IDirect3DTexture9 *buttons::buttonFillTex, *buttons::buttonBorderTex;
IDirect3DTexture9 *buttons::checkboxFillTex, *buttons::checkboxBorderTex;
IDirect3DTexture9 *buttons::checkboxActiveTex, *buttons::valueBoxIconTex;

ID3DXSprite *buttons::sprite;

#define bcd buttons::constdata

void menu::buttons::Initializing()
{
	using namespace buttons::constdata;

	d3dresloader::sprite(&sprite);
	
	d3dresloader::texture(size_x, size_y, mcd::fcPath, &buttonFillTex);
	d3dresloader::texture(size_x + DefBorder, size_y + DefBorder, mcd::fcPath, &buttonBorderTex);

	d3dresloader::texture(checkbox_active_size, checkbox_active_size, mcd::fcPath, &checkboxActiveTex);
	d3dresloader::texture(checkbox_active_size, checkbox_active_size, mcd::fcPath, &valueBoxIconTex);

	d3dresloader::texture(checkbox_size, checkbox_size, mcd::fcPath, &checkboxFillTex);
	d3dresloader::texture(checkbox_size + DefBorder, checkbox_size + DefBorder, mcd::fcPath, &checkboxBorderTex);
}

void b_prototype::DrawButton(ID3DXSprite *spr) const
{
	spr->Draw(buttonFillTex, 0, 0, &border_pos, core::color::board_color);
	spr->Draw(buttonBorderTex, 0, 0, &pos, core::color::color);
}

void b_boolean::Draw(ID3DXSprite *spr) const
{
	DrawButton(spr);

	spr->Draw(checkboxBorderTex, 0, 0, &checkbox_board_pos, core::color::board_color);
	spr->Draw(checkboxFillTex, 0, 0, &checkbox_pos, core::color::color);

	if (active) {
		spr->Draw(checkboxActiveTex, 0, 0, &checkbox_active_pos, core::color::board_color);
	}

	core::font::big_size->DrawText(spr, text, -1, (RECT *)&text_rect, DT_NOCLIP, core::color::font_color);
}

void b_value::Draw(ID3DXSprite *spr) const
{
	DrawButton(spr);

	spr->Draw(checkboxBorderTex, 0, 0, &checkbox_border_pos, core::color::board_color);
	spr->Draw(checkboxFillTex, 0, 0, &checkbox_pos, core::color::color);
	spr->Draw(valueBoxIconTex, 0, 0, &icon_pos, core::color::font_color);

	core::font::medium_size->DrawTextA(spr, v_text, -1, (RECT *)&v_text_rect, DT_NOCLIP, core::color::font_color);

	core::font::big_size->DrawText(spr, text, -1, (RECT *)&text_rect, DT_NOCLIP, core::color::font_color);
}

void b_simple::Draw(ID3DXSprite *spr) const {
	DrawButton(spr);
	core::font::big_size->DrawText(spr, text, -1, (RECT *)&text_rect, DT_NOCLIP, core::color::font_color - text_color_offset);
}

void b_boolean::Activate() {
	active = !active;
	function(active);
}

void b_value::Activate() {
	static char textBuffer[256];
	sprintf(textBuffer, "%s%s", "Enter value to : ", text);
	messagebox::CreateGetValue(set_value_address, (char*)textBuffer, v_type, use_call_for_set_value);
}

void b_simple::Activate() {
	((ARGB*)&text_color_offset)->a = 127;
	((ARGB*)&text_color_offset)->r = 127;
	((ARGB*)&text_color_offset)->g = 127;
	((ARGB*)&text_color_offset)->b = 127;
	function();
}

void b_value::Update()
{
	switch (v_type)
	{
	case v_type_char:
		if (use_call_for_get_value) sprintf(v_text, "%u", ((unsigned char(*)())get_value_address)());
		else sprintf(v_text, "%u", *(unsigned char*)get_value_address);
		return;
	case v_type_short:
		if (use_call_for_get_value) sprintf(v_text, "%d", ((short(*)())get_value_address)());
		else sprintf(v_text, "%d", *(short*)get_value_address);
		return;
	case v_type_int:
		if (use_call_for_get_value) sprintf(v_text, "%d", ((int(*)())get_value_address)());
		else sprintf(v_text, "%d", *(int*)get_value_address);
		return;
	case v_type_float:
		if (use_call_for_get_value) sprintf(v_text, "%f", ((float(*)())get_value_address)());
		else sprintf(v_text, "%f", *(float*)get_value_address);
		return;
	case v_type_double:
		if (use_call_for_get_value) sprintf(v_text, "%f", ((double(*)())get_value_address)());
		else sprintf(v_text, "%f", *(double*)get_value_address);
		return;
	case v_type_string:
		if (use_call_for_get_value) strcpy(v_text, ((char*(*)())get_value_address)());
		else strcpy(v_text, (char*)get_value_address);
		return;
	}
}

const int b_value::int_value_factor = 1;
const float b_value::float_value_factor = 0.001f;
const double b_value::double_value_factor = 0.001;

void b_value::add_to_function()
{
	if (use_call_for_set_value)
	{
		if (use_call_for_get_value)
		{
			switch (v_type)
			{
			case v_type_char:((void(*)(char))set_value_address)(((char(*)())get_value_address)() + int_value_factor); break;
			case v_type_short:((void(*)(short))set_value_address)(((short(*)())get_value_address)() + int_value_factor); break;
			case v_type_int:((void(*)(int))set_value_address)(((int(*)())get_value_address)() + int_value_factor); break;
			case v_type_float:((void(*)(float))set_value_address)(((float(*)())get_value_address)() + float_value_factor); break;
			case v_type_double:((void(*)(double))set_value_address)(((double(*)())get_value_address)() + double_value_factor); break;
			}
		}
		else
		{
			switch (v_type)
			{
			case v_type_char:((void(*)(char))set_value_address)(*(char*)get_value_address + int_value_factor); break;
			case v_type_short:((void(*)(short))set_value_address)(*(short*)get_value_address + int_value_factor); break;
			case v_type_int:((void(*)(int))set_value_address)(*(int*)get_value_address + int_value_factor); break;
			case v_type_float:((void(*)(float))set_value_address)(*(float*)get_value_address + float_value_factor); break;
			case v_type_double:((void(*)(double))set_value_address)(*(double*)get_value_address + double_value_factor); break;
			}
		}
	}
	else
	{
		if (use_call_for_get_value)
		{
			switch (v_type)
			{
			case v_type_char:*(char*)set_value_address = ((char(*)())get_value_address)() + int_value_factor; break;
			case v_type_short:*(short*)set_value_address = ((short(*)())get_value_address)() + int_value_factor; break;
			case v_type_int:*(int*)set_value_address = ((int(*)())get_value_address)() + int_value_factor; break;
			case v_type_float:*(float*)set_value_address = ((float(*)())get_value_address)() + float_value_factor; break;
			case v_type_double:*(double*)set_value_address = ((double(*)())get_value_address)() + double_value_factor; break;
			}
		}
		else
		{
			switch (v_type)
			{
			case v_type_char:*(char*)set_value_address = *(char*)get_value_address + int_value_factor; break;
			case v_type_short:*(short*)set_value_address = *(short*)get_value_address + int_value_factor; break;
			case v_type_int:*(int*)set_value_address = *(int*)get_value_address + int_value_factor; break;
			case v_type_float:*(float*)set_value_address = *(float*)get_value_address + float_value_factor; break;
			case v_type_double:*(double*)set_value_address = *(double*)get_value_address + double_value_factor; break;
			}
		}
	}
}

void b_value::sub_to_function()
{
	if (use_call_for_set_value)
	{
		if (use_call_for_get_value)
		{
			switch (v_type)
			{
			case v_type_char:((void(*)(char))set_value_address)(((char(*)())get_value_address)() - int_value_factor); break;
			case v_type_short:((void(*)(short))set_value_address)(((short(*)())get_value_address)() - int_value_factor); break;
			case v_type_int:((void(*)(int))set_value_address)(((int(*)())get_value_address)() - int_value_factor); break;
			case v_type_float:((void(*)(float))set_value_address)(((float(*)())get_value_address)() - float_value_factor); break;
			case v_type_double:((void(*)(double))set_value_address)(((double(*)())get_value_address)() - double_value_factor); break;
			}
		}
		else
		{
			switch (v_type)
			{
			case v_type_char:((void(*)(char))set_value_address)(*(char*)get_value_address - int_value_factor); break;
			case v_type_short:((void(*)(short))set_value_address)(*(short*)get_value_address - int_value_factor); break;
			case v_type_int:((void(*)(int))set_value_address)(*(int*)get_value_address - int_value_factor); break;
			case v_type_float:((void(*)(float))set_value_address)(*(float*)get_value_address - float_value_factor); break;
			case v_type_double:((void(*)(double))set_value_address)(*(double*)get_value_address - double_value_factor); break;
			}
		}
	}
	else
	{
		if (use_call_for_get_value)
		{
			switch (v_type)
			{
			case v_type_char:*(char*)set_value_address = ((char(*)())get_value_address)() - int_value_factor; break;
			case v_type_short:*(short*)set_value_address = ((short(*)())get_value_address)() - int_value_factor; break;
			case v_type_int:*(int*)set_value_address = ((int(*)())get_value_address)() - int_value_factor; break;
			case v_type_float:*(float*)set_value_address = ((float(*)())get_value_address)() - float_value_factor; break;
			case v_type_double:*(double*)set_value_address = ((double(*)())get_value_address)() - double_value_factor; break;
			}
		}
		else
		{
			switch (v_type)
			{
			case v_type_char:*(char*)set_value_address = *(char*)get_value_address - int_value_factor; break;
			case v_type_short:*(short*)set_value_address = *(short*)get_value_address - int_value_factor; break;
			case v_type_int:*(int*)set_value_address = *(int*)get_value_address - int_value_factor; break;
			case v_type_float:*(float*)set_value_address = *(float*)get_value_address - float_value_factor; break;
			case v_type_double:*(double*)set_value_address = *(double*)get_value_address - double_value_factor; break;
			}
		}
	}
}

void b_value::Process() {
	Update();
}
void b_simple::Process() {
	if (((ARGB*)&text_color_offset)->a > 0) { ((ARGB*)&text_color_offset)->a -= 1; }
	if (((ARGB*)&text_color_offset)->r > 0) { ((ARGB*)&text_color_offset)->r -= 1; }
	if (((ARGB*)&text_color_offset)->g > 0) { ((ARGB*)&text_color_offset)->g -= 1; }
	if (((ARGB*)&text_color_offset)->b > 0) { ((ARGB*)&text_color_offset)->b -= 1; }
}

bool b_boolean::OnCursor() {
	return cursor::in_object_prop(&checkbox_pos, buttons::constdata::checkbox_size);
}
bool b_value::OnCursor() {
	return cursor::in_object_prop(&checkbox_pos, buttons::constdata::checkbox_size);
}
bool b_value::OnCursorPlus() {
	return cursor::in_object_prop(&b_plus_pos, buttons::constdata::size_y);
}
bool b_value::OnCursorMinus() {
	return cursor::in_object_prop(&b_minus_pos, buttons::constdata::size_y);
}
bool b_simple::OnCursor() {
	return cursor::in_object_prop(&pos, buttons::constdata::checkbox_size);
}

bool b_boolean::LMBClickProcess() {
	if (OnCursor()) { Activate(); return true; }
	else return false;
}
bool b_value::LMBClickProcess() {
	if (OnCursor()) {
		Activate(); return true;
	}
	else if (OnCursorPlus()) {
		add_to_function(); return true;
	}
	else if (OnCursorMinus()) {
		sub_to_function(); return true;
	}
	else {
		return false;
	}
}
bool b_simple::LMBClickProcess() {
	if (OnCursor()) { Activate(); return true; }
	else { return false; }
}

void LMBProcSection()
{
	s_simple *os = opened_section;
	for (int i = 0; i < os->buttons_count; i++) {
		if (os->bpp[i]->LMBClickProcess()) {
			while (GetAsyncKeyState(VK_LBUTTON)) { Sleep(50); } return;
		}
	}
}

void ProcSection()
{
	s_simple *os = opened_section;
	for (int i = 0; i < os->buttons_count; i++) {
		os->bpp[i]->Process();
	}
}

void DrawSection(IDirect3DDevice9 *dev)
{
	ID3DXSprite *spr = sprite;
	s_simple *os = opened_section;


	spr->Begin(D3DXSPRITE_ALPHABLEND);

	for (int i = 0; i < os->buttons_count; i++) {
		os->bpp[i]->Draw(spr);
	}

	spr->End();
}

void menu::buttons::Show()
{
	core::AddLoop(ProcSection);
	core::AddLmbLoop(LMBProcSection);
	core::AddDirectLoop(DrawSection);
}

void menu::buttons::Hide()
{
	core::FreeLoop(ProcSection);
	core::FreeLmbLoop(LMBProcSection);
	core::FreeDirectLoop(DrawSection);
}

