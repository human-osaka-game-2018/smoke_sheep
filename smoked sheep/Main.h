#pragma once

#define MAP_HEIGHT 12
#define MAP_WIDTH 300
#define GRAVITY 5
#define IMAGESIZE 2048.f
#define IMAGESIZE2 2048.f
#define AND true
#define OR false
#define RIGHT true
#define LEFT false
#define CHARA_WIDTH 135.f/2048.f
#define CHARA_HEIGHT 125.f/2048.f

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
enum Scene
{

aaa,
};
enum TEXTURE
{
	M_01_01_TEX,
	C_01_01_TEX,
	Fire_TEX,
	Wataame_TEX,
	Smoke_Smoke_TEX,
	iveblock_TEX,
	BACKGROUND_TEX,
	ENEMY_TEX,
	TEXMAX,
};


enum BlockNumber
{
	Empty=0,
	Soil,
	Grass,
	NightSoil,
	NightGrass,
	Ice,
	Snow,
	Ive,
	Deth,
	Goal,
	///////////////エネミー
	E_nomal=21,
	E_speed,
	E_strong,
	E_hide,
	E_kids,
	//////////////アイテム
	Cottoncandy=41,
	Fire,
	Snowcloud,
	/////////////ギミック
	Sitch=51,
	Needle,
	Icicles,
	Cloud,
	Breakflow,
	Breakflow2,
	Breakflow3,
	Wind_strong,
	Wind_weak,
	Pinata,
	/////////看板
	Signboard1=71,
	Signboard2,
	Signboard3,
	Signboard4,
	Signboard5,
	Signboard6,
	Signboard7,
	Signboard8,
	Signboard9,
	Signboard10,
	/////////背景オブジェクト
	Rubbit=201,
	Squirrel,
	grandmother,
	House1,
	House2,
	Arrowboard,
	Noteboard








};
extern CUSTOMVERTEX background[4];
extern LPDIRECT3DTEXTURE9	  g_pTexture[TEXMAX];	//	画像の情報を入れておく為のポインタ配列
extern IDirect3DDevice9*	  g_pD3Device;		//	Direct3Dのデバイス
extern D3DPRESENT_PARAMETERS g_D3dPresentParameters;		//	パラメータ
extern D3DDISPLAYMODE		  g_D3DdisplayMode;
extern IDirect3D9*			  g_pDirect3D;		//	Direct3Dのインターフェイス
extern LPDIRECTINPUT8 pDinput;
extern LPDIRECTINPUTDEVICE8 pKeyDevice;
extern HRESULT InitD3d(HWND);
extern HRESULT InitDinput(HWND);
extern LPD3DXFONT MainFont;



extern int Map_scroll ;
extern int Enemy_Number;
extern int Map[MAP_HEIGHT][MAP_WIDTH];
extern bool isjump;
extern bool jflag ;
extern bool SmokeTransNow;
extern bool Smoke;
extern bool LRjudg[100];
extern bool SmokeReturnNomal;

void Render();
void mapRender();
void MainKeyControl();
void MainControl();
void Gravity();
void jump();
