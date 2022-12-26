//=============================================================================
//
// game.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "manager.h"
#include "game.h"
#include "input.h"
#include "texture.h"
#include "ui.h"

//*****************************************************************************
//	マクロ定義
//*****************************************************************************
#define MAX_TIME (5)
#define TIMELIMIT (30)

//*****************************************************************************
// グローバル宣言
//*****************************************************************************
PUSHSTATE g_PushState;

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CGame::CGame()
{
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CGame::~CGame()
{
}

//*****************************************************************************
// 初期化
//*****************************************************************************
HRESULT CGame::Init()
{
	//各数値初期化
	g_PushState.NowTargetButton == TARGETBUTTON_NONE;
	g_PushState.nPushCount = 0;
	g_PushState.nPushLimitTime = 0;
	g_PushState.nTotalLimitTime = TIMELIMIT * 60;

	//乱数の種を取得
	DWORD time = timeGetTime();
	srand((unsigned int)time);

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CGame::Uninit()
{
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CGame::Update()
{
	//制限時間減少
	g_PushState.nPushLimitTime--;
	g_PushState.nTotalLimitTime--;
	if (g_PushState.nPushLimitTime <= 0)
	{//次のボタンまでの時間が０になったとき

		//目標ボタンをランダムに設定
		int nRandButton = rand()%(TARGETBUTTON_MAX-1);
		int nRandTime = (rand() % MAX_TIME + 1) * 60;

		g_PushState.NowTargetButton = (TARGETBUTTON)(nRandButton + 1);
		g_PushState.nPushLimitTime = nRandTime;
	}

	//GetInput
	CInput *pInput = CInput::GetKey();

	//===============================================
	//目標ボタンが押されているかの判定
	if (g_PushState.NowTargetButton == TARGETBUTTON_UP)
	{
		if (pInput->Trigger(KEY_UP) == true)
		{
			g_PushState.nPushCount++;
		}
	}
	else if (g_PushState.NowTargetButton == TARGETBUTTON_DOWN)
	{
		if (pInput->Trigger(KEY_DOWN) == true)
		{
			g_PushState.nPushCount++;
		}
	}
	else if (g_PushState.NowTargetButton == TARGETBUTTON_RIGHT)
	{
		if (pInput->Trigger(KEY_RIGHT) == true)
		{
			g_PushState.nPushCount++;
		}
	}
	else if (g_PushState.NowTargetButton == TARGETBUTTON_LEFT)
	{
		if (pInput->Trigger(KEY_LEFT) == true)
		{
			g_PushState.nPushCount++;
		}
	}

	//EndGame
	if (g_PushState.nTotalLimitTime <= 0)
	{//制限時間がなくなったとき
		CManager * pManager = GetManager();
		pManager->NextMode(TYPE_RESULT);
	}
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CGame::Draw()
{
}
