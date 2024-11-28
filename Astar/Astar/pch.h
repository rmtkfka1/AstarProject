#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <vector>
#include <Windows.h>
#include <queue>
#include <stack>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include "stb_image.h"
#include <assert.h>

using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;

using namespace std;


struct Pos
{
	Pos() {};
	Pos(int32 x, int32 y)
	{
		this->x = x;
		this->y = y;
	}

	bool operator==(const Pos& other)
	{
		if (this->x == other.x && this->y == other.y)
			return true;

		return false;
	}

	bool operator!=(const Pos& other)
	{
		if (this->x == other.x && this->y == other.y)
			return false;

		return true;
	}

	Pos operator+(const Pos& other)
	{
		Pos pos;
		pos.x = this->x + other.x;
		pos.y = this->y + other.y;
		return pos;
	}

	Pos operator-(const Pos& other)
	{
		Pos pos;
		pos.x = this->x - other.x;
		pos.y = this->y - other.y;
		return pos;
	}

	Pos& operator+=(const Pos& other)
	{
		this->x += other.x;
		this->y += other.y;
		return *this;
	}

	Pos& operator-=(const Pos& other)
	{
		this->x -= other.x;
		this->y -= other.y;
		return *this;
	}


	int32 x{};
	int32 y{};

};


enum Dir
{
	DIR_UP=0,
	DIR_LEFT,
	DIR_DOWN,
	DIR_RIGHT,
	DIR_COUNT
};