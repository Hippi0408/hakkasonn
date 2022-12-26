//==================
//十字キー処理
//==================
#ifndef _BULLET_H_
#define _BULLET_H_
#include "main.h"

//プロトタイプ宣言
#define MAX_BULLET (1280)


//弾の種類
typedef enum
{
	BULLETTYPE_PLAYER = 0,
	BULLETTYPE_ENEMY,
	BULLETTYPE_MAX
}BULLETTYPE;

typedef enum
{
	SHOTTYPE_NORMAL = 0,
	SHOTTYPE_SCATTER,
	SHOTTYPE_HOMING,
	SHOTTYPE_FIREWORK,
	SHOTTYPE_SETBOM,
	SHOTTYPE_MAX
}SHOTTYPE;

//構造体を宣言
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXMATRIX  mtx;
	int nIndexShadow;
	float fRadius;
	int nPlayer;
	int nLife;
	int nDamage;
	bool bUse;
	float fSpeed;
	SHOTTYPE type;
	BULLETTYPE BulletType;
}Bullet;

//プロトタイプ宣言
void InitBullet();
void UninitBullet();
void UpdateBullet();
void DrawBullet();


#endif
