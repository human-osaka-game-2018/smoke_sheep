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
  3,     //	int life;
  wait    //isAction state;
};


CUSTOMVERTEX player_chara[] =
{
	{ Sheep.x - Sheep.scale , Sheep.y - Sheep.scale , 0.5f, 1.0f, 0xFFFFFFFF, 0.0f,  0.0f },
{ Sheep.x + Sheep.scale-30, Sheep.y - Sheep.scale , 0.5f, 1.0f, 0xFFFFFFFF, CHARA_WIDTH, 0.0f },
{ Sheep.x + Sheep.scale-30, Sheep.y + Sheep.scale, 0.5f, 1.0f, 0xFFFFFFFF, CHARA_WIDTH, CHARA_HEIGHT },
{ Sheep.x - Sheep.scale,Sheep.y + Sheep.scale, 0.5f, 1.0f, 0xFFFFFFFF, 0.0f,  CHARA_HEIGHT },
};

float Player_tv(playerpicture_tv a) {
	switch (a)
	{
	case tv_wait:
		return 0.f;
	case tv_walk:
		return 0.f;
	case tv_jump:
		return 0.f;
	case tv_atack:
		return CHARA_HEIGHT * 1;
	case tv_smokewait:
			return CHARA_HEIGHT*2;
		case tv_hensin:
			return CHARA_HEIGHT*2;
		case tv_smokewalk:
			return  CHARA_HEIGHT * 3;
		
	}

}

float Player_tu(playerpicture_tu a) {
	switch (a)
	{
	case tu_wait:
			return 0.f / IMAGESIZE;
	case tu_walk:
		return CHARA_WIDTH*4;
	case tu_jump:
		return CHARA_WIDTH*10;
	case tu_smokewait:
		return CHARA_WIDTH*4;
	case tu_smokewalk:
		return  0.f / IMAGESIZE;
	case tu_hensin:
		return 0.f/ IMAGESIZE;

	}
}
void SettingPlayer_tu(playerpicture_tu a) {
	player_chara[0].tu = Player_tu(a);
	player_chara[1].tu = Player_tu(a) + CHARA_WIDTH;
	player_chara[2].tu = Player_tu(a) + CHARA_WIDTH ;
	player_chara[3].tu = Player_tu(a);
}

void SettingPlayer_tv(playerpicture_tv a) {
	player_chara[0].tv = Player_tv(a);
	player_chara[1].tv = Player_tv(a);
	player_chara[2].tv = Player_tv(a)+CHARA_HEIGHT ;
	player_chara[3].tv = Player_tv(a)+CHARA_HEIGHT ;
}


void SettingPlayer_tutv(playerpicture_tu a ,playerpicture_tv b,isAction c) {
	if (Sheep.state != c) {
		Sheep.state = c;
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
		//‰æ‘œ‚Ì¶‰E”½“]
		if (player_chara[0].tu > player_chara[1].tu)
		{
			DrawTurn(player_chara);
		}



		if (jflag)
		{
			if (Right_Hit(player_chara, Soil, AND)) {
				for (int i = 0; i < 4; i++)
				{
					player_chara[i].x += Sheep.x_speed;
				}
			}

		}
		else {
			//‰Eã‚Æ‰E‰º‚Ì‚ ‚½‚è”»’è

			if (Right_Hit(player_chara, Soil, AND)) {

				if (!Smoke)
				{
					SettingPlayer_tutv(tu_walk, tv_walk, walk);
					if (Right_Hit(player_chara, Ive, AND))
					{
						for (int i = 0; i < 4; i++)
						{
							player_chara[i].x += Sheep.x_speed;
							if (P_game_time % 4 == 0)
							{
								player_chara[i].tu += CHARA_WIDTH;
							}
						}
					}
					if (player_chara[0].tu == Player_tu(tu_walk) + CHARA_WIDTH * 6)
					{
						SettingPlayer_tu(tu_walk);
					}
				}
				else if (Smoke)
				{
					SettingPlayer_tutv(tu_smokewalk, tv_smokewalk, smokewalk);
					for (int i = 0; i < 4; i++)
					{
						player_chara[i].x += Sheep.x_speed;
						if (P_game_time % 4 == 0)
						{
							player_chara[i].tu += CHARA_WIDTH;
						}
					}
					if (player_chara[0].tu == Player_tu(tu_smokewalk) + CHARA_WIDTH * 6)
					{
						SettingPlayer_tu(tu_smokewalk);
					}
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
		if (jflag)
		{
			if (Right_Hit(player_chara, Soil, AND)) {
				for (int i = 0; i < 4; i++)
				{
					player_chara[i].x -= Sheep.x_speed;
				}
			}

		}
		else {
			if (Left_Hit(player_chara, Soil, AND) == true)
			{
				if (Smoke == false) {
					SettingPlayer_tutv(tu_walk, tv_walk, walk);
					if (Left_Hit(player_chara, Ive, AND) == true)
					{
						for (int i = 0; i < 4; i++)
						{
							player_chara[i].x -= Sheep.x_speed; //Player‚ÌSpeed

							if (P_game_time % 4 == 0)
							{
								player_chara[i].tu += CHARA_WIDTH;
							}
						}
					}
					if (player_chara[1].tu == Player_tu(tu_walk) + CHARA_WIDTH * 6)
					{
						SettingPlayer_tu(tu_walk);
						DrawTurn(player_chara);
					}
				}
				else if (Smoke == true)
				{
					SettingPlayer_tutv(tu_smokewalk, tv_smokewalk, smokewalk);
					for (int i = 0; i < 4; i++)
					{
						player_chara[i].x -= Sheep.x_speed; //Player‚ÌSpeed

						if (P_game_time % 4 == 0)
						{
							player_chara[i].tu += CHARA_WIDTH;
						}
					}

					if (player_chara[1].tu == Player_tu(tu_smokewalk) + CHARA_WIDTH * 6)
					{
						SettingPlayer_tu(tu_smokewalk);
						DrawTurn(player_chara);
					}
				}
			}
		}
}

void smokehensintime()
{
	
	if (SmokeTransNow&&!SmokeReturnNomal)
	{
		/*if (player_chara[1].tv != Player_tv(tv_hensin))
		{*/
			SettingPlayer_tutv(tu_hensin, tv_hensin,henshin);
		
		static int count = 0;
		count++;

		for (int i = 0; i < 4; i++)
		{
			if (count % 10 == 0)
			{
				player_chara[i].tu += CHARA_WIDTH ;
			}
		}
		if (player_chara[0].tu == CHARA_WIDTH * 4)
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
			SettingPlayer_tutv(tu_hensin, tv_hensin,henshin);
			player_chara[0].tu = CHARA_WIDTH * 3;
			player_chara[1].tu = CHARA_WIDTH * 4;
			player_chara[2].tu = CHARA_WIDTH * 4;
			player_chara[3].tu = CHARA_WIDTH * 3;
		}

		for (int i = 0; i < 4; i++)
		{
			if (count % 10 == 0)
			{
				player_chara[i].tu -= CHARA_WIDTH;
			}
		}
		if (player_chara[1].tu == CHARA_WIDTH * 0) {
			SmokeReturnNomal = false;
			SmokeTransNow = false;
			Smoke = false;
			SettingPlayer_tutv(tu_walk, tv_walk,walk);

		}
	}


}

void PlayerWait(int count)
{
	if (!jflag) {
		if (Sheep.state != wait)
		{
			if (player_chara[0].tu > player_chara[1].tu)
			{
				SettingPlayer_tutv(tu_wait, tv_wait, wait);
				DrawTurn(player_chara);
			}
			else if (player_chara[0].tu < player_chara[1].tu)
			{
				SettingPlayer_tutv(tu_wait, tv_wait, wait);
			}

		}
		if (count % 4 == 0)
		{
			for (int i = 0; i < 4; i++)
			{
				player_chara[i].tu += CHARA_WIDTH;
			}
		}
		if (player_chara[0].tu > player_chara[1].tu)
		{
			if (player_chara[1].tu == CHARA_WIDTH * 4)
			{
				SettingPlayer_tu(tu_wait);
				DrawTurn(player_chara);
			}
		}
		if (player_chara[0].tu < player_chara[1].tu)
		{
			if (player_chara[0].tu == CHARA_WIDTH * 4)
			{
				SettingPlayer_tu(tu_wait);
			}
		}
	}
}







void MainControl()
{
	
	
	
	
}





