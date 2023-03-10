//==================================================================================================
//
//Hand.cpp
//Author:ûüRç
//
//==================================================================================================

#include "main.h"
#include "hand.h"
#include "manager.h"
#include "game.h"
#include "input.h"

//}Nè`
#define HAND_TEX				""									//eNX`t@C¼
#define HAND_HEIGHT			(100)									//³
#define HAND_WIDTH			(100)									//

//O[oÏé¾
LPDIRECT3DTEXTURE9 g_pTextureHand = NULL;							//eNX`ÖÌ|C^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHand = NULL;						//¸_obt@ÖÌ|C^
Hand g_hand;														//\¢Ì
int g_nHandNum;														//GÌ

//vg^Cvé¾
void UpdateHandPos(Hand *pHand);
void UpdateHandPolygon(Hand *pHand, int nCntHand);
void ManageStateHand(Hand *pHand);

//==================================================================================================
//ú»
//==================================================================================================
void InitHand(void)
{
	//Ïé¾
	int nCntHand;

	//Ïú»
	g_nHandNum = 0;

	//foCXæ¾
	CManager *pManager = GetManager();

	LPDIRECT3DDEVICE9 pDevice = nullptr;

	pDevice = pManager->GetDeviceManager();

	//eNX`ÇÝÝ
	D3DXCreateTextureFromFile(pDevice,
		HAND_TEX,
		&g_pTextureHand);

	//¸_obt@Ì¶¬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffHand,
		NULL);

	//¸_îñÌ|C^
	VERTEX_2D *pVtx;

	//¸_obt@ðbNµA¸_îñÖÌ|C^ðæ¾
	g_pVtxBuffHand->Lock(0, 0, (void**)&pVtx, 0);

	//îñæ¾
	Hand *pHand = GetHand();

	//îñÌÝè
	pHand->pos = { 0.0f ,0.0f,0.0f };
	pHand->posWorld = { 0.0f ,0.0f,0.0f };
	pHand->col = D3DXCOLOR{ 1.0f,1.0f,1.0f,1.0f };
	pHand->state = HANDSTATE_NORMAL;

	//¸_ÀWÌÝè
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0, 0, 0.0f);

	//rhwÌÝè
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//¸_J[ÌÝè
	pVtx[0].col = pHand->col;
	pVtx[1].col = pHand->col;
	pVtx[2].col = pHand->col;
	pVtx[3].col = pHand->col;

	//eNX`ÀW
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//¸_obt@ðAbN
	g_pVtxBuffHand->Unlock();
}

//==================================================================================================
//I¹
//==================================================================================================
void UninitHand(void)
{
	if (g_pTextureHand != NULL)
	{//eNX`ÖÌ|C^jü
		g_pTextureHand->Release();
		g_pTextureHand = NULL;
	}


	if (g_pVtxBuffHand != NULL)
	{//¸_obt@ÖÌ|C^jü
		g_pVtxBuffHand->Release();
		g_pVtxBuffHand = NULL;
	}
}

//==================================================================================================
//XV
//==================================================================================================
void UpdateHand(void)
{
}

//==================================================================================================
//ÊuXV
//==================================================================================================
void UpdateHandPos(Hand *pHand)
{
	//ÎÊuÝè
	pHand->pos = *GetPosWorld() + pHand->posWorld;
}

//==================================================================================================
//|SXV
//==================================================================================================
void UpdateHandPolygon(Hand *pHand, int nCntHand)
{
}

//==================================================================================================
//óÔÇ
//==================================================================================================
void ManageStateHand(Hand *pHand)
{
}

//==================================================================================================
//`æ
//==================================================================================================
void DrawHand(void)
{
}

//==================================================================================================
//|C^æ¾
//==================================================================================================
Hand *GetHand(void)
{
}