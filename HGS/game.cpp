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
#define MAX_TIME (5)
#define TIMELIMIT (30)


//*****************************************************************************
// �O���[�o���錾
//*****************************************************************************
PUSHSTATE g_PushState;
static const D3DXVECTOR3 POS_UP = D3DXVECTOR3(100.0f, 100.0f, 0.0f);

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
	g_PushState.nTotalLimitTime = TIMELIMIT * 60;

	//�����̎���擾
	DWORD time = timeGetTime();
	srand((unsigned int)time);


	m_pButton = new C2DPolygon;
	if (FAILED(m_pButton->Init()))
	{
		return -1;
	}
	int nTex = CTexture::LoadTexture("data\\TEXTURE\\�\��.png");
	m_pButton->SetTextIndex(nTex);
	m_pButton->SetUp(POS_UP, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pButton->SetDiagonalLine(100.0f,100.0f);
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
	//�������Ԍ���
	g_PushState.nPushLimitTime--;
	g_PushState.nTotalLimitTime--;
	if (g_PushState.nPushLimitTime <= 0)
	{//���̃{�^���܂ł̎��Ԃ��O�ɂȂ����Ƃ�

		//�ڕW�{�^���������_���ɐݒ�
		int nRandButton = rand()%(TARGETBUTTON_MAX-1);
		int nRandTime = (rand() % MAX_TIME + 1) * 60;

		g_PushState.NowTargetButton = (TARGETBUTTON)(nRandButton + 1);
		g_PushState.nPushLimitTime = nRandTime;
	}

	//GetInput
	CInput *pInput = CInput::GetKey();

	//===============================================
	//�ڕW�{�^����������Ă��邩�̔���
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
	{//�������Ԃ��Ȃ��Ȃ����Ƃ�
		CManager * pManager = GetManager();
		pManager->NextMode(TYPE_RESULT);
	}
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CGame::Draw()
{
	m_pButton->Draw();
}
