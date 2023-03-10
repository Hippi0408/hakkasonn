//==================================================================================================
//
//Domino.cpp
//Author:ûüRç
//
//==================================================================================================

#include "main.h"
#include "domino.h"
#include <stdlib.h>
#include "manager.h"
#include "game.h"
#include "input.h"

//}Nè`
#define DOMINO_TEX				""										//eNX`t@C¼
#define DOMINO_HEIGHT			(100)									//³
#define DOMINO_WIDTH			(20)									//
#define ROLL_SPEED				(-0.16f)									//ñ]Xs[h
#define ROLL_LIMIT				(D3DX_PI * 0.35f)						//|ê«épx

//O[oÏé¾
LPDIRECT3DTEXTURE9 g_apTextureDomino[DOMINOTYPE_MAX] = {};				//eNX`ÖÌ|C^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffDomino = NULL;						//¸_obt@ÖÌ|C^
Domino g_aDomino[MAX_DOMINO];											//\¢Ì
int g_nDominoNum;													//GÌ

//vg^Cvé¾
void UpdateDominoPos(Domino *pDomino);
void UpdateDominoPolygon(Domino *pDomino, int nCntDomino);
void ManageStateDomino(Domino *pDomino);

//==================================================================================================
//ú»
//==================================================================================================
void InitDomino(void)
{
	//Ïé¾
	int nCntDomino;

	//Ïú»
	g_nDominoNum = 0;

	//foCXæ¾
	CManager *pManager = GetManager();

	LPDIRECT3DDEVICE9 pDevice = nullptr;

	pDevice = pManager->GetDeviceManager();

	//eNX`ÇÝÝ
	for (int nCntTex = 0;nCntTex < DOMINOTYPE_MAX;nCntTex++)
	{
		D3DXCreateTextureFromFile(pDevice,
			DOMINO_TEX,
			&g_apTextureDomino[nCntTex]);
	}

	//¸_obt@Ì¶¬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_DOMINO,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffDomino,
		NULL);

	//¸_îñÌ|C^
	VERTEX_2D *pVtx;

	//¸_obt@ðbNµA¸_îñÖÌ|C^ðæ¾
	g_pVtxBuffDomino->Lock(0, 0, (void**)&pVtx, 0);

	//îñæ¾
	Domino *pDomino = GetDomino();

	for (nCntDomino = 0; nCntDomino < MAX_DOMINO; nCntDomino++, pDomino++)
	{//SÄÌú»

	    //îñÌÝè
		pDomino->pos = { 0.0f ,0.0f,0.0f };
		pDomino->rot = { 0.0f ,0.0f,0.0f };
		pDomino->posWorld = { 0.0f ,0.0f,0.0f };
		pDomino->col = D3DXCOLOR{ 1.0f,1.0f,1.0f,1.0f };
		pDomino->state = DOMINOSTATE_NORMAL;
		pDomino->fAngle = 0;
		pDomino->fLength = 0;
		pDomino->bUse = false;

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
		pVtx[0].col = pDomino->col;
		pVtx[1].col = pDomino->col;
		pVtx[2].col = pDomino->col;
		pVtx[3].col = pDomino->col;

		//eNX`ÀW
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//¸_f[^Ì|C^ð4Âªißé
		pVtx += 4;
	}

	//¸_obt@ðAbN
	g_pVtxBuffDomino->Unlock();
}

//==================================================================================================
//I¹
//==================================================================================================
void UninitDomino(void)
{
	for (int nCnt = 0; nCnt < DOMINOTYPE_MAX; nCnt++)
	{
		if (g_apTextureDomino[nCnt] != NULL)
		{//eNX`ÖÌ|C^jü
			g_apTextureDomino[nCnt]->Release();
			g_apTextureDomino[nCnt] = NULL;
		}
	}

	if (g_pVtxBuffDomino != NULL)
	{//¸_obt@ÖÌ|C^jü
		g_pVtxBuffDomino->Release();
		g_pVtxBuffDomino = NULL;
	}
}

//==================================================================================================
//XV
//==================================================================================================
void UpdateDomino(void)
{
	//|C^é¾
	Domino *pDomino = GetDomino();

	//CvbgÌ|C^ðé¾
	CInput *pInput = CInput::GetKey();

	if (pDomino->state == DOMINOSTATE_NORMAL)
	{//ÅÌh~mª|êé
		pDomino->state = DOMINOSTATE_DOWN;
	}

	for (int nCntDomino = 0; nCntDomino < MAX_DOMINO; nCntDomino++, pDomino++)
	{//SÄð`FbN·é
		if (pDomino->bUse)
		{//gpµÄ¢éóÔÈç

			//ÊuXV
			UpdateDominoPos(pDomino);

			//|SXV
			UpdateDominoPolygon(pDomino,nCntDomino);

			if (GetGameState() == GAMESTATE_DOWN)
			{
				//óÔXV
				ManageStateDomino(pDomino);
			}
		}
	}
}

//==================================================================================================
//ÊuXV
//==================================================================================================
void UpdateDominoPos(Domino *pDomino)
{
	//ÎÊuÝè
	pDomino->pos = *GetPosWorld() + pDomino->posWorld;
}

//==================================================================================================
//|SXV
//==================================================================================================
void UpdateDominoPolygon(Domino *pDomino, int nCntDomino)
{
	//¸_îñÌ|C^
	VERTEX_2D *pVtx;

	//¸_obt@ðbNµA¸_îñÖÌ|C^ðæ¾
	g_pVtxBuffDomino->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4 * nCntDomino;

	//¸_ÀWÌÝè
	pVtx[0].pos = D3DXVECTOR3
	(
		pDomino->pos.x + sinf(pDomino->rot.z - D3DX_PI + pDomino->fAngle) * pDomino->fLength, 
		pDomino->pos.y + cosf(pDomino->rot.z - D3DX_PI + pDomino->fAngle) * pDomino->fLength,
		0.0f
	);

	pVtx[1].pos = D3DXVECTOR3
	(
		pDomino->pos.x + sinf(pDomino->rot.z + D3DX_PI - pDomino->fAngle) * pDomino->fLength,
		pDomino->pos.y + cosf(pDomino->rot.z + D3DX_PI - pDomino->fAngle) * pDomino->fLength,
		0.0f
	);

	pVtx[2].pos = D3DXVECTOR3
	(
		pDomino->pos.x + sinf(pDomino->rot.z - D3DX_PI * 0.5f) * DOMINO_WIDTH * 0.5f,
		pDomino->pos.y + cosf(pDomino->rot.z - D3DX_PI * 0.5f) * DOMINO_WIDTH * 0.5f,
		0.0f
	);

	pVtx[3].pos = D3DXVECTOR3
	(
		pDomino->pos.x + sinf(pDomino->rot.z + D3DX_PI * 0.5f) * DOMINO_WIDTH * 0.5f,
		pDomino->pos.y + cosf(pDomino->rot.z + D3DX_PI * 0.5f) * DOMINO_WIDTH * 0.5f,
		0.0f
	);

	//¸_obt@ðAbN
	g_pVtxBuffDomino->Unlock();
}

//==================================================================================================
//óÔÇ
//==================================================================================================
void ManageStateDomino(Domino *pDomino)
{
	switch (pDomino->state)
	{
	case DOMINOSTATE_NORMAL:
		break;
	case DOMINOSTATE_DOWN:

		pDomino->rot.z += ROLL_SPEED;

		if (pDomino->rot.z < -ROLL_LIMIT && pDomino[1].bUse)
		{
			pDomino->state = DOMINOSTATE_END;
			pDomino[1].state = DOMINOSTATE_DOWN;
		}
		else if (pDomino->rot.z < -D3DX_PI * 0.5f && pDomino[1].bUse == false)
		{
			pDomino->rot.z = -D3DX_PI * 0.5f;
			pDomino->state = DOMINOSTATE_END;
			SetGameState(GAMESTATE_END);
		}

		break;
	case DOMINOSTATE_END:
		break;
	}
}

//==================================================================================================
//Ýè
//==================================================================================================
void SetDomino(D3DXVECTOR3 pos)
{
	//îñæ¾
	Domino *pDomino = GetDomino();

	//¸_îñÌ|C^
	VERTEX_2D *pVtx;

	//¸_obt@ðbNµA¸_îñÖÌ|C^ðæ¾
	g_pVtxBuffDomino->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntDomino = 0; nCntDomino < MAX_DOMINO; nCntDomino++, pDomino++)
	{//SÄð`FbN·é
		if (pDomino->bUse == false)
		{
			//ÎpüÌpxÝè
			pDomino->fAngle = atan2f(DOMINO_WIDTH,DOMINO_HEIGHT);

			//ÎpüÌ·³Ýè
			pDomino->fLength = sqrtf((DOMINO_WIDTH * 0.5f) * (DOMINO_WIDTH * 0.5f) + (DOMINO_HEIGHT) * (DOMINO_HEIGHT)) * 0.5f;

			//øó¯æè
			pDomino->posWorld = pos;
			pDomino->pos = pos;

			//gpóÔÉ·é
			pDomino->bUse = true;

			//¸_ÀWÌÝè
			pVtx[0].pos = D3DXVECTOR3
			(
				pDomino->pos.x + sinf(pDomino->rot.z - D3DX_PI + pDomino->fAngle) * pDomino->fLength,
				pDomino->pos.y + cosf(pDomino->rot.z - D3DX_PI + pDomino->fAngle) * pDomino->fLength,
				0.0f
			);

			pVtx[1].pos = D3DXVECTOR3
			(
				pDomino->pos.x + sinf(pDomino->rot.z + D3DX_PI - pDomino->fAngle) * pDomino->fLength,
				pDomino->pos.y + cosf(pDomino->rot.z + D3DX_PI - pDomino->fAngle) * pDomino->fLength,
				0.0f
			);

			pVtx[2].pos = D3DXVECTOR3
			(
				pDomino->pos.x + sinf(pDomino->rot.z - D3DX_PI * 0.5f) * DOMINO_WIDTH * 0.5f,
				pDomino->pos.y + cosf(pDomino->rot.z - D3DX_PI * 0.5f) * DOMINO_WIDTH * 0.5f,
				0.0f
			);

			pVtx[3].pos = D3DXVECTOR3
			(
				pDomino->pos.x + sinf(pDomino->rot.z + D3DX_PI * 0.5f) * DOMINO_WIDTH * 0.5f,
				pDomino->pos.y + cosf(pDomino->rot.z + D3DX_PI * 0.5f) * DOMINO_WIDTH * 0.5f,
				0.0f
			);

			g_nDominoNum++;

			break;
		}

		pVtx += 4;
	}

	//¸_obt@ðAbN
	g_pVtxBuffDomino->Unlock();
}

//==================================================================================================
//`æ
//==================================================================================================
void DrawDomino(void)
{
	//foCXæ¾
	CManager *pManager = GetManager();

	LPDIRECT3DDEVICE9 pDevice = nullptr;

	pDevice = pManager->GetDeviceManager();

	//|C^é¾
	Domino *pDomino = GetDomino();

	//Ïé¾
	int nCntDomino;

	//¸_obt@ðf[^Xg[ÉÝè
	pDevice->SetStreamSource(0, g_pVtxBuffDomino, 0, sizeof(VERTEX_2D));

	//¸_tH[}bgÌÝè
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntDomino = 0; nCntDomino < MAX_DOMINO; nCntDomino++, pDomino++)
	{//SÄð`FbN·é
		if (pDomino->bUse == true)
		{//gpµÄ¢éóÔÈç

			//eNX`Ýè
			pDevice->SetTexture(0, g_apTextureDomino[0]);

			//|SÌ`æ
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntDomino * 4, 2);
		}
	}
}

//==================================================================================================
//|C^æ¾
//==================================================================================================
Domino *GetDomino(void)
{
	return &g_aDomino[0];
}

//==================================================================================================
//G
//==================================================================================================
int GetDominoNum(void)
{
	return g_nDominoNum;
}