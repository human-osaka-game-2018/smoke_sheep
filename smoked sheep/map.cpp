#include"Map.h"

int Map_Hit(int x, int y)
{
	int map_x = x / 64;
	int map_y = y / 64;
	if (map_y < 0)
	{
		map_y = 0;
	}
	if (Map[map_y][map_x] == 1)
	{
		return 1;
	}
	if (Map[map_y][map_x] == 6)
	{
		return 1;
	}
	if (Map[map_y][map_x] == 2)
	{
		return 2;
	}
	if (Map[map_y][map_x] == 3)
	{
		return 3;
	}
	if (Map[map_y][map_x] == 7)
	{
		return 7;
	}
	if(Map[map_y][map_x] == 8)
	{
		return 8;
	}
	if (Map[map_y][map_x] == 53)
	{
		return 53;
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