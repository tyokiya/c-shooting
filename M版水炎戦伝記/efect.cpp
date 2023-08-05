#include<DxLib.h>
#include "efect.h"
#include"player.h"

//エフェクトの変数
int PlyEfect1[11];      //プレイヤーエフェクト１
int EmyJumpEffect[7];   //敵のジャンプエフェクト

void PlyEfectInit()
{
    LoadDivGraph("efect/pipo-mapeffect006.png", 11, 11, 1, 240, 240, PlyEfect1);
}

void EnemyEfectInit()
{
    LoadDivGraph("efect/jumpefect.png", 11, 11, 1, 240, 240, PlyEfect1);
}

void EfectDraw(int efect[], int num, float x, float y)
{
    DrawRotaGraph(x, y, 1.0, 0, efect[num], TRUE);
}