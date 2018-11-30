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
void EnemyInit(int type, int enemy_number);
void Enemy_LRrevFlag();
void EnemyMove();
float Enemy_tu(enemytype a);
float Enemy_tv(enemytype a);
float EnemyWidth_tu();
float EnemyHeight_tv();
void FormatEnemy_tu();
void FormatEnemy_tv();
void SettingEnemy_tv(enemytype a);
void SettingEnemy_tu(enemytype a);
void SettingEnemy_tutv(enemytype a);