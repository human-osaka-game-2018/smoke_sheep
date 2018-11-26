#include"player.h"

g_player Sheep = { 155.f,215.f,55.f,5,5,5,3 };

CUSTOMVERTEX player_chara[] =
{
	{ Sheep.x - Sheep.scale , Sheep.y - Sheep.scale , 0.5f, 1.0f, 0xFFFFFFFF, 0.0f,  0.0f },
{ Sheep.x + Sheep.scale, Sheep.y - Sheep.scale , 0.5f, 1.0f, 0xFFFFFFFF, 0.125f, 0.0f },
{ Sheep.x + Sheep.scale, Sheep.y + Sheep.scale, 0.5f, 1.0f, 0xFFFFFFFF, 0.125f, 1.0f },
{ Sheep.x - Sheep.scale ,Sheep.y + Sheep.scale, 0.5f, 1.0f, 0xFFFFFFFF, 0.0f,  1.0f },
};
