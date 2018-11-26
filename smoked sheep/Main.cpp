#include"player.h"
#include"Enemy.h"
#include"map.h"
#include"Main.h"
#include"render.h"


//Directx�֌W----------------------------
LPDIRECT3DTEXTURE9	  g_pTexture[TEXMAX];	//	�摜�̏������Ă����ׂ̃|�C���^�z��
IDirect3DDevice9*	  g_pD3Device;		//	Direct3D�̃f�o�C�X
D3DPRESENT_PARAMETERS g_D3dPresentParameters;		//	�p�����[�^
D3DDISPLAYMODE		  g_D3DdisplayMode;
IDirect3D9*			  g_pDirect3D;		//	Direct3D�̃C���^�[�t�F�C�X
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
bool a[100];//���F�G�l�~�[�̍��E������



void MainKeyControl()
{
	static int count = 0;
	count++;
	//�L�[�{�[�h�ŉ�����Ă���L�[�𒲂ׁA�Ή���������Ɉړ�������
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
	//�X�N���[��
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
				enemy[j][i].x += 2;//enemy��Speed
			}
		}

		if (a[j] == false) {

			for (int i = 0; i < 4; i++)
			{
				enemy[j][i].x -= 2;//enemy��Speed
			}
		}
	}

}









void Gravity(){
	if (smoke == false)
	{
		//�E���̓����蔻��
		if (Map_Hit(int(player_chara[2].x - map_error), int(player_chara[2].y)) != 1)
		{
			//���̓����蔻��
			if (Map_Hit(int(player_chara[2].x - 64 - map_error), int(player_chara[2].y)) != 1)
			{
				//�����̓����蔻��
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

	//�E���̓����蔻��
	for (int j = 0; j < number; j++) {
		if (Map_Hit(int(enemy[j][2].x - map_error), int(enemy[j][2].y)) != 1)
		{
			//���̓����蔻��
			if (Map_Hit(int(enemy[j][2].x - 64 - map_error), int(enemy[j][2].y)) != 1)
			{
				//�����̓����蔻��
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
//�߂荞�݃o�O�̏C��
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


//�W�����v����
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
		//�E��ƉE���̂����蔻��
		if (Map_Hit(int(player_chara[2].x - map_error), int(player_chara[2].y-6 )) != 1 && Map_Hit(int(player_chara[1].x - map_error), int(player_chara[1].y)) !=1&& Map_Hit(int(player_chara[1].x - map_error), int(player_chara[1].y+55)) != 1)
		{
			if (smoke == false)
			{
				if (Map_Hit(int(player_chara[2].x - map_error), int(player_chara[2].y - 6)) != 5 && Map_Hit(int(player_chara[5].x - map_error), int(player_chara[5].y)) != 5 && Map_Hit(int(player_chara[5].x - map_error), int(player_chara[5].y + 55)) != 5)
				{

					for (int i = 0; i < 4; i++)
					{
						player_chara[i].x += Sheep.x_speed;//Player��Speed


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
					player_chara[i].x += Sheep.x_speed;//Player��Speed


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
						player_chara[i].x -= Sheep.x_speed; //Player��Speed

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
					player_chara[i].x -= Sheep.x_speed; //Player��Speed

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
*���b�Z�[�W����
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
	//directinput�I�u�W�F�N�g�̍쐬
	if (FAILED(hr = DirectInput8Create(GetModuleHandle(NULL),
		DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDinput, NULL)))
	{
		return hr;
	}
	//directinput�f�o�C�X�I�u�W�F�N�g�̍쐬
	if (FAILED(hr = pDinput->CreateDevice(GUID_SysKeyboard,
		&pKeyDevice, NULL)))
	{
		return hr;
	}

	//�f�o�C�X���L�[�{�[�h�ɐݒ�
	if (FAILED(hr = pKeyDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return hr;
	}
	//�������x���̐ݒ�
	if (FAILED(hr = pKeyDevice->SetCooperativeLevel(
		hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
	{
		return hr;
	}
	pKeyDevice->Acquire();
	return S_OK;
}
/**
*�I�u�W�F�N�g�̊J��
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
*���C�����[�`��
*/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	WNDCLASS Wndclass;
	HWND hWnd;

	//Windows���̐ݒ�
	Wndclass.style = CS_HREDRAW | CS_VREDRAW;
	Wndclass.lpfnWndProc = WndProc;
	Wndclass.cbClsExtra = Wndclass.cbWndExtra = 0;
	Wndclass.hInstance = hInstance;
	Wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	Wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	Wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	Wndclass.lpszMenuName = NULL;
	Wndclass.lpszClassName = TEXT("AAAA");	//�N���X��
											//Window�̓o�^
	RegisterClass(&Wndclass);
	//Window�̐���
	hWnd = CreateWindow(
		TEXT("AAAA"),								//�E�B���h�E�̃N���X��
		TEXT("�X���[�N�V�[�v"), 							//�E�B���h�E�̃^�C�g��
		WS_VISIBLE | WS_OVERLAPPEDWINDOW,	//�E�B���h�E�X�^�C��
		CW_USEDEFAULT,						// �E�B���h�E�̉������̈ʒux
		CW_USEDEFAULT,						// �E�B���h�E�̏c�����̈ʒuy
		DISPLAY_WIDTH,							// Width�i���j
		DISPLAY_HIGHT,							// Height�i�����j
		NULL,
		NULL,
		hInstance,							// �A�v���P�[�V�����C���X�^���X�̃n���h��
		NULL
	);
	if (!hWnd) return 0;

	//DirectX �I�u�W�F�N�g�̐���
	g_pDirect3D = Direct3DCreate9(
		D3D_SDK_VERSION);

	//directinput�̏������֐����Ă�
	if (FAILED(InitDinput(hWnd)))
	{
		return 0;
	}

	//Display Mode �̐ݒ�
	g_pDirect3D->GetAdapterDisplayMode(
		D3DADAPTER_DEFAULT,
		&g_D3DdisplayMode);

	ZeroMemory(&g_D3dPresentParameters,
		sizeof(D3DPRESENT_PARAMETERS));
	g_D3dPresentParameters.BackBufferFormat = g_D3DdisplayMode.Format;
	g_D3dPresentParameters.BackBufferCount = 1;
	g_D3dPresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	g_D3dPresentParameters.Windowed = TRUE;

	//�f�o�C�X�����
	g_pDirect3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&g_D3dPresentParameters, &g_pD3Device);

	//�`��ݒ�
	g_pD3Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pD3Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);  //SRC�̐ݒ�
	g_pD3Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	g_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	//���_�ɓ����f�[�^��ݒ�
	g_pD3Device->SetFVF(D3DFVF_CUSTOMVERTEX);

	TEX_Init();


	//�t�H���g�I�u�W�F�N�g�̍쐬
	D3DXCreateFont(
		g_pD3Device,				// Direct3D�f�o�C�X
		40,						// ����
		25,							// ��
		FW_BLACK,					// �t�H���g�̑��� ����
		NULL,						// ����
		FALSE,						// �Α�
		DEFAULT_CHARSET,			// �����Z�b�g
		OUT_DEFAULT_PRECIS,			// �o�͐��x�͕���
		DEFAULT_QUALITY,			// �����i�����d��
		FIXED_PITCH | FF_SCRIPT,	// �s�b�`�ƃt�@�~��
		TEXT("venus rising"),		// �t�H���g��
		&MainFont);
	DWORD SyncOld = timeGetTime();	//	�V�X�e�����Ԃ��擾
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
			if (SyncNow - SyncOld >= 1000 / 60) //	1�b�Ԃ�60�񂱂̒��ɓ���͂�
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







