#include"player.h"
#include"Main.h"
#define MAP_HEIGHT 12
#define MAP_WIDTH 130
#define GRAVITY 9.8

//Directx関係----------------------------
LPDIRECT3DTEXTURE9	  g_pTexture[TEXMAX];	//	画像の情報を入れておく為のポインタ配列
IDirect3DDevice9*	  g_pD3Device;		//	Direct3Dのデバイス
D3DPRESENT_PARAMETERS g_D3dPresentParameters;		//	パラメータ
D3DDISPLAYMODE		  g_D3DdisplayMode;
IDirect3D9*			  g_pDirect3D;		//	Direct3Dのインターフェイス
LPDIRECTINPUT8 pDinput = NULL;
LPDIRECTINPUTDEVICE8 pKeyDevice = NULL;
HRESULT InitD3d(HWND);
HRESULT InitDinput(HWND);
LPD3DXFONT MainFont;

CUSTOMVERTEX map_tip[] =
{
	{ 0.0f,  0.0f,  0.5f, 1.0f, 0xFFFFFFFF, 0.0f, 0.0f },
{ 64.0f, 0.0f,  0.5f, 1.0f, 0xFFFFFFFF, 1.0f, 0.0f },
{ 64.0f, 64.0f, 0.5f, 1.0f, 0xFFFFFFFF, 1.0f, 1.0f },
{ 0.0f,  64.0f, 0.5f, 1.0f, 0xFFFFFFFF, 0.0f, 1.0f },
};


CUSTOMVERTEX enemy[] =
{
	{ 0.0f,  0.0f,  0.5f, 1.0f, 0xFFFFFFFF, 0.0f, 0.0f },
{ 64.0f, 0.0f,  0.5f, 1.0f, 0xFFFFFFFF, 1.0f, 0.0f },
{ 64.0f, 64.0f, 0.5f, 1.0f, 0xFFFFFFFF, 1.0f, 1.0f },
{ 0.0f,  64.0f, 0.5f, 1.0f, 0xFFFFFFFF, 0.0f, 1.0f },
};

int map_error = 0;
int map[MAP_HEIGHT][MAP_WIDTH];
bool isRight = false;
bool isLeft = false;
bool jflag = false;
unsigned int game_time = 0;
bool key_space = false;
bool smoke = false;

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
int Map_Hit(int x, int y)
{
	int map_x = x / 64;
	int map_y = y / 64;
	if (map_y < 0)
	{
		map_y = 0;
	}
  	if (map[map_y][map_x] ==1 )
	{
		return 1;
	}
	if (map[map_y][map_x] == 2)
	{
		return 2;
	}
	if (map[map_y][map_x] == 3)
	{
		return 3;
	}
	return 0;
}

void Map_Search(int x, int y, int* px, int* py)
{
	int map_x = x / 64;
	int map_y = y / 64;
	if (x % 64 != 0)
	{
		x++;
	}
	if (y % 64 != 0)
	{
		y++;
	}
	*px = map_x;
	*py = map_y;
}



void MainKeyControl()
{
	static int count = 0;
	count++;
	//キーボードで押されているキーを調べ、対応する方向に移動させる
	HRESULT hr = pKeyDevice->Acquire();
	if ((hr == DI_OK) || (hr == S_FALSE))
	{
		BYTE diks[256];
		pKeyDevice->GetDeviceState(sizeof(diks), &diks);

		if (diks[DIK_H] & 0x80)
		{
			
		}

		if (diks[DIK_A] & 0x80)
		{
			isLeft = true;
		}
		else
		{
			isLeft = false;
		}
		if (diks[DIK_D] & 0x80)
		{
			isRight = true;
		}
		else
		{
			isRight = false;
		}
		if (diks[DIK_UP] & 0x80)
		{
		}
		if (diks[DIK_DOWN] & 0x80)
		{
		}
		if (diks[DIK_W] & 0x80 && count > 10)
		{
			
			key_space = true;
			count = 0;
		}
		else {
			key_space = false;
		}
	}
}

void mapRender()
{
	static bool CsvReading = true;
	if (CsvReading == true)
	{
		FILE*  fp;
		fopen_s(&fp, "map.csv", "r");
		for (int i = 0; i < MAP_HEIGHT; i++)
		{
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				fscanf_s(fp, "%d,", &map[i][j], _countof(map));
			}
		}
		CsvReading = false;
	}

		/*マップの描画処理*/
		CUSTOMVERTEX tmp_map1[4];
		CUSTOMVERTEX enemy[4];
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
				if (map[y][x] == 1)
				{
					Tex_Set_Draw(g_pD3Device, g_pTexture[M_01_01_TEX], tmp_map1);
				}
				if (map[y][x] == 2)
				{

					for (int i = 0; i < 4; i++)
					{
						enemy[i] = tmp_map1[i];
						
					}
					Tex_Set_Draw(g_pD3Device, g_pTexture[Fire_TEX], enemy);

				}
				if (map[y][x] == 3)
				{
					Tex_Set_Draw(g_pD3Device, g_pTexture[Wataame_TEX], tmp_map1);

				}
			}
		}
}
void scroll() {
	//スクロール
	if (player_chara[1].x > 568 && map_error > -2880)
	{
		for (int i = 0; i < 4; i++)
		{
			map_tip[i].x -= 5;
 			player_chara[i].x -= 5;
		}
		map_error -= 5;

	}
	else if (player_chara[0].x < 440 && map_error < 0)
	{
		for (int i = 0; i < 4; i++)
		{
			map_tip[i].x += 5;
			player_chara[i].x += 5;
		}
		map_error += 5;
	}
}



void move() {
	
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
		/*	if (Map_Hit(int(enemy[2].x - map_error), int(enemy[2].y)) != 1 && Map_Hit(int(enemy[1].x - map_error), int(enemy[1].y)) != 1)
			{*/
			
						for (int i = 0; i < 4; i++)
						{
							enemy[i].x += 5;//PlayerのSpeed
						}
					}
	}
}










void Render()
{
	//頂点情報を入れる--------------------------------------

	CUSTOMVERTEX background[4]
	{
		{ 0.f  ,0.f  ,1.f ,1.f, 0xFFFFFFFF, 0.f,0.f },
	{ WIDTH,0.f  ,1.f ,1.f, 0xFFFFFFFF, 1.f, 0.f },
	{ WIDTH,HIGHT,1.f ,1.f, 0xFFFFFFFF, 1.f,  1.f },
	{ 0.f  ,HIGHT,1.f ,1.f, 0xFFFFFFFF, 0.f, 1.f },
	};


	//画面の消去
	g_pD3Device->Clear(0, NULL,
		D3DCLEAR_TARGET,
		D3DCOLOR_XRGB(0x00, 0x00, 0x00),
		1.0, 0);
	//描画の開始
	g_pD3Device->BeginScene();

	Tex_Set_Draw(g_pD3Device, g_pTexture[C_01_01_TEX], player_chara);

	mapRender();

	//描画の終了
	g_pD3Device->EndScene();

	//表示
	g_pD3Device->Present(NULL, NULL, NULL, NULL);
}



void Gravity(){
	
		//右下と右上の当たり判定
		if (Map_Hit(int(player_chara[2].x  - map_error), int(player_chara[2].y)) !=1 )
		{
			//下と右の当たり判定
 			if (Map_Hit(int(player_chara[2].x - 64 - map_error), int(player_chara[2].y)) !=1 )
			{
				//左下と左上の当たり判定
				if ( Map_Hit(int(player_chara[3].x  - map_error), int(player_chara[3].y)) !=1)
				{
					////左と上の当たり判定
					//if (Map_Hit(int(player_chara[0].x + 64 - map_error), int(player_chara[0].y)) !=1 && Map_Hit(int(player_chara[3].x - map_error), int(player_chara[3].y - 64)) !=1)
					//{
						for (int i = 0; i < 4; i++)
						{
							player_chara[i].y += 5;
						}
					/*}*/
				}
			}	
}
	if (Map_Hit(int(player_chara[2].x - map_error), int(player_chara[2].y)) == 1 && Map_Hit(int(player_chara[1].x - map_error), int(player_chara[1].y+100)) == 1&& Map_Hit(int(player_chara[2].x -64 -map_error), int(player_chara[2].y )) != 1)
	{
		for (int i = 0; i < 4; i++)
		{
			player_chara[i].y += 5;
		}
	}
	if (Map_Hit(int(player_chara[3].x - map_error), int(player_chara[3].y)) == 1 && Map_Hit(int(player_chara[0].x - map_error), int(player_chara[0].y + 100)) == 1 && Map_Hit(int(player_chara[2].x - 64 - map_error), int(player_chara[2].y)) != 1)
	{
		for (int i = 0; i < 4; i++)
		{
			player_chara[i].y += 5;
		}
	}
}

//
//
//めり込みバグの修正
void bug() {
	
	while (Map_Hit(int(player_chara[3].x+6  - map_error), int(player_chara[3].y-1)) == 1 || Map_Hit(int(player_chara[2].x-6  - map_error), int(player_chara[2].y-1)) == 1 || Map_Hit(int(player_chara[2].x - 64 - map_error), int(player_chara[2].y-1)) == 1)
	{
		for (int i = 0; i < 4; i++) {
			player_chara[i].y -= 0.1f;
		}
	}
	/*while (Map_Hit(int(player_chara[3].x +1 - map_error), int(player_chara[3].y)) == 1 || Map_Hit(int(player_chara[3].x  - map_error), int(player_chara[3].y - 55)) == 1 || Map_Hit(int(player_chara[0].x + 1 - map_error), int(player_chara[0].y)) == 1)
	{
		for (int i = 0; i < 4; i++) {
			player_chara[i].x += 0.1f;
		}
	}
	while (Map_Hit(int(player_chara[2].x -1 - map_error), int(player_chara[2].y)) == 1 || Map_Hit(int(player_chara[1].x  - map_error), int(player_chara[1].y + 55)) == 1 + 55 || Map_Hit(int(player_chara[1].x + 1 - map_error), int(player_chara[1].y)) == 1)
	{
		for (int i = 0; i < 4; i++) {
			player_chara[i].x -= 0.1f;
		}
	}*/
}


//ジャンプ処理
void jump() {
	static float p_y1[4] = { 0,0,0,0}, p_y2[4] = { 0,0,0,0};
	

		if (jflag == true) {
			
			for (int i = 0; i < 4; i++)
			{
				p_y1[i] = player_chara[i].y;

				player_chara[i].y += (player_chara[i].y - p_y2[i]) + 1;

				p_y2[i] = p_y1[i];
			}
			if (Map_Hit(int(player_chara[1].x - 6 - map_error), int(player_chara[1].y)) == 1 || Map_Hit(int(player_chara[0].x + 6 - map_error), int(player_chara[0].y)) == 1 || Map_Hit(int(player_chara[1].x - 64 - map_error), int(player_chara[1].y)) == 1)
			{
				for (int i = 0; i < 4; i++)
				{
					player_chara[i].y += 18;
				}
			}
			if (Map_Hit(int(player_chara[2].x -6-map_error), int(player_chara[2].y))==1||  Map_Hit(int(player_chara[3].x +6-map_error), int(player_chara[3].y)) == 1|| Map_Hit(int(player_chara[2].x - 64 - map_error), int(player_chara[2].y)) == 1)
			
			{
					jflag = false;
				
				
			}
		}
		if( key_space==true&& jflag == false) {
			jflag = true;

			for (int i = 0; i < 4; i++)
			{
				p_y2[i] = player_chara[i].y;
				player_chara[i].y = player_chara[i].y - 20;
			}
		}
}

void MainControl()
{
	if (isRight == true)
	{
		game_time++;
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
		//右上と右下のあたり判定
		if (Map_Hit(int(player_chara[2].x - map_error), int(player_chara[2].y-6 )) != 1 && Map_Hit(int(player_chara[1].x - map_error), int(player_chara[1].y)) !=1&& Map_Hit(int(player_chara[1].x - map_error), int(player_chara[1].y+55)) != 1)
		{
	
			for (int i = 0; i < 4; i++)
			{
				player_chara[i].x += 5;//PlayerのSpeed
				
				
				if (game_time % 4 == 0)
				{
					player_chara[i].tu += 0.125f;
				}
			}
		}
		if (player_chara[0].tu == 0.75f)
		{
			player_chara[0].tu = 0.0f;
			player_chara[1].tu = 0.125f;
			player_chara[2].tu = 0.125f;
			player_chara[3].tu = 0.0f;
		}
	}
	if (isLeft == true)
	{
		game_time++;
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
		if (Map_Hit(int(player_chara[0].x - map_error), int(player_chara[0].y)) !=1 && Map_Hit(int(player_chara[3].x - map_error), int(player_chara[3].y - 20)) !=1 &&Map_Hit(int(player_chara[0].x - map_error), int(player_chara[0].y + 55)) != 1)
		{
			for (int i = 0; i < 4; i++)
			{
				player_chara[i].x -= 5; //PlayerのSpeed
				
				if (game_time % 4 == 0)
				{
					player_chara[i].tu += 0.125f;
				}
			}
		}
		if (player_chara[1].tu == 0.75f)
		{
			player_chara[0].tu = 0.125f;
			player_chara[1].tu = 0.0f;
			player_chara[2].tu = 0.0f;
			player_chara[3].tu = 0.125f;
		}
	}
}
/**
*メッセージ処理
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wp, lp);
}
HRESULT InitDinput(HWND hWnd)
{
	HRESULT hr;
	//directinputオブジェクトの作成
	if (FAILED(hr = DirectInput8Create(GetModuleHandle(NULL),
		DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDinput, NULL)))
	{
		return hr;
	}
	//directinputデバイスオブジェクトの作成
	if (FAILED(hr = pDinput->CreateDevice(GUID_SysKeyboard,
		&pKeyDevice, NULL)))
	{
		return hr;
	}

	//デバイスをキーボードに設定
	if (FAILED(hr = pKeyDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return hr;
	}
	//協調レベルの設定
	if (FAILED(hr = pKeyDevice->SetCooperativeLevel(
		hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
	{
		return hr;
	}
	pKeyDevice->Acquire();
	return S_OK;
}
/**
*オブジェクトの開放
*/
void FreeDx()
{
	for (int i = 0; i <= TEXMAX; i++)
	{
		SAFE_RELEASE(g_pTexture[i]);
	}
	SAFE_RELEASE(g_pD3Device);
	SAFE_RELEASE(g_pDirect3D);
	SAFE_RELEASE(pDinput);
	if (pKeyDevice)
	{
		pKeyDevice->Unacquire();
	}
	SAFE_RELEASE(pKeyDevice);
	SAFE_RELEASE(MainFont);
}
/**
*メインルーチン
*/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	WNDCLASS Wndclass;
	HWND hWnd;

	//Windows情報の設定
	Wndclass.style = CS_HREDRAW | CS_VREDRAW;
	Wndclass.lpfnWndProc = WndProc;
	Wndclass.cbClsExtra = Wndclass.cbWndExtra = 0;
	Wndclass.hInstance = hInstance;
	Wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	Wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	Wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	Wndclass.lpszMenuName = NULL;
	Wndclass.lpszClassName = TEXT("AAAA");	//クラス名
											//Windowの登録
	RegisterClass(&Wndclass);
	//Windowの生成
	hWnd = CreateWindow(
		TEXT("AAAA"),								//ウィンドウのクラス名
		TEXT("スモークシープ"), 							//ウィンドウのタイトル
		WS_VISIBLE | WS_OVERLAPPEDWINDOW,	//ウィンドウスタイル
		CW_USEDEFAULT,						// ウィンドウの横方向の位置x
		CW_USEDEFAULT,						// ウィンドウの縦方向の位置y
		DISPLAY_WIDTH,							// Width（幅）
		DISPLAY_HIGHT,							// Height（高さ）
		NULL,
		NULL,
		hInstance,							// アプリケーションインスタンスのハンドル
		NULL
	);
	if (!hWnd) return 0;

	//DirectX オブジェクトの生成
	g_pDirect3D = Direct3DCreate9(
		D3D_SDK_VERSION);

	//directinputの初期化関数を呼ぶ
	if (FAILED(InitDinput(hWnd)))
	{
		return 0;
	}

	//Display Mode の設定
	g_pDirect3D->GetAdapterDisplayMode(
		D3DADAPTER_DEFAULT,
		&g_D3DdisplayMode);

	ZeroMemory(&g_D3dPresentParameters,
		sizeof(D3DPRESENT_PARAMETERS));
	g_D3dPresentParameters.BackBufferFormat = g_D3DdisplayMode.Format;
	g_D3dPresentParameters.BackBufferCount = 1;
	g_D3dPresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	g_D3dPresentParameters.Windowed = TRUE;

	//デバイスを作る
	g_pDirect3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&g_D3dPresentParameters, &g_pD3Device);

	//描画設定
	g_pD3Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pD3Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);  //SRCの設定
	g_pD3Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	g_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	//頂点に入れるデータを設定
	g_pD3Device->SetFVF(D3DFVF_CUSTOMVERTEX);
	D3DXCreateTextureFromFile(
		g_pD3Device,
		"text/M_01_01.png",
		&g_pTexture[M_01_01_TEX]);
	D3DXCreateTextureFromFile(
		g_pD3Device,
		"text/C_01_01.png",
		&g_pTexture[C_01_01_TEX]);
	D3DXCreateTextureFromFile(
		g_pD3Device,
		"text/fire.png",
		&g_pTexture[Fire_TEX]);
	D3DXCreateTextureFromFile(
		g_pD3Device,
		"text/wataame.png",
		&g_pTexture[Wataame_TEX]);
	//フォントオブジェクトの作成
	D3DXCreateFont(
		g_pD3Device,				// Direct3Dデバイス
		40,						// 高さ
		25,							// 幅
		FW_BLACK,					// フォントの太さ 普通
		NULL,						// 下線
		FALSE,						// 斜体
		DEFAULT_CHARSET,			// 文字セット
		OUT_DEFAULT_PRECIS,			// 出力制度は普通
		DEFAULT_QUALITY,			// 文字品質を重視
		FIXED_PITCH | FF_SCRIPT,	// ピッチとファミリ
		TEXT("venus rising"),		// フォント名
		&MainFont);
	DWORD SyncOld = timeGetTime();	//	システム時間を取得
	DWORD SyncNow;
	timeBeginPeriod(1);
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		Sleep(1);
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			SyncNow = timeGetTime();
			if (SyncNow - SyncOld >= 1000 / 60) //	1秒間に60回この中に入るはず
			{
				Render();
					MainKeyControl();
					if (jflag == false) {
						Gravity();
					}
					jump();
				scroll();
					MainControl();
					bug();
					move();
					SyncOld = SyncNow;
			}
		}
	}
	timeEndPeriod(1);

	FreeDx();
	return (int)msg.wParam;
}







