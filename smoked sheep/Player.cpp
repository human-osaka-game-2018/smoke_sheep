#include"player.h"
#include"map.h"


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
{ Sheep.x + Sheep.scale-30, Sheep.y - Sheep.scale , 0.5f, 1.0f, 0xFFFFFFFF, 75.f/1024.f, 0.0f },
{ Sheep.x + Sheep.scale-30, Sheep.y + Sheep.scale, 0.5f, 1.0f, 0xFFFFFFFF, 75.f/1024.f, 124.f/1024.f },
{ Sheep.x - Sheep.scale,Sheep.y + Sheep.scale, 0.5f, 1.0f, 0xFFFFFFFF, 0.0f,  124.f/1024.f },
};

float Player_tv(playerpicture_tv a) {
	switch (a)
	{
	case tv_walk:
		return 0;
		case tv_run:
			return 0;
		case tv_smokewait:
			return 500.f / 1024.f;
		case tv_smokewalk:
			return  375.f / 1024.f;
		case tv_hensin:
			return 625.f / 1024.f;
		case tv_atack:
			return 750.f / 1024.f;
	}

}

float Player_tu(playerpicture_tu a) {
	switch (a)
	{
	case tu_walk:
		return 75.f/1024.f;
	case tu_run:
		return 125.f/1024.f;
	case tu_jump:
		return 80.f / 1024.f;
	case tu_smokewait:
		return 105.f / 1024.f;
	case tu_smokewalk:
		return  105.f / 1024.f;
	case tu_hensin:
		return 105.f / 1024.f;
	case tu_atack:
		return 95.f / 1024.f;
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
	player_chara[2].tv = 124.f / 1024.f;
	player_chara[3].tv = 124.f / 1024.f;
}


void SettingPlayer_tv(playerpicture_tv a) {
		PlayerFormat_tv();//tv‚Ì‰Šú‰»
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
	if (smoke) {
		for (int i = 0; i < 4; i++)
		{
			player_chara[i].y -= Sheep.y_speed;
		}
	}
}

void PlayerDown() {
	if (smoke) {
		for (int i = 0; i < 4; i++)
		{
			player_chara[i].y += Sheep.y_speed;
		}
	}
}

void PlayerRight() {
	static unsigned int P_game_time;
		P_game_time++;
		//‰æ‘œ‚Ì¶‰E”½“]
		if (player_chara[0].tu > player_chara[1].tu)
		{
			float tmp_tu;

			tmp_tu = player_chara[0].tu;
			player_chara[0].tu = player_chara[1].tu;
			player_chara[1].tu = tmp_tu;

			tmp_tu = player_chara[2].tu;
			player_chara[2].tu = player_chara[3].tu;
			player_chara[3].tu = tmp_tu;
		}
		//‰Eã‚Æ‰E‰º‚Ì‚ ‚½‚è”»’è
		if (Map_Hit(int(player_chara[2].x - map_error), int(player_chara[2].y - 6)) != 1 &&
			Map_Hit(int(player_chara[1].x - map_error), int(player_chara[1].y)) != 1 &&
			Map_Hit(int(player_chara[1].x - map_error), int(player_chara[1].y + 55)) != 1) {

			if (smoke == false)
			{
				SettingPlayer_tutv(tu_walk,tv_walk);
				if (Map_Hit(int(player_chara[2].x - map_error), int(player_chara[2].y - 6)) != 5 &&
					Map_Hit(int(player_chara[5].x - map_error), int(player_chara[5].y)) != 5
					&& Map_Hit(int(player_chara[5].x - map_error), int(player_chara[5].y + 55)) != 5)
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
			else if(smoke==true)
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
			float tmp_tu;

			tmp_tu = player_chara[0].tu;
			player_chara[0].tu = player_chara[1].tu;
			player_chara[1].tu = tmp_tu;

			tmp_tu = player_chara[2].tu;
			player_chara[2].tu = player_chara[3].tu;
			player_chara[3].tu = tmp_tu;
		}
		if (Map_Hit(int(player_chara[0].x - map_error), int(player_chara[0].y)) != 1
			&& Map_Hit(int(player_chara[3].x - map_error), int(player_chara[3].y - 20)) != 1
			&& Map_Hit(int(player_chara[0].x - map_error), int(player_chara[0].y + 55)) != 1)
		{
			if (smoke == false) {
				SettingPlayer_tutv(tu_walk,tv_walk);
				if (Map_Hit(int(player_chara[0].x - map_error), int(player_chara[0].y)) != 5
					&& Map_Hit(int(player_chara[3].x - map_error), int(player_chara[3].y - 20)) != 5
					&& Map_Hit(int(player_chara[0].x - map_error), int(player_chara[0].y + 55)) != 5)
				{
					for (int i = 0; i < 4; i++)
					{
						player_chara[i].x -= Sheep.x_speed; //Player‚ÌSpeed

						if (P_game_time % 4== 0)
						{
							player_chara[i].tu += Player_tu(tu_walk);
						}
					}
				}
				if (player_chara[1].tu == Player_tu(tu_walk)*3)
				{
					player_chara[0].tu = Player_tu(tu_walk);
					player_chara[1].tu = 0.0f;
					player_chara[2].tu = 0.0f;
					player_chara[3].tu = Player_tu(tu_walk);
				}
			}
			else if(smoke==true)
			{
				SettingPlayer_tutv(tu_smokewalk,tv_smokewalk);
				for (int i = 0; i < 4; i++)
				{
					player_chara[i].x -= Sheep.x_speed; //Player‚ÌSpeed

					if (P_game_time % 4 == 0)
					{
						player_chara[i].tu += Player_tu(tu_smokewalk);
					}
				}
			}
			if (player_chara[1].tu == Player_tu(tu_smokewalk)*3)
			{
				player_chara[0].tu = Player_tu(tu_smokewalk);
				player_chara[1].tu = 0.0f;
				player_chara[2].tu = 0.0f;
				player_chara[3].tu = Player_tu(tu_smokewalk);
			}
		}
}

void smokehensintime()
{
	
	if (smokehensinnow&&!smokereturnnomal)
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
			smoke = true;
			smokehensinnow = false;
		}
	}
	if (smokehensinnow&&smokereturnnomal)
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
			smokereturnnomal = false;
			smokehensinnow = false;
			smoke = false;
			SettingPlayer_tutv(tu_walk, tv_walk);

		}
	}


}
void MainControl()
{
	
	
	
	
}





