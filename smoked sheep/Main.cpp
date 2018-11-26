#include"player.h"
#include"Enemy.h"
#include"map.h"
#include"Main.h"
#include"render.h"


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


CUSTOMVERTEX background[4]
{
{ 0.f  ,0.f  ,1.f ,1.f, 0xFFFFFFFF,0.f  ,0.f },
{ WIDTH,0.f  ,1.f ,1.f, 0xFFFFFFFF,1.f,0.f },
{ WIDTH,HIGHT,1.f ,1.f, 0xFFFFFFFF,1.f,1.f },
{ 0.f  ,HIGHT,1.f ,1.f, 0xFFFFFFFF,0.f  ,1.f },
};





int map_error = 0;
int number = 0;
int map[MAP_HEIGHT][MAP_WIDTH];
bool isRight = false;
bool isLeft = false;
bool jflag = false;
unsigned int game_time = 0;
bool key_space = false;
bool smoke = false;
bool smokeUPmove = false;
bool smokeDOWNmove = false;
bool a[100];//仮：エネミーの左右動作情報



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
			smoke = true;
			jflag = false;

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
		if (diks[DIK_S] & 0x80&&smoke==true)
		{
		smokeDOWNmove= true;
		}
		else
		{
			smokeDOWNmove = false;
		}
		
		if (diks[DIK_W] & 0x80 && count > 10&&smoke==false)
		{
			
			key_space = true;
			count = 0;
		}
		else {
			key_space = false;
		}

		if (diks[DIK_W] & 0x80 && smoke==true)
		{
			smokeUPmove=true;
		}
		else {
			smokeUPmove = false;
		}
		if (diks[DIK_SPACE] & 0x80)
		{
			Sheep.x_speed = 10;
		}
	}
}




void scroll() {
	//スクロール
	if (player_chara[1].x > 568 /*&& map_error > -2880*/)
	{
		for (int i = 0; i < 4; i++)
		{
			map_tip[i].x -= Sheep.x_speed;
 			player_chara[i].x -= Sheep.x_speed;
			background[i].tu += 0.002f;
			for (int j = 0; j < number; j++) {
				enemy[j][i].x -= Sheep.x_speed;
			}
		}
		map_error -= Sheep.x_speed;

	}
	else if (player_chara[0].x < 440 && map_error < 0)
	{
		for (int i = 0; i < 4; i++)
		{
			map_tip[i].x += Sheep.x_speed;
			player_chara[i].x += Sheep.x_speed;
			background[i].tu -= 0.002f;

			for (int j = 0; j < number; j++) {
				enemy[j][i].x += Sheep.x_speed;
			}
		}
		map_error += Sheep.x_speed;
	}
}



void enemymove()
{
	for (int i = 0; i < number; i++)
	{
		if (Map_Hit(int(enemy[i][2].x - map_error), int(enemy[i][2].y-GRAVITY)) == 1 || Map_Hit(int(enemy[i][1].x - map_error), int(enemy[i][1].y + GRAVITY)) == 1)
		{
			a[i] = false;
		}

		if (Map_Hit(int(enemy[i][2].x - map_error), int(enemy[i][2].y - GRAVITY)) == 5 || Map_Hit(int(enemy[i][1].x - map_error), int(enemy[i][1].y + GRAVITY)) == 5)
		{
			a[i] = false; 
		}

		if (Map_Hit(int(enemy[i][0].x - map_error), int(enemy[i][0].y + GRAVITY)) == 1 || Map_Hit(int(enemy[i][3].x - map_error), int(enemy[i][3].y - GRAVITY)) == 1)
		{
			a[i] = true;
		}

		if (Map_Hit(int(enemy[i][0].x - map_error), int(enemy[i][0].y+ GRAVITY)) == 5 || Map_Hit(int(enemy[i][3].x - map_error), int(enemy[i][3].y - GRAVITY)) == 5)
		{
			a[i] = true;
		}
	}


}

void move() {
	enemymove();
	for (int j = 0; j < number; j++)
	{
		

		if (a[j] == true) {
			for (int i = 0; i < 4; i++)
			{
				enemy[j][i].x += 2;//enemyのSpeed
			}
		}

		if (a[j] == false) {

			for (int i = 0; i < 4; i++)
			{
				enemy[j][i].x -= 2;//enemyのSpeed
			}
		}
	}

}









void Gravity(){
	if (smoke == false)
	{
		//右下の当たり判定
		if (Map_Hit(int(player_chara[2].x - map_error), int(player_chara[2].y)) != 1)
		{
			//下の当たり判定
			if (Map_Hit(int(player_chara[2].x - 64 - map_error), int(player_chara[2].y)) != 1)
			{
				//左下の当たり判定
				if (Map_Hit(int(player_chara[3].x - map_error), int(player_chara[3].y)) != 1)
				{

					for (int i = 0; i < 4; i++)
					{
						player_chara[i].y += GRAVITY;
					}
				}
			}
		}
	
	}

	//右下の当たり判定
	for (int j = 0; j < number; j++) {
		if (Map_Hit(int(enemy[j][2].x - map_error), int(enemy[j][2].y)) != 1)
		{
			//下の当たり判定
			if (Map_Hit(int(enemy[j][2].x - 64 - map_error), int(enemy[j][2].y)) != 1)
			{
				//左下の当たり判定
				if (Map_Hit(int(enemy[j][3].x - map_error), int(enemy[j][3].y)) != 1)
				{

					for (int i = 0; i < 4; i++)
					{
						enemy[j][i].y += GRAVITY;
					}
				}
			}
		}
	}
}

//
//
//めり込みバグの修正
void bug() {

	while (Map_Hit(int(player_chara[3].x + 1 + Sheep.x_speed - map_error), int(player_chara[3].y - 1)) == 1 || Map_Hit(int(player_chara[2].x - 1 - Sheep.x_speed - map_error), int(player_chara[2].y - 1)) == 1 || Map_Hit(int(player_chara[2].x - 64 - map_error), int(player_chara[2].y - 1)) == 1)
	{
		for (int i = 0; i < 4; i++) {
			player_chara[i].y -= 0.1f;
		}
	}
	while (Map_Hit(int(player_chara[3].x + 1 - map_error), int(player_chara[3].y - Sheep.scale)) == 1)
	{
		for (int i = 0; i < 4; i++) {
			player_chara[i].x += 0.1f;
		}
	}
	while (Map_Hit(int(player_chara[2].x - 1 - map_error), int(player_chara[2].y - Sheep.scale)) == 1)
	{
		for (int i = 0; i < 4; i++) {
			player_chara[i].x -= 0.1f;
		}
	}
	for (int j = 0; j < number; j++)
	{
		while (Map_Hit(int(enemy[j][3].x + 1 + 2- map_error), int(enemy[j][3].y -1)) == 1 || Map_Hit(int(enemy[j][2].x - 1 -2 - map_error), int(enemy[j][2].y -1)) == 1)
		{
			for (int i = 0; i < 4; i++) {
				enemy[j][i].y -= 0.1f;
			}
		}
	}





}

void smoketime() {
	if (smoke == true)
	{
	
		static int smokecount = 0;
		smokecount++;

		if (smokecount > 60*Sheep.smoketime) {
			smokecount = 0;
			smoke = false;
		}
	}
	
		
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
			if (Map_Hit(int(player_chara[1].x -1-Sheep.x_speed - map_error), int(player_chara[1].y)) == 1 || Map_Hit(int(player_chara[0].x + 1 + Sheep.x_speed - map_error), int(player_chara[0].y)) == 1 || Map_Hit(int(player_chara[1].x - 64 - map_error), int(player_chara[1].y)) == 1)
			{
				for (int i = 0; i < 4; i++)
				{
					player_chara[i].y += 18;
				}
			}
			if (Map_Hit(int(player_chara[2].x - 1 - Sheep.x_speed -map_error), int(player_chara[2].y))==1||  Map_Hit(int(player_chara[3].x + 1 + Sheep.x_speed -map_error), int(player_chara[3].y)) == 1|| Map_Hit(int(player_chara[2].x - 64 - map_error), int(player_chara[2].y)) == 1)
			
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
	if (smokeUPmove == true)
	{
		for (int i = 0; i < 4; i++)
		{
			player_chara[i].y -= 3;
		}
	}
	if (smokeDOWNmove == true)
	{
		for (int i = 0; i < 4; i++)
		{
			player_chara[i].y += 3;
		}
	}





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
			if (smoke == false)
			{
				if (Map_Hit(int(player_chara[2].x - map_error), int(player_chara[2].y - 6)) != 5 && Map_Hit(int(player_chara[5].x - map_error), int(player_chara[5].y)) != 5 && Map_Hit(int(player_chara[5].x - map_error), int(player_chara[5].y + 55)) != 5)
				{

					for (int i = 0; i < 4; i++)
					{
						player_chara[i].x += Sheep.x_speed;//PlayerのSpeed


						if (game_time % 4 == 0)
						{
							player_chara[i].tu += 0.125f;
						}
					}
				}
			}
			else
			{
				for (int i = 0; i < 4; i++)
				{
					player_chara[i].x += Sheep.x_speed;//PlayerのSpeed


					if (game_time % 4 == 0)
					{
						player_chara[i].tu += 0.125f;
					}
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
		if (Map_Hit(int(player_chara[0].x - map_error), int(player_chara[0].y)) != 1 && Map_Hit(int(player_chara[3].x - map_error), int(player_chara[3].y - 20)) != 1 && Map_Hit(int(player_chara[0].x - map_error), int(player_chara[0].y + 55)) != 1)
		{
			if (smoke == false) {
				if (Map_Hit(int(player_chara[0].x - map_error), int(player_chara[0].y)) != 5 && Map_Hit(int(player_chara[3].x - map_error), int(player_chara[3].y - 20)) != 5 && Map_Hit(int(player_chara[0].x - map_error), int(player_chara[0].y + 55)) != 5)
				{

					for (int i = 0; i < 4; i++)
					{
						player_chara[i].x -= Sheep.x_speed; //PlayerのSpeed

						if (game_time % 4 == 0)
						{
							player_chara[i].tu += 0.125f;
						}
					}
				}
			}
			else
			{
				for (int i = 0; i < 4; i++)
				{
					player_chara[i].x -= Sheep.x_speed; //PlayerのSpeed

					if (game_time % 4 == 0)
					{
						player_chara[i].tu += 0.125f;
					}
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

	TEX_Init();


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
					smoketime();
					SyncOld = SyncNow;
			}
		}
	}
	timeEndPeriod(1);

	FreeDx();
	return (int)msg.wParam;
}







