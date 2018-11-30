#include"Enemy.h"
#include"map.h"

//エネミー画像の比率が200×287

CUSTOMVERTEX enemy[100][4] =
{
	{ 0.0f,  0.0f,  0.5f, 1.0f, 0xFFFFFFFF, 0.0f, 0.0f },
	{ 64.0f, 0.0f,  0.5f, 1.0f, 0xFFFFFFFF, 1.0f, 0.0f },
	{ 64.0f, 64.0f, 0.5f, 1.0f, 0xFFFFFFFF, 1.0f, 1.0f },
	{ 0.0f,  64.0f, 0.5f, 1.0f, 0xFFFFFFFF, 0.0f, 1.0f },
};
enemy_wolf wolf[100];

float Enemy_tu(enemytype a) {
	switch (a)
	{
	case nomal:
		return 0.f / 2048.f;
	case speed:
		return 800.f / 2048.f;
	case strong:
		return 0.f / 2048.f;
	case hide:
		return 0.f / 2048.f;
	}
}

float Enemy_tv(enemytype a) {
	switch (a)
	{
	case nomal:
		return 0.f / 2048.f;
	case speed:
		return 0.f / 2048.f;
	case strong:
		return 287.f / 2048.f;
	case hide:
		return 574.f / 2048.f;
	}
}

float EnemyWidth_tu() {
	return 200.f / 2048.f;
}
float EnemyHeight_tv() {

	return 287.f / 2048.f;
}
void FormatEnemy_tu()
{
	enemy[enemy_number][0].tu = 0.f / 2048.f;
	enemy[enemy_number][1].tu = EnemyWidth_tu();
	enemy[enemy_number][2].tu = EnemyWidth_tu();
	enemy[enemy_number][3].tu = 0.f / 2048.f;
}
void FormatEnemy_tv() {
	enemy[enemy_number][0].tv = 0.f / 2048.f;
	enemy[enemy_number][1].tv = 0.f / 2048.f;
	enemy[enemy_number][2].tv = EnemyHeight_tv();
	enemy[enemy_number][3].tv =  EnemyHeight_tv();
}

void SettingEnemy_tv(enemytype a)
{
	FormatEnemy_tv();
	for (int i = 0; i < 4; i++)
	{
		enemy[enemy_number][i].tv += Enemy_tv(a);
	}
}

void SettingEnemy_tu(enemytype a) {
	FormatEnemy_tu();
	for (int i = 0; i < 4; i++)
	{
		enemy[enemy_number][i].tu += Enemy_tu(a);
	}
}

void SettingEnemy_tutv(enemytype a)
{
	
		SettingEnemy_tv(a);
		SettingEnemy_tu(a);
	
}

//
//float Enemy_tu(enemytype a) {
//	switch (a)
//	{
//	case nomal:
//		return 125.f / 1024.f;
//	case speed:
//		return 170.f / 1024.f;
//	case strong:
//		return 130.f / 1024.f;
//	case hide:
//		return 200.f / 1024.f;
//	}
//}
//
//void SettingEnemy_tu()
//{
//	enemy[enemy_number][0].tu = 0.f / 1024.f;
//	enemy[enemy_number][1].tu = Enemy_tu(wolf[enemy_number].type);
//	enemy[enemy_number][2].tu = Enemy_tu(wolf[enemy_number].type);
//	enemy[enemy_number][3].tu = 0.f / 1024.f;
//}
//
//
//void SettingEnemy_tv(enemytype a)
//{
//	switch (a)
//	{
//	case nomal:
//		enemy[enemy_number][0].tv = 0.f / 1024.f;
//		enemy[enemy_number][1].tv = 0.f / 1024.f;
//		enemy[enemy_number][2].tv = 140.f / 1024.f;
//		enemy[enemy_number][3].tv = 140.f / 1024.f;
//		break;
//	case speed:
//		enemy[enemy_number][0].tv = 140.f / 1024.f;
//		enemy[enemy_number][1].tv = 140.f / 1024.f;
//		enemy[enemy_number][2].tv = 240.f / 1024.f;
//		enemy[enemy_number][3].tv = 240.f / 1024.f;
//		break;
//	case strong:
//		enemy[enemy_number][0].tv = 240.f / 1024.f;
//		enemy[enemy_number][1].tv = 240.f / 1024.f;
//		enemy[enemy_number][2].tv = 385.f / 1024.f;
//		enemy[enemy_number][3].tv = 385.f / 1024.f;
//		break;
//	case hide:
//		enemy[enemy_number][0].tv = 510.f / 1024.f;
//		enemy[enemy_number][1].tv = 510.f / 1024.f;
//		enemy[enemy_number][2].tv = 655.f / 1024.f;
//		enemy[enemy_number][3].tv = 655.f / 1024.f;
//		break;
//	}
//}


void EnemyInit(int type,int enemy_number) {
	switch(type)
	{
	case 21:
		wolf[enemy_number] = {nomal,1,2.f,2.f ,4};
		break;
	case 22:
		wolf[enemy_number] = {speed,1,4.f,4.f,8 };
		break;
	case 23:
		wolf[enemy_number] = { strong,2,2.f,2.f,4 };
		break;
	case 24:
		wolf[enemy_number] = {hide,1,2.f,2.f ,8};
		break;
	}
}

void EnemyRender()
{
}


void Enemy_LRrevFlag()
{
	for (int i = 0; i < enemy_number; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (Map_Hit(int(enemy[i][j].x - map_error), int(enemy[i][j].y - GRAVITY == 1))) {
				a[i] = !a[i];
				break;
			}
			if (Map_Hit(int(enemy[i][j].x - map_error), int(enemy[i][j].y - GRAVITY == 5))) {
				a[i] = !a[i];
				break;
			}

		}
	}
}

void EnemyMove() {
	static unsigned int E_game_time;
	E_game_time++;
	
	Enemy_LRrevFlag();
	for (int j = 0; j < enemy_number; j++)
	{
		if (a[j]) {
			if (enemy[j][0].tu < enemy[j][1].tu)
			{
				float tmp_tu;

				tmp_tu = enemy[j][0].tu;
				enemy[j][0].tu = enemy[j][1].tu;
				enemy[j][1].tu = tmp_tu;

				tmp_tu = enemy[j][2].tu;
				enemy[j][2].tu = enemy[j][3].tu;
				enemy[j][3].tu = tmp_tu;
			}
			for (int i = 0; i < 4; i++)
			{
				enemy[j][i].x += wolf[j].move_x;//enemyのSpeed
				if (E_game_time % 4 == 0)
				{
					enemy[j][i].tu += EnemyWidth_tu();
				}
			}
			if (enemy[j][0].tu == EnemyWidth_tu() * wolf[j].drawnumber)
			{
				SettingEnemy_tu(wolf[j].type);
				float tmp_tu;

				tmp_tu = enemy[j][0].tu;
				enemy[j][0].tu = enemy[j][1].tu;
				enemy[j][1].tu = tmp_tu;

				tmp_tu = enemy[j][2].tu;
				enemy[j][2].tu = enemy[j][3].tu;
				enemy[j][3].tu = tmp_tu;
		      /*enemy[j][0].tu = Enemy_tu(wolf[j].type);
				enemy[j][1].tu = 0.f / 2048.f;
				enemy[j][2].tu = 0.f / 2048.f;
				enemy[j][3].tu = Enemy_tu(wolf[j].type);*/
			}
		}
		else {
			if (enemy[j][0].tu > enemy[j][1].tu)
			{
				float tmp_tu;

				tmp_tu = enemy[j][0].tu;
				enemy[j][0].tu = enemy[j][1].tu;
				enemy[j][1].tu = tmp_tu;

				tmp_tu = enemy[j][2].tu;
				enemy[j][2].tu = enemy[j][3].tu;
				enemy[j][3].tu = tmp_tu;
			}
			
			for (int i = 0; i < 4; i++)
			{
				enemy[j][i].x -= wolf[j].move_y;//enemyのSpeed
				if (E_game_time % 4== 0)
				{
					enemy[j][i].tu += EnemyWidth_tu();
				}
			}
			if (enemy[j][0].tu == EnemyWidth_tu() * wolf[j].drawnumber)
			{
				/*enemy[j][0].tu = 0.f / 2048.f;
				enemy[j][1].tu = Enemy_tu(wolf[j].type);
				enemy[j][2].tu = Enemy_tu(wolf[j].type);
				enemy[j][3].tu = 0.f / 2048.f;*/
				SettingEnemy_tu(wolf[j].type);

			}
			

		}
	}
}
