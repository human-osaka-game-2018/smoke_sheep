#pragma once
#include"main.h"
struct enemy_wolf {
	int type;
	int life;
	float move_x, move_y;

};

enum
{
	nomal,
	speed,
	strong,
	hide,
};
extern enemy_wolf wolf[100];
extern CUSTOMVERTEX enemy[100][4];