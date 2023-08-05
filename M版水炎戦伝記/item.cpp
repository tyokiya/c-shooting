#include "DxLib.h"
#include"item.h"
#include"enemy.h"

extern int LifeCnt;									//敵HPのカウント(グローバル変数)
extern int frame;									//フレーム数(グローバル変数)
extern int EnemyHp[HpGauge];						//敵HPの配列(3ゲージ分)(グローバル変数)

int UpItemImg;										//パワーアップアイテム画像変数
bool UpItemFlg;										//パワーアップアイテムの生存フラグ
int UpItemX, UpItemY;								//パワーアップアイテムの座標x,y
int BombItemImg;									//ボムの画像変数
bool BombItemFlg;									//ボムの生存フラグ
int BombItemX, BombItemY;							//ボムの座標x,y
bool itemFlg;										//アイテムフラグ
bool DisplayFlg;									//表示フラグ

void ItemInit()
{
	//画像読み込み
	UpItemImg = LoadGraph("image/item.png");
	BombItemImg = LoadGraph("image/bomb.png");

	//フラグ初期化
	UpItemFlg = false;
	BombItemFlg = false;
	itemFlg = false;
	DisplayFlg = false;

	//初期座標追加
	UpItemX = 480;
	UpItemY = -15;

	BombItemX = 480;
	BombItemY = -15;
}

void ItemUpdate()
{
	//パワーアップアイテムドロップ
	if (LifeCnt == 2 && frame == 1550)
	{
		//フラグを立てる
		UpItemFlg = true;
	}

	//フラグが立ってる場合移動
	if (UpItemFlg == true)
	{
		ItemMove();
	}

	//ボスの1ゲージ目が0なったらボムをドロップ
	if (EnemyHp[2] <= 0 && itemFlg == false)
	{
		BombItemFlg = true;
		itemFlg = true;
	}
	//フラグが立ってる場合移動
	if (BombItemFlg == true)
	{
		ItemMove();
	}
}

void ItemMove()
{
	if (UpItemFlg == true)
	{
		UpItemY += ItemMoveSpeed;
	}
	if (BombItemFlg == true)
	{
		BombItemY += ItemMoveSpeed;
	}
}

void ItemDraw()
{
	//フラグが立ってる場合のみ描画
	if (UpItemFlg == true)
	{
		//10フレームごとにフラグ切り替え
		if (frame % 10 == 0)
		{
			if (DisplayFlg == false)
			{
				DisplayFlg = true;
			}
			else
			{
				DisplayFlg = false;
			}
		}
		if (DisplayFlg == true)
		{
			DrawExtendGraph(UpItemX, UpItemY, UpItemX + ItemSize, UpItemY + ItemSize, UpItemImg, TRUE);
		}
	}
	if (BombItemFlg == true)
	{
		//10フレームごとにフラグ切り替え
		if (frame % 10 == 0)
		{
			if (DisplayFlg == false)
			{
				DisplayFlg = true;
			}
			else
			{
				DisplayFlg = false;
			}
		}
		if (DisplayFlg == true)
		{
			DrawExtendGraph(BombItemX, BombItemY, BombItemX + ItemSize, BombItemY + ItemSize, BombItemImg, TRUE);
		}
	}
}