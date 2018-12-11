#include"player.h"
#include"Map.h"
#include"Hit.h"


g_player Sheep =
{ 
  155.f, //	float x
  215.f, //	float y
  55.f,  //	float scale
  5,     // int x_speed;
  3,     //	int	y_speed;
  5,     //	int smoketime;
  3      //	int life;
};


CUSTOMVERTEX player_chara[] =
{
	{ Sheep.x - Sheep.scale , Sheep.y - Sheep.scale , 0.5f, 1.0f, 0xFFFFFFFF, 0.0f,  0.0f },
{ Sheep.x + Sheep.scale-30, Sheep.y - Sheep.scale , 0.5f, 1.0f, 0xFFFFFFFF, 75.f/IMAGESIZE, 0.0f },
{ Sheep.x + Sheep.scale-30, Sheep.y + Sheep.scale, 0.5f, 1.0f, 0xFFFFFFFF, 75.f/IMAGESIZE, 124.f/IMAGESIZE },
{ Sheep.x - Sheep.scale,Sheep.y + Sheep.scale, 0.5f, 1.0f, 0xFFFFFFFF, 0.0f,  124.f/IMAGESIZE },
};

float Player_tv(playerpicture_tv a) {
	switch (a)
	{
	case tv_walk:
		return 0;
		case tv_run:
			return 0;
		case tv_smokewait:
			return 500.f / IMAGESIZE;
		case tv_smokewalk:
			return  375.f / IMAGESIZE;
		case tv_hensin:
			return 625.f / IMAGESIZE;
		case tv_atack:
			return 750.f / IMAGESIZE;
	}

}

float Player_tu(playerpicture_tu a) {
	switch (a)
	{
	case tu_walk:
		return 75.f/IMAGESIZE;
	case tu_run:
		return 125.f/IMAGESIZE;
	case tu_jump:
		return 80.f / IMAGESIZE;
	case tu_smokewait:
		return 105.f / IMAGESIZE;
	case tu_smokewalk:
		return  105.f / IMAGESIZE;
	case tu_hensin:
		return 105.f / IMAGESIZE;
	case tu_atack:
		return 95.f / IMAGESIZE;
	}
}
void SettingPlayer_tu(playerpicture_tu a) {
	player_chara[0].tu = 0;
	player_chara[1].tu = Player_tu(a);
	player_chara[2].tu = Player_tu(a);
	player_chara[3].tu = 0;
}

void PlayerFormat_tv() {
	player_chara[0].tv = 0;
	player_chara[1].tv = 0;
	player_chara[2].tv = 124.f / IMAGESIZE;
	player_chara[3].tv = 124.f / IMAGESIZE;
}


void SettingPlayer_tv(playerpicture_tv a) {
		PlayerFormat_tv();//tvÇÃèâä˙âª
		for (int i = 0; i < 4; i++)
		{
			player_chara[i].tv += Player_tv(a);
		}
}

void SettingPlayer_tutv(playerpicture_tu a ,playerpicture_tv b) {
	if (player_chara[0].tv != Player_tv(b))
	{
		SettingPlayer_tv(b);
		SettingPlayer_tu(a);
	}
}









void PlayerUp()
{
	if (Smoke) {
		for (int i = 0; i < 4; i++)
		{
			player_chara[i].y -= Sheep.y_speed;
		}
	}
}

void PlayerDown() {
	if (Smoke) {
		for (int i = 0; i < 4; i++)
		{
			player_chara[i].y += Sheep.y_speed;
		}
	}
}

void PlayerRight() {
	static unsigned int P_game_time;
		P_game_time++;
		//âÊëúÇÃç∂âEîΩì]
		if (player_chara[0].tu > player_chara[1].tu)
		{
			DrawTurn(player_chara);
		}
		//âEè„Ç∆âEâ∫ÇÃÇ†ÇΩÇËîªíË
		if (Right_Hit(player_chara, 1,AND) == true) {

			if (Smoke == false)
			{
				SettingPlayer_tutv(tu_walk,tv_walk);
				if (Right_Hit(player_chara, 7,AND) == true)
				{
					for (int i = 0; i < 4; i++)
					{
						player_chara[i].x += Sheep.x_speed;
						if (P_game_time % 4 == 0)
						{
							player_chara[i].tu += Player_tu(tu_walk);
						}
					}
				}
				if (player_chara[0].tu == Player_tu(tu_walk)*3)
				{
					SettingPlayer_tu(tu_walk);
				}
			}
			else if(Smoke==true)
			{
				SettingPlayer_tutv(tu_smokewalk,tv_smokewalk);
				for (int i = 0; i < 4; i++)
				{
					player_chara[i].x += Sheep.x_speed;
					if (P_game_time % 4 == 0)
					{	
						player_chara[i].tu += Player_tu(tu_smokewalk);
					}
				}
				if (player_chara[0].tu == Player_tu(tu_smokewalk)*3)
				{
					SettingPlayer_tu(tu_smokewalk);
				}
			}
		}
}
void PlayerLeft() {

	static unsigned int P_game_time;
		P_game_time++;
		if (player_chara[0].tu < player_chara[1].tu)
		{
			DrawTurn(player_chara);
		}
		if (Left_Hit(player_chara, 1,AND)==true)
		{
			if (Smoke == false) {
				SettingPlayer_tutv(tu_walk,tv_walk);
				if(Left_Hit(player_chara, 7,AND)==true)
				{
					for (int i = 0; i < 4; i++)
					{
						player_chara[i].x -= Sheep.x_speed; //PlayerÇÃSpeed

						if (P_game_time % 4== 0)
						{
							player_chara[i].tu += Player_tu(tu_walk);
						}
					}
				}
				if (player_chara[1].tu == Player_tu(tu_walk)*3)
				{
				
					SettingPlayer_tu(tu_walk);
					DrawTurn(player_chara);
				}
			}
			else if(Smoke==true)
			{
				SettingPlayer_tutv(tu_smokewalk,tv_smokewalk);
				for (int i = 0; i < 4; i++)
				{
					player_chara[i].x -= Sheep.x_speed; //PlayerÇÃSpeed

					if (P_game_time % 4 == 0)
					{
						player_chara[i].tu += Player_tu(tu_smokewalk);
					}
				}
			}
			if (player_chara[1].tu == Player_tu(tu_smokewalk)*3)
			{
				SettingPlayer_tu(tu_smokewalk);
				DrawTurn(player_chara);
			}
		}
}

void smokehensintime()
{
	
	if (SmokeTransNow&&!SmokeReturnNomal)
	{
		if (player_chara[1].tv != Player_tv(tv_hensin))
		{
			SettingPlayer_tutv(tu_hensin, tv_hensin);
		}
		static int count = 0;
		count++;

		for (int i = 0; i < 4; i++)
		{
			if (count % 10 == 0)
			{
				player_chara[i].tu += Player_tu(tu_hensin);
			}
		}
		if (player_chara[0].tu == Player_tu(tu_hensin) * 4)
		{
			Smoke = true;
			SmokeTransNow = false;
		}
	}
	if (SmokeTransNow&&SmokeReturnNomal)
	{
		static int count;
		count++;
		
		if (player_chara[1].tv != Player_tv(tv_hensin))
		{
			SettingPlayer_tutv(tu_hensin, tv_hensin);
			player_chara[0].tu = Player_tu(tu_hensin) * 3;
			player_chara[1].tu = Player_tu(tu_hensin) * 4;
			player_chara[2].tu = Player_tu(tu_hensin) * 4;
			player_chara[3].tu = Player_tu(tu_hensin) * 3;
		}

		for (int i = 0; i < 4; i++)
		{
			if (count % 10 == 0)
			{
				player_chara[i].tu -= Player_tu(tu_hensin);
			}
		}
		if (player_chara[1].tu == Player_tu(tu_hensin) * 0) {
			SmokeReturnNomal = false;
			SmokeTransNow = false;
			Smoke = false;
			SettingPlayer_tutv(tu_walk, tv_walk);

		}
	}


}
void MainControl()
{
	
	
	
	
}





