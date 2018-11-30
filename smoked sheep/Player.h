#pragma once

#include"main.h"
struct g_player
{
	float x, y, scale;
	int x_speed;
	int	y_speed;
	int smoketime;
	int life;
	/*float CutTex_x, CutTex_y;*/
};
enum playerpicture_tv//‰¼
{
	tv_walk,
	tv_run,
	tv_jump,
	tv_rotate,
	tv_smokewait,
    tv_smokewalk,
	tv_hensin,
	tv_atack,
};

enum playerpicture_tu//‰¼
{
	tu_walk,
	tu_run,
	tu_jump,
	tu_rotate,
	tu_smokewait,
	tu_smokewalk,
	tu_hensin,
	tu_atack,
};




extern g_player Sheep;
extern CUSTOMVERTEX player_chara[4];


void PlayerUp();
void PlayerDown();
void PlayerLeft();
void PlayerRight();
float Player_tv(playerpicture_tv a);
float Player_tu(playerpicture_tu a);
void PlayerFormat_tv();
void SettingPlayer_tu(playerpicture_tu a);
void SettingPlayer_tv(playerpicture_tv a);
void SettingPlayer_tutv(playerpicture_tu a, playerpicture_tv b);
void smokehensintime();
