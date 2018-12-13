#include"player.h"
#include"Enemy.h"
#include"Map.h"
#include"Main.h"
#include"render.h"
#include"main.h"
#include"Hit.h"

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

int Map_scroll = 0;
int Enemy_Number = 0;
int Map[MAP_HEIGHT][MAP_WIDTH];
bool SmokeTransNow = false;
bool isJump = false;//ジャンプキーが押されたか否か
bool jflag = false;//ジャンプ中か否か
bool Smoke = false;//煙状態か普通状態か
bool LRjudg[100];//仮：エネミーの左右動作情報
bool SmokeReturnNomal = false;



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
			if (Smoke == false)
			{
				SmokeTransNow = true;
			}
			//Smoke = true;
			jflag = false;
		}
		if (diks[DIK_A] & 0x80&& (diks[DIK_D] & 0x80)==false)
		{
			PlayerLeft();
		}
		else if (diks[DIK_D] & 0x80 && (diks[DIK_A] & 0x80) == false)
		{
			PlayerRight();
		}
		else if(Smoke)
		{
			SettingPlayer_tutv(tu_smokewait, tv_smokewait,smokewait);
			if (count % 4 == 0)
			{
				for (int i = 0; i < 4; i++)
				{
					{
						player_chara[i].tu += CHARA_WIDTH;
					}
				}
			}
			if (player_chara[0].tu == (Player_tu(tu_smokewait) +CHARA_WIDTH*6))
			{
				SettingPlayer_tu(tu_smokewait);
			}
		}
		else if (!Smoke)
		{
			PlayerWait(count);
			
		}
		
		
		if (diks[DIK_S] & 0x80)
		{
			PlayerDown();
		}
		if (diks[DIK_W] & 0x80 && count > 10&&!Smoke)
		{
			isJump = true;
			count = 0;
		}
		else {
			isJump = false;
		}
		if (diks[DIK_W] & 0x80 )
		{
			PlayerUp();
		}
		if (diks[DIK_SPACE] & 0x80)
		{
			Sheep.x_speed = 7;
		}
		else
		{
			Sheep.x_speed = 5;
		}
	}
}

void scroll() {
	//スクロール
	if (player_chara[1].x > 568 /*&& Map_scroll > -2880*/)
	{
		for (int i = 0; i < 4; i++)
		{
			map_tip[i].x -= Sheep.x_speed;
 			player_chara[i].x -= Sheep.x_speed;
			background[i].tu += 0.002f;
			for (int j = 0; j < Enemy_Number; j++) {
				enemy[j][i].x -= Sheep.x_speed;
			}
		}
		Map_scroll -= Sheep.x_speed;
	}
	else if (player_chara[0].x < 440 && Map_scroll < 0)
	{
		for (int i = 0; i < 4; i++)
		{
			map_tip[i].x += Sheep.x_speed;
			player_chara[i].x += Sheep.x_speed;
			background[i].tu -= 0.002f;

			for (int j = 0; j < Enemy_Number; j++) {
				enemy[j][i].x += Sheep.x_speed;
			}
		}
		Map_scroll += Sheep.x_speed;
	}
}




void Gravity(){
	//プレイヤーの重力判定
	if (jflag == false&& Smoke == false) {
		
			//下の当たり判定
			if (Down_Hit(player_chara, Soil, AND, Sheep.x_speed * 2,GRAVITY))
			{
				for (int i = 0; i < 4; i++)
				{
					player_chara[i].y += GRAVITY;
				}
			}
		
	}
	//エネミーの重力判定
	//右下・下・左下の当たり判定
	for (int j = 0; j < Enemy_Number; j++) {
		if (Down_Hit(enemy[j], Soil, AND, Sheep.x_speed * 2, GRAVITY))
		{
			for (int i = 0; i < 4; i++)
			{
				enemy[j][i].y += GRAVITY;
			}
		}
	}
}

//
//
//めり込みバグの修正
void bug() {

	//プレイヤーのバグ修正
	while (!Down_Hit(player_chara, Soil,AND,Sheep.x_speed * 2,GRAVITY-1))
	{
		for (int i = 0; i < 4; i++) { player_chara[i].y -= 0.1f; }
	}
	if (Smoke)
	{
		while (!Left_Hit(player_chara, Soil,OR))
		{
			for (int i = 0; i < 4; i++) { player_chara[i].x += 0.1f; }
		}
		while (!Right_Hit(player_chara, Soil,OR))
		{
			for (int i = 0; i < 4; i++) { player_chara[i].x -= 0.1f; }
		}
	}
	else
	{
		while (!Left_Hit(player_chara, Ive,OR)||
			   !Left_Hit(player_chara, Soil,OR))
		{
			for (int i = 0; i < 4; i++) { player_chara[i].x += 0.1f; }
		}
		while (!Right_Hit(player_chara, Ive,OR)||
	   		   !Right_Hit(player_chara, Soil,OR))
		{
			for (int i = 0; i < 4; i++) { player_chara[i].x -= 0.1f; }
		}
	}

	
	//エネミーのバグ修正
	for (int j = 0; j < Enemy_Number; j++)
	{
		while (!Down_Hit(enemy[j], Soil, OR, wolf[j].move_x * 2, GRAVITY - 1))
		{
			for (int i = 0; i < 4; i++) { enemy[j][i].y -= 0.1f; }
		}
		while (!Left_Hit(enemy[j], Ive, OR) ||
			!Left_Hit(enemy[j], Soil, OR))
		{
			for (int i = 0; i < 4; i++) {enemy[j][i].x += 0.1f; }
		}
		while (!Right_Hit(enemy[j], Ive, OR) ||
			!Right_Hit(enemy[j], Soil, OR))
		{
			for (int i = 0; i < 4; i++) { enemy[j][i].x -= 0.1f; }
		}
	}
}

void smoketime() {
	if (Smoke == true)
	{
		static int smokecount = 0;
		smokecount++;
		if (smokecount > 60*Sheep.smoketime) {
			smokecount = 0;
			SmokeTransNow = true;
			SmokeReturnNomal = true;
		}
	}	
}

void Returnnomal() {
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

			if (player_chara[0].y < p_y2[0])
			{
				if (player_chara[0].tu > player_chara[1].tu) {
					SettingPlayer_tu(tu_jump);
					DrawTurn(player_chara);
				}
				else {
					SettingPlayer_tu(tu_jump);
				}

				for (int i = 0; i < 4; i++)
				{
					player_chara[i].tu += CHARA_WIDTH;
				}

			}

			if (player_chara[0].y > p_y2[0])
			{
				if (player_chara[0].tu > player_chara[1].tu) {
					SettingPlayer_tu(tu_jump);
					DrawTurn(player_chara);
				}
				else {
					SettingPlayer_tu(tu_jump);
				}
			
				for (int i = 0; i < 4; i++)
				{
					player_chara[i].tu += CHARA_WIDTH*2;
				}

			}

			if (!Up_Hit(player_chara,Soil,OR))
			{
				for (int i = 0; i < 4; i++)
				{
					player_chara[i].y = p_y2[i]+1;
				}
			}
			if (!Down_Hit(player_chara, Soil, AND, Sheep.x_speed,GRAVITY))
			{
					jflag = false;
			}
			
		}
		if(Down_Hit(player_chara, Empty, OR, Sheep.x_speed, GRAVITY))
		{ 
			if (isJump == true && jflag == false) {
				jflag = true;
				SettingPlayer_tutv(tu_jump, tv_jump, jumping);
				for (int i = 0; i < 4; i++)
				{
					p_y2[i] = player_chara[i].y;
					player_chara[i].y = player_chara[i].y - 20;
				}
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
				if (SmokeTransNow)
				{
					smokehensintime();
					Returnnomal();
				}
				else {
					MainKeyControl();
					
					jump();
					scroll();
					MainControl();
					bug();
					EnemyMainControl();
					smoketime();
					
					Gravity();
			
				}
				Render();
					SyncOld = SyncNow;

			}
		}
	}
	timeEndPeriod(1);
	FreeDx();
	return (int)msg.wParam;
}







