#include"map.h"

int Map_Hit(int x, int y)
{
	int map_x = x / 64;
	int map_y = y / 64;
	if (map_y < 0)
	{
		map_y = 0;
	}
	if (map[map_y][map_x] == 1)
	{
		return 1;
	}
	if (map[map_y][map_x] == 2)
	{
		return 2;
	}
	if (map[map_y][map_x] == 3)
	{
		return 3;
	}
	if (map[map_y][map_x] == 5)
	{
		return 5;
	}
	return 0;
}



void Map_Search(int x, int y, int* px, int* py)
{
	int map_x = x / 64;
	int map_y = y / 64;
	if (x % 64 != 0)
	{
		x++;
	}
	if (y % 64 != 0)
	{
		y++;
	}
	*px = map_x;
	*py = map_y;
}

CUSTOMVERTEX map_tip[] =
{
	{ 0.0f,  0.0f,  0.5f, 1.0f, 0xFFFFFFFF, 0.0f, 0.0f },
{ 64.0f, 0.0f,  0.5f, 1.0f, 0xFFFFFFFF, 1.0f, 0.0f },
{ 64.0f, 64.0f, 0.5f, 1.0f, 0xFFFFFFFF, 1.0f, 1.0f },
{ 0.0f,  64.0f, 0.5f, 1.0f, 0xFFFFFFFF, 0.0f, 1.0f },
};