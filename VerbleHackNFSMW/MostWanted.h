#pragma once

#include <Windows.h>

struct mw_object_data {
	float inc1;
	float rot1;
	float inc2;
	float rot2;
	float y, z, x;
	int DamageSensivity;
	float spdY, spdZ, spdX;
	float weight;
	float spdIncHor1;
	float spdRot1;
	float spdIncVer1;
	float power;
	float coupVer;
	float handlingmass;
	float coupHor;
	float unknownmemory;
	float spdtY, spdtZ, spdtX;
	byte sym1, blockcarinfo, sym2, sym3;
	float spdIncHor2;
	float spdRot2;
	float spdIncVer2;
	float unknownmemory2;
	float stretHor, stretang, convex;
	int unknownmemory3;
	float distort[7];
	int updatetexinfo, updatetexinfo2, updatetexinfo3;
	double end;
};

mw_object_data** const mw_object((mw_object_data **)0x009383B0);
mw_object_data* const my_object((mw_object_data *)0x009386C8);

float __fastcall mw_object_get_distance(mw_object_data * basic_object, mw_object_data * they_object) {
	float result = 0.0f;
	if (basic_object->y < they_object->y) {
		result += they_object->y - basic_object->y;
	}
	else {
		result += basic_object->y - they_object->y;
	}
	if (basic_object->z < they_object->z) {
		result += they_object->z - basic_object->z;
	}
	else {
		result += basic_object->z - they_object->z;
	}
	if (basic_object->x < they_object->x) {
		result += they_object->x - basic_object->x;
	}
	else {
		result += basic_object->x - they_object->x;
	}
	return result;
}

mw_object_data * FindNearObject(mw_object_data * obj, mw_object_data * expertion)
{
	mw_object_data * object = nullptr;
	float max_distance = 0.0f;
	for (int i = 1; i < 50; i++) 
	{
		if (mw_object[i] != nullptr && mw_object[i] != expertion)
		{
			float distance = mw_object_get_distance(obj, mw_object[i]);
			if (distance > max_distance)
			{
				object = mw_object[i];
				max_distance = distance;
			}
		}
	}
	if (max_distance != 0.0f)
	{
		return object;
	}
	else
	{
		return 0;
	}
}