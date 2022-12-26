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

	//GetUiData
	m_pBg = new CUI;

	//UiInit
	if (FAILED(m_pBg->Init()))
	{
		return -1;
	}

	//GetUiPointer
	C2DPolygon *pPolygon = m_pBg->CreateUi(3);

	//SetUiData
	int nIndex = CTexture::LoadTexture("data/TEXTURE/sky.png");
	pPolygon[0].SetTextIndex(nIndex);
	pPolygon[0].SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	pPolygon[0].SetDiagonalLine(SCREEN_WIDTH, SCREEN_HEIGHT);
	pPolygon[0].SetPolygon();

	nIndex = 0;
	pPolygon[1].SetTextIndex(nIndex);
	pPolygon[1].SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f + 30.0f, 0.0f));
	pPolygon[1].SetDiagonalLine(SCREEN_WIDTH, 20.0f);
	pPolygon[1].SetColor(D3DXCOLOR(0.4f,1.0f,1.0f,1.0f));
	pPolygon[1].SetPolygon();

	nIndex = CTexture::LoadTexture("data/TEXTURE/.png");
	pPolygon[1].SetTextIndex(nIndex);
	pPolygon[1].SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 100.0f, 0.0f));
	pPolygon[1].SetDiagonalLine(SCREEN_WIDTH, 20.0f);
	pPolygon[1].SetColor(D3DXCOLOR(0.4f, 1.0f, 1.0f, 1.0f));
	pPolygon[1].SetPolygon();

	nIndex = CTexture::LoadTexture("data/TEXTURE/sea.png");
	pPolygon[2].SetTextIndex(nIndex);
	pPolygon[2].SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	pPolygon[2].SetDiagonalLine(SCREEN_WIDTH, SCREEN_HEIGHT);
	pPolygon[2].SetUVMove(D3DXVECTOR2(0.0005f, 0.0f));
	pPolygon[2].SetPolygon();

	return S_OK;

}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CGame::Uninit()
{
	if (m_pBg != nullptr)
	{
		m_pBg->Uninit();
		delete m_pBg;
		m_pBg = nullptr;
	}
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CGame::Update()
{
	m_pBg->Update();

	//GetInput
	CInput *pInput = CInput::GetKey();

	//EndGame
	if (pInput->Trigger(KEY_DECISION))
	{
		CManager * pManager = GetManager();
		pManager->NextMode(TYPE_RESULT);
	}
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CGame::Draw()
{
	m_pBg->Draw();
}
