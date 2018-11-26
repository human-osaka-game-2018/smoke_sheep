#pragma once

#define MAP_HEIGHT 12
#define MAP_WIDTH 130
#define GRAVITY 5

#include <windows.h>
#include <mmsystem.h>
#include <d3dx9.h>
#include<math.h>
#include<dinput.h>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<iostream>

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define DISPLAY_WIDTH 1280
#define DISPLAY_HIGHT 720
#define SAFE_RELEASE(p) {if(p){(p)->Release(); (p)=NULL;}}
#define WIDTH 1280
#define HIGHT 720

struct CUSTOMVERTEX
{
	FLOAT	x, y, z, rhw;
	DWORD	color;
	FLOAT	tu, tv;
};

enum TEXTURE
{
	M_01_01_TEX,
	C_01_01_TEX,
	Fire_TEX,
	Wataame_TEX,
	SmokeS_Smoke_TEX,
	iveblock_TEX,
	BACKGROUND_TEX,
	TEXMAX,

};

struct center
{
	float x, y, scale;
};

enum Scene
{

aaa,
};

extern CUSTOMVERTEX map_tip[4];
extern CUSTOMVERTEX background[4];
extern LPDIRECT3DTEXTURE9	  g_pTexture[TEXMAX];	//	�摜�̏������Ă����ׂ̃|�C���^�z��
extern IDirect3DDevice9*	  g_pD3Device;		//	Direct3D�̃f�o�C�X
extern D3DPRESENT_PARAMETERS g_D3dPresentParameters;		//	�p�����[�^
extern D3DDISPLAYMODE		  g_D3DdisplayMode;
extern IDirect3D9*			  g_pDirect3D;		//	Direct3D�̃C���^�[�t�F�C�X
extern LPDIRECTINPUT8 pDinput;
extern LPDIRECTINPUTDEVICE8 pKeyDevice;
extern HRESULT InitD3d(HWND);
extern HRESULT InitDinput(HWND);
extern LPD3DXFONT MainFont;

extern int map_error ;
extern int number;
extern int map[MAP_HEIGHT][MAP_WIDTH];
extern bool isRight;
extern bool isLeft;
extern bool jflag ;
extern unsigned int game_time;
extern bool key_space;
extern bool smoke ;
extern bool smokeUPmove ;
extern bool smokeDOWNmove ;



void Render();
void mapRender();
void MainKeyControl();
void MainControl();
void Gravity();
void jump();