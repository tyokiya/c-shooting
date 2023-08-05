#include <math.h>
#include "DxLib.h"
#include"player.h"
#include"collision.h"
#include"stage.h"
#include"SoundLoad.h"
#include"enemy.h"
#include"effect.h"

//変数宣言
int PlayCharaImg[CharaPatarn];//キャラクターの配列
int LifeImg;                 //プレイヤーライフのイメージ画像
int BombImg;                 //プレイヤーボムのイメージ画像
double PlayCharaX;   //プレイヤーのx座標
double PlayCharaY;   //プレイヤーのy座標
int PlayLife;       //プレイヤーのライフ数
int PlayBomb;       //プレイヤーのボム数
int PlayFlg;      //プレイヤー画像のの配列番号のフラグ
double DefoSpeed;            //デフォルトの速度
double SlowSpeed;            //スローモードの速度
float PlyHitSizeX = 15;      //当たり判定サイズ幅
float PlyHitSizeY = 15;      //当たり判定サイズ高さ
int DeathTime;           //死亡時のフレーム
int ShotLevel;           //プレイヤーの弾幕レベル
int LifeTextImg, BombTextImg;//テキスト画像ハンドル

sHitRect PlyHit;      //自機のヒット判定構造体

shot playershot[PShotNum];//プレイヤーの弾の構造体配列
shot playershot2[PShotNum];
shot playershot3[PShotNum];
int ShotCnt = 0;            //弾の配列番号を指すカウント
int ShotCnt2 = 0;
int ShotCnt3 = 0;
int playershotImg;          //弾の画像ハンドル
int ShieldImg;              //シールドの画像ハンドル

//当たり判定サークルの中心座標
float HitCircleX;     //x
float HitCircleY;     //y
int CircleColor;        //円の色
int CircleColor2;
int FontColor;          //フォントの色

//音関連
int PlayerShotSound;            //サウンドハンドル
int BombSound;                  //ボム発動時のサウンド
int GetSound;                   //アイテムの獲得サウンドハンドル
int DamageSound;                //被弾サウンドハンドル

//コントローラー
int PadInput;

int BombTime;                   //ボム発動時の時間計測

//エフェクトのグローバル変数
extern int PlyEfect1[11], PlyRevivalEffect[10];

int PlyEfectCnt,RevivalCnt;     //エフェクトカウント
bool PlyEfectFlg, RevivalFlg;       //エフェクトフラグ

void PlayerInit()
{
    PlayCharaImg[0] = LoadGraph("image/player1(100).png");   //左向き
    PlayCharaImg[1] = LoadGraph("image/player2(100).png");   //右向き
    LifeImg = LoadGraph("image/heart.png");                  //ライフ画像の読み込み
    BombImg = LoadGraph("image/star.png");                   //ボム画像読み込み
    ShieldImg = LoadGraph("image/foam.png");                 //シールド画像の読み込み
    LifeTextImg = LoadGraph("image/LifeText.png");
    BombTextImg = LoadGraph("image/BombText.png");

    PlayFlg = 0;                    //フラグの初期化
    PlayCharaX = InitalPositionX;   //プレイヤーの初期x座標
    PlayCharaY = InitalPositionY;   //プレイヤーの初期y座標
    PlayLife = PlayInitalLife;      //プレイヤーのライフ設定
    PlayBomb = PlayInitalBomb;      //プレイヤーのボム設定 
         
    HitCircleX = PlayCharaX + PlaySize / 2 - 2;   //当たり判定の中心座標
    HitCircleY = PlayCharaY + PlaySize / 2 + 5;
    PlyinitRect(PlyHit, PlyHitSizeX, PlyHitSizeY,HitCircleX,HitCircleY);   //プレイヤーの当たり判定構造体設定
    CircleColor = GetColor(139, 0, 0);    //白色
    CircleColor2 = GetColor(211, 211, 211);    //赤色
    FontColor = GetColor(238, 130, 238);        //ピンク色

    DeathTime = 0;           //死亡時のフレーム
    ShotLevel = 1;           //プレイヤーの弾幕レベル
    BombTime = 0;

    PlyEfectCnt, RevivalCnt = 0;     //エフェクトカウント初期化
    //フラグ初期化
    PlyEfectFlg, RevivalFlg = false;


    //プレイヤーの弾初期化
    PShotInit();

    //サウンド読み込み
    LoadPlySound();

    //エフェクトの初期化
    PlyEfectInit();
}

void PShotInit()
{
    for (int i = 0; i < PShotNum; i++)
    {
        playershot[i].shotflg = false;
        playershot[i].width = ShotWidth;
        playershot[i].height = ShotWidth;
        playershot2[i].shotflg = false;
        playershot2[i].width = ShotWidth;
        playershot2[i].height = ShotWidth;
        playershot3[i].shotflg = false;
        playershot3[i].width = ShotWidth;
        playershot3[i].height = ShotWidth;
    }
    playershotImg = LoadGraph("image/PlyShot.png");
}

void PlayerUpdate(int frame)
{
    //入力数のカウント
    int hitcnt = 0;

    //X軸の処理
    PadInput = GetJoypadInputState(DX_INPUT_KEY_PAD1);  //キーの読み込み

    //斜めに入力されてるかのカウント
    if ((PadInput & PAD_INPUT_RIGHT) != 0)
    {
            hitcnt++;
    }
    else if ((PadInput & PAD_INPUT_LEFT) != 0) //スローなしで押されてる場合
    {
            hitcnt++;
    }
    if ((PadInput & PAD_INPUT_UP) != 0)
    {
            hitcnt++;
    }
    else if ((PadInput & PAD_INPUT_DOWN) != 0 )
    {
            hitcnt++;
    }

    if (hitcnt == 1)//左右上下の速度設定
    {
        DefoSpeed = 5;            //デフォルトの速度
        SlowSpeed = 3;            //スローモードの速度
    }
    else if (hitcnt == 2)//斜めの速度
    {
        DefoSpeed = sqrt(50) / 2;            //デフォルトの速度
        SlowSpeed = sqrt(18) / 2;            //スローモードの速度
    }
    
    //右の増加
    if ((PadInput & PAD_INPUT_RIGHT) != 0 && (PadInput & PAD_INPUT_5) == 0) //スローなしで押されてる場合
    {
        if (PlayCharaX < GameWindowX2 - PlaySize + 15)
        {
            PlayCharaX += DefoSpeed;
            HitCircleX += DefoSpeed;
            PlayFlg = 1;
        }
    }
    else if ((PadInput & PAD_INPUT_RIGHT) != 0 && (PadInput & PAD_INPUT_5) != 0) //スローありで押されてる場合
    {
        if (PlayCharaX < GameWindowX2 - PlaySize + 15)
        {
            PlayCharaX += SlowSpeed;
            HitCircleX += SlowSpeed;
            PlayFlg = 1;
        }
    }
    //左の増加
    else if ((PadInput & PAD_INPUT_LEFT) != 0 && (PadInput & PAD_INPUT_5) == 0) //スローなしで押されてる場合
    {
        if (PlayCharaX > GameWindowX1 -15)
        {
            PlayCharaX -= DefoSpeed;
            HitCircleX -= DefoSpeed;
            PlayFlg = 0;
        }
    }
    else if ((PadInput & PAD_INPUT_LEFT) != 0 && (PadInput & PAD_INPUT_5) != 0) //スローありで押されてる場合
    {
        if (PlayCharaX > GameWindowX1 - 15)
        {
            PlayCharaX -= SlowSpeed;
            HitCircleX -= SlowSpeed;
            PlayFlg = 0;
        }
    }
    //Y軸の処理
    //上の増加
    if ((PadInput & PAD_INPUT_UP) != 0 && (PadInput & PAD_INPUT_5) == 0) //スローなしで押されてる場合
    {
        if (PlayCharaY > 0)
        {
            PlayCharaY -= DefoSpeed;
            HitCircleY -= DefoSpeed;
        }
    }
    else if ((PadInput & PAD_INPUT_UP) != 0 && (PadInput & PAD_INPUT_5) != 0) //スローありで押されてる場合
    {
        if (PlayCharaY > 0)
        {
            PlayCharaY -= SlowSpeed;
            HitCircleY -= SlowSpeed;
        }
    }
    //下の増加
    else if ((PadInput & PAD_INPUT_DOWN) != 0 && (PadInput & PAD_INPUT_5) == 0) //スローなしで押されてる場合
    {
        if (PlayCharaY < GameWindowY - PlaySize - 8)
        {
            PlayCharaY += DefoSpeed;
            HitCircleY += DefoSpeed;
        }
    }
    else if ((PadInput & PAD_INPUT_DOWN) != 0 && (PadInput & PAD_INPUT_5) != 0) //スローありで押されてる場合
    {
        if (PlayCharaY < GameWindowY - PlaySize - 8)
        {
            PlayCharaY += SlowSpeed;
            HitCircleY += SlowSpeed;
        }
    }

    //当たり判定の更新
    PlyRectUpdate(PlyHit, HitCircleX, HitCircleY);

    //aボタンが押されたら弾を発射(3フレームに一発)
    if ((PadInput & PAD_INPUT_3) != 0 && frame % 3 == 0 && frame != 0)
    {
        ShotAddition();
        if (ShotCnt == PShotNum)
        {
            ShotCnt = 0;//カウント初期化
        }
        if (ShotCnt2 == PShotNum)
        {
            ShotCnt2 = 0;//カウント初期化
        }
        if (ShotCnt3 == PShotNum)
        {
            ShotCnt3 = 0;//カウント初期化
        }
        //ショット音の再生
        PlaySoundMem(PlayerShotSound, DX_PLAYTYPE_BACK);
    }

    //R1のキー入力確認
    if ((PadInput & PAD_INPUT_6) != 0 && PlayBomb > 0)
    {
        //前回のボム発動から1秒以上経過したかの確認
        if (frame >= BombTime + 60)
        {
            //ボムの発動
            EnemyBulletReset();
            //ボムの個数を減らす
            PlayBomb--;
            //ボムの時間計測
            BombTime = frame;
            //サウンドの再生
            PlaySoundMem(BombSound, DX_PLAYTYPE_BACK);
            //エフェクトフラグを立てる
            PlyEfectFlg = true;
        }
    }
    
    //エフェクトの描画
    if (PlyEfectFlg == true)
    {
        EfectDraw(PlyEfect1, PlyEfectCnt, HitCircleX, HitCircleY, 1.0);
    }
    //エフェクトフラグが立っているかの確認
    if (PlyEfectFlg == true && frame % 5 == 0)
    {
        //カウントの追加
        EffectCountCheck(PlyEfectCnt, PlyEfectFlg, 11);
    }
    
    //復活エフェクトが立っているかの確認
    if (RevivalFlg == true && frame % 5 == 0)
    {
        //カウントの追加
        EffectCountCheck(RevivalCnt, RevivalFlg, 10);
    }
    ShotMove();
}

void ShotAddition()
{
    //ショットレベル１
    if (ShotLevel == 1)
    {
        playershot[ShotCnt].shotflg = true;
        //弾が射出される座標
        playershot[ShotCnt].x = PlayCharaX + 40;
        playershot[ShotCnt].y = PlayCharaY - 10;
        ShotCnt++;
    }
    //ショットレベル2
    if (ShotLevel == 2)
    {
        playershot[ShotCnt].shotflg = true;
        //弾が射出される座標
        playershot[ShotCnt].x = PlayCharaX + 40;
        playershot[ShotCnt].y = PlayCharaY - 10;
        ShotCnt++;
        playershot2[ShotCnt2].shotflg = true;
        //弾が射出される座標
        playershot2[ShotCnt2].x = PlayCharaX + 40;
        playershot2[ShotCnt2].y = PlayCharaY - 10;
        ShotCnt2++;
        playershot3[ShotCnt3].shotflg = true;
        //弾が射出される座標
        playershot3[ShotCnt3].x = PlayCharaX + 40;
        playershot3[ShotCnt3].y = PlayCharaY - 10;
        ShotCnt3++;
    }
    
}

void PlayerDraw()
{
    DrawGraph(PlayCharaX,PlayCharaY, PlayCharaImg[PlayFlg], TRUE);
    //ヒットサークルの描写
    DrawCircle(HitCircleX, HitCircleY, Radius, CircleColor2, TRUE);
    DrawCircle(HitCircleX, HitCircleY, Radius, CircleColor, FALSE,4);
    //ヒットボックス描画
    //DrawLine(PlyHit.worldLX, PlyHit.worldLY, PlyHit.worldLX + PlyHit.w, PlyHit.worldLY, GetColor(255, 0, 0));
    //DrawLine(PlyHit.worldRX, PlyHit.worldRY, PlyHit.worldRX - PlyHit.w, PlyHit.worldRY, GetColor(255, 0, 0));
}

void ShieldDraw()
{
    DrawExtendGraph(PlayCharaX, PlayCharaY, PlayCharaX + 100, PlayCharaY + 100, ShieldImg, true);
}

void StatusDraw()
{
    SetFontSize(35);
    //ライフの表示
    DrawExtendGraph(995, 190, 1155, 250, LifeTextImg, TRUE);
    //DrawString(1010, 200, "Player", FontColor);
    for (int l = 0; l < PlayLife; l++)
    {
        DrawExtendGraph((l * 35) + 1000, 225, (l * 35) + 1050, 275, LifeImg, true);
    }
    //ボム表示
    //DrawString(1010, 280, "Bomb", FontColor);
    DrawExtendGraph(995, 270, 1155, 330, BombTextImg, TRUE);
    for (int b = 0; b < PlayBomb; b++)
    {
        DrawExtendGraph((b * 40) + 1000, 310, (b * 40) + 1050, 360, BombImg, true);
    }
}

void ShotMove()
{
    for (int i = 0; i < PShotNum; i++)
    {
        if (playershot[i].shotflg == true)
        {
            //弾の移動
            playershot[i].y -= ShotSpeed;
            if (playershot[i].y < -10)
            {
                //画面外に出たらフラグを下す
                playershot[i].shotflg = false;
            }
        }
        if (playershot2[i].shotflg == true)
        {
            //弾の移動
            playershot2[i].y -= ShotSpeed;
            playershot2[i].x -= 1;
            if (playershot2[i].y < -10 || playershot2[i].x < 40 || playershot2[i].x + ShotWidth > 1000)
            {
                //画面外に出たらフラグを下す
                playershot2[i].shotflg = false;
            }
        }
        if (playershot3[i].shotflg == true)
        {
            //弾の移動
            playershot3[i].y -= ShotSpeed;
            playershot3[i].x += 1;
            if (playershot3[i].y < -10 || playershot3[i].x < 40 || playershot3[i].x + ShotWidth > 1000)
            {
                //画面外に出たらフラグを下す
                playershot3[i].shotflg = false;
            }
        }
    }
}

void ShotDisplay()
{
    for (int i = 0; i < PShotNum; i++)
    {
        if (playershot[i].shotflg == true)
        {
            DrawExtendGraph(playershot[i].x, playershot[i].y, playershot[i].x + playershot[i].width, playershot[i].y + playershot[i].height, playershotImg, true);
        }
        if (playershot2[i].shotflg == true)
        {
            DrawExtendGraph(playershot2[i].x, playershot2[i].y, playershot2[i].x + playershot2[i].width, playershot2[i].y + playershot2[i].height, playershotImg, true);
        }
        if (playershot3[i].shotflg == true)
        {
            DrawExtendGraph(playershot3[i].x, playershot3[i].y, playershot3[i].x + playershot3[i].width, playershot3[i].y + playershot3[i].height, playershotImg, true);
        }
    }
}


void PlyHitEffect(int frame)
{
    PlayLife--;     //ライフの減少
    //初期位置への移動
    PlayCharaX = InitalPositionX;
    PlayCharaY = InitalPositionY;
    //当たり判定の中心座標
    HitCircleX = PlayCharaX + PlaySize / 2 - 2;   
    HitCircleY = PlayCharaY + PlaySize / 2 + 5;
    DeathTime = frame;
    PlayBomb = PlayInitalBomb;      //プレイヤーのボム再設定

    //被弾サウンド再生
    PlaySoundMem(DamageSound, DX_PLAYTYPE_BACK);

    //復活エフェクトフラグをたてる
    RevivalFlg = true;
}