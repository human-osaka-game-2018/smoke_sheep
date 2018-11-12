#include"player.h"
g_player Sheep = { 155,215,55 };

CUSTOMVERTEX player_chara[] =
{
{ Sheep.x- Sheep.scale , Sheep.y- Sheep.scale , 0.5f, 1.0f, 0xFFFFFFFF, 0.0f,  0.0f },
{  Sheep.x+ Sheep.scale, Sheep.y- Sheep.scale , 0.5f, 1.0f, 0xFFFFFFFF, 0.125f, 0.0f },
{  Sheep.x+ Sheep.scale, Sheep.y+ Sheep.scale, 0.5f, 1.0f, 0xFFFFFFFF, 0.125f, 1.0f },
{ Sheep.x - Sheep.scale ,Sheep.y+ Sheep.scale, 0.5f, 1.0f, 0xFFFFFFFF, 0.0f,  1.0f },
};
