#include<DxLib.h>
#include "effect.h"
#include"player.h"

//エフェクトの変数
int PlyEfect1[11];      //プレイヤーエフェクト１
int EmyJumpEffect[7];   //敵のジャンプエフェクト
int EmyDownEffect[9];   //敵のダウンエフェクト
int BuffEffect[15];		//バフエフェクト(グローバル変数)
int ResultEffect[15];   //リザルトエフェクト
int EmyShotEffect1[25]; //敵の攻撃エフェクト1
int PlyRevivalEffect[10];//プレイヤーの復活エフェクト
int EmySlashingEffect[10];//敵の斬撃エフェクト
int MagicEffect1[30];      //魔法陣エフェクト1
int MagicEffect2[30];      //魔法陣エフェクト2
int MagicEffect3[16];      //魔法陣エフェクト3

void PlyEfectInit()
{
    LoadDivGraph("effect/pipo-mapeffect006.png", 11, 11, 1, 240, 240, PlyEfect1);
    LoadDivGraph("effect/buffeffect.png", 15, 1, 15, 320, 120, BuffEffect);
    LoadDivGraph("effect/pipo-btleffect173_192.png", 10, 5, 2, 192, 192, PlyRevivalEffect);
}

void EnemyEfectInit()
{
    LoadDivGraph("effect/jumpeffect.png", 7, 7, 1, 120, 120, EmyJumpEffect);
    LoadDivGraph("effect/downeffect.png", 9, 9, 1, 120, 120, EmyDownEffect);
    LoadDivGraph("effect/pipo-btleffect165_960.png", 25, 5, 5, 960, 720, EmyShotEffect1);
    LoadDivGraph("effect/pipo-btleffect145.png", 10, 1, 10, 320, 240, EmySlashingEffect);
    LoadDivGraph("effect/pipoya-mceffect_01_a07_c01_192.png", 30, 5, 6, 192, 192, MagicEffect1);
    LoadDivGraph("effect/pipoya-mceffect_01_a07_c01_192.png", 30, 5, 6, 192, 192, MagicEffect2);
    LoadDivGraph("effect/tktk_Impact_41.png", 16, 5, 4, 192, 128, MagicEffect3);
}

void ResultEffectInit()
{
    LoadDivGraph("effect/bolt.png", 15, 5, 3, 1280, 960, ResultEffect);
}

void EfectDraw(int efect[], int num, float x, float y, float size)
{
    DrawRotaGraph(x, y, size, 0, efect[num], TRUE);
}

void EffectCountCheck(int& cnt, bool& flg, int maxframenum)
{
    //カウントの追加
    cnt++;
    //最大値になったら初期化
    if (cnt > maxframenum)
    {
        //カウント初期化
        cnt = 0;
        //フラグをおろす
        flg = false;
    }
}