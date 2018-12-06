#pragma once
#include"main.h"
enum enemytype
{
	nomal,
	speed,
	strong,
	hide,
};
struct enemy_wolf {
	enemytype type;
	int life;
	float move_x, move_y;
	int drawnumber;
};
extern enemy_wolf wolf[100];
extern CUSTOMVERTEX enemy[100][4];



void EnemyInit(int type, int Enemy_Number);
void Enemy_LRrevFlag();
void EnemyMainControl();
void EnemyMove(CUSTOMVERTEX *a, enemy_wolf *b, bool RIGHTorLEFT,unsigned int E_game_time);
float Enemy_tu(enemytype a);
float Enemy_tv(enemytype a);
float EnemyWidth_tu();
float EnemyHeight_tv();
void FormatEnemy_tu();
void FormatEnemy_tv();
void SettingEnemy_tv(enemytype a);
void SettingEnemy_tu(enemytype a);
void SettingEnemy_tutv(enemytype a);
