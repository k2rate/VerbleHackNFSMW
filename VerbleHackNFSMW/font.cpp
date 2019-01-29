#include "core.h"

using namespace core;

unsigned __cdecl _get_font_value_data(const char * data_name)
{
	unsigned retValue = GetPrivateProfileIntA(font::constdata::configBasicBlockName, data_name, -1, font::constdata::configFilePath);
	if (retValue != -1) {
		return retValue;
	}
	
	char errorText[256];

	strcpy(errorText, data_name);
	strcat(errorText, " read error :(\n function returned -1\n Close game?");

	int mbResult = MessageBoxA(NULL, errorText, "_get_font_value_data()", MB_YESNO | MB_ICONERROR);

	if (mbResult == IDYES) {
		exit(retValue);
	}

	return retValue;
}

ID3DXFont *font::small_size = 0, 
	*font::medium_size = 0, 
	*font::big_size = 0;

void font::Initializing(IDirect3DDevice9 *pDev)
{
	char fontName[264];

	GetPrivateProfileStringA("main", "fontName", font::constdata::defaultName, fontName, sizeof(fontName), font::constdata::configFilePath);

	if (strcmp(font::constdata::defaultName, fontName) == 0) {
		MessageBoxA(NULL, "strcmp(font::constdata::defaultName, fontName) == 0\n check resources or reinstall software\n", "font::Initializing()", MB_OK | MB_ICONWARNING);
	}
	
	AddFontResourceExA(fontName, FR_PRIVATE, 0);

	DWORD small_size_x = _get_font_value_data("small_size_x") * xm;
	DWORD small_size_y = _get_font_value_data("small_size_y") * ym;
	DWORD small_weight = _get_font_value_data("small_weight");

	DWORD medium_size_x = _get_font_value_data("medium_size_x") * xm;;
	DWORD medium_size_y = _get_font_value_data("medium_size_y") * ym;
	DWORD medium_weight = _get_font_value_data("medium_weight");

	DWORD big_size_x = _get_font_value_data("big_size_x") * xm;;
	DWORD big_size_y = _get_font_value_data("big_size_y") * ym;
	DWORD big_weight = _get_font_value_data("big_weight");

	small_size = MyD3DXCreateFont(pDev, small_size_y, small_size_x,  small_weight, 8, 0, RUSSIAN_CHARSET, 0, 0, 0 | FF_DONTCARE, fontName);
	medium_size = MyD3DXCreateFont(pDev, medium_size_y, medium_size_x,  medium_weight, 8, 0, RUSSIAN_CHARSET, 0, 0, 0 | FF_DONTCARE, fontName);
	big_size = MyD3DXCreateFont(pDev, big_size_y, big_size_x,  big_weight, 8, 0, RUSSIAN_CHARSET, 0, 0, 0 | FF_DONTCARE, fontName);
}
