#pragma once


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
	TEXMAX,

};

struct center
{
	float x, y, scale;
};

enum Scene
{


};

extern CUSTOMVERTEX map_tip[];




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


void Render();
void mapRender();
void MainKeyControl();
void MainControl();
void Gravity();
void jump();