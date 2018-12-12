#include"render.h"
#include"enemy.h"
#include"Player.h"
#include"Map.h"

void Tex_Load(const char* name, LPDIRECT3DTEXTURE9* pTexture, IDirect3DDevice9* pD3Device)
{
	FAILED(D3DXCreateTextureFromFile(
		pD3Device,
		TEXT(name),
		pTexture));
}

void Tex_Set(IDirect3DDevice9* pD3Device, LPDIRECT3DTEXTURE9 pTexture)
{
	pD3Device->SetTexture(0, pTexture);
}

void Tex_Set_Draw(IDirect3DDevice9* pD3Device, LPDIRECT3DTEXTURE9 pTexture, CUSTOMVERTEX* Vertex)
{
	Tex_Set(pD3Device, pTexture);

	pD3Device->DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		Vertex,
		sizeof(CUSTOMVERTEX));
}

void DrawTurn(CUSTOMVERTEX *a) {
	float tmp_tu;

	tmp_tu = a[0].tu;
	a[0].tu = a[1].tu;
	a[1].tu = tmp_tu;

	tmp_tu = a[2].tu;
	a[2].tu = a[3].tu;
	a[3].tu = tmp_tu;
}

void Render()
{
	//画面の消去
	g_pD3Device->Clear(0, NULL,
		D3DCLEAR_TARGET,
		D3DCOLOR_XRGB(0x00, 0x00, 0x00),
		1.0, 0);
	//描画の開始
g_pD3Device->BeginScene();

	Tex_Set_Draw(g_pD3Device, g_pTexture[BACKGROUND_TEX], background);

	PlayerRender();
	mapRender();

	for (int i = 0; i < Enemy_Number; i++)
	{
		Tex_Set_Draw(g_pD3Device, g_pTexture[ENEMY_TEX], enemy[i]);
	}

	//描画の終了
	g_pD3Device->EndScene();

	//表示
	g_pD3Device->Present(NULL, NULL, NULL, NULL);
}

void mapRender()
{
	static bool CsvReading = true;
	if (CsvReading == true)
	{
		FILE*  fp;
		fopen_s(&fp, "Map.csv", "r");
		

		for (int i = 0; i < MAP_HEIGHT; i++)
		{
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				fscanf_s(fp, "%d,", &Map[i][j], _countof(Map));
			}
		}
	}

	/*マップの描画処理*/
	CUSTOMVERTEX tmp_map1[4];


	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{

			for (int i = 0; i < 4; i++)
			{
				tmp_map1[i] = map_tip[i];
			}
			for (int i = 0; i < 4; i++)
			{
				tmp_map1[i].x += (x * 64);
				tmp_map1[i].y += (y * 64);
			}

			///////////////////////////////////////////////////////////

			if (Map[y][x] == 1)Tex_Set_Draw(g_pD3Device, g_pTexture[M_01_01_TEX], tmp_map1);
			//if (Map[y][x] == 2);//
			//if (Map[y][x] == 3);//
			//if (Map[y][x] == 4);//
			//if (Map[y][x] == 5);//
			if (Map[y][x] == 6)Tex_Set_Draw(g_pD3Device, g_pTexture[M_01_01_TEX], tmp_map1);
			if (Map[y][x] == 7)Tex_Set_Draw(g_pD3Device, g_pTexture[iveblock_TEX], tmp_map1);
			if (Map[y][x] == 8)Tex_Set_Draw(g_pD3Device, g_pTexture[iveblock_TEX], tmp_map1);
			if (Map[y][x] == 53)Tex_Set_Draw(g_pD3Device, g_pTexture[iveblock_TEX], tmp_map1);
			if (CsvReading)
			{
				if (Map[y][x] == 21)
				{
					if (Enemy_Number < 100)
					{
						for (int i = 0; i < 4; i++)
						{
							enemy[Enemy_Number][i] = tmp_map1[i];
						}
				
						InitEnemy(Map[y][x], Enemy_Number);
						 SettingEnemy_tutv(wolf[Enemy_Number].type);
						Enemy_Number++;
					}
				}

				if (Map[y][x] == 22)
				{
					if (Enemy_Number < 100)
					{
						for (int i = 0; i < 4; i++)
						{
							enemy[Enemy_Number][i] = tmp_map1[i];
						}
						InitEnemy(Map[y][x], Enemy_Number);
					
						SettingEnemy_tutv(wolf[Enemy_Number].type);
						Enemy_Number++;
					}
				}
				if (Map[y][x] == 23)
				{
					if (Enemy_Number < 100)
					{
						for (int i = 0; i < 4; i++)
						{
							enemy[Enemy_Number][i] = tmp_map1[i];
						}
						InitEnemy(Map[y][x], Enemy_Number);

						SettingEnemy_tutv(wolf[Enemy_Number].type);
						Enemy_Number++;
					}
				}
				if (Map[y][x] == 24)
				{
					if (Enemy_Number < 100)
					{
						for (int i = 0; i < 4; i++)
						{
							enemy[Enemy_Number][i] = tmp_map1[i];
						}
						InitEnemy(Map[y][x], Enemy_Number);
						
						SettingEnemy_tutv(wolf[Enemy_Number].type);
						Enemy_Number++;
					}
				}

			}
		}
	}
	CsvReading = false;
}

void PlayerRender()
{

	Tex_Set_Draw(g_pD3Device, g_pTexture[C_01_01_TEX], player_chara);
	
}





void TEX_Init()
{

	//enum TEXTURE
	//{
	//	M_01_01_TEX,
	//	C_01_01_TEX,
	//	Fire_TEX,
	//	Wataame_TEX,
	//	SmokeS_Smoke_TEX,
	//	iveblock_TEX,
	//	BACKGROUND_TEX,
	//  ENEMY_TEX
	//	TEXMAX,

	//};
	
	Tex_Load("text/M_01_01.png", &g_pTexture[M_01_01_TEX], g_pD3Device);
	Tex_Load("text/chara.png", &g_pTexture[C_01_01_TEX], g_pD3Device);
	Tex_Load("text/fire.png", &g_pTexture[Fire_TEX], g_pD3Device);
	Tex_Load("text/wataame.png", &g_pTexture[Wataame_TEX], g_pD3Device);
	Tex_Load("text/ive_block.png", &g_pTexture[iveblock_TEX], g_pD3Device);
	Tex_Load("text/SmokeS_Smoke.png", &g_pTexture[Smoke_Smoke_TEX], g_pD3Device);
	Tex_Load("text/background.png", &g_pTexture[BACKGROUND_TEX], g_pD3Device);
	Tex_Load("text/enemy1.png", &g_pTexture[ENEMY_TEX], g_pD3Device);


	//画像読み込みのストック
	/*

	Tex_Load(".png", &g_pTexture[], g_pD3Device);
	
	*/


}


