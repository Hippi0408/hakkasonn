//=============================================================================
//
// game.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "manager.h"
#include "game.h"
#include "input.h"
#include "texture.h"
#include "ui.h"

//*****************************************************************************
//	�}�N����`
//*****************************************************************************
#define MAX_TIME (3)
#define TIMELIMIT (30)
#define CLOSSKEY (4)

//*****************************************************************************
// �O���[�o���錾
//*****************************************************************************
PUSHSTATE g_PushState;
static const D3DXVECTOR3 POS = D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f);
static const D3DXVECTOR3 POS_UP = D3DXVECTOR3(POS.x, POS.y - 70.0f, 0.0f);
static const D3DXVECTOR3 POS_DOWN = D3DXVECTOR3(POS.x, POS.y + 70.0f, 0.0f);
static const D3DXVECTOR3 POS_RIGHT = D3DXVECTOR3(POS.x + 70.0f, POS.y, 0.0f);
static const D3DXVECTOR3 POS_LEFT = D3DXVECTOR3(POS.x - 70.0f, POS.y, 0.0f);

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CGame::CGame()
{
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CGame::~CGame()
{
}

//*****************************************************************************
// ������
//*****************************************************************************
HRESULT CGame::Init()
{
	//�e���l������
	g_PushState.NowTargetButton = TARGETBUTTON_NONE;
	g_PushState.nPushCount = 0;
	g_PushState.nPushLimitTime = 0;
	g_PushState.nColorCount = 0;
	g_PushState.nTotalLimitTime = TIMELIMIT * 60;

	//�����̎���擾
	DWORD time = timeGetTime();
	srand((unsigned int)time);


	m_pButton = new C2DPolygon;
	if (FAILED(m_pButton->Init()))
	{
		return -1;
	}
	int nTex = CTexture::LoadTexture("data\\TEXTURE\\�{�^��.png");
	m_pButton->SetTextIndex(nTex);
	m_pButton->SetUp(POS_UP, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pButton->SetDiagonalLine(100.0f,100.0f);
	m_pButton->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pButton->SetPolygon();

	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CGame::Uninit()
{
	if (m_pButton != nullptr)
	{
		m_pButton->Uninit();
		delete m_pButton;
		m_pButton = nullptr;
	}
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CGame::Update()
{
	if (g_PushState.nColorCount <= 0)
	{
		//�F�̃��Z�b�g
		m_pButton->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		g_PushState.nColorCount = 0;
	}
	else
	{
		//�F�̕ύX
		m_pButton->SetColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	}

	//�������Ԍ���
	g_PushState.nPushLimitTime--;
	g_PushState.nTotalLimitTime--;
	g_PushState.nColorCount--;
	if (g_PushState.nPushLimitTime <= 0)
	{//���̃{�^���܂ł̎��Ԃ��O�ɂȂ����Ƃ�

		//�ڕW�{�^���������_���ɐݒ�
		int nRandButton = rand()%(TARGETBUTTON_MAX-1);
		int nRandTime = (rand() % MAX_TIME + 2) * 60;

		g_PushState.NowTargetButton = (TARGETBUTTON)(nRandButton + 1);
		g_PushState.nPushLimitTime = nRandTime;
	}

	//GetInput
	CInput *pInput = CInput::GetKey();

	//===============================================
	//�ڕW�{�^����������Ă��邩�̔���
	if (g_PushState.NowTargetButton == TARGETBUTTON_UP)
	{
		m_pButton->SetPos(POS_UP);
		m_pButton->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(180)));
		if (pInput->Trigger(KEY_UP) == true)
		{
			g_PushState.nPushCount++;
			g_PushState.nColorCount = 3;
		}
	}
	else if (g_PushState.NowTargetButton == TARGETBUTTON_DOWN)
	{
		m_pButton->SetPos(POS_DOWN);
		m_pButton->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(0)));
		if (pInput->Trigger(KEY_DOWN) == true)
		{
			g_PushState.nPushCount++;
			g_PushState.nColorCount = 3;
		}
	}
	else if (g_PushState.NowTargetButton == TARGETBUTTON_RIGHT)
	{
		m_pButton->SetPos(POS_RIGHT);
		m_pButton->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(90)));
		if (pInput->Trigger(KEY_RIGHT) == true)
		{
			g_PushState.nPushCount++;
			g_PushState.nColorCount = 3;
		}
	}
	else if (g_PushState.NowTargetButton == TARGETBUTTON_LEFT)
	{
		m_pButton->SetPos(POS_LEFT);
		m_pButton->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(270)));
		if (pInput->Trigger(KEY_LEFT) == true)
		{
			g_PushState.nPushCount++;
			g_PushState.nColorCount = 3;
		}
	}

	//EndGame
	if (g_PushState.nTotalLimitTime <= 0)
	{//�������Ԃ��Ȃ��Ȃ����Ƃ�
		CManager * pManager = GetManager();
		pManager->NextMode(TYPE_RESULT);
	}
	m_pButton->Update();
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CGame::Draw()
{
	m_pButton->Draw();
}
