#pragma once

#include"main.h"

enum isAction
{
	wait,
	walk,
	jumping,
	sping,
	atack,
	isdamaged,
	henshin,
	smokewait,
	smokewalk,
};
struct g_player
{
	float x, y, scale;
	int x_speed;
	int	y_speed;
	int smoketime;
	int life;
	isAction state;

	/*float CutTex_x, CutTex_y;*/
};
enum playerpicture_tv//‰¼
{
	tv_wait,
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
	tu_wait,
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

void DrawTurn(CUSTOMVERTEX *a);

void PlayerUp();
void PlayerDown();
void PlayerLeft();
void PlayerRight();
float Player_tv(playerpicture_tv a);
float Player_tu(playerpicture_tu a);
void SettingPlayer_tu(playerpicture_tu a);
void SettingPlayer_tv(playerpicture_tv a);
void SettingPlayer_tutv(playerpicture_tu a, playerpicture_tv b,isAction c);
void smokehensintime();
void PlayerWait(int count);

