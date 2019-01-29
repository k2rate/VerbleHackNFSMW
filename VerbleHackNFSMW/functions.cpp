#include "menu.h"

#include <Windows.h>
#include <stdio.h>

#include "MostWanted.h"
#include "menu.h"
#include "messagebox.h"

using namespace core;

#pragma region Profile

void Name(const char* v) { strcpy((char*)(*(DWORD*)(*(DWORD*)(0x0091CF90) + 0x10) + 0x0), v); }
const char* GetName() { return (char*)(*(DWORD*)(*(DWORD*)(0x0091CF90) + 0x10) + 0x0); }

void Money(int v) { *(int*)(*(DWORD*)(*(DWORD*)(0x0091CF90) + 0x10) + 0xB4) = v; }
int GetMoney() { return *(int*)(*(DWORD*)(*(DWORD*)(0x0091CF90) + 0x10) + 0xB4); }

float MaxHeatLevel = 5.0f, MinHeatLevel = 1.0f;
DWORD HeatLevelsCodeCaveExit = 0x00443DC9;
void __declspec(naked) HeatLevelsCodeCave()
{
	_asm
	{
		mov ebx, MaxHeatLevel
		mov[esi + 0xE0], ebx
		mov edx, ebx
		mov ebx, MinHeatLevel
		mov[esi + 0xDC], ebx
		jmp HeatLevelsCodeCaveExit
	}
}

void HeatLimitHook()
{
	// Ranged Nop
	for (int i = 0x00443DC3; i < 0x00443DC9; i++)
	{
		*(byte*)i = 0x90;
	}

	// Make jmp
	*(byte*)0x00443DC3 = 0xE9;
	*(DWORD*)(0x00443DC3 + 0x1) = (DWORD)HeatLevelsCodeCave - (0x00443DC3 + 0x5);
}

void HeatLimitUpdate()
{
	*(float*)0x7bb502 = MaxHeatLevel;
	*(float*)0x7b1387 = MaxHeatLevel;
	*(float*)0x7b0c89 = MaxHeatLevel;
	*(float*)0x7B4D7C = MaxHeatLevel;
	*(float**)0x435079 = &MaxHeatLevel;
	*(float*)0x435088 = MaxHeatLevel;
}

void MaxHeat(float v) { MaxHeatLevel = v; HeatLimitUpdate(); }
float GetMaxHeat() { return **(float**)0x435079; }

void HeatLevel(float v)
{
	if (*(DWORD*)0x00934CF4 == 0)
	{
		return;
	}
	*(float*)(*(DWORD*)0x00934CF4 + 0x14) = v;
}
float GetHeatLevel()
{
	if (*(DWORD*)0x00934CF4 == 0)
	{
		return 0.0f;
	}
	return *(float*)(*(DWORD*)0x00934CF4 + 0x14);
}

void CameraMode(int v) { *(int*)(*(DWORD*)(*(DWORD*)(0x0091CF90) + 0x10) + 0x8C) = v; }
int GetCameraMode() { return *(int*)(*(DWORD*)(*(DWORD*)(0x0091CF90) + 0x10) + 0x8C); }

void UnlockAll(bool t) { *(int*)0x00926124 = t; }

void GarageSlots(char v) { *(char*)0x007C1A77 = v; }
char GetGarageSlots() { return *(char*)0x007C1A77; }

void AutoDrive(bool t) { *(unsigned char*)0x90D5FA = 1; }

#pragma endregion

#pragma region Car

void UseNitroIfIsNotInstalled(bool t)
{
	if (t)
	{
		*(byte*)0x00692944 = 0xEB; // always jmp in start function
		*(byte*)(0x00692A79 + 0x2) = 0x00; // test al,00
	}
	else
	{
		*(byte*)0x00692944 = 0x75;
		*(byte*)(0x00692A79 + 0x2) = 0x41;
	}
}
void UseNitroIfNotMotion(bool t)
{
	if (t)
	{
		*(byte*)0x00692A1D = 0x84;
		*(byte*)(0x00692A1D + 0x1) = 0xC4;
		*(byte*)(0x00692A1D + 0x2) = 0x90;

		*(byte*)0x006929F7 = 0x84;
		*(byte*)(0x006929F7 + 0x1) = 0xC4;
		*(byte*)(0x006929F7 + 0x2) = 0x90;
	}
	else
	{
		*(byte*)0x00692A1D = 0xF6;
		*(byte*)(0x00692A1D + 0x1) = 0xC4;
		*(byte*)(0x00692A1D + 0x2) = 0x05;

		*(byte*)0x006929F7 = 0xF6;
		*(byte*)(0x006929F7 + 0x1) = 0xC4;
		*(byte*)(0x006929F7 + 0x2) = 0x41;
	}
}
void UseNitroIfIsEmpty(bool t)
{
	if (t)
	{
		for (int i = 0x00692AA7; i < 0x00692AAD; i++) {
			*(byte*)i = 0x90;
		}
	}
	else
	{
		*(byte*)0x00692AA7 = 0x0F;
		*(byte*)(0x00692AA7 + 0x1) = 0x85;
		*(DWORD*)(0x00692AA7 + 0x2) = 0xA4;
	}
}

void nitropower(float v)
{
	if (*(DWORD*)0x0925E90 != 6) { return; }
	if (*(DWORD*)0x00913E80 == NULL) { return; }

	DWORD LocalPlayer = *(DWORD*)0x00913E80 + 0x08;

	if (*(DWORD*)LocalPlayer == NULL) { return; }

	DWORD LocalPlayerOffset = *(DWORD*)LocalPlayer + 0x60;
	DWORD LocalPlayerOffset2 = *(DWORD*)LocalPlayerOffset + 0xD0;

	*(float*)(*(DWORD*)LocalPlayerOffset2 + 0x04) = v;
}
float getnitropower()
{
	if (*(DWORD*)0x0925E90 != 6) { return 0.0f; }
	if (*(DWORD*)0x00913E80 == NULL) { return 0.0f; }

	DWORD LocalPlayer = *(DWORD*)0x00913E80 + 0x08;

	if (*(DWORD*)LocalPlayer == NULL) { return 0.0f; }

	DWORD LocalPlayerOffset = *(DWORD*)LocalPlayer + 0x60;
	DWORD LocalPlayerOffset2 = *(DWORD*)LocalPlayerOffset + 0xD0;

	return *(float*)(*(DWORD*)LocalPlayerOffset2 + 0x04);
}

DWORD bfaddr2jn;

void NitroNotEnd(bool t)
{
	if (t)
	{
		*(byte*)(0x00692B06 + 0x1) = 0x1D;
		*(DWORD*)(0x00692B06 + 0x2) = (DWORD)&bfaddr2jn;
	}
	else
	{
		*(byte*)(0x00692B06 + 0x1) = 0x9E;
		*(DWORD*)(0x00692B06 + 0x2) = 0xF8;
	}
}
void SpeedbrakerNotEnd(bool t)
{
	if (t)
	{
		*(byte*)(0x006EDE03 + 0x1) = 0x1D;
		*(DWORD*)(0x006EDE03 + 0x2) = (DWORD)&bfaddr2jn;
	}
	else
	{
		*(byte*)(0x006EDE03 + 0x1) = 0x9E;
		*(DWORD*)(0x006EDE03 + 0x2) = 0x84;
	}
}

DWORD IndividualHandlingCodeCave = 0x0069CB87; // ret 0004
DWORD HBuffer = 0;
DWORD eaxbuff = 0;
float HandlingSensivity = 0.1f;
float HandlingBrakeSensivity = 0.3f;
float HandlingOutSensivity = 0.06f;
float HandlingDeadline = 1.0f;
void _declspec(naked) IndividualHandlingHookedCode()
{
	_asm
	{
		mov HBuffer, ecx
	}

	if ((HBuffer + 0x0C) == (*(DWORD*)(*(DWORD*)0x009352B0 + 0xE8) + 0x0C))
	{
		if (GetAsyncKeyState(VK_LEFT))
		{
			if (*(float*)(HBuffer + 0x0C) > -HandlingDeadline)
			{
				*(float*)(HBuffer + 0x0C) += ((-1.1f - *(float*)(HBuffer + 0x0C)) * HandlingSensivity);
				if (GetAsyncKeyState(VK_SPACE)) {
					*(float*)(HBuffer + 0x0C) += ((-1.1f - *(float*)(HBuffer + 0x0C)) * HandlingBrakeSensivity);
				}
			}

		}
		else if (GetAsyncKeyState(VK_RIGHT))
		{
			if (*(float*)(HBuffer + 0x0C) < HandlingDeadline)
			{
				*(float*)(HBuffer + 0x0C) += ((1.1f - *(float*)(HBuffer + 0x0C)) * HandlingSensivity);
				if (GetAsyncKeyState(VK_SPACE)) {
					*(float*)(HBuffer + 0x0C) += ((1.1f - *(float*)(HBuffer + 0x0C)) * HandlingBrakeSensivity);
				}
			}
		}
		else
		{

			if (*(float*)(HBuffer + 0x0C) > 0.0f)
			{
				if (*(float*)(HBuffer + 0x0C) < 0.02f)
				{
					*(float*)(HBuffer + 0x0C) = 0.0f;
				}
				else
				{
					*(float*)(HBuffer + 0x0C) -= HandlingOutSensivity;
				}
			}
			else if (*(float*)(HBuffer + 0x0C) < 0.0f)
			{
				if (*(float*)(HBuffer + 0x0C) > -0.02f)
				{
					*(float*)(HBuffer + 0x0C) = 0.0f;
				}
				else
				{
					*(float*)(HBuffer + 0x0C) += HandlingOutSensivity;
				}
			}

		}
	}
	else
	{
		_asm
		{
			mov ecx, HBuffer
			mov eax, [esp + 0x04]
			mov[ecx + 0x0C], eax
		}
	}
	_asm
	{
		jmp IndividualHandlingCodeCave
	}
}
void IndividualHandling(bool t)
{
	if (t)
	{
		*(byte*)0x0069CB80 = 0xE9;
		*(DWORD*)(0x0069CB80 + 0x1) = (DWORD)IndividualHandlingHookedCode - (0x0069CB80 + 0x5);
		*(byte*)(0x0069CB80 + 0x5) = 0x90; *(byte*)(0x0069CB80 + 0x6) = 0x90;
	}
	else
	{
		*(DWORD*)0x0069CB80 = (DWORD)0x0424448B; // mov eax,[esp + 04]
		// mov [ecx + 0C], eax
		*(short*)(0x0069CB80 + 0x4) = (short)0x4189;
		*(byte*)(0x0069CB80 + 0x6) = 0x0C;
	}
}

int Return0Hook() { return 0; }
void NoRev(bool t)
{
	if (t)
	{
		*(DWORD*)0x008AB78C = (DWORD)&Return0Hook;
		*(DWORD*)0x008AC034 = (DWORD)&Return0Hook;
	}
	else
	{
		*(DWORD*)0x008AB78C = 0x006A05E0;
		*(DWORD*)0x008AC034 = 0x006B3D20;
	}
}
void NoClip(bool t)
{
	if (t)
	{
		*(byte*)0x006BB77E = 0xEB;
	}
	else
	{
		*(byte*)0x006BB77E = 0x75;
	}
}
void NoCollision(bool t)
{
	if (t)
	{
		*(byte*)0x00699F55 = 0x00;
	}
	else
	{
		*(byte*)0x00699F55 = 0x02;
	}
}

#pragma endregion

#pragma region Objects
#pragma region data
unsigned g_selected_object = 0;

void setinc1(float v) { *(float*)(0x009386C8 + (g_selected_object * 0xB0)) = v; }
void setrot1(float v) { *(float*)(0x009386CC + (g_selected_object * 0xB0)) = v; }
void setinc2(float v) { *(float*)(0x009386D0 + (g_selected_object * 0xB0)) = v; }
void setrot2(float v) { *(float*)(0x009386D4 + (g_selected_object * 0xB0)) = v; }
float getinc1() { return  *(float*)(0x009386C8 + (g_selected_object * 0xB0)); }
float getrot1() { return  *(float*)(0x009386CC + (g_selected_object * 0xB0)); }
float getinc2() { return  *(float*)(0x009386D0 + (g_selected_object * 0xB0)); }
float getrot2() { return  *(float*)(0x009386D4 + (g_selected_object * 0xB0)); }

void setY(float v) { *(float*)(0x009386D8 + (g_selected_object * 0xB0)) = v; }
void setZ(float v) { *(float*)(0x009386DC + (g_selected_object * 0xB0)) = v; }
void setX(float v) { *(float*)(0x009386E0 + (g_selected_object * 0xB0)) = v; }
float getY() { return *(float*)(0x009386D8 + (g_selected_object * 0xB0)); }
float getZ() { return *(float*)(0x009386DC + (g_selected_object * 0xB0)); }
float getX() { return *(float*)(0x009386E0 + (g_selected_object * 0xB0)); }

void setspdY(float v) { *(float*)(0x009386E8 + (g_selected_object * 0xB0)) = v; }
void setspdZ(float v) { *(float*)(0x009386EC + (g_selected_object * 0xB0)) = v; }
void setspdX(float v) { *(float*)(0x009386F0 + (g_selected_object * 0xB0)) = v; }
float getspdY() { return *(float*)(0x009386E8 + (g_selected_object * 0xB0)); }
float getspdZ() { return *(float*)(0x009386EC + (g_selected_object * 0xB0)); }
float getspdX() { return *(float*)(0x009386F0 + (g_selected_object * 0xB0)); }

void setweight(float v) { *(float*)(0x009386F4 + (g_selected_object * 0xB0)) = v; }
float getweight() { return *(float*)(0x009386F4 + (g_selected_object * 0xB0)); }

void setcoup1(float v) { *(float*)(0x009386F8 + (g_selected_object * 0xB0)) = v; }
void setturn1(float v) { *(float*)(0x009386FC + (g_selected_object * 0xB0)) = v; }
void setincline1(float v) { *(float*)(0x00938700 + (g_selected_object * 0xB0)) = v; }
float getcoup1() { return *(float*)(0x009386F8 + (g_selected_object * 0xB0)); }
float getturn1() { return *(float*)(0x009386FC + (g_selected_object * 0xB0)); }
float getincline1() { return *(float*)(0x00938700 + (g_selected_object * 0xB0)); }

void setpower(float v) { *(float*)(0x00938704 + (g_selected_object * 0xB0)) = v; }
void setshakiness1(float v) { *(float*)(0x00938708 + (g_selected_object * 0xB0)) = v; }
void setmobility(float v) { *(float*)(0x0093870C + (g_selected_object * 0xB0)) = v; }
void setshakiness2(float v) { *(float*)(0x00938710 + (g_selected_object * 0xB0)) = v; }
float getpower() { return *(float*)(0x00938704 + (g_selected_object * 0xB0)); }
float getshakiness1() { return *(float*)(0x00938708 + (g_selected_object * 0xB0)); }
float getmobility() { return *(float*)(0x0093870C + (g_selected_object * 0xB0)); }
float getshakiness2() { return *(float*)(0x00938710 + (g_selected_object * 0xB0)); }

void setspdY2(float v) { *(float*)(0x00938718 + (g_selected_object * 0xB0)) = v; }
void setspdZ2(float v) { *(float*)(0x0093871C + (g_selected_object * 0xB0)) = v; }
void setspdX2(float v) { *(float*)(0x00938720 + (g_selected_object * 0xB0)) = v; }
float getspdY2() { return *(float*)(0x00938718 + (g_selected_object * 0xB0)); }
float getspdZ2() { return *(float*)(0x0093871C + (g_selected_object * 0xB0)); }
float getspdX2() { return *(float*)(0x00938720 + (g_selected_object * 0xB0)); }

void setblock(char v) { *(char*)(0x00938725 + (g_selected_object * 0xB0)) = v; }
char getblock() { return *(char*)(0x00938725 + (g_selected_object * 0xB0)); }

void setcoup2(float v) { *(float*)(0x00938728 + (g_selected_object * 0xB0)) = v; }
void setturn2(float v) { *(float*)(0x0093872C + (g_selected_object * 0xB0)) = v; }
void setincline2(float v) { *(float*)(0x00938730 + (g_selected_object * 0xB0)) = v; }
float getcoup2() { return *(float*)(0x00938728 + (g_selected_object * 0xB0)); }
float getturn2() { return *(float*)(0x0093872C + (g_selected_object * 0xB0)); }
float getincline2() { return *(float*)(0x00938730 + (g_selected_object * 0xB0)); }
#pragma endregion
void delete_traffic_thread()
{
	for (int i = 1; i < 50; i++)
	{
		if (mw_object[i] != 0)
		{
			mw_object[i]->x = 0;
			mw_object[i]->y = 0;
			mw_object[i]->z = 0;
		}
	}
}
void ObjectsToTrash(bool t)
{
	if (t)
	{
		core::AddLoop(delete_traffic_thread);
	}
	else
	{
		core::FreeLoop(delete_traffic_thread);
	}
}
#pragma endregion

#pragma region Camera

DWORD __degstr; DWORD mem_ = (DWORD)&__degstr; DWORD freeptr = (DWORD)&mem_;
DWORD camhookcave = 0x006514B2;
DWORD ecxbf, eaxbf;

__declspec(naked)void pushact()
{
	_asm
	{
		mov ecx, ecxbf
		fadd dword ptr[ecx + 0x1C]
		mov ecx, freeptr
		fstp dword ptr[ecx]

		mov ecx, ecxbf
		mov eax, eaxbf

		jmp camhookcave
	}
}

DWORD rCamRotX = FALSE, rCamRotY = FALSE, rCamInclineY = FALSE, rCamAngle = FALSE, rCamRotAngle = FALSE, rCamDistance = FALSE, rCamHeight = FALSE;
#define checkcambool(x) if(x==TRUE){_asm{jmp pushact}}

__declspec(naked)void hookedcamupdate()
{
	_asm
	{
		mov ecxbf, ecx
		mov eaxbf, eax
	}

	if (ecxbf == (DWORD)(float*)(*(DWORD*)(*(DWORD*)0x0093DA4C + 0x94) + 0x00))
	{
		checkcambool(rCamRotAngle);
	}
	else if (ecxbf == (DWORD)(float*)(*(DWORD*)(*(DWORD*)0x0093DA4C + 0x94) + 0x2C))
	{
		checkcambool(rCamRotAngle);
	}
	else if (ecxbf == (DWORD)(float*)(*(DWORD*)(*(DWORD*)0x0093DA4C + 0x90) + 0x00))
	{
		checkcambool(rCamRotX);
	}
	else if (ecxbf == (DWORD)(float*)(*(DWORD*)(*(DWORD*)0x0093DA4C + 0x90) + 0x2C))
	{
		checkcambool(rCamRotX);
	}
	else if (ecxbf == (DWORD)(float*)(*(DWORD*)(*(DWORD*)0x0093DA4C + 0x90) + 0x58))
	{
		checkcambool(rCamRotY);
	}
	else if (ecxbf == (DWORD)(float*)(*(DWORD*)(*(DWORD*)0x0093DA4C + 0x8C) + 0x58))
	{
		checkcambool(rCamInclineY);
	}
	else if (ecxbf == (DWORD)(float*)(*(DWORD*)(*(DWORD*)0x0093DA4C + 0x84) + 0x00))
	{
		checkcambool(rCamAngle);
	}
	else if (ecxbf == (DWORD)(float*)(*(DWORD*)(*(DWORD*)0x0093DA4C + 0x88) + 0x00))
	{
		checkcambool(rCamDistance);
	}
	else if (ecxbf == (DWORD)(float*)(*(DWORD*)(*(DWORD*)0x0093DA4C + 0x88) + 0x58))
	{
		checkcambool(rCamHeight);
	}

	// exit
	_asm
	{
		mov ecx, ecxbf
		mov eax, eaxbf

		fadd dword ptr[ecx + 0x1C]
		fstp dword ptr[ecx]
		jmp camhookcave
	}
}
void camhook(bool t)
{
	if (t)
	{
		*(byte*)0x006514AD = 0xE9; *(DWORD*)(0x006514AD + 0x1) = ((DWORD)hookedcamupdate - 0x006514AD) - 0x5;
	}
	else
	{
		*(byte*)0x006514AD = 0xD8; *(DWORD*)(0x006514AD + 0x1) = 0x19D91C41;
	}
}

bool debug_camera_enable = false;

void ReleaseCameraRotAngle(bool t) { rCamRotAngle = t; }
void SetCameraRotAngle1(float v) { if (*(DWORD*)0x0925E90 == 6) { *(float*)(*(DWORD*)(*(DWORD*)0x0093DA4C + 0x94) + 0x0) = v; } }
float GetCameraRotAngle1()
{
	if (*(DWORD*)0x0925E90 == 6 && !debug_camera_enable) { return *(float*)(*(DWORD*)(*(DWORD*)0x0093DA4C + 0x94) + 0x0); }
	return 0.0f;
}
void SetCameraRotAngle2(float v) { if (*(DWORD*)0x0925E90 == 6) { *(float*)(*(DWORD*)(*(DWORD*)0x0093DA4C + 0x94) + 0x2C) = v; } }
float GetCameraRotAngle2()
{
	if (*(DWORD*)0x0925E90 == 6 && !debug_camera_enable) { return *(float*)(*(DWORD*)(*(DWORD*)0x0093DA4C + 0x94) + 0x2C); }
	return 0.0f;
}

void ReleaseCameraRotX(bool t) { rCamRotX = t; }
void SetCameraRotX1(float v) { if (*(DWORD*)0x0925E90 == 6) { *(float*)(*(DWORD*)(*(DWORD*)0x0093DA4C + 0x90) + 0x0) = v; } }
float GetCameraRotX1()
{
	if (*(DWORD*)0x0925E90 == 6 && !debug_camera_enable) { return *(float*)(*(DWORD*)(*(DWORD*)0x0093DA4C + 0x90) + 0x0); }
	return 0.0f;
}
void SetCameraRotX2(float v) { if (*(DWORD*)0x0925E90 == 6) { *(float*)(*(DWORD*)(*(DWORD*)0x0093DA4C + 0x90) + 0x2C) = v; } }
float GetCameraRotX2()
{
	if (*(DWORD*)0x0925E90 == 6 && !debug_camera_enable) { return *(float*)(*(DWORD*)(*(DWORD*)0x0093DA4C + 0x90) + 0x2C); }
	return 0.0f;
}

void ReleaseCameraRotY(bool t) { rCamRotY = t; }
void SetCameraRotY(float v) { if (*(DWORD*)0x0925E90 == 6) { *(float*)(*(DWORD*)(*(DWORD*)0x0093DA4C + 0x90) + 0x58) = v; } }
float GetCameraRotY(float v)
{
	if (*(DWORD*)0x0925E90 == 6 && !debug_camera_enable) { return *(float*)(*(DWORD*)(*(DWORD*)0x0093DA4C + 0x90) + 0x58); }
	return 0.0f;
}

void ReleaseCameraInclineY(bool t) { rCamInclineY = t; }
void SetCameraInclineY(float v) { if (*(DWORD*)0x0925E90 == 6) { *(float*)(*(DWORD*)(*(DWORD*)0x0093DA4C + 0x8C) + 0x58) = v; } }
float GetCameraInclineY(float v)
{
	if (*(DWORD*)0x0925E90 == 6 && !debug_camera_enable) { return *(float*)(*(DWORD*)(*(DWORD*)0x0093DA4C + 0x8C) + 0x58); }
	return 0.0f;
}

void ReleaseCameraAngle(bool t) { rCamAngle = t; }
void SetCameraAngle(float v) { if (*(DWORD*)0x0925E90 == 6) { *(float*)(*(DWORD*)(*(DWORD*)0x0093DA4C + 0x84) + 0x0) = v; } }
float GetCameraAngle()
{
	if (*(DWORD*)0x0925E90 == 6 && !debug_camera_enable) { return *(float*)(*(DWORD*)(*(DWORD*)0x0093DA4C + 0x84) + 0x0); }
	return 0.0f;
}

void ReleaseCameraDistance(bool t) { rCamDistance = t; }
void SetCameraDistance(float v) { if (*(DWORD*)0x0925E90 == 6) { *(float*)(*(DWORD*)(*(DWORD*)0x0093DA4C + 0x88) + 0x0) = v; } }
float GetCameraDistance()
{
	if (*(DWORD*)0x0925E90 == 6 && !debug_camera_enable) { return *(float*)(*(DWORD*)(*(DWORD*)0x0093DA4C + 0x88) + 0x0); }
	return 0.0f;
}

void ReleaseCameraHeight(bool t) { rCamHeight = t; }
void SetCameraHeight(float v) { if (*(DWORD*)0x0925E90 == 6) { *(float*)(*(DWORD*)(*(DWORD*)0x0093DA4C + 0x88) + 0x58) = v; } }
float GetCameraHeight()
{
	if (*(DWORD*)0x0925E90 == 6 && !debug_camera_enable) { return *(float*)(*(DWORD*)(*(DWORD*)0x0093DA4C + 0x88) + 0x58); }
	return 0.0f;
}

#pragma endregion

#pragma region World
void DebugCamera(bool t)
{
	*(unsigned char*)0x00911058 = 1;
	if (*(DWORD*)0x00925E90 == 6)
	{
		if (t)
		{
			debug_camera_enable = true; Sleep(200);
			*(unsigned char*)0x00750F4C = 0xEB;
			*(unsigned int*)0x0091102C = 0;
			((void(*)(int, const char*))0x479EB0)(1, (char*)"CDActionDebug");
		}
		else
		{
			((void(*)(int, const char*))0x479EB0)(1, (char*)"CDActionDrive");
			*(unsigned char*)0x00911038 = 0;
			*(unsigned char*)0x00750F4C = 0x75;
			debug_camera_enable = false;
		}
	}
}

void OpenOldBridge(bool t) { t ? *(unsigned char*)0x008B2817 = 0x20 : *(unsigned char*)0x008B2817 = 0x5F; }

void OffInfiniteMass(bool t)
{
	if (t)
	{
		*(short*)0x006982C5 = 0x00B1; // mov cl, 00
		*(DWORD*)0x006982C7 = 0x90909090; // nop 4 bytes
		*(byte*)0x0069828F = 0x00; // mov cl, 00
	}
	else
	{
		*(byte*)0x0069828F = 0x01; // mov cl, 01
	}
}

#pragma endregion

#pragma region Attributes

byte freemem[500];

DWORD GetCarAddr()
{
	if (*(DWORD*)(*(DWORD*)0x009B27F0 + 0x318) == 0)
	{
		if (*(DWORD*)0x009B37D8 == 0)
		{
			return (DWORD)freemem;
		}

		if (*(DWORD*)(*(DWORD*)0x009B37D8 + 0x44) == 0)
		{
			return (DWORD)freemem;
		}

		return *(DWORD*)(*(DWORD*)(*(DWORD*)0x009B37D8 + 0x44) + 0x17B4);
	}

	return *(DWORD*)(*(DWORD*)(*(DWORD*)0x009B27F0 + 0x318) + 0x17B4);
}

void FEC_Front(float v) { *(float*)(GetCarAddr() + 0x128) = v; }
float GetFEC_Front() { return *(float*)(GetCarAddr() + 0x128); }
void FEC_Rear(float v) { *(float*)(GetCarAddr() + 0x12C) = v; }
float GetFEC_Rear() { return *(float*)(GetCarAddr() + 0x12C); }

void CamberFront(float v) { *(float*)(GetCarAddr() + 0xF0) = v; }
float GetCamberFront() { return *(float*)(GetCarAddr() + 0xF0); }
void CamberRear(float v) { *(float*)(GetCarAddr() + 0xF8) = v; }
float GetCamberRear() { return *(float*)(GetCarAddr() + 0xF8); }

void ReflectionOffset(float v) { *(float*)(GetCarAddr() + 0xF4) = v; }
float GetReflectionOffset() { return *(float*)(GetCarAddr() + 0xF4); }

void RideHeight(float v) { *(float*)(GetCarAddr() + 0xFC) = v; }
float GetRideHeight() { return *(float*)(GetCarAddr() + 0xFC); }

void KWOffsetRear1(char v) { *(char*)(GetCarAddr() + 0x108) = v; }
char GetKWOffsetRear1() { return *(char*)(GetCarAddr() + 0x108); }
void KWOffsetRear2(char v) { *(char*)(GetCarAddr() + 0x109) = v; }
char GetKWOffsetRear2() { return *(char*)(GetCarAddr() + 0x109); }
void KWOffsetRear3(char v) { *(char*)(GetCarAddr() + 0x10A) = v; }
char GetKWOffsetRear3() { return *(char*)(GetCarAddr() + 0x10A); }
void KWOffsetRear4(char v) { *(char*)(GetCarAddr() + 0x10B) = v; }
char GetKWOffsetRear4() { return *(char*)(GetCarAddr() + 0x10B); }
void KWOffsetRear5(char v) { *(char*)(GetCarAddr() + 0x10C) = v; }
char GetKWOffsetRear5() { return *(char*)(GetCarAddr() + 0x10C); }
void KWOffsetRear6(char v) { *(char*)(GetCarAddr() + 0x10D) = v; }
char GetKWOffsetRear6() { return *(char*)(GetCarAddr() + 0x10D); }

void KWOffsetFront1(char v) { *(char*)(GetCarAddr() + 0x116) = v; }
char GetKWOffsetFront1() { return *(char*)(GetCarAddr() + 0x116); }
void KWOffsetFront2(char v) { *(char*)(GetCarAddr() + 0x117) = v; }
char GetKWOffsetFront2() { return *(char*)(GetCarAddr() + 0x117); }
void KWOffsetFront3(char v) { *(char*)(GetCarAddr() + 0x118) = v; }
char GetKWOffsetFront3() { return *(char*)(GetCarAddr() + 0x118); }
void KWOffsetFront4(char v) { *(char*)(GetCarAddr() + 0x119) = v; }
char GetKWOffsetFront4() { return *(char*)(GetCarAddr() + 0x119); }
void KWOffsetFront5(char v) { *(char*)(GetCarAddr() + 0x11A) = v; }
char GetKWOffsetFront5() { return *(char*)(GetCarAddr() + 0x11A); }
void KWOffsetFront6(char v) { *(char*)(GetCarAddr() + 0x11B) = v; }
char GetKWOffsetFront6() { return *(char*)(GetCarAddr() + 0x11B); }

void TireOffsetFrontLeft1(float v) { *(float*)(GetCarAddr() + 0x10) = v; }
float GetTireOffsetFrontLeft1() { return *(float*)(GetCarAddr() + 0x10); }
void TireOffsetFrontLeft2(float v) { *(float*)(GetCarAddr() + 0x14) = v; }
float GetTireOffsetFrontLeft2() { return *(float*)(GetCarAddr() + 0x14); }
void TireOffsetFrontLeft3(float v) { *(float*)(GetCarAddr() + 0x18) = v; }
float GetTireOffsetFrontLeft3() { return *(float*)(GetCarAddr() + 0x18); }
void TireOffsetFrontLeft4(float v) { *(float*)(GetCarAddr() + 0x1C) = v; }
float GetTireOffsetFrontLeft4() { return *(float*)(GetCarAddr() + 0x1C); }

void TireOffsetFrontRight1(float v) { *(float*)(GetCarAddr() + 0x20) = v; }
float GetTireOffsetFrontRight1() { return *(float*)(GetCarAddr() + 0x20); }
void TireOffsetFrontRight2(float v) { *(float*)(GetCarAddr() + 0x24) = v; }
float GetTireOffsetFrontRight2() { return *(float*)(GetCarAddr() + 0x24); }
void TireOffsetFrontRight3(float v) { *(float*)(GetCarAddr() + 0x28) = v; }
float GetTireOffsetFrontRight3() { return *(float*)(GetCarAddr() + 0x28); }
void TireOffsetFrontRight4(float v) { *(float*)(GetCarAddr() + 0x2C) = v; }
float GetTireOffsetFrontRight4() { return *(float*)(GetCarAddr() + 0x2C); }

void TireOffsetRearRight1(float v) { *(float*)(GetCarAddr() + 0x30) = v; }
float GetTireOffsetRearRight1() { return *(float*)(GetCarAddr() + 0x30); }
void TireOffsetRearRight2(float v) { *(float*)(GetCarAddr() + 0x34) = v; }
float GetTireOffsetRearRight2() { return *(float*)(GetCarAddr() + 0x34); }
void TireOffsetRearRight3(float v) { *(float*)(GetCarAddr() + 0x38) = v; }
float GetTireOffsetRearRight3() { return *(float*)(GetCarAddr() + 0x38); }
void TireOffsetRearRight4(float v) { *(float*)(GetCarAddr() + 0x3C) = v; }
float GetTireOffsetRearRight4() { return *(float*)(GetCarAddr() + 0x3C); }

void TireOffsetRearLeft1(float v) { *(float*)(GetCarAddr() + 0x40) = v; }
float GetTireOffsetRearLeft1() { return *(float*)(GetCarAddr() + 0x40); }
void TireOffsetRearLeft2(float v) { *(float*)(GetCarAddr() + 0x44) = v; }
float GetTireOffsetRearLeft2() { return *(float*)(GetCarAddr() + 0x44); }
void TireOffsetRearLeft3(float v) { *(float*)(GetCarAddr() + 0x48) = v; }
float GetTireOffsetRearLeft3() { return *(float*)(GetCarAddr() + 0x48); }
void TireOffsetRearLeft4(float v) { *(float*)(GetCarAddr() + 0x4C) = v; }
float GetTireOffsetRearLeft4() { return *(float*)(GetCarAddr() + 0x4C); }

void TSWFrontLeft(float v) { *(float*)(GetCarAddr() + 0xDC) = v; }
float GetTSWFrontLeft() { return *(float*)(GetCarAddr() + 0xDC); }
void TSWFrontRight(float v) { *(float*)(GetCarAddr() + 0xE0) = v; }
float GetTSWFrontRight() { return *(float*)(GetCarAddr() + 0xE0); }
void TSWRearRight(float v) { *(float*)(GetCarAddr() + 0xE4) = v; }
float GetTSWRearRight() { return *(float*)(GetCarAddr() + 0xE4); }
void TSWRearLeft(float v) { *(float*)(GetCarAddr() + 0xE8) = v; }
float GetTSWRearLeft() { return *(float*)(GetCarAddr() + 0xE8); }

#pragma endregion

#pragma region Functions
#pragma region Point_teleport
float pt_x[64];
float pt_y[64];
float pt_z[64];
float pt_rot1[64];
float pt_inc1[64];
float pt_rot2[64];
float pt_inc2[64];
float pt_spdx[64];
float pt_spdy[64];
float pt_spdz[64];

int pt_id = 0;
int pt_obj_id = 0;

#pragma region point_list
void TeleportToCarLot1()
{
	while (GetAsyncKeyState(0x1))
	{
		mw_object[pt_obj_id]->y = -2147.321;
		mw_object[pt_obj_id]->z = 155.2939;
		mw_object[pt_obj_id]->x = 981.6318;
		Sleep(1);
	}
}
void TeleportToCarLot2()
{
	while (GetAsyncKeyState(0x1))
	{
		if (mw_object[pt_obj_id] == nullptr) { Sleep(1); continue; }
		mw_object[pt_obj_id]->y = -1257.427;
		mw_object[pt_obj_id]->z = 49.18896;
		mw_object[pt_obj_id]->x = 4204.79;
		Sleep(1);
	}
}
void TeleportToCarLot3()
{
	while (GetAsyncKeyState(0x1))
	{
		if (mw_object[pt_obj_id] == nullptr) { Sleep(1); continue; }
		mw_object[pt_obj_id]->y = -512.1406;
		mw_object[pt_obj_id]->z = 93.85645;
		mw_object[pt_obj_id]->x = 1750.89;
		Sleep(1);
	}
}
void TeleportToCustomShop1()
{
	while (GetAsyncKeyState(0x1))
	{
		if (mw_object[pt_obj_id] == nullptr) { Sleep(1); continue; }
		mw_object[pt_obj_id]->y = -4523.472;
		mw_object[pt_obj_id]->z = 217.6646;
		mw_object[pt_obj_id]->x = 698.1821;
		Sleep(1);
	}
}
void TeleportToCustomShop2()
{
	while (GetAsyncKeyState(0x1))
	{
		if (mw_object[pt_obj_id] == nullptr) { Sleep(1); continue; }
		mw_object[pt_obj_id]->y = -2563.893;
		mw_object[pt_obj_id]->z = 160.6162;
		mw_object[pt_obj_id]->x = 1509.355;
		Sleep(1);
	}
}
void TeleportToCustomShop3()
{
	while (GetAsyncKeyState(0x1))
	{
		if (mw_object[pt_obj_id] == nullptr) { Sleep(1); continue; }
		mw_object[pt_obj_id]->y = -1211.021;
		mw_object[pt_obj_id]->z = 146.5498;
		mw_object[pt_obj_id]->x = 1850.652;
		Sleep(1);
	}
}
void TeleportToCustomShop4()
{
	while (GetAsyncKeyState(0x1))
	{
		if (mw_object[pt_obj_id] == nullptr) { Sleep(1); continue; }
		mw_object[pt_obj_id]->y = -3627.557;
		mw_object[pt_obj_id]->z = 33.47705;
		mw_object[pt_obj_id]->x = 3595.972;
		Sleep(1);
	}
}
void TeleportToCustomShop5()
{
	while (GetAsyncKeyState(0x1))
	{
		if (mw_object[pt_obj_id] == nullptr) { Sleep(1); continue; }
		mw_object[pt_obj_id]->y = -2011.371;
		mw_object[pt_obj_id]->z = 76.98682;
		mw_object[pt_obj_id]->x = 3497.088;
		Sleep(1);
	}
}
void TeleportToCustomShop6()
{
	while (GetAsyncKeyState(0x1))
	{
		if (mw_object[pt_obj_id] == nullptr) { Sleep(1); continue; }
		mw_object[pt_obj_id]->y = -719.4024;
		mw_object[pt_obj_id]->z = 57.27002;
		mw_object[pt_obj_id]->x = 4246.829;
		Sleep(1);
	}
}
void TeleportToCustomShop7()
{
	while (GetAsyncKeyState(0x1))
	{
		if (mw_object[pt_obj_id] == nullptr) { Sleep(1); continue; }
		mw_object[pt_obj_id]->y = 231.7847;
		mw_object[pt_obj_id]->z = 15.44727;
		mw_object[pt_obj_id]->x = 3398.796;
		Sleep(1);
	}
}
void TeleportToCustomShop8()
{
	while (GetAsyncKeyState(0x1))
	{
		if (mw_object[pt_obj_id] == nullptr) { Sleep(1); continue; }
		mw_object[pt_obj_id]->y = -51.79076;
		mw_object[pt_obj_id]->z = 102.67774;
		mw_object[pt_obj_id]->x = 1064.187;
		Sleep(1);
	}
}
void TeleportToSafeHouse1()
{
	while (GetAsyncKeyState(0x1))
	{
		if (mw_object[pt_obj_id] == nullptr) { Sleep(1); continue; }
		mw_object[pt_obj_id]->y = -2503.468;
		mw_object[pt_obj_id]->z = 150.7935;
		mw_object[pt_obj_id]->x = 1777.095;
		Sleep(1);
	}
}
void TeleportToSafeHouse2()
{
	while (GetAsyncKeyState(0x1))
	{
		if (mw_object[pt_obj_id] == nullptr) { Sleep(1); continue; }
		mw_object[pt_obj_id]->y = -78.69839;
		mw_object[pt_obj_id]->z = 12.291016;
		mw_object[pt_obj_id]->x = 4257.524;
		Sleep(1);
	}
}
void TeleportToSafeHouse4()
{
	while (GetAsyncKeyState(0x1))
	{
		if (mw_object[pt_obj_id] == nullptr) { Sleep(1); continue; }
		mw_object[pt_obj_id]->y = -3340.5;
		mw_object[pt_obj_id]->z = 9.772949;
		mw_object[pt_obj_id]->x = 3627.767;
		Sleep(1);
	}
}
void TeleportToSafeHouse5()
{
	while (GetAsyncKeyState(0x1))
	{
		if (mw_object[pt_obj_id] == nullptr) { Sleep(1); continue; }
		mw_object[pt_obj_id]->y = 66.36417;
		mw_object[pt_obj_id]->z = 93.9668;
		mw_object[pt_obj_id]->x = 2328.785;
		Sleep(1);
	}
}
#pragma endregion

bool pt_save_rotation = false;
bool pt_save_speed = false;

void PtSelectMyObject() { pt_obj_id = 0; }

void PtSavePos()
{
	while (GetAsyncKeyState(0x1))
	{
		if (pt_id >= 0 && pt_id < 64)
		{
			if (mw_object[pt_obj_id] != nullptr)
			{
				pt_x[pt_id] = mw_object[pt_obj_id]->x;
				pt_y[pt_id] = mw_object[pt_obj_id]->y;
				pt_z[pt_id] = mw_object[pt_obj_id]->z;
				if (pt_save_rotation)
				{
					pt_rot1[pt_id] = mw_object[pt_obj_id]->rot1;
					pt_inc1[pt_id] = mw_object[pt_obj_id]->inc1;
					pt_rot2[pt_id] = mw_object[pt_obj_id]->rot2;
					pt_inc2[pt_id] = mw_object[pt_obj_id]->inc2;
				}
				if (pt_save_speed)
				{
					pt_spdx[pt_id] = mw_object[pt_obj_id]->spdX;
					pt_spdy[pt_id] = mw_object[pt_obj_id]->spdY;
					pt_spdz[pt_id] = mw_object[pt_obj_id]->spdZ;
				}
			}
			else
			{
				pt_x[pt_id] = 0;
				pt_y[pt_id] = 0;
				pt_z[pt_id] = 0;
			}
		}
		Sleep(1);
	}
}

void PtTeleportTo()
{
	while (GetAsyncKeyState(0x1))
	{
		if (pt_id >= 0 && pt_id < 64)
		{
			if (mw_object[pt_obj_id] != nullptr)
			{
				mw_object[pt_obj_id]->x = pt_x[pt_id];
				mw_object[pt_obj_id]->y = pt_y[pt_id];
				mw_object[pt_obj_id]->z = pt_z[pt_id];
				if (pt_save_rotation)
				{
					mw_object[pt_obj_id]->rot1 = pt_rot1[pt_id];
					mw_object[pt_obj_id]->inc1 = pt_inc1[pt_id];
					mw_object[pt_obj_id]->rot2 = pt_rot2[pt_id];
					mw_object[pt_obj_id]->inc2 = pt_inc2[pt_id];
				}
				if (pt_save_speed)
				{
					mw_object[pt_obj_id]->spdX = pt_spdx[pt_id];
					mw_object[pt_obj_id]->spdY = pt_spdy[pt_id];
					mw_object[pt_obj_id]->spdZ = pt_spdz[pt_id];
				}
			}
		}
		Sleep(1);
	}
}

float GetPointY() { if (pt_id >= 0 && pt_id < 64) { return pt_y[pt_id]; } else { return 0.0f; } };
float GetPointZ() { if (pt_id >= 0 && pt_id < 64) { return pt_z[pt_id]; } else { return 0.0f; } };
float GetPointX() { if (pt_id >= 0 && pt_id < 64) { return pt_x[pt_id]; } else { return 0.0f; } };
void SetPointY(float v) { if (pt_id >= 0 && pt_id < 64) { pt_y[pt_id] = v; } };
void SetPointZ(float v) { if (pt_id >= 0 && pt_id < 64) { pt_z[pt_id] = v; } };
void SetPointX(float v) { if (pt_id >= 0 && pt_id < 64) { pt_x[pt_id] = v; } };

void PtSaveRotation(bool t) { pt_save_rotation = t; }
void PtSaveSpeed(bool t) { pt_save_speed = t; }

#pragma endregion
#pragma region Object_teleport
int obj_t_id = 0, to_obj_t_id = 0;
float obj_t_y_offset = 0.0f, obj_t_z_offset = 4.3f, obj_t_x_offset = 0.0f;
bool obj_t_copy_rotation = false;
bool obj_t_copy_speed = false;
float obj_t_speed_multiplier = 0.5f;

void obj_teleport()
{
	while (GetAsyncKeyState(0x1))
	{
		if (mw_object[obj_t_id] != nullptr && mw_object[to_obj_t_id] != nullptr)
		{
			mw_object[obj_t_id]->x = mw_object[to_obj_t_id]->x + obj_t_x_offset;
			mw_object[obj_t_id]->y = mw_object[to_obj_t_id]->y + obj_t_y_offset;
			mw_object[obj_t_id]->z = mw_object[to_obj_t_id]->z + obj_t_z_offset;
			if (obj_t_copy_rotation)
			{
				mw_object[obj_t_id]->rot1 = mw_object[to_obj_t_id]->rot1;
				mw_object[obj_t_id]->inc1 = mw_object[to_obj_t_id]->inc1;
				mw_object[obj_t_id]->rot2 = mw_object[to_obj_t_id]->rot2;
				mw_object[obj_t_id]->inc2 = mw_object[to_obj_t_id]->inc2;
			}
			if (obj_t_copy_speed)
			{
				mw_object[obj_t_id]->spdX = mw_object[to_obj_t_id]->spdX * obj_t_speed_multiplier;
				mw_object[obj_t_id]->spdY = mw_object[to_obj_t_id]->spdY * obj_t_speed_multiplier;
				mw_object[obj_t_id]->spdZ = mw_object[to_obj_t_id]->spdZ * obj_t_speed_multiplier;
			}
		}
	}
}

float OtGetObjectY() { if (mw_object[obj_t_id] != nullptr) { return mw_object[obj_t_id]->y; } else { return 0.0f; } };
float OtGetObjectZ() { if (mw_object[obj_t_id] != nullptr) { return mw_object[obj_t_id]->z; } else { return 0.0f; } };
float OtGetObjectX() { if (mw_object[obj_t_id] != nullptr) { return mw_object[obj_t_id]->x; } else { return 0.0f; } };
void OtSetObjectY(float v) { if (mw_object[obj_t_id] != nullptr) { mw_object[obj_t_id]->y = v; } };
void OtSetObjectZ(float v) { if (mw_object[obj_t_id] != nullptr) { mw_object[obj_t_id]->z = v; } };
void OtSetObjectX(float v) { if (mw_object[obj_t_id] != nullptr) { mw_object[obj_t_id]->x = v; } };

float OtGetToObjectY() { if (mw_object[to_obj_t_id] != nullptr) { return mw_object[to_obj_t_id]->y; } else { return 0.0f; } };
float OtGetToObjectZ() { if (mw_object[to_obj_t_id] != nullptr) { return mw_object[to_obj_t_id]->z; } else { return 0.0f; } };
float OtGetToObjectX() { if (mw_object[to_obj_t_id] != nullptr) { return mw_object[to_obj_t_id]->x; } else { return 0.0f; } };
void OtSetToObjectY(float v) { if (mw_object[to_obj_t_id] != nullptr) { mw_object[to_obj_t_id]->y = v; } };
void OtSetToObjectZ(float v) { if (mw_object[to_obj_t_id] != nullptr) { mw_object[to_obj_t_id]->z = v; } };
void OtSetToObjectX(float v) { if (mw_object[to_obj_t_id] != nullptr) { mw_object[to_obj_t_id]->x = v; } };

void OtCopyRotation(bool t) { obj_t_copy_rotation = t; }
void OtCopySpeed(bool t) { obj_t_copy_speed = t; }

#pragma endregion

bool active_boost = false;
float boost_power = 1.1f;
DWORD WINAPI threadBoost(LPVOID)
{
	while (active_boost)
	{
		if (GetAsyncKeyState(0x56))
		{
			my_object->spdX *= boost_power;
			my_object->spdY *= boost_power;
		}
		Sleep(10);
	}
	return EXIT_SUCCESS;
}
void __cdecl Boost(bool t)
{
	if (t)
	{
		active_boost = true;
		CreateThread(0, 0, threadBoost, 0, 0, 0);
	}
	else
	{
		active_boost = false;
	}
}

bool active_shotobject = false;
struct shotobject_parameters
{
	static float power;
	static float z_up;
	static float min_mass_object;
	static float mass_exception, mass_exception2;
	static int delay, resept_id_delay;
	static int max_car_id;
};
float shotobject_parameters::power = 4.15f;
float shotobject_parameters::z_up = 2.5f;
float shotobject_parameters::min_mass_object = 650.0f;
float shotobject_parameters::mass_exception = 0.0f, shotobject_parameters::mass_exception2 = 0.0f;
int shotobject_parameters::delay = 25, shotobject_parameters::resept_id_delay = 50;
int shotobject_parameters::max_car_id = 50;
DWORD WINAPI threadShotObject(LPVOID)
{
	unsigned int objecpt_id = 0;

	while (active_shotobject)
	{
	shotobject_jmp:
		if (GetAsyncKeyState(0x45))
		{
			if (objecpt_id > shotobject_parameters::max_car_id)
			{
				Sleep(shotobject_parameters::resept_id_delay);
				objecpt_id = 0;
			}
			objecpt_id++;

			mw_object_data * other_object = mw_object[objecpt_id];

			if (other_object == nullptr) { continue; }

			if (other_object->weight >= shotobject_parameters::min_mass_object && other_object->weight != shotobject_parameters::mass_exception && other_object->weight != shotobject_parameters::mass_exception2)
			{
				//SetIncline
				other_object->inc1 = my_object->inc1;
				other_object->inc2 = my_object->inc2;
				other_object->rot1 = my_object->rot1;
				other_object->rot2 = my_object->rot2;

				//SetPos
				other_object->x = my_object->x;
				other_object->y = my_object->y;
				other_object->z = my_object->z + shotobject_parameters::z_up;

				//SetSpd
				other_object->spdX = my_object->spdX * shotobject_parameters::power;
				other_object->spdY = my_object->spdY * shotobject_parameters::power;
				other_object->spdZ = my_object->spdZ * shotobject_parameters::power;

			}
			else
			{
				continue;
			}
		}

		Sleep(shotobject_parameters::delay);
	}

	return EXIT_SUCCESS;
}
void __cdecl ShotObject(bool t)
{
	if (t)
	{
		CreateThread(0, 0, threadShotObject, 0, 0, 0);
		active_shotobject = true;
	}
	else
	{
		active_shotobject = false;
	}
}

DWORD shield_code_jmp_exit_addr = 0x00697972;
DWORD shield_eax_buff, shield_ecx_buff, shield_esi_buff, shield_ebx_buff, shield_edx_buff;
float shield_radius = 40.0f;
float shield_power = 1.0f;
__declspec(naked) void __cdecl shield_code_insert()
{
	__asm // save registers
	{
		push eax
		push ecx
		push esi
		push ebx
		push edx
	}

	mw_object_data * shield_they_object;

	__asm
	{
		mov shield_they_object, esi
	}

	if (shield_they_object != my_object)
	{
		if (mw_object_get_distance(my_object, shield_they_object) < shield_radius)
		{
			shield_they_object->spdX += ((shield_they_object->x - my_object->x) * shield_power);
			shield_they_object->spdY += ((shield_they_object->y - my_object->y) * shield_power);
		}
	}

	__asm // load registers
	{
		pop edx
		pop ebx
		pop esi
		pop ecx
		pop eax
	}

	__asm // prev code
	{
		fld dword ptr[esp + 0x64]
		fmul dword ptr[edi]
	}

	__asm // exit
	{
		jmp shield_code_jmp_exit_addr
	}
}
void __cdecl Shield(bool t)
{
	if (t)
	{
		*(byte*)0x0069796C = 0xE9;
		*(DWORD*)(0x0069796C + 0x1) = ((DWORD)shield_code_insert - 0x0069796C) - 0x5;
		*(byte*)(0x0069796C + 0x5) = 0x90;
	}
	else
	{
		*(DWORD*)0x0069796C = 0x642444D9;
		*(short*)0x00697970 = 0x0FD8;
	}
}

DWORD magnet_code_cave = 0x006A70AF;
float magnet_power = 1.0f;
float repulsion_power = 1.0f;
__declspec(naked)void magnet_code_insert()
{
	_asm
	{
		fstp dword ptr[esi + 8]
		mov ebx, [ebx]

		push edx
		push ecx
		push esi
		push ebx
		push eax
	}

	static mw_object_data *obj = 0;
	_asm
	{
		mov obj, edi
	}

	if (GetAsyncKeyState(0x59))
	{
		if (obj != my_object)
		{
			obj->spdX = (my_object->x - obj->x) * magnet_power;
			obj->spdY = (my_object->y - obj->y) * magnet_power;
			obj->spdZ = (my_object->z - obj->z) * magnet_power;
		}
	}
	if (GetAsyncKeyState(0x55))
	{
		if (obj != my_object)
		{
			obj->spdX = (obj->x - my_object->x) * repulsion_power;
			obj->spdY = (obj->y - my_object->y) * repulsion_power;
			obj->spdZ = (obj->z - my_object->z) * repulsion_power;
		}
	}

	_asm
	{
		pop eax
		pop ebx
		pop esi
		pop ecx
		pop edx
	}

	_asm
	{
		jmp magnet_code_cave
	}

}
void __cdecl Magnet(bool t)
{
	if (t)
	{
		*(byte*)0x006A70AA = 0xE9;
		*(DWORD*)(0x006A70AA + 0x1) = ((DWORD)magnet_code_insert - 0x006A70AA) - 0x5;
	}
	else
	{
		*(DWORD*)0x006A70AA = 0x8B085ED9;
		*(byte*)0x006A70AE = 0x1B;
	}
}

void NeverGetBusted(bool t)
{
	if (t)
	{
		*(DWORD*)0x0040AED3 = 0x81C7EED9;
		*(DWORD*)0x0040AED7 = 0x000000DC;
		*(DWORD*)0x0040AEDB = 0x00000000;
	}
	else
	{
		*(DWORD*)0x0040AED3 = 0x00DC81D9;
		*(DWORD*)0x0040AED7 = 0x0DD80000;
		*(DWORD*)0x0040AEDB = 0x00890864;
	}
}

#pragma endregion

#pragma region Graphics

void DisableFlashlights(bool t) { *(int*)0x009017E4 = !t; }
void DisableParticles(bool t) { *(int*)0x009017EC = !t; }

void DisableHUD(bool t)
{
	if (t)
	{
		*(float*)0x006E6F55 = 0.0f;
		*(float*)0x006E6F5D = 0.0f;
	}
	else
	{
		*(float*)0x006E6F55 = 1.0f;
		*(float*)0x006E6F5D = 1.0f;
	}
}

#pragma region Car light
HANDLE htr_disco_backlights = 0;

DWORD WINAPI thread_disco_backlights(LPVOID)
{
	while (true)
	{
		for (int i = 0; i < 1000 / 50; i++)
		{
			*(float*)0x00742AD1 += 0.05f;
			*(float*)0x00742AE1 -= 0.05f;
			Sleep(10);
		}
		for (int i = 0; i < 1000 / 50; i++)
		{
			*(float*)0x00742AD1 -= 0.05f;
			*(float*)0x00742AE1 += 0.05f;
			Sleep(10);
		}
	}
}

void DiscoBacklights(bool t)
{
	if (t)
	{
		*(float*)0x00742AD1 = 0.0f;
		*(float*)0x00742AE1 = 1.0f;
		htr_disco_backlights = CreateThread(0, 0, thread_disco_backlights, 0, 0, 0);
	}
	else
	{
		if (htr_disco_backlights != 0)
		{
			*(float*)0x00742AD1 = 0.5f;
			*(float*)0x00742AE1 = 0.5f;
			TerminateThread(htr_disco_backlights, 0);
		}
	}
}

#pragma endregion

#pragma endregion

#pragma region GameWindow

RECT WndRect;

void WindowFrame(bool a)
{
	*(byte*)0x00982BF0 = a;
	SetWindowLongPtr(*(HWND*)0x00982BF4, GWL_STYLE, a ? WS_VISIBLE | WS_OVERLAPPEDWINDOW : WS_VISIBLE);
	SetWindowPos(*(HWND*)0x00982BF4, 0, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_DRAWFRAME);
}

int GetWindowX()
{
	GetWindowRect(*(HWND*)0x00982BF4, &WndRect);
	return WndRect.left;
}

int GetWindowY()
{
	GetWindowRect(*(HWND*)0x00982BF4, &WndRect);
	return WndRect.top;
}

int GetWindowXSize() { return WndRect.right - GetWindowX(); }
int GetWindowYSize() { return WndRect.bottom - GetWindowY(); }

void WindowXSize(int v) { SetWindowPos(*(HWND*)0x00982BF4, HWND_NOTOPMOST, 0, 0, v, GetWindowYSize(), SWP_NOMOVE); }
void WindowYSize(int v) { SetWindowPos(*(HWND*)0x00982BF4, HWND_NOTOPMOST, 0, 0, GetWindowXSize(), v, SWP_NOMOVE); }

void WindowX(int v) { SetWindowPos(*(HWND*)0x00982BF4, HWND_NOTOPMOST, v, GetWindowY(), 0, 0, SWP_NOSIZE); }
void WindowY(int v) { SetWindowPos(*(HWND*)0x00982BF4, HWND_NOTOPMOST, GetWindowX(), v, 0, 0, SWP_NOSIZE); }

#pragma endregion

#pragma region Credits
void CreditK2Re8()
{
	ShellExecute(NULL, "open", "https://vk.com/hacked_ys", NULL, NULL, SW_SHOW);
	ShellExecute(NULL, "open", "https://www.youtube.com/channel/UCvgtjKJJQ3KKVTeMT6ZMYdA", NULL, NULL, SW_SHOW);
}
void CreditTimofeheus()
{
	ShellExecute(NULL, "open", "https://vk.com/timofeheus", NULL, NULL, SW_SHOW);
}
void CreditOsdever()
{
	ShellExecute(NULL, "open", "https://www.youtube.com/channel/UCh3spQzxfBHD09tAw7IlRnA/videos", NULL, NULL, SW_SHOW);
}
#pragma endregion

void __cdecl initializing()
{
#pragma region protect_memory

	DWORD old_protect;

	// Garage slots
	VirtualProtect((void*)0x007C1A77, 1, PAGE_EXECUTE_READWRITE, &old_protect);

	// UseNitroIfIsNotInstalled
	VirtualProtect((void*)0x00692944, sizeof(unsigned char), PAGE_EXECUTE_READWRITE, &old_protect);
	VirtualProtect((void*)(0x00692A79 + 0x2), sizeof(unsigned char), PAGE_EXECUTE_READWRITE, &old_protect);

	// UseNitroIfNotMotion
	VirtualProtect((void*)0x00692A1D, 0x3, PAGE_EXECUTE_READWRITE, &old_protect);
	VirtualProtect((void*)0x006929F7, 0x3, PAGE_EXECUTE_READWRITE, &old_protect);

	// UseNitroIfIsEmpty
	VirtualProtect((void*)0x00692AA7, 0x6, PAGE_EXECUTE_READWRITE, &old_protect);

	// NitroNotEnd
	VirtualProtect((void*)0x00692B06, 0x6, PAGE_EXECUTE_READWRITE, &old_protect);

	// SpeedbrakerNotEnd
	VirtualProtect((void*)0x006EDE03, 0x6, PAGE_EXECUTE_READWRITE, &old_protect);

	// Individual handling
	VirtualProtect((void*)0x0069CB80, 7, PAGE_EXECUTE_READWRITE, &old_protect);

	// No rev
	VirtualProtect((void*)0x8AB78C, 4, PAGE_EXECUTE_READWRITE, &old_protect);
	VirtualProtect((void*)0x8AC034, 4, PAGE_EXECUTE_READWRITE, &old_protect);

	// No clip
	VirtualProtect((void*)0x006BB77E, 1, PAGE_EXECUTE_READWRITE, &old_protect);

	// No collision
	VirtualProtect((void*)0x00699F55, 1, PAGE_EXECUTE_READWRITE, &old_protect);

	// Camera hook
	VirtualProtect((void*)0x006514AD, 5, PAGE_EXECUTE_READWRITE, &old_protect);

	// Open old bridge
	VirtualProtect((void*)0x008B2817, sizeof(unsigned char), PAGE_EXECUTE_READWRITE, &old_protect);

	// Off infinite mass
	VirtualProtect((void*)0x006982C5, 6, PAGE_EXECUTE_READWRITE, &old_protect);
	VirtualProtect((void*)0x0069828F, 1, PAGE_EXECUTE_READWRITE, &old_protect);

	// GUI HUD X,Y
	VirtualProtect((void*)0x006E6F55, 4, PAGE_EXECUTE_READWRITE, &old_protect);
	VirtualProtect((void*)0x006E6F5D, 4, PAGE_EXECUTE_READWRITE, &old_protect);

	VirtualProtect((void*)0x00750F4C, 5, PAGE_EXECUTE_READWRITE, &old_protect);
	VirtualProtect((void*)0x00692AA7, 6, PAGE_EXECUTE_READWRITE, &old_protect);
	VirtualProtect((void*)0x8AB78C, 4, PAGE_EXECUTE_READWRITE, &old_protect);
	VirtualProtect((void*)0x8AC034, 4, PAGE_EXECUTE_READWRITE, &old_protect);
	VirtualProtect((void*)0x7bb502, 4, PAGE_EXECUTE_READWRITE, &old_protect);
	VirtualProtect((void*)0x7b1387, 4, PAGE_EXECUTE_READWRITE, &old_protect);
	VirtualProtect((void*)0x7b0c89, 4, PAGE_EXECUTE_READWRITE, &old_protect);
	VirtualProtect((void*)0x7B4D7C, 4, PAGE_EXECUTE_READWRITE, &old_protect);
	VirtualProtect((void*)0x435079, 4, PAGE_EXECUTE_READWRITE, &old_protect);
	VirtualProtect((void*)0x435088, 4, PAGE_EXECUTE_READWRITE, &old_protect);
	VirtualProtect((void*)0x00443DC3, 6, PAGE_EXECUTE_READWRITE, &old_protect);

	// shield
	VirtualProtect((void*)0x0069796C, 0x6, PAGE_EXECUTE_READWRITE, &old_protect);

	// magnet
	VirtualProtect((void*)0x006A70AA, 0x5, PAGE_EXECUTE_READWRITE, &old_protect);

	// car lights
	VirtualProtect((void*)0x742b94, 4, PAGE_EXECUTE_READWRITE, &old_protect);
	VirtualProtect((void*)0x742bb3, 4, PAGE_EXECUTE_READWRITE, &old_protect);
	VirtualProtect((void*)0x742ad1, 4, PAGE_EXECUTE_READWRITE, &old_protect);
	VirtualProtect((void*)0x742ae1, 4, PAGE_EXECUTE_READWRITE, &old_protect);

	// NeverGetBusted
	VirtualProtect((void*)0x0040AED3, 12, PAGE_EXECUTE_READWRITE, &old_protect);

	HeatLimitHook();

#pragma endregion

	IDirect3DDevice9 *pDev;
	ID3DXSprite *menu_sprite;
	IDirect3DTexture9 *title_tex, *section_tex, *button_tex, *checkbox_tex, *checkbox_active_tex, *vf_button_tex, *tr1, *tr2, *plus_tex, *minus_tex;

	d3d9hook::GetDevice(&pDev);
	d3d9hook::BreakPresent();

	menu_sprite = MyD3DXCreateSprite(pDev);

	title_tex = MyD3DXCreateTexture(pDev, section_size_x * xm + button_size_x * xm + button_x_bias * xm, title_size_y * ym, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED);
	section_tex = MyD3DXCreateTexture(pDev, section_size_x * xm, section_size_y * ym, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED);
	// a1 = MyD3DXCreateTexture(pDev, section_size_x * xm, section_size_y * ym, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED);
	button_tex = MyD3DXCreateTexture(pDev, button_size_x * xm, button_size_y * ym, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED);
	checkbox_tex = MyD3DXCreateTexture(pDev, 20 * xm, 20 * ym, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED);
	checkbox_active_tex = MyD3DXCreateTexture(pDev, 20 * xm, 20 * ym, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED);
	vf_button_tex = MyD3DXCreateTextureFromFileEx(pDev, "verblehack/enter.png", 20 * xm, 20 * ym, D3DX_DEFAULT, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL);
	tr1 = MyD3DXCreateTextureFromFileEx(pDev, "verblehack/triangle1.png", 18 * xm, 9 * ym, D3DX_DEFAULT, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL);
	tr2 = MyD3DXCreateTextureFromFileEx(pDev, "verblehack/triangle2.png", 9 * xm, 18 * ym, D3DX_DEFAULT, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL);
	plus_tex = MyD3DXCreateTexture(pDev, 20 * xm, 20 * ym, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED);
	minus_tex = MyD3DXCreateTexture(pDev, 20 * xm, 20 * ym, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED);
	
	// D3DCOLOR_ARGB(200, 0, 0, 0)
#define FillColor D3DCOLOR_ARGB(200,0,0,0)
	
	// D3DCOLOR_ARGB(255,255,0,0)
#define BorderColor D3DCOLOR_ARGB(255,255,255,255)

	MyD3DXSimpleFillTexture(title_tex, FillColor);
	MyD3DXBorderTextureWithShadow(title_tex, BorderColor, 2, 50);

	MyD3DXSimpleFillTexture(section_tex, FillColor);
	MyD3DXBorderTextureWithShadow(section_tex, BorderColor, 2, 50);

	MyD3DXSimpleFillTexture(button_tex, FillColor);
	MyD3DXBorderTextureWithShadow(button_tex, BorderColor, 2, 50);

	MyD3DXBorderTextureWithShadow(checkbox_tex, BorderColor, 2, 50);
	RECT rect = _RECT((20.0 * (xm * 0.150)), (20.0 * (ym * 0.150)), (20.0 * (xm * 0.850)), (20.0 * (ym * 0.850)));
	MyD3DXFillTextureRectWithShadow(checkbox_active_tex, BorderColor, &rect, 50);
	MyD3DXBorderTextureWithShadow(checkbox_active_tex, BorderColor, 2, 50);

	MyD3DXBorderTextureWithShadow(vf_button_tex, BorderColor, 2, 50);

	MyD3DXBorderTextureWithShadow(plus_tex, BorderColor, 2, 50);
	MyD3DXBorderTextureWithShadow(minus_tex, BorderColor, 2, 50);

	rect = _RECT((LONG)(3 * xm), (LONG)(9 * ym), (LONG)(17 * xm), (LONG)(11 * ym));
	MyD3DXFillTextureRectWithShadow(minus_tex, D3DCOLOR_ARGB(255, 255, 255, 255), &rect, 25);
	MyD3DXFillTextureRectWithShadow(plus_tex, D3DCOLOR_ARGB(255, 255, 255, 255), &rect, 25);
	rect = _RECT((LONG)(9 * xm), (LONG)(3 * ym), (LONG)(11 * xm), (LONG)(17 * ym));
	MyD3DXFillTextureRectWithShadow(plus_tex, D3DCOLOR_ARGB(255, 255, 255, 255), &rect, 25);

	messagebox::Init(pDev);

	d3d9hook::UnBreakPresent();

	Menu *menu = new Menu("VerbleHack v4.1", { 20.0f * core::xm,15.0f*core::ym }, title_tex, font::big_size, 256, menu_sprite, VK_END);

	b_section *profile, *car, *objects, *camera, *world, *attributes, *functions, *graphics, *game_window, *credits;

	profile = menu->CreateSection("Profile", section_tex, font::big_size, tr1, tr2, 30);
	car = menu->CreateSection("Car", section_tex, font::big_size, tr1, tr2, 30);
	objects = menu->CreateSection("Objects", section_tex, font::big_size, tr1, tr2, 30);
	camera = menu->CreateSection("Camera", section_tex, font::big_size, tr1, tr2, 30);
	world = menu->CreateSection("World", section_tex, font::big_size, tr1, tr2, 5);
	attributes = menu->CreateSection("Attributes", section_tex, font::big_size, tr1, tr2, 20);
	functions = menu->CreateSection("Functions", section_tex, font::big_size, tr1, tr2, 20);
	graphics = menu->CreateSection("Graphics", section_tex, font::big_size, tr1, tr2, 20);
	game_window = menu->CreateSection("Game window", section_tex, font::big_size, tr1, tr2, 20);
	credits = menu->CreateSection("Credits", section_tex, font::big_size, tr1, tr2, 20);

#define cs(text,size) CreateSection(text,button_tex,font::big_size,tr1,tr2,size)
#define cvf(text,vt,uc_get,uc_set,addr_get,addr_set) CreateValueFunction(text, button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, vt, uc_get, uc_set, addr_get, addr_set)
#define cbf(text,addr) CreateBooleanFunction(text,button_tex, font::big_size, checkbox_tex, checkbox_active_tex,addr)
#define cbtf(text,addr) CreateButtonFunction(text, button_tex, font::big_size, addr)

	profile->CreateValueFunction("Money", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_long, true, true, GetMoney, Money);
	profile->CreateValueFunction("Min Heat", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, false, false, &MinHeatLevel, &MinHeatLevel);
	profile->CreateValueFunction("Max Heat", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, GetMaxHeat, MaxHeat);
	profile->CreateValueFunction("Heat Level", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, GetHeatLevel, HeatLevel);
	profile->CreateValueFunction("Camera Mode", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_long, true, true, GetCameraMode, CameraMode);
	profile->CreateValueFunction("Garage Slots", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_byte, true, true, GetGarageSlots, GarageSlots);
	profile->CreateBooleanFunction("Unlock all", button_tex, font::big_size, checkbox_tex, checkbox_active_tex, UnlockAll);
	profile->CreateBooleanFunction("Auto Drive", button_tex, font::big_size, checkbox_tex, checkbox_active_tex, AutoDrive);

	car->CreateValueFunction("Nitro power", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, getnitropower, nitropower);
	car->CreateBooleanFunction("Use nitro if is not installed", button_tex, font::big_size, checkbox_tex, checkbox_active_tex, UseNitroIfIsNotInstalled);
	car->CreateBooleanFunction("Use nitro if not motion", button_tex, font::big_size, checkbox_tex, checkbox_active_tex, UseNitroIfNotMotion);
	car->CreateBooleanFunction("Use nitro if is empty", button_tex, font::big_size, checkbox_tex, checkbox_active_tex, UseNitroIfIsEmpty);
	car->CreateBooleanFunction("Nitro not end", button_tex, font::big_size, checkbox_tex, checkbox_active_tex, NitroNotEnd);
	car->CreateBooleanFunction("Speedbraker not end", button_tex, font::big_size, checkbox_tex, checkbox_active_tex, SpeedbrakerNotEnd);
	b_section * ih = car->CreateSection("Individual handling", button_tex, font::big_size, tr1, tr2, 5);
	{
		ih->CreateBooleanFunction("Enable", button_tex, font::big_size, checkbox_tex, checkbox_active_tex, IndividualHandling);
		ih->CreateValueFunction("Sensivity", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, false, false, &HandlingSensivity, &HandlingSensivity);
		ih->CreateValueFunction("Brake sensivity", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, false, false, &HandlingBrakeSensivity, &HandlingBrakeSensivity);
		ih->CreateValueFunction("Out sensivity", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, false, false, &HandlingOutSensivity, &HandlingOutSensivity);
		ih->CreateValueFunction("Deadline", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, false, false, &HandlingDeadline, &HandlingDeadline);
	}
	car->CreateBooleanFunction("No rev", button_tex, font::big_size, checkbox_tex, checkbox_active_tex, NoRev);
	car->CreateBooleanFunction("No clip", button_tex, font::big_size, checkbox_tex, checkbox_active_tex, NoClip);
	car->CreateBooleanFunction("No collision", button_tex, font::big_size, checkbox_tex, checkbox_active_tex, NoCollision);
	car->cvf("SpdBrakerMassMult.", v_type_float, false, false, (float*)0x00901AEC, (float*)0x00901AEC);

	b_section * odata = objects->CreateSection("data", button_tex, font::big_size, tr1, tr2, 30);
	{
		odata->CreateValueFunction("Object id", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_long, false, false, &g_selected_object, &g_selected_object);
		odata->CreateValueFunction("inc 1", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, getinc1, setinc1);
		odata->CreateValueFunction("rot 1", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, getrot1, setrot1);
		odata->CreateValueFunction("inc 2", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, getinc2, setinc2);
		odata->CreateValueFunction("rot 2", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, getrot2, setrot2);
		odata->CreateValueFunction("y", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, getY, setY);
		odata->CreateValueFunction("z", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, getZ, setZ);
		odata->CreateValueFunction("x", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, getX, setX);
		odata->CreateValueFunction("spd y", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, getspdY, setspdY);
		odata->CreateValueFunction("spd z", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, getspdZ, setspdZ);
		odata->CreateValueFunction("spd x", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, getspdX, setspdX);
		odata->CreateValueFunction("weight", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, getweight, setweight);
		odata->CreateValueFunction("coup 1", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, getcoup1, setcoup1);
		odata->CreateValueFunction("turn 1", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, getturn1, setturn1);
		odata->CreateValueFunction("incline 1", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, getincline1, setincline1);
		odata->CreateValueFunction("power", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, getpower, setpower);
		odata->CreateValueFunction("shakiness 1", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, getshakiness1, setshakiness1);
		odata->CreateValueFunction("mobility", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, getmobility, setmobility);
		odata->CreateValueFunction("shakiness 2", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, getshakiness2, setshakiness2);
		odata->CreateValueFunction("spd y 2", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, getspdY2, setspdY2);
		odata->CreateValueFunction("spd z 2", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, getspdZ2, setspdZ2);
		odata->CreateValueFunction("spd x 2", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, getspdX2, setspdX2);
		odata->CreateValueFunction("block", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_byte, true, true, getblock, setblock);
		odata->CreateValueFunction("coup 2", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, getcoup2, setcoup2);
		odata->CreateValueFunction("turn 2", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, getturn2, setturn2);
		odata->CreateValueFunction("incline 2", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, getincline2, setincline2);
	}
	objects->CreateBooleanFunction("Objects to trash", button_tex, font::big_size, checkbox_tex, checkbox_active_tex, ObjectsToTrash);

	camera->CreateBooleanFunction("Enable hook", button_tex, font::big_size, checkbox_tex, checkbox_active_tex, camhook);
	camera->CreateBooleanFunction("Release rotation angle", button_tex, font::big_size, checkbox_tex, checkbox_active_tex, ReleaseCameraRotAngle);
	camera->CreateBooleanFunction("Release rotation X", button_tex, font::big_size, checkbox_tex, checkbox_active_tex, ReleaseCameraRotX);
	camera->CreateBooleanFunction("Release rotation Y", button_tex, font::big_size, checkbox_tex, checkbox_active_tex, ReleaseCameraRotY);
	camera->CreateBooleanFunction("Release incline Y", button_tex, font::big_size, checkbox_tex, checkbox_active_tex, ReleaseCameraInclineY);
	camera->CreateBooleanFunction("Release Angle", button_tex, font::big_size, checkbox_tex, checkbox_active_tex, ReleaseCameraAngle);
	camera->CreateBooleanFunction("Release distance", button_tex, font::big_size, checkbox_tex, checkbox_active_tex, ReleaseCameraDistance);
	camera->CreateBooleanFunction("Release Height", button_tex, font::big_size, checkbox_tex, checkbox_active_tex, ReleaseCameraHeight);
	camera->CreateValueFunction("Rotation angle 1", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, GetCameraRotAngle1, SetCameraRotAngle1);
	camera->CreateValueFunction("Rotation angle 2", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, GetCameraRotAngle2, SetCameraRotAngle2);
	camera->CreateValueFunction("Rotation X 1", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, GetCameraRotX1, SetCameraRotX1);
	camera->CreateValueFunction("Rotation X 2", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, GetCameraRotX2, SetCameraRotX2);
	camera->CreateValueFunction("Rotation Y", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, GetCameraRotY, SetCameraRotY);
	camera->CreateValueFunction("Incline Y", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, GetCameraInclineY, SetCameraInclineY);
	camera->CreateValueFunction("Angle", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, GetCameraAngle, SetCameraAngle);
	camera->CreateValueFunction("Distance", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, GetCameraDistance, SetCameraDistance);
	camera->CreateValueFunction("Height", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, GetCameraHeight, SetCameraHeight);

	world->CreateBooleanFunction("Debug Camera", button_tex, font::big_size, checkbox_tex, checkbox_active_tex, DebugCamera);
	world->CreateBooleanFunction("Open old bridge", button_tex, font::big_size, checkbox_tex, checkbox_active_tex, OpenOldBridge);
	world->CreateBooleanFunction("Off infinite mass", button_tex, font::big_size, checkbox_tex, checkbox_active_tex, OffInfiniteMass);
	world->CreateValueFunction("Animation speed", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, false, false, (float*)0x00904AEC, (float*)0x00904AEC);
	world->CreateValueFunction("Game speed", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, false, false, (float*)0x00901B1C, (float*)0x00901B1C);

	b_section *FEC = attributes->CreateSection("FEC", button_tex, font::big_size, tr1, tr2, 2);
	{
		FEC->CreateValueFunction("Front", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, GetFEC_Front, FEC_Front);
		FEC->CreateValueFunction("Rear", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, GetFEC_Rear, FEC_Rear);
	}
	b_section *Camber = attributes->CreateSection("Camber", button_tex, font::big_size, tr1, tr2, 2);
	{
		Camber->CreateValueFunction("Front", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, GetCamberFront, CamberFront);
		Camber->CreateValueFunction("Rear", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, GetCamberRear, CamberRear);
	}
	b_section *AttributesOther = attributes->CreateSection("Other", button_tex, font::big_size, tr1, tr2, 6);
	{
		AttributesOther->CreateValueFunction("Reflection offset", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, GetReflectionOffset, ReflectionOffset);
		AttributesOther->CreateValueFunction("Ride height", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, GetRideHeight, RideHeight);
	}
	b_section *WheelsOffsets = attributes->CreateSection("Wheels offsets", button_tex, font::big_size, tr1, tr2, 8);
	{
		b_section *WhoFL = WheelsOffsets->CreateSection("Front left", button_tex, font::big_size, tr1, tr2, 6);
		b_section *WhoFR = WheelsOffsets->CreateSection("Front right", button_tex, font::big_size, tr1, tr2, 6);
		b_section *WhoRR = WheelsOffsets->CreateSection("Rear right", button_tex, font::big_size, tr1, tr2, 6);
		b_section *WhoRL = WheelsOffsets->CreateSection("Rear left", button_tex, font::big_size, tr1, tr2, 6);
		b_section *KWR = WheelsOffsets->CreateSection("KW rear", button_tex, font::big_size, tr1, tr2, 6);
		b_section *KWF = WheelsOffsets->CreateSection("KW front", button_tex, font::big_size, tr1, tr2, 6);
		b_section *TSWF = WheelsOffsets->CreateSection("TSW front", button_tex, font::big_size, tr1, tr2, 6);
		b_section *TSWR = WheelsOffsets->CreateSection("TSW rear", button_tex, font::big_size, tr1, tr2, 6);
		{
			WhoFL->CreateValueFunction("1", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, GetTireOffsetFrontLeft1, TireOffsetFrontLeft1);
			WhoFL->CreateValueFunction("2", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, GetTireOffsetFrontLeft2, TireOffsetFrontLeft2);
			WhoFL->CreateValueFunction("3", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, GetTireOffsetFrontLeft3, TireOffsetFrontLeft3);
			WhoFL->CreateValueFunction("4", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, GetTireOffsetFrontLeft4, TireOffsetFrontLeft4);

			WhoFR->CreateValueFunction("1", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, GetTireOffsetFrontRight1, TireOffsetFrontRight1);
			WhoFR->CreateValueFunction("2", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, GetTireOffsetFrontRight2, TireOffsetFrontRight2);
			WhoFR->CreateValueFunction("3", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, GetTireOffsetFrontRight3, TireOffsetFrontRight3);
			WhoFR->CreateValueFunction("4", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, GetTireOffsetFrontRight4, TireOffsetFrontRight4);

			WhoRR->CreateValueFunction("1", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, GetTireOffsetRearRight1, TireOffsetRearRight1);
			WhoRR->CreateValueFunction("2", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, GetTireOffsetRearRight2, TireOffsetRearRight2);
			WhoRR->CreateValueFunction("3", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, GetTireOffsetRearRight3, TireOffsetRearRight3);
			WhoRR->CreateValueFunction("4", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, GetTireOffsetRearRight4, TireOffsetRearRight4);

			WhoRL->CreateValueFunction("1", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, GetTireOffsetRearLeft1, TireOffsetRearLeft1);
			WhoRL->CreateValueFunction("2", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, GetTireOffsetRearLeft2, TireOffsetRearLeft2);
			WhoRL->CreateValueFunction("3", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, GetTireOffsetRearLeft3, TireOffsetRearLeft3);
			WhoRL->CreateValueFunction("4", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, GetTireOffsetRearLeft4, TireOffsetRearLeft4);

			KWR->CreateValueFunction("1", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_byte, true, true, GetKWOffsetRear1, KWOffsetRear1);
			KWR->CreateValueFunction("2", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_byte, true, true, GetKWOffsetRear2, KWOffsetRear2);
			KWR->CreateValueFunction("3", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_byte, true, true, GetKWOffsetRear3, KWOffsetRear3);
			KWR->CreateValueFunction("4", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_byte, true, true, GetKWOffsetRear4, KWOffsetRear4);
			KWR->CreateValueFunction("5", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_byte, true, true, GetKWOffsetRear5, KWOffsetRear5);
			KWR->CreateValueFunction("6", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_byte, true, true, GetKWOffsetRear6, KWOffsetRear6);

			KWF->CreateValueFunction("1", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_byte, true, true, GetKWOffsetFront1, KWOffsetFront1);
			KWF->CreateValueFunction("2", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_byte, true, true, GetKWOffsetFront2, KWOffsetFront2);
			KWF->CreateValueFunction("3", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_byte, true, true, GetKWOffsetFront3, KWOffsetFront3);
			KWF->CreateValueFunction("4", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_byte, true, true, GetKWOffsetFront4, KWOffsetFront4);
			KWF->CreateValueFunction("5", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_byte, true, true, GetKWOffsetFront5, KWOffsetFront5);
			KWF->CreateValueFunction("6", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_byte, true, true, GetKWOffsetFront6, KWOffsetFront6);

			TSWF->CreateValueFunction("Left", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, GetTSWFrontLeft, TSWFrontLeft);
			TSWF->CreateValueFunction("Right", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, GetTSWFrontRight, TSWFrontRight);

			TSWR->CreateValueFunction("Left", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, GetTSWRearLeft, TSWRearLeft);
			TSWR->CreateValueFunction("Right", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, true, true, GetTSWRearRight, TSWRearRight);
		}
	}

	b_section *point_teleport = functions->cs("Point teleport", 11);
	{
		b_section *point_list = point_teleport->cs("Point list", 15);
		{
			point_list->cbtf("Car Lot #1", TeleportToCarLot1);
			point_list->cbtf("Car Lot #2", TeleportToCarLot2);
			point_list->cbtf("Car Lot #3", TeleportToCarLot3);
			point_list->cbtf("Custom Shop #1", TeleportToCustomShop1);
			point_list->cbtf("Custom Shop #2", TeleportToCustomShop2);
			point_list->cbtf("Custom Shop #3", TeleportToCustomShop3);
			point_list->cbtf("Custom Shop #4", TeleportToCustomShop4);
			point_list->cbtf("Custom Shop #5", TeleportToCustomShop5);
			point_list->cbtf("Custom Shop #6", TeleportToCustomShop6);
			point_list->cbtf("Custom Shop #7", TeleportToCustomShop7);
			point_list->cbtf("Custom Shop #8", TeleportToCustomShop8);
			point_list->cbtf("Safe House #1", TeleportToSafeHouse1);
			point_list->cbtf("Safe House #2", TeleportToSafeHouse2);
			point_list->cbtf("Safe House #4", TeleportToSafeHouse4);
			point_list->cbtf("Safe House #5", TeleportToSafeHouse5);
		}
		point_teleport->cvf("Point id[max 63]", v_type_long, false, false, &pt_id, &pt_id);
		point_teleport->cvf("Object id[>50 danger]", v_type_long, false, false, &pt_obj_id, &pt_obj_id);
		point_teleport->cbtf("Select my object", PtSelectMyObject);
		point_teleport->cbtf("Save point", PtSavePos);
		point_teleport->cbtf("Teleport to point", PtTeleportTo);
		point_teleport->cvf("point y", v_type_float, true, true, GetPointY, SetPointY);
		point_teleport->cvf("point z", v_type_float, true, true, GetPointZ, SetPointZ);
		point_teleport->cvf("point x", v_type_float, true, true, GetPointX, SetPointX);
		point_teleport->cbf("Save rotation", PtSaveRotation);
		point_teleport->cbf("Save speed", PtSaveSpeed);
	}
	b_section *object_teleport = functions->cs("Object teleport", 15);
	{
		object_teleport->cvf("Object id", v_type_long, false, false, &obj_t_id, &obj_t_id);
		object_teleport->cvf("To object id", v_type_long, false, false, &to_obj_t_id, &to_obj_t_id);
		object_teleport->cbtf("Teleport to", obj_teleport);
		object_teleport->cvf("Object y", v_type_float, true, true, OtGetObjectY, OtSetObjectY);
		object_teleport->cvf("Object z", v_type_float, true, true, OtGetObjectZ, OtSetObjectZ);
		object_teleport->cvf("Object x", v_type_float, true, true, OtGetObjectX, OtSetObjectX);
		object_teleport->cvf("To object y", v_type_float, true, true, OtGetToObjectY, OtSetToObjectY);
		object_teleport->cvf("To object z", v_type_float, true, true, OtGetToObjectZ, OtSetToObjectZ);
		object_teleport->cvf("To object x", v_type_float, true, true, OtGetToObjectX, OtSetToObjectX);
		object_teleport->cvf("Y offset", v_type_float, false, false, &obj_t_y_offset, &obj_t_y_offset);
		object_teleport->cvf("Z offset", v_type_float, false, false, &obj_t_z_offset, &obj_t_z_offset);
		object_teleport->cvf("X offset", v_type_float, false, false, &obj_t_x_offset, &obj_t_x_offset);
		object_teleport->cbf("Copy rotation", OtCopyRotation);
		object_teleport->cbf("Copy speed", OtCopySpeed);
		object_teleport->cvf("Speed multiplier", v_type_float, false, false, &obj_t_speed_multiplier, &obj_t_speed_multiplier);
	}
	b_section *boost = functions->cs("Boost [V]", 2);
	{
		boost->CreateBooleanFunction("Enable", button_tex, font::big_size, checkbox_tex, checkbox_active_tex, Boost);
		boost->CreateValueFunction("Power", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, false, false, &boost_power, &boost_power);
	}
	b_section *shotobject = functions->CreateSection("Shot object [E]", button_tex, font::big_size, tr1, tr2, 9);
	{
		shotobject->CreateBooleanFunction("Enable", button_tex, font::big_size, checkbox_tex, checkbox_active_tex, ShotObject);
		shotobject->CreateValueFunction("Power", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, false, false, &shotobject_parameters::power, &shotobject_parameters::power);
		shotobject->CreateValueFunction("z_up", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, false, false, &shotobject_parameters::z_up, &shotobject_parameters::z_up);
		shotobject->CreateValueFunction("max_car_id", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_long, false, false, &shotobject_parameters::max_car_id, &shotobject_parameters::max_car_id);
		shotobject->CreateValueFunction("min_mass_object", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, false, false, &shotobject_parameters::min_mass_object, &shotobject_parameters::min_mass_object);
		shotobject->CreateValueFunction("mass_exception", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, false, false, &shotobject_parameters::mass_exception, &shotobject_parameters::mass_exception);
		shotobject->CreateValueFunction("mass_exception2", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, false, false, &shotobject_parameters::mass_exception2, &shotobject_parameters::mass_exception2);
		shotobject->CreateValueFunction("delay", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_long, false, false, &shotobject_parameters::delay, &shotobject_parameters::delay);
		shotobject->CreateValueFunction("resept_id_delay", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_long, false, false, &shotobject_parameters::resept_id_delay, &shotobject_parameters::resept_id_delay);
	}
	b_section *shield = functions->CreateSection("Shield", button_tex, font::big_size, tr1, tr2, 3);
	{
		shield->CreateBooleanFunction("Enable", button_tex, font::big_size, checkbox_tex, checkbox_active_tex, Shield);
		shield->CreateValueFunction("Power", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, false, false, &shield_power, &shield_power);
		shield->CreateValueFunction("Radius", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, false, false, &shield_radius, &shield_radius);
	}
	b_section *magnet = functions->CreateSection("Magnet[Y][U]", button_tex, font::big_size, tr1, tr2, 3);
	{
		magnet->CreateBooleanFunction("Enable", button_tex, font::big_size, checkbox_tex, checkbox_active_tex, Magnet);
		magnet->CreateValueFunction("Magnet power", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, false, false, &magnet_power, &magnet_power);
		magnet->CreateValueFunction("Repulsion power", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, false, false, &repulsion_power, &repulsion_power);
	}
	functions->cbf("Never get busted", NeverGetBusted);

	graphics->CreateBooleanFunction("Disable flashlights", button_tex, font::big_size, checkbox_tex, checkbox_active_tex, DisableFlashlights);
	graphics->CreateBooleanFunction("Disable particles", button_tex, font::big_size, checkbox_tex, checkbox_active_tex, DisableParticles);
	graphics->CreateValueFunction("Texture lighting", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, false, false, (float*)0x009018C4, (float*)0x009018C4);
	graphics->CreateValueFunction("Reflection power", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, false, false, (float*)0x009018DC, (float*)0x009018DC);
	graphics->CreateValueFunction("color offset?", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_long, false, false, (int*)0x00901934, (int*)0x00901934);
	graphics->CreateValueFunction("color diffusion", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, false, false, (float*)0x00901938, (float*)0x00901938);
	graphics->CreateValueFunction("fog", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, false, false, (float*)0x0090193C, (float*)0x0090193C);
	graphics->CreateValueFunction("GUI HUD X", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, false, false, (float*)0x006E6F55, (float*)0x006E6F55);
	graphics->CreateValueFunction("GUI HUD Y", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_float, false, false, (float*)0x006E6F5D, (float*)0x006E6F5D);
	graphics->CreateBooleanFunction("Disable HUD", button_tex, font::big_size, checkbox_tex, checkbox_active_tex, DisableHUD);
	b_section * car_lights = graphics->cs("Car lights", 5);
	{
		car_lights->cvf("Front left", v_type_float, false, false, (float*)0x742b94, (float*)0x742b94);
		car_lights->cvf("Front right", v_type_float, false, false, (float*)0x742bb3, (float*)0x742bb3);
		car_lights->cvf("Rear left", v_type_float, false, false, (float*)0x742ad1, (float*)0x742ad1);
		car_lights->cvf("Rear right", v_type_float, false, false, (float*)0x742ae1, (float*)0x742ae1);
		car_lights->cbf("disco", DiscoBacklights);
	}

	game_window->CreateBooleanFunction("Window frame", button_tex, font::big_size, checkbox_tex, checkbox_active_tex, WindowFrame);
	game_window->CreateValueFunction("Window X Size", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_long, true, true, GetWindowXSize, WindowXSize);
	game_window->CreateValueFunction("Window Y Size", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_long, true, true, GetWindowYSize, WindowYSize);
	game_window->CreateValueFunction("Window X", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_long, true, true, GetWindowX, WindowX);
	game_window->CreateValueFunction("Window Y", button_tex, font::big_size, vf_button_tex, font::medium_size, plus_tex, minus_tex, v_type_long, true, true, GetWindowY, WindowY);

	credits->cbtf("K2Re8 (Creator)", CreditK2Re8);
	credits->cbtf("osdever (Helper)", CreditOsdever);
	credits->cbtf("Timofeheus (Helper)", CreditTimofeheus);
	
}

