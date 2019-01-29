#include "core.h"

void ErrorMessage(const char *_text) {
	char text[256]; sprintf(text, "%s\nOk - close game", _text);
	if (MessageBox(0, text, 0, MB_ICONERROR | MB_OKCANCEL) == IDOK) { exit(1); }
}

void ErrorMessageWithLastError(const char *_text) {
	char text[256]; sprintf(text, "%s\nGetLastError returned - 0x%X\nOk - close game", _text, GetLastError());
	if (MessageBox(0, text, 0, MB_ICONERROR | MB_OKCANCEL) == IDOK) { exit(1); }
}

void ErrorMessageWithHexValue(const char *_text, DWORD HexValue) {
	char text[256]; sprintf(text, "%s0x%X\nOk - close game", _text, HexValue);
	if (MessageBox(0, text, 0, MB_ICONERROR | MB_OKCANCEL) == IDOK) { exit(1); }
}