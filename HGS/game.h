//=============================================================================
//
// game.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _GAME_H_			//このマクロ定義がされなかったら
#define _GAME_H_			//2重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// 列挙型宣言
//*****************************************************************************
typedef enum
{
	TARGETBUTTON_NONE = 0,
	TARGETBUTTON_UP,
	TARGETBUTTON_DOWN,
	TARGETBUTTON_RIGHT,
	TARGETBUTTON_LEFT
}TARGETBUTTON;

//*****************************************************************************
// 構造体宣言
//*****************************************************************************
typedef struct
{
	TARGETBUTTON NowTargetButton;
	int nPushCount;
	int nPushLimitTime;
}PUSHSTATE;

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CUI;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CGame : public CObject
{
private:
	
public:
	CGame();
	~CGame() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
	CUI *m_pUi;
};

//*****************************************************************************
//プロトタイプ宣言
//*****************************************************************************
void InitGame();
void UninitGame();
void UpdateGame();
void DrawGame();

#endif