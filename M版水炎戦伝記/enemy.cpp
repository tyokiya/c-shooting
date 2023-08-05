#include "DxLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _USE_MATH_DEFINES
#include"enemy.h"
#include<math.h> /* M_PI */
#include"collision.h"
#include "stage.h"
#include"SoundLoad.h"
#include"drawbullet.h"
#include"calculation.h"
#include"effect.h"

//変数
int EnemyImg;           //敵の画像
double EnemyX;          //敵のx座標
double EnemyY;          //敵のy座標
double EnemyMoveX;         //敵の縦軸移動数
double EnemyMoveY;         ////敵の横軸移動数
int EnemyHp[HpGauge];   //敵HPの配列(3ゲージ分)
int LifeCnt;            //敵HPのカウント
int Life0Color, Life1Color, Life2Color; //各ライフ時のhpバーの色
bool EnemySurvivalFlg;                  //敵の生存フラグ
int HpTextImg;                                  //テキスト画像ハンドル

int Bullet4AngleCnt = 0;                        //バレット４のアングルの追加分カウント

float EnemyHitSizeX = 100;      //敵の当たり判定サイズ幅(画像サイスは140)
float EnemyHitSizeY = 150;      //敵の当たり判定サイズ高さ

int DownX, DownY;               //ダウン時の座標x

extern bool EnemyFlg;			//敵が登場してるかのフラグ

//弾
EnemyBullet Bullet1[EnemyBulletNum];        //ランダム弾
EnemyBullet Bullet2[EnemyBulletNum];        //自機狙い弾
EnemyBullet Bullet3[EnemyBulletNum];        //円形弾
EnemyBullet Bullet4[EnemyBulletNum];
EnemyBullet5 Bullet5[EnemyBulletNum];       //縦長弾
EnemyBullet Bullet6[EnemyBulletNum];         //壁からの発射
EnemyBullet Bullet7[EnemyBulletNum];         //魔法陣からの自機狙い1
EnemyBullet Bullet8[EnemyBulletNum];         //魔法陣からの自機狙い2
EnemyBullet Bullet9[EnemyBulletNum];         //敵の円形弾
EnemyBullet Bullet10[EnemyBulletNum];         //敵のランダム弾

//画像ハンドル
int Bullet1Img, Bullet2Img, Bullet3Img, Bullet4Img, Bullet5Img, Bullet6Img,Bullet7Img,Bullet8Img,Bullet9Img,Bullet10Img;             
int HitEfectImg;
int MeterImg;               //メーターフレームのイメージハンドル

int Bullet1Cnt, Bullet2Cnt, Bullet3Cnt, Bullet4Cnt, Bullet5Cnt, Bullet6Cnt, Bullet7Cnt, Bullet8Cnt, Bullet9Cnt, Bullet10Cnt = 0;     //弾数のカウント
int EnemyMoveSpeedX, EnemyMoveSpeedY;   //敵の移動速度
bool Bullet2flg;                        //バレット2のフラグ
bool Atack2Flg;                 //攻撃2のフラグ
bool LifeFlg2;
bool LifeFlg3;
bool LifeFlg1;
bool AttackPattern3Flg;         //攻撃パターン3のフラグ
bool MoveFlg;                   //瞬間移動のフラグ
bool MoveFlg2;
bool RightFlg, LeftFlg;  //左右の移動フラグ
bool UpFlg, DownFlg;     //上下の移動フラグ

bool LineFlg;                           //敵の攻撃上ラインのフラグ
int LineFrame;                                  //攻撃した時のフレーム数を記憶する
int LineX1, LineY1, LineX2, LineY2;                               //線を引く時の一時的プレイヤー座標の記憶領域

//サウンドハンドル
int Bullet1Sound;       
int EnemySound1;
int EnemySound2;
int EnemySound3;        //移動音
int EnemySound4;
int EnemySound5;        //落雷
int EnemySound6;
int SordSound;          //刀の音
int DownSE;             //撃破時のサウンドハンドル
int EnemyBombSound;     //敵の爆発サウンドハンドル

sHitRect EnemyHit;      //敵のヒット判定構造体

int TextCnt;            //表示テキストの識別カウント

//プレイヤー座標グローバル変数
extern double PlayCharaX;   //プレイヤーのx座標
extern double PlayCharaY;   //プレイヤーのy座標
extern sHitRect PlyHit;		   //自機の自機のヒット判定構造体(グローバル変数)

//プレイヤーのエフェクトグローバル変数
extern int PlyEfect1[11];
extern int PlyEfectCnt;
extern bool PlyEfectFlg;

extern int BombTime;                   //ボム発動時の時間計測

//エフェクトグローバル変数
extern int EmyJumpEffect[7];            //敵のジャンプエフェクト
extern int EmyDownEffect[9];            //敵のダウンエフェクト
extern int EmyShotEffect1[25];          //敵の攻撃エフェクト1
extern int EmySlashingEffect[10];       //敵の斬撃エフェクト
extern int MagicEffect1[30];            //魔法陣エフェクト1
extern int MagicEffect2[30];            //魔法陣エフェクト2
extern int MagicEffect3[16];            //魔法陣エフェクト3

int EmyJumpEfectCnt, DownEffectCnt, EmyShotEffect1Cnt,EmySlashingCnt,Magic1Cnt,Magic2Cnt,Magic3Cnt;            //エフェクトカウント
bool EmyJumpEfectFlg, DownEffectFlg,EmyShotEffect1Flg, EmySlashingFlg,Magic1Flg,Magic2Flg,Magic3Flg;           //エフェクトフラグ

extern bool ShieldFlg;			//シールドフラグ

extern bool ResultChangeFlg;			//リザルトの切り替えフラグ

int EnemyDownTime;                      //敵を倒したフレーム数
int DownTimeFlg;

void EnemyInit()
{
    EnemyImg = LoadGraph("image/enemy1.png");     //敵画像の読み込み
    MeterImg = LoadGraph("image/meter.png");        //メーター画像読み込み
    EnemyX = InitEnemyX;        //敵の初期x座標
    EnemyY = InitEnemyY;        //敵の初期y座標
    //敵HPの設定
    for (int i = 0; i < HpGauge; i++)
    {
        EnemyHp[i] = 1000;
    }
    EnemyInitRect(EnemyHit, EnemyHitSizeX, EnemyHitSizeY, EnemyX, EnemyY);      //敵の当たり判定構造体設定
    //ライフカウントの初期設定
    LifeCnt = 2;
    //HPバーの色設定
    Life0Color = GetColor(255, 0, 0);
    Life1Color = GetColor(0, 255, 0);
    Life2Color = GetColor(0, 255, 255);

    //エフェクト画像の読み込み
    HitEfectImg = LoadGraph("image/efect.png");
    HpTextImg = LoadGraph("image/HPText.png");

    //移動量初期化
    EnemyMoveX = 5;         //敵の縦軸移動数
    EnemyMoveY = 2;         ////敵の横軸移動数

    //フラグ初期化
    EnemySurvivalFlg = true;                  //敵の生存フラグ
    Atack2Flg = false;                 //攻撃2のフラグ
    LifeFlg2 = false;
    LifeFlg3 = false;
    LifeFlg1 = false;
    AttackPattern3Flg = true;         //攻撃パターン3のフラグ
    MoveFlg = false;                   //瞬間移動のフラグ
    MoveFlg2 = false;
    RightFlg = false, LeftFlg = true;  //左右の移動フラグ
    UpFlg = false, DownFlg = true;     //上下の移動フラグ
    LineFlg = false;                           //敵の攻撃上ラインのフラグ

    EnemyDownTime = 0;
    DownTimeFlg = false;

    EmyJumpEfectCnt, DownEffectCnt, EmyShotEffect1Cnt, EmySlashingCnt, Magic1Cnt, Magic2Cnt, Magic3Cnt = 0;     //エフェクトカウント
    EmyJumpEfectFlg, DownEffectFlg, EmyShotEffect1Flg, EmySlashingFlg, Magic1Flg, Magic2Flg, Magic3Flg = false;                   //エフェクトフラグ

    //敵の弾情報の初期化
    EnemyBulletInit();

    //サウンドハンドル読み込み
    LoadEnemySound();

    //エフェクト初期化
    EnemyEfectInit();
}

void EnemyBulletInit()
{
    //フラグ初期化
    for (int i = 0; i < EnemyBulletNum; i++)
    {
        Bullet1[i].shotflg = false;
        Bullet2[i].shotflg = false;
        Bullet3[i].shotflg = false;
        Bullet4[i].shotflg = false;
        Bullet5[i].shotflg = false;
        Bullet6[i].shotflg = false;
        Bullet7[i].shotflg = false;
        Bullet8[i].shotflg = false;
        Bullet9[i].shotflg = false;
        Bullet10[i].shotflg = false;

        Bullet1[i].width = Bullet1Widh;
        Bullet2[i].width = Bullet1Widh;
        Bullet3[i].width = Bullet1Widh;
        Bullet4[i].width = Bullet1Widh;
        Bullet5[i].width = Bullet5Widh;
        Bullet6[i].width = Bullet1Widh;
        Bullet7[i].width = Bullet1Widh;
        Bullet8[i].width = Bullet1Widh;
        Bullet9[i].width = Bullet1Widh;
        Bullet10[i].width = Bullet1Widh;

        Bullet1[i].height = Bullet1Widh;
        Bullet2[i].height = Bullet1Widh;
        Bullet3[i].height = Bullet1Widh;
        Bullet4[i].height = Bullet1Widh;
        Bullet5[i].height = Bullet5Height;
        Bullet6[i].height = Bullet1Widh;
        Bullet7[i].height = Bullet1Widh;
        Bullet8[i].height = Bullet1Widh;
        Bullet9[i].height = Bullet1Widh;
        Bullet10[i].height = Bullet1Widh;
    }
    Bullet1Img = LoadGraph("image/shot1.png");
    Bullet2Img = LoadGraph("image/shot2.png");
    Bullet3Img = LoadGraph("image/shot1.png");
    Bullet4Img = LoadGraph("image/shot4.png");
    Bullet5Img = LoadGraph("image/shot3.png");      //縦長弾
    Bullet6Img = LoadGraph("image/shot3.png");
}

void EnemyDraw()
{
    if (EnemySurvivalFlg == true)
    {
        DrawGraph(EnemyX, EnemyY, EnemyImg, TRUE);
    }
    //ヒットボックス描画
    //DrawLine(EnemyHit.worldLX, EnemyHit.worldLY, EnemyHit.worldLX + EnemyHit.w, EnemyHit.worldLY, GetColor(255, 0, 0));
    //DrawLine(EnemyHit.worldRX, EnemyHit.worldRY, EnemyHit.worldRX - EnemyHit.w, EnemyHit.worldRY, GetColor(255, 0, 0));
}

void EnemyIn(bool& EnemyFlg)
{
    if (EnemyY < 0)
    {
        EnemyY++;   //座標の追加
        TextCnt = 1;
    }
    else
    {
        //座標が0を超えた時点でフラグをを立てる
        EnemyFlg = true;
    }
}

void EnemyUpdate(int& frame)
{
    if (EnemyFlg == true)
    {
        //テキストカウント初期化
        TextCnt = 0;
    }
    //LifeCnt = 1;

    //移動量初期化
    EnemyMoveSpeedX = 0;
    EnemyMoveSpeedY = 0;
    //攻撃1
    if (LifeCnt == 2 && frame < 1550 && frame > 0)
    {
        //生存フラグを立てる
        EnemySurvivalFlg == true;
        AttackPattern1(frame);
    }

    //バレット1の移動
    EnemyBulletMove(Bullet1, EnemyBulletNum, Bullet1Widh, Bullet1Widh);
    //バレット2の移動
    EnemyBulletMove(Bullet2, EnemyBulletNum, Bullet1Widh, Bullet1Widh);

    //インターバル中は生存フラグを下ろす
    if (LifeCnt == 2 && frame >= 1550 && frame < 1650)
    {
        EnemySurvivalFlg = false;
        //テキストカウント追加
        TextCnt = 2;
    }

    //バレット1，2のカウント初期化
    if (frame == 1649)
    {
        Bullet1Cnt = NULL;
        Bullet2Cnt = NULL;
    }

    //攻撃2(hp0になるまで攻撃)
    if (LifeCnt == 2 && frame >= 1650)
    {
        //生存フラグを立てる
        EnemySurvivalFlg = true;
        AttackPattern2(frame);
    }

    //バレット3の移動
    EnemyBulletMove(Bullet3, EnemyBulletNum, Bullet1Widh, Bullet1Widh);

    //hpが0になったら消える
    if (EnemyHp[2] <= 0 && LifeFlg2 == false)
    {
        //ダウンエフェクトフラグを立てる
        DownEffectFlg = true;
        //ダウン時の座標を入れる
        DownX = EnemyX + EnemySizeX / 2;
        DownY = EnemyY + EnemySizeY / 2;
        EnemyDisappear(frame);
        //フラグを立てる
        LifeFlg2 = true;
        //表示中の弾を消す
        EnemyBulletReset();
    }

    if (EnemyHp[2] <= 0 && EnemySurvivalFlg == false && EnemyHp[1] == 1000)
    {
        //テキストカウント追加
        TextCnt = 3;
    }

    //再登場
    if (LifeCnt == 1 && frame == 240 && MoveFlg2 == false)
    {
        //フラグを立てる
        EnemySurvivalFlg = true;
        MoveFlg2 = true;
        //中心へ移動
        EnemyX = InitEnemyX;
        EnemyY = 0;
        //移動音
        PlaySoundMem(EnemySound3, DX_PLAYTYPE_BACK);
        //移動量初期化
        EnemyMoveX = 0;
        EnemyMoveY = 0;
        //エフェクトフラグをたてる
        EmyShotEffect1Flg = true;
    }

    //攻撃パターン3
    if (LifeCnt == 1 && frame > 300 && EnemyHp[1] > 500)
    {
        AttackPattern3(frame);
    }
    //バレット4の移動
    EnemyBulletMove(Bullet4, EnemyBulletNum, Bullet1Widh, Bullet1Widh);

    //一度消える
    if (EnemyHp[1] <= 500 && MoveFlg == false)
    {
        EnemyDisappear(frame);
        //フラグを立てる
        MoveFlg = true;
        //表示中の弾を消す
        EnemyBulletReset();
    }
    if (EnemyHp[1] <= 500 && EnemyHp[1] == 1000 && EnemySurvivalFlg == false)
    {
        //テキストカウント追加
        TextCnt = 4;
    }
    //再登場
    if (frame == 60 && LifeCnt == 1 && EnemyHp[1] <= 500)
    {
        //フラグを立てる
        EnemySurvivalFlg = true;
        //中心へ移動
        EnemyX = InitEnemyX;
        EnemyY = 0;
        //移動音
        PlaySoundMem(EnemySound3, DX_PLAYTYPE_BACK);
    }

    //攻撃パターン4
    if (LifeCnt == 1 && EnemyHp[1] <= 500 && frame >= 70)
    {
        AttackPattern4(frame);
    }
    //バレット5の移動
    EnemyBulletMove5(Bullet5, EnemyBulletNum, Bullet5Widh, Bullet5Height);

    //hpが0になったら消える
    if (EnemyHp[1] <= 0 && LifeFlg3 == false)
    {
        //ダウンエフェクトフラグを立てる
        DownEffectFlg = true;
        //ダウン時の座標を入れる
        DownX = EnemyX + EnemySizeX / 2;
        DownY = EnemyY + EnemySizeY / 2;
        EnemyDisappear(frame);
        LifeFlg3 = true;
        //表示中の弾を消す
        EnemyBulletReset();
    }

    if (EnemyHp[1] <= 0 && EnemyHp[1] == 1000 && EnemySurvivalFlg == false)
    {
        //テキストカウント追加
        TextCnt = 5;
    }

    //再登場
    if (frame == 60 && LifeCnt == 0 && EnemyHp[0] >= 500)
    {
        //フラグを立てる
        EnemySurvivalFlg = true;
        //左上へ移動
        EnemyX = 40;
        EnemyY = 0;
        //移動音
        PlaySoundMem(EnemySound3, DX_PLAYTYPE_BACK);
    }

    //攻撃パターン5
    if (LifeCnt == 0 && EnemyHp[0] > 500 && frame >= 70)
    {
        AttackPattern5(frame);
    }
    //バレット6の移動
    EnemyBulletMove(Bullet6, EnemyBulletNum, Bullet1Widh, Bullet1Widh);

    //一度消える
    if (LifeFlg1 == false && EnemyHp[0] <= 500)
    {
        EnemyDisappear(frame);
        //フラグを立てる
        LifeFlg1 = true;
        //表示中の弾を消す
        EnemyBulletReset();
    }

    if (EnemyHp[0] == 500 && EnemySurvivalFlg == false)
    {
        //テキストカウント追加
        TextCnt = 6;
    }

    //再登場
    if (frame == 60 && LifeCnt == 0 && EnemyHp[0] <= 500)
    {
        //フラグを立てる
        EnemySurvivalFlg = true;
        //中心へ移動
        EnemyX = InitEnemyX;
        EnemyY = 0;
        //移動音
        PlaySoundMem(EnemySound3, DX_PLAYTYPE_BACK);
        //移動量の設定
        EnemyMoveX = 3;
        EnemyMoveY = 3;
    }

    //攻撃パターン6
    if (LifeCnt == 0 && EnemyHp[0] <= 500 && frame > 60)
    {
        AttackPattern6(frame);
    }

    //バレット7,8の移動
    EnemyBulletMove(Bullet7, EnemyBulletNum, Bullet1Widh, Bullet1Widh);
    EnemyBulletMove(Bullet8, EnemyBulletNum, Bullet1Widh, Bullet1Widh);
    //バレット9の移動
    EnemyBulletMove(Bullet9, EnemyBulletNum, Bullet1Widh, Bullet1Widh);

    //ダウンフラグが立っていたらエフェクト再生
    if (DownEffectFlg == true)
    {
        EfectDraw(EmyDownEffect, DownEffectCnt, DownX, DownY, 2.0);
    }
    //エフェクトカウント増加
    if (DownEffectFlg == true && frame % 5 == 0)
    {
        EffectCountCheck(DownEffectCnt, DownEffectFlg, 9);
    }

    //敵の当たり判定更新
    EnemyRectUpdate(EnemyHit, EnemyX, EnemyY);

    //撃破時のフレーム数をとる
    if (EnemyHp[0] == 0 && DownTimeFlg == false)
    {
        EnemyDownTime = frame;
        //フラグを立てる
        DownTimeFlg = true;
        EnemyBulletReset();
    }

    //倒した後の処理
    if (EnemyHp[0] <= 0)
    {
        DownMotion(frame);
    }
}

void EnemyHitEfect()
{
    DrawGraph(EnemyX, EnemyY, HitEfectImg, TRUE);
    if (EnemyHp[LifeCnt] <= 0)
    {
        LifeCnt--;
    }
}

void DrawMeter()
{
    //テキスト画像描画
    DrawExtendGraph(1000, -20, 1200, 72, HpTextImg, TRUE);

    //メーター画像描画
    DrawExtendGraph(1010, 40, 1368, 85, MeterImg, TRUE);
    if (EnemyHp[0] != 0)
    {
        DrawBox(1020, 50, 1020 + EnemyHp[0] / 3, 50 + 20, Life0Color, TRUE);
    }
    if (EnemyHp[1] != 0)
    {
        DrawBox(1020, 50, 1020 + EnemyHp[1] / 3, 50 + 20, Life1Color, TRUE);
    }
    if (EnemyHp[2] != 0)
    {
        DrawBox(1020, 50, 1020 + EnemyHp[2] / 3, 50 + 20, Life2Color, TRUE);
    }
}

void AttackPattern1(int frame)
{
    //移動速度の設定
    EnemyMoveSpeedX = 3;
    EnemyMoveSpeedY = 1;
    //敵の移動量(横)
    if (EnemyX <= 5)
    {
        EnemyMoveX = EnemyMoveSpeedX;
    }
    if (EnemyX + EnemySizeX >= 995)
    {
        EnemyMoveX = -EnemyMoveSpeedX;
    }
    //敵の移動量(縦)
    if (EnemyY < 1)
    {
        EnemyMoveY = EnemyMoveSpeedY;
    }
    if (EnemyY > 100)
    {
        EnemyMoveY = -EnemyMoveSpeedY;
    }

    //敵の移動
    EnemyMove();

    //Bullet1の追加
    if (frame % 2 == 0)
    {
        Bullet1Add(EnemyX, EnemyY);
        //カウント追加
        Bullet1Cnt++;
        //配列のカウントが最大値になったら初期化
        if (Bullet1Cnt > EnemyBulletNum)
        {
            Bullet1Cnt = 0;
        }
    }

    //2フレームに一回ショット音再生(バレット1)
    if (frame % 2)
    {
        //ショット音の再生
        PlaySoundMem(EnemySound1, DX_PLAYTYPE_BACK);
    }

    //バレット2フラグを10フレームごと切り替え
    if (frame % 10 == 0)
    {
        if (Bullet2flg == false)
        {
            Bullet2flg = true;
        }
        else
        {
            Bullet2flg = false;
        }
    }

    //Bullet2の追加(5フレームごと発射)
    if (Bullet2flg == true && frame % 5 == 0)
    {
        Bullet2Add(EnemyX, EnemyY);
        //カウント追加
        Bullet2Cnt++;
    }
    //配列のカウントが最大値になったら初期化
    if (Bullet2Cnt > EnemyBulletNum)
    {
        Bullet2Cnt = 0;
    }
}

void AttackPattern2(int frame)
{
    //移動速度の設定
    if (Atack2Flg == false)//一回目は定位置への瞬間移動
    {
        EnemyX = 50;
        EnemyY = 50;
        //フラグを立てる
        Atack2Flg = true;
    }
    else                   //二回目以降は200づつの移動
    {
        EnemyMoveX = 200;
        EnemyMoveY = 0;

    }
    //2秒に1回瞬間移動
    if (frame % 120 == 0)
    {
        //エフェクトフラグを立てる
        EmyJumpEfectFlg = true;

        //敵の移動
        EnemyMove();
        //ゲームフレームより行こうとした場合初期値に戻す
        if (EnemyX > GameWindowX2 - EnemySizeX)
        {
            EnemyX = 50;
        }
        //移動音
        PlaySoundMem(EnemySound3, DX_PLAYTYPE_BACK);
    }
    if (frame % 60 == 0)
    {
        //円形弾追加
        Bullet3Add(EnemyX + (EnemySizeX / 2), EnemyY + (EnemySizeY / 2));


        //発射音の再生
        PlaySoundMem(EnemySound2, DX_PLAYTYPE_BACK);
    }

    //ジャンプエフェクトの描画
    if (EmyJumpEfectFlg == true)
    {
        EfectDraw(EmyJumpEffect, EmyJumpEfectCnt, EnemyX + 60, EnemyY + 190, 1.0);
    }
    //エフェクトフラグが立っているかの確認
    if (EmyJumpEfectFlg == true && frame % 5 == 0)
    {
        EffectCountCheck(EmyJumpEfectCnt, EmyJumpEfectFlg, 7);
    }
}

void AttackPattern3(int frame)
{
    //移動量
    if (frame % 720 == 0)
    {
        EnemyMoveX = -400;
        EnemyMoveY = 0;
        //敵の移動
        EnemyMove();
        //画面外に行ってないかの判定
        if (EnemyX <= 40 || EnemyX >= 1000 - EnemySizeX)
        {
            EnemyX = InitEnemyX;
        }
    }
    else if (frame % 360 == 0)
    {
        EnemyMoveX = 200;
        EnemyMoveY = 0;
        //敵の移動
        EnemyMove();
        //画面外に行ってないかの判定
        if (EnemyX <= 40 || EnemyX >= 1000 - EnemySizeX)
        {
            EnemyX = InitEnemyX;
        }
    }

    //ショットエフェクト描画
    if (EmyShotEffect1Flg == true)
    {
        DrawExtendGraph(40, 0, 1000, 900, EmyShotEffect1[EmyShotEffect1Cnt], true);
    }
    //エフェクトフラグが立っているかの確認
    if (EmyShotEffect1Flg == true && frame % 3 == 0)
    {
        //カウントの追加
        EffectCountCheck(EmyShotEffect1Cnt, EmyShotEffect1Flg, 24);
    }

    if (frame % 10 == 0 && AttackPattern3Flg == true)
    {
        //1づつずらしながら円形に発射
        //弾の追加
        Bullet4Add(EnemyX + (EnemySizeX / 2), EnemyY + (EnemySizeY / 2));
        //配列数が最大になったら初期化
        if (Bullet4Cnt > EnemyBulletNum)
        {
            Bullet4Cnt = 0;
        }
        //発射音再生
        PlaySoundMem(EnemySound4, DX_PLAYTYPE_BACK);
    }
    if (frame % 120 == 0)
    {
        AttackPattern3Flg = false;  //射出のクールタイム
    }
    if (frame % 180 == 0)
    {
        AttackPattern3Flg = true;   //再射出
    }
}

void AttackPattern4(int frame)
{
    //縦長弾の発射
    if (frame % 60 == 0)
    {
        Bullet5Add(EnemyX + (EnemySizeX / 2), EnemyY + (EnemySizeY / 2));
        //配列数が最大になったら初期化
        if (Bullet5Cnt > EnemyBulletNum)
        {
            Bullet5Cnt = 0;
        }
        //発射音再生
        PlaySoundMem(EnemySound5, DX_PLAYTYPE_BACK);
    }

    //敵の移動
    //左へ移動
    if (LeftFlg == true)
    {
        EnemyMoveX = -5;
        //下へ移動
        if (DownFlg == true)
        {
            EnemyMoveY = 5;
        }
        else if (UpFlg == true) //上へ移動
        {
            EnemyMoveY = -5;
        }
    }
    //右へ移動
    if (RightFlg == true)
    {
        EnemyMoveX = 5;
        //下へ移動
        if (DownFlg == true)
        {
            EnemyMoveY = 5;
        }
        else if (UpFlg == true) //上へ移動
        {
            EnemyMoveY = -5;
        }
    }
    //敵の移動
    EnemyMove();
    //画面外に行こうとしていないかの確認
    if (EnemyX <= GameWindowX1)
    {
        //フラグの入れ替え
        LeftFlg = false;
        RightFlg = true;
    }
    else if (EnemyX + EnemySizeX >= GameWindowX2)
    {
        //フラグの入れ替え
        LeftFlg = true;
        RightFlg = false;
    }
    if (EnemyY + EnemySizeY >= 900)
    {
        //フラグの入れ替え
        UpFlg = true;
        DownFlg = false;
    }
    else if (EnemyY <= 0)
    {
        //フラグの入れ替え
        UpFlg = false;
        DownFlg = true;
    }
}

void AttackPattern5(int frame)
{
    float v;          //正規化用変数
    int moveSpeed = 20;  //移動速度
    int randx, randy;
    //移動する直線を表示し、切込み攻撃
    if (frame % 160 == 0 && LineFlg == false)
    {
        //敵の中心からプレイヤーまでの直線距離を求める
        EnemyMoveX = (PlyHit.worldLX - EnemySizeX / 2) - EnemyX;
        EnemyMoveY = (PlyHit.worldLY - EnemySizeY / 2) - EnemyY;
        v = sqrt(EnemyMoveX * EnemyMoveX + EnemyMoveY * EnemyMoveY);//正規化
        //加速度計算
        EnemyMoveX = (EnemyMoveX / v) * moveSpeed;
        EnemyMoveY = (EnemyMoveY / v) * moveSpeed;
        //フラグを立てフレーム数を記憶する
        LineFlg = true;
        LineFrame = frame;
        //座標の記憶
        LineX1 = EnemyX + EnemySizeX / 2;
        LineY1 = EnemyY + EnemySizeY / 2;
        LineX2 = PlyHit.worldLX;
        LineY2 = PlyHit.worldLY;
    }
    //表示時間中はラインを表示
    if (LineFlg == true)
    {
        if (frame % 2 == 0)
        {
            DrawLine(LineX1, LineY1, LineX2, LineY2, GetColor(255, 0, 0), 3);
        }

    }

    //サウンド再生
    if (LineFrame + 30 == frame)
    {
        PlaySoundMem(SordSound, DX_PLAYTYPE_BACK);
    }

    //敵の移動
    if (LineFrame + 30 <= frame && LineFlg == true)
    {
        //エフェクトフラグを立てる
        EmySlashingFlg = true;

        EnemyMove();
        //画面外に行こうとしていないかの確認
        if (EnemyX <= GameWindowX1 || EnemyX + EnemySizeX >= GameWindowX2)
        {
            //フラグを下ろす
            LineFlg = false;
        }
        if (EnemyY + EnemySizeY >= 900 || EnemyY <= 0)
        {
            //フラグを下ろす
            LineFlg = false;
        }
    }
    //壁3面からランダムで弾を発射
    if (frame % 60 == 0)
    {
        for (int i = 0; i < 2; i++)
        {
            Bullet6Add((rand() % 960) + 40, 0, 0, 4);
            Bullet6Add(1000 - Bullet1Widh, (rand() % 900), -4, 0);
            Bullet6Add(40, (rand() % 900), 4, 0);
        }
    }
}

void AttackPattern6(int frame)
{
    //魔法陣のフラグの確認
    if (Magic1Flg == false && Magic2Flg == false)
    {
        //エフェクトフラグを立てる
        Magic1Flg = true;
        Magic2Flg = true;
        //Magic3Flg = true;
    }

    //エフェクト描画
    if (Magic1Flg == true && Magic2Flg == true)
    {
        //描画
        EfectDraw(MagicEffect1, Magic1Cnt, 140, 450, 1.0);
        EfectDraw(MagicEffect2, Magic2Cnt, 900, 450, 1.0);
        //EfectDraw(MagicEffect3, Magic3Cnt, 140, 450, 2.0);
    }

    //エフェクトカウント追加
    if (Magic1Flg == true && Magic2Flg == true && frame % 5 == 0)
    {
        Magic1Cnt++;
        Magic2Cnt++;
        Magic3Cnt++;
        if (Magic1Cnt == 30 && Magic2Cnt == 30)
        {
            //カウント初期化
            Magic1Cnt = 0;
            Magic2Cnt = 0;
        }
        if (Magic3Cnt == 16)
        {
            //カウント初期化
            Magic3Cnt = 0;
        }
    }

    //魔法陣からの弾追加
    if (frame % 30 == 0)
    {
        Bullet7Add(140, 450);
    }
    if (frame % 45 == 0)
    {
        Bullet8Add(900, 450);
    }

    //円形状に弾を発射
    //弾の追加
    if (frame % 60 == 0)
    {
        //発射音再生
        PlaySoundMem(EnemySound6, DX_PLAYTYPE_BACK);
        Bullet9Add(EnemyX + (EnemySizeX / 2), EnemyY + (EnemySizeY / 2));
    }

    //配列数が最大になったら初期化
    if (Bullet9Cnt > EnemyBulletNum)
    {
        Bullet9Cnt = 0;
    }
    //発射音再生
    PlaySoundMem(EnemySound4, DX_PLAYTYPE_BACK);

    //移動
    EnemyMove();

    if (EnemyX <= GameWindowX1)
    {
        EnemyMoveX = 2;
    }
    if (EnemyX + EnemySizeX >= GameWindowX2)
    {
        EnemyMoveX = -2;
    }
    if (EnemyY + EnemyMoveY <= 0)
    {
        EnemyMoveY = 2;
    }
    if (EnemyY + EnemySizeY >= 400)
    {
        EnemyMoveY = -2;
    }
    EnemyMove();


}

void EnemyMove()
{
    //値の追加
    EnemyX += EnemyMoveX;
    EnemyY += EnemyMoveY;
}

void Bullet1Add(double x, double y)
{
    Bullet1[Bullet1Cnt].shotflg = true;                         //生存フラグ
    Bullet1[Bullet1Cnt].x = x;                                  //座標ｘ
    Bullet1[Bullet1Cnt].y = y + 50;                             //座標ｙ
    Bullet1[Bullet1Cnt].angle = rand() % 360;                  //角度
    Bullet1[Bullet1Cnt].speed = 5;                              //速度

    Bullet1[Bullet1Cnt].vx = cos(Bullet1[Bullet1Cnt].angle) * Bullet1[Bullet1Cnt].speed;    //加速度x
    Bullet1[Bullet1Cnt].vy = sin(Bullet1[Bullet1Cnt].angle) * Bullet1[Bullet1Cnt].speed;    //加速度y
}

void Bullet2Add(double x, double y)
{
    float v;          //正規化用変数
    Bullet2[Bullet2Cnt].shotflg = true;                         //生存フラグ
    Bullet2[Bullet2Cnt].x = x + EnemySizeX;                     //座標ｘ
    Bullet2[Bullet2Cnt].y = y + 50;                             //座標ｙ
    Bullet2[Bullet2Cnt].vx = PlyHit.worldLX - Bullet2[Bullet2Cnt].x;                    //加速度x
    Bullet2[Bullet2Cnt].vy = PlyHit.worldLY - Bullet2[Bullet2Cnt].y;                    //加速度y
    Bullet2[Bullet2Cnt].speed = 3;                              //速度
    v = sqrt(Bullet2[Bullet2Cnt].vx * Bullet2[Bullet2Cnt].vx + Bullet2[Bullet2Cnt].vy * Bullet2[Bullet2Cnt].vy);//正規化

    Bullet2[Bullet2Cnt].vx = (Bullet2[Bullet2Cnt].vx / v) * Bullet2[Bullet2Cnt].speed;      //加速度x
    Bullet2[Bullet2Cnt].vy = (Bullet2[Bullet2Cnt].vy / v) * Bullet2[Bullet2Cnt].speed;      //加速度y

}

void Bullet3Add(double x, double y)
{
    for (int i = 0; i < 360; i += 10)
    {
        Bullet3[Bullet3Cnt].shotflg = true;            //生存フラグ
        Bullet3[Bullet3Cnt].x = x;                     //発射する中心座標座標ｘ
        Bullet3[Bullet3Cnt].y = y;                     //発射する中心座標座標y
        Bullet3[Bullet3Cnt].speed = 2;                 //速度
        ChangeRadian(Bullet3, EnemyBulletNum, Bullet3Cnt, i);            //角度
        Bullet3[Bullet3Cnt].vx = cos(Bullet3[Bullet3Cnt].angle) * Bullet3[Bullet3Cnt].speed;    //加速度x
        Bullet3[Bullet3Cnt].vy = sin(Bullet3[Bullet3Cnt].angle) * Bullet3[Bullet3Cnt].speed;    //加速度y
        //バレット3のカウント追加
        Bullet3Cnt++;
        //配列のカウントが最大値になったら初期化
        if (Bullet3Cnt > EnemyBulletNum)
        {
            Bullet3Cnt = 0;
        }
    }

}

void Bullet4Add(double x, double y)
{
    for (int i = 0; i < 360; i++)
    {
        if (i % 10 == 0)
        {
            Bullet4[Bullet4Cnt].shotflg = true;                        //生存フラグ
            Bullet4[Bullet4Cnt].x = x;                                  //発射する中心座標座標ｘ
            Bullet4[Bullet4Cnt].y = y;                                  //発射する中心座標座標y
            Bullet4[Bullet4Cnt].speed = 3;                              //速度
            ChangeRadian(Bullet4, EnemyBulletNum, Bullet4Cnt, i + Bullet4AngleCnt);                //角度(ラジアン)
            Bullet4[Bullet4Cnt].vx = cos(Bullet4[Bullet4Cnt].angle) * Bullet4[Bullet4Cnt].speed;    //加速度x
            Bullet4[Bullet4Cnt].vy = sin(Bullet4[Bullet4Cnt].angle) * Bullet4[Bullet4Cnt].speed;    //加速度y
            //配列カウントの増加
            Bullet4Cnt++;
            //配列のカウントが最大値になったら初期化
            if (Bullet4Cnt > EnemyBulletNum)
            {
                Bullet4Cnt = 0;
            }
        }
    }
    //アングルカウントの追加
    Bullet4AngleCnt += 2;
}

void Bullet5Add(double x, double y)
{
    for (int i = 0; i < 360; i++)
    {
        if (i % 20 == 0)
        {
            Bullet5[Bullet5Cnt].shotflg = true;                        //生存フラグ
            Bullet5[Bullet5Cnt].x = x;                                  //発射する中心座標座標ｘ
            Bullet5[Bullet5Cnt].y = y;                                  //発射する中心座標座標y
            Bullet5[Bullet5Cnt].speed = 2;                              //速度
            ChangeRadian2(Bullet5, EnemyBulletNum, Bullet5Cnt, i);                              //角度(ラジアン)
            Bullet5[Bullet5Cnt].vx = cos(Bullet5[Bullet5Cnt].angle) * Bullet5[Bullet5Cnt].speed;    //加速度x
            Bullet5[Bullet5Cnt].vy = sin(Bullet5[Bullet5Cnt].angle) * Bullet5[Bullet5Cnt].speed;    //加速度y
            //矩形の生成
            Bullet5[Bullet5Cnt].lx = x - 6;
            Bullet5[Bullet5Cnt].ly = y - 6;
            Bullet5[Bullet5Cnt].rx = x + 6;
            Bullet5[Bullet5Cnt].ry = y + 6;
            //配列カウントの増加
            Bullet5Cnt++;
        }
    }
}

void Bullet6Add(float x, float y, float vx, float vy)
{
    Bullet6[Bullet6Cnt].shotflg = true;                        //生存フラグ
    Bullet6[Bullet6Cnt].x = x;                                  //発射する標座標ｘ
    Bullet6[Bullet6Cnt].y = y;                                  //発射する標座標y
    Bullet6[Bullet6Cnt].vx = vx;                                 //加速度x
    Bullet6[Bullet6Cnt].vy = vy;                                 //加速度y
    //配列カウントの増加
    Bullet6Cnt++;
    //配列のカウントが最大値になったら初期化
    if (Bullet6Cnt > EnemyBulletNum)
    {
        Bullet6Cnt = 0;
    }
}

void Bullet7Add(float x, float y)
{
    float v;          //正規化用変数
    Bullet7[Bullet7Cnt].shotflg = true;                         //生存フラグ
    Bullet7[Bullet7Cnt].x = x;                     //座標ｘ
    Bullet7[Bullet7Cnt].y = y;                             //座標ｙ
    Bullet7[Bullet7Cnt].vx = PlyHit.worldLX - Bullet7[Bullet7Cnt].x;                    //加速度x
    Bullet7[Bullet7Cnt].vy = PlyHit.worldLY - Bullet7[Bullet7Cnt].y;                    //加速度y
    Bullet7[Bullet7Cnt].speed = 3;                              //速度
    v = sqrt(Bullet7[Bullet7Cnt].vx * Bullet7[Bullet7Cnt].vx + Bullet7[Bullet7Cnt].vy * Bullet7[Bullet7Cnt].vy);//正規化

    Bullet7[Bullet7Cnt].vx = (Bullet7[Bullet7Cnt].vx / v) * Bullet7[Bullet7Cnt].speed;      //加速度x
    Bullet7[Bullet7Cnt].vy = (Bullet7[Bullet7Cnt].vy / v) * Bullet7[Bullet7Cnt].speed;      //加速度y
    //配列カウントの増加
    Bullet7Cnt++;
    //配列のカウントが最大値になったら初期化
    if (Bullet7Cnt > EnemyBulletNum)
    {
        Bullet7Cnt = 0;
    }
}

void Bullet8Add(float x, float y)
{
    float v;          //正規化用変数
    Bullet8[Bullet8Cnt].shotflg = true;                         //生存フラグ
    Bullet8[Bullet8Cnt].x = x;                     //座標ｘ
    Bullet8[Bullet8Cnt].y = y;                             //座標ｙ
    Bullet8[Bullet8Cnt].vx = PlyHit.worldLX - Bullet8[Bullet8Cnt].x;                    //加速度x
    Bullet8[Bullet8Cnt].vy = PlyHit.worldLY - Bullet8[Bullet8Cnt].y;                    //加速度y
    Bullet8[Bullet8Cnt].speed = 3;                              //速度
    v = sqrt(Bullet8[Bullet8Cnt].vx * Bullet8[Bullet8Cnt].vx + Bullet8[Bullet8Cnt].vy * Bullet8[Bullet8Cnt].vy);//正規化

    Bullet8[Bullet8Cnt].vx = (Bullet8[Bullet8Cnt].vx / v) * Bullet8[Bullet8Cnt].speed;      //加速度x
    Bullet8[Bullet8Cnt].vy = (Bullet8[Bullet8Cnt].vy / v) * Bullet8[Bullet8Cnt].speed;      //加速度y
    //配列カウントの増加
    Bullet8Cnt++;
    //配列のカウントが最大値になったら初期化
    if (Bullet8Cnt > EnemyBulletNum)
    {
        Bullet8Cnt = 0;
    }
}

void Bullet9Add(double x, double y)
{
    for (int i = 0; i < 360; i++)
    {
        if (i % 15 == 0)
        {
            Bullet9[Bullet9Cnt].shotflg = true;                        //生存フラグ
            Bullet9[Bullet9Cnt].x = x;                                  //発射する中心座標座標ｘ
            Bullet9[Bullet9Cnt].y = y;                                  //発射する中心座標座標y
            Bullet9[Bullet9Cnt].speed = 3;                              //速度
            ChangeRadian(Bullet9, EnemyBulletNum, Bullet9Cnt, i + Bullet4AngleCnt);                //角度(ラジアン)
            Bullet9[Bullet9Cnt].vx = cos(Bullet9[Bullet9Cnt].angle) * Bullet9[Bullet9Cnt].speed;    //加速度x
            Bullet9[Bullet9Cnt].vy = sin(Bullet9[Bullet9Cnt].angle) * Bullet9[Bullet9Cnt].speed;    //加速度y
            //配列カウントの増加
            Bullet9Cnt++;
            //配列のカウントが最大値になったら初期化
            if (Bullet4Cnt > EnemyBulletNum)
            {
                Bullet4Cnt = 0;
            }
        }
    }
    //アングルカウントの追加(バレット4から流用)
    Bullet4AngleCnt += 10;
}

void EnemyBulletMove(EnemyBullet Bullet[], int size, int widh, int height)
{
    for (int i = 0; i < EnemyBulletNum; i++)
    {
        if (Bullet[i].shotflg == true)
        {
            Bullet[i].x += Bullet[i].vx;
            Bullet[i].y += Bullet[i].vy;
            //画面外で消滅
            if (Bullet[i].x < -height || Bullet[i].y + widh >= WindowMaxY - height || Bullet[i].x + widh >= GameWindowX2 || Bullet[i].x <= GameWindowX1)
            {
                Bullet[i].shotflg = false;
            }
        }
    }
}

void EnemyBulletMove5(EnemyBullet5 Bullet[], int size, int widh, int height)
{
    for (int i = 0; i < EnemyBulletNum; i++)
    {
        if (Bullet[i].shotflg == true)
        {
            Bullet[i].x += Bullet[i].vx;
            Bullet[i].y += Bullet[i].vy;
            //矩形の更新
            Bullet5[i].lx += Bullet[i].vx;
            Bullet5[i].ly += Bullet[i].vy;
            Bullet5[i].rx += Bullet[i].vx;
            Bullet5[i].ry += Bullet[i].vy;
            //画面外で消滅
            if (Bullet[i].x < -height || Bullet[i].y + widh >= WindowMaxY - height || Bullet[i].x + widh >= GameWindowX2 || Bullet[i].x <= GameWindowX1)
            {
                Bullet[i].shotflg = false;
            }
        }
    }

}

void BulletDraw()
{
    EnemyBulletDraw(Bullet1, EnemyBulletNum, Bullet1Img);
    EnemyBulletDraw(Bullet2, EnemyBulletNum, Bullet2Img);
    EnemyBulletDraw(Bullet3, EnemyBulletNum, Bullet1Img);
    EnemyBulletDraw(Bullet4, EnemyBulletNum, Bullet4Img);
    EnemyBulletDraw2(Bullet5, EnemyBulletNum, Bullet5Img);
    EnemyBulletDraw(Bullet6, EnemyBulletNum, Bullet1Img);
    EnemyBulletDraw(Bullet7, EnemyBulletNum, Bullet1Img);
    EnemyBulletDraw(Bullet8, EnemyBulletNum, Bullet1Img);
    EnemyBulletDraw(Bullet9, EnemyBulletNum, Bullet4Img);
}

void EnemyBulletReset()
{
    //すべてのバレットフラグを下ろす
    {
        for (int i = 0; i < EnemyBulletNum; i++)
        {
            Bullet1[i].shotflg = false;
            Bullet2[i].shotflg = false;
            Bullet3[i].shotflg = false;
            Bullet4[i].shotflg = false;
            Bullet5[i].shotflg = false;
            Bullet6[i].shotflg = false;
            Bullet7[i].shotflg = false;
            Bullet8[i].shotflg = false;
            Bullet9[i].shotflg = false;
        }
    }
}

void EnemyDisappear(int& frame)
{
    EnemySurvivalFlg = false;
    //移動音
    //PlaySoundMem(EnemySound3, DX_PLAYTYPE_BACK);
    //撃破サウンド
    PlaySoundMem(DownSE, DX_PLAYTYPE_BACK);
    //フレームを初期化
    frame = 0;
    ShieldFlg = false;
    //エフェクトカウント初期化
    PlyEfectCnt = 0;
    PlyEfectFlg = false;
    //プレイヤーのボム計測タイム初期化
    BombTime = 0;
}

void DownMotion(int frame)
{
    EnemyMoveX = 0;
    EnemyMoveY = 0;
    if (frame <= EnemyDownTime + 120)
    {
        if (frame % 10 == 0)
        {
            if (EnemySurvivalFlg == false)
            {
                EnemySurvivalFlg = true;
            }
            else
            {
                EnemySurvivalFlg = false;
            }
        }

        if (frame % 30 == 0)
        {
            //爆発音再生
            PlaySoundMem(EnemyBombSound, DX_PLAYTYPE_BACK);
        }
    }
    else
    {
        //リザルトフラグを立てる
        ResultChangeFlg = true;
    }   
}