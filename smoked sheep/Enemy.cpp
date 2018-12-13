#include"Enemy.h"
#include"player.h"
#include"Map.h"
#include"Hit.h"


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
		return 0.f / IMAGESIZE2;
	case speed:
		return 800.f / IMAGESIZE2;
	case strong:
		return 0.f / IMAGESIZE2;
	case hide:
		return 0.f / IMAGESIZE2;
	}
}

float Enemy_tu_ex(enemytype a) {
	switch (a)
	{
	case nomal:
		return 0.f / IMAGESIZE2;
	case speed:
		return 800.f / IMAGESIZE2;
	case strong:
		return 0.f / IMAGESIZE2;
	case hide:
		return 800.f / IMAGESIZE2;
	}
}

float Enemy_tv(enemytype a) {//2回目以降のループの初期座標
	switch (a)
	{
	case nomal:
		return 0.f / IMAGESIZE2;
	case speed:
		return 0.f / IMAGESIZE2;
	case strong:
		return EnemyHeight_tv();
	case hide:
		return EnemyHeight_tv()*2;
	}
}

float EnemyWidth_tu() {
	return 200.f / IMAGESIZE2;
}
float EnemyHeight_tv() {

	return 145.f / IMAGESIZE2;
}
void FormatEnemy_tu()
{
	enemy[Enemy_Number][0].tu = 0.f / IMAGESIZE2;
	enemy[Enemy_Number][1].tu = EnemyWidth_tu();
	enemy[Enemy_Number][2].tu = EnemyWidth_tu();
	enemy[Enemy_Number][3].tu = 0.f / IMAGESIZE2;
}
void FormatEnemy_tv() {
	enemy[Enemy_Number][0].tv = 0.f / IMAGESIZE2;
	enemy[Enemy_Number][1].tv = 0.f / IMAGESIZE2;
	enemy[Enemy_Number][2].tv = EnemyHeight_tv();
	enemy[Enemy_Number][3].tv =  EnemyHeight_tv();
}

void SetEnemy_tv(enemytype a)
{
	FormatEnemy_tv();
	for (int i = 0; i < 4; i++)
	{
		enemy[Enemy_Number][i].tv += Enemy_tv(a);
	}
}

void SetEnemy_tu(enemytype a) {
	FormatEnemy_tu();
	for (int i = 0; i < 4; i++)
	{
		enemy[Enemy_Number][i].tu += Enemy_tu(a);
	}
}

void SettingEnemy_tutv(enemytype a)
{
	
		SetEnemy_tv(a);
		SetEnemy_tu(a);
	
}
void InitEnemy(int mapnumber,int Enemy_Number) {
	switch(mapnumber)
	{
	case 21:
		wolf[Enemy_Number] = {nomal,1,2.f,2.f ,4};
		break;
	case 22:
		wolf[Enemy_Number] = {speed,1,4.f,4.f,8 };
		break;
	case 23:
		wolf[Enemy_Number] = { strong,2,2.f,2.f,4 };
		break;
	case 24:
		wolf[Enemy_Number] = {hide,1,2.f,2.f ,8};
		break;
	}
}

void EnemyRender()
{
}


void Enemy_ReverseFlag()
{
	for (int i = 0; i < Enemy_Number; i++)
	{
		if (LRjudg[i] == LEFT)
		{
			if (Left_Hit(enemy[i], Empty, OR,-1))
			{
				LRjudg[i] = !LRjudg[i];
				
			}
		}
		else if(LRjudg[i] == RIGHT) {
			if (Right_Hit(enemy[i], Empty, OR,-1))
			{
				LRjudg[i] = !LRjudg[i];
				

			}
		}
	}
}

void EnemyMove(CUSTOMVERTEX *a, enemy_wolf *b, bool RIGHTorLEFT,unsigned int E_FrameTime) {
	for (int i = 0; i < 4; i++)
	{
		if (RIGHTorLEFT == RIGHT)
		{
			a[i].x += b->move_x;//enemyのSpeed
			if (E_FrameTime % 4 == 0)
			{
				a[i].tu += EnemyWidth_tu();
			}
		}
	}
	for (int i = 0; i < 4; i++)
	{
		if (RIGHTorLEFT == LEFT)
		{
			a[i].x -= b->move_x;//enemyのSpeed
			if (E_FrameTime % 4 == 0)
			{
				a[i].tu += EnemyWidth_tu();
			}
		}
	}
	
	
}



void EnemyMainControl() {
	static unsigned int E_FrameTime;
	E_FrameTime++;
	Enemy_ReverseFlag();//エネミーの左右反転の確認

	for (int j = 0; j < Enemy_Number; j++)
	{
		if (LRjudg[j]) {
			if (enemy[j][0].tu < enemy[j][1].tu)
			{
				DrawTurn(enemy[j]);
			}
			EnemyMove(enemy[j], &wolf[j], LRjudg[j], E_FrameTime);

			if (enemy[j][1].tu == (EnemyWidth_tu() * wolf[j].drawnumber))
			{

				enemy[j][0].tu = EnemyWidth_tu() + Enemy_tu_ex(wolf[j].type);
				enemy[j][1].tu = (0.f / IMAGESIZE2) + Enemy_tu_ex(wolf[j].type);
				enemy[j][2].tu = (0.f / IMAGESIZE2) + Enemy_tu_ex(wolf[j].type);
				enemy[j][3].tu = EnemyWidth_tu() + Enemy_tu_ex(wolf[j].type);
			}
			
			
		}
		else {
			if (enemy[j][0].tu > enemy[j][1].tu)
			{
				DrawTurn(enemy[j]);
			}
			EnemyMove(enemy[j], &wolf[j], LRjudg[j], E_FrameTime);
			
			if (enemy[j][0].tu == (EnemyWidth_tu() * wolf[j].drawnumber))
			{
		        enemy[j][0].tu = (0.f / IMAGESIZE2)+Enemy_tu_ex(wolf[j].type);
				enemy[j][1].tu = EnemyWidth_tu()+ Enemy_tu_ex(wolf[j].type);
				enemy[j][2].tu = EnemyWidth_tu()+ Enemy_tu_ex(wolf[j].type);
				enemy[j][3].tu = (0.f / IMAGESIZE2)+Enemy_tu_ex(wolf[j].type);
			}
			
		}
	}
}
