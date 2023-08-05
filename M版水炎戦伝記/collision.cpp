#include "DxLib.h"
#include"player.h"
#include"collision.h"
#include"player.h"
#include"enemy.h"
#include"stage.h"

extern bool EnemySurvivalFlg;						//敵の生存フラグ(グローバル変数)
extern int DeathTime;								//プレイヤーの死亡時のフレーム(グローバル変数)
extern double PlayCharaX;                           //プレイヤーのx座標(グローバル変数)
extern double PlayCharaY;                           //プレイヤーのy座標(グローバル変数)

extern bool UpItemFlg;								//パワーアップアイテムの生存フラグ(グローバル変数)
extern int UpItemX, UpItemY;						//パワーアップアイテムの座標x,y(グローバル変数)
extern int BombItemX, BombItemY;					//ボムの座標x,y(グローバル変数)
extern bool BombItemFlg;							//ボムの生存フラグ(グローバル変数)

extern int PlayLife;                                //プレイヤーのライフ数(グローバル変数)
extern int PlayBomb;                                //プレイヤーのボム数(グローバル変数)
extern int ShotLevel;                               //プレイヤーの弾幕レベル(グローバル変数)
extern int GetSound;                                //アイテム獲得時のサウンド(グローバル変数)

extern int EnemyHp[HpGauge];   //敵HPの配列(3ゲージ分)(グローバル変数)
extern int LifeCnt;            //敵HPのカウント(グローバル変数)

extern float HitCircleX;     //x
extern float HitCircleY;     //y

extern int frame;                           //フレーム
extern bool BuffEffectFlg;					//エフェクトフラグ(グローバル変数)

void PlyinitRect(sHitRect& Rect, float w, float h, float CenterPointX, float CenterPointY)
{
    //当たり判定のピクセル数
    Rect.w = w;
    Rect.h = h;
    //ヒットサークル矩形左上、左下の座標,中心座標
    Rect.worldLX = CenterPointX - (w / 2);                  //ヒットサークルの左上ｘ
    Rect.worldLY = CenterPointY - (h / 2);                  //ヒットサークルの左上ｙ
    Rect.worldRX = CenterPointX + (w / 2);                  //ヒットサークルのみぎしたｘ
    Rect.worldRY = CenterPointY + (h / 2);                  //ヒットサークルの右下ｙ
    Rect.CenterX = Rect.worldLX + ((Rect.worldRX - Rect.worldLX) / 2);//ヒットサークルのセンターｘ
    Rect.CenterY = Rect.worldLY + ((Rect.worldRY - Rect.worldLY) / 2);//ヒットサークルのセンターｙ
}

void EnemyInitRect(sHitRect& Rect, float w, float h, float EnemyX, float EnemyY)
{
    //当たり判定のピクセル数
    Rect.w = w;
    Rect.h = h;
    //ヒットボックス左上、左下の座標
    Rect.worldLX = EnemyX + 20;             //ヒットボックの左上ｘ
    Rect.worldLY = EnemyY;                  //ヒットボックの左上ｙ
    Rect.worldRX = EnemyX + 130;            //ヒットボックスの右下ｘ
    Rect.worldRY = EnemyY + h;              //ヒットボックスの右下y
}

void PlyRectUpdate(sHitRect& Rect, float CenterPointX, float CenterPointY)
{
    //ヒットサークル矩形左上、左下の座標の更新
    Rect.worldLX = CenterPointX - (Rect.w / 2);
    Rect.worldLY = CenterPointY - (Rect.h / 2);
    Rect.worldRX = CenterPointX + (Rect.w / 2);
    Rect.worldRY = CenterPointY + (Rect.h / 2);
}


void EnemyRectUpdate(sHitRect& Rect, double EnemyX, double EnemyY)
{
    //ヒットボックス左上、左下の座標の更新
    Rect.worldLX = EnemyX;                     
    Rect.worldLY = EnemyY;                      
    Rect.worldRX = EnemyX + EnemySizeX;         
    Rect.worldRY = EnemyY + Rect.h;             
}


bool EnemyCollisionJudge(sHitRect PlyRect, sHitRect EnemyRect)
{
        if (EnemySurvivalFlg == true)
        {
            if (PlyRect.worldLX >= EnemyRect.worldLX && PlyRect.worldLX <= EnemyRect.worldRX || PlyRect.worldRX >= EnemyRect.worldLX && PlyRect.worldRX <= EnemyRect.worldRX)      //x座標の衝突確認
            {
                if (PlyRect.worldLY >= EnemyRect.worldLY && PlyRect.worldLY <= EnemyRect.worldRY || PlyRect.worldRY >= EnemyRect.worldLY && PlyRect.worldRY <= EnemyRect.worldRY)  //y座標の衝突確認
                {
                    return true;
                }
            }
            return false;
        }
}

bool PlyBulletCollision(shot playerBullet[], int size, sHitRect EnemyHit)
{
    if (EnemySurvivalFlg == true)
    {
        for (int i = 0; i < PShotNum; i++)
        {
            if (playerBullet[i].shotflg == true)
            {
                if (playerBullet[i].x >= EnemyHit.worldLX && playerBullet[i].x <= EnemyHit.worldRX)     //x座標の衝突確認
                {
                    if (playerBullet[i].y >= EnemyHit.worldLY && playerBullet[i].y <= EnemyHit.worldRY)  //y座標の衝突確認
                    {
                        playerBullet[i].shotflg = false;  //当たったら球を消す
                        EnemyHp[LifeCnt] -= PlayerDamage;
                        return true;
                    }
                }
            }
        }
        return false;
    }
}

void PlyBulletCollision2(shot playerBullet[], int size, sHitRect EnemyHit)
{
    if (EnemySurvivalFlg == true)
    {
        for (int i = 0; i < PShotNum; i++)
        {
            if (playerBullet[i].shotflg == true)
            {
                if (playerBullet[i].x >= EnemyHit.worldLX && playerBullet[i].x <= EnemyHit.worldRX)     //x座標の衝突確認
                {
                    if (playerBullet[i].y >= EnemyHit.worldLY && playerBullet[i].y <= EnemyHit.worldRY)  //y座標の衝突確認
                    {
                        playerBullet[i].shotflg = false;  //当たったら球を消す
                        EnemyHp[LifeCnt] -= PlayerDamage;
                    }
                }
            }
        }
    }
}

bool EnemyBullet1Collision(sHitRect PlyRect, EnemyBullet Bullet[], int size)
{
    for (int i = 0; i < EnemyBulletNum; i++)
    {
        if (Bullet[i].shotflg == true)
        {
            if (Bullet[i].x >= PlyRect.worldLX && Bullet[i].x <= PlyRect.worldRX || Bullet[i].x + Bullet1Widh >= PlyRect.worldLX && Bullet[i].x + Bullet1Widh <= PlyRect.worldRX)
            {
                if (Bullet[i].y >= PlyRect.worldLY && Bullet[i].y <= PlyRect.worldRY || Bullet[i].y + Bullet1Widh >= PlyRect.worldLY && Bullet[i].y + Bullet1Widh <= PlyRect.worldRY)
                {
                    Bullet[i].shotflg = false;  //当たったら球を消す
                    return true;
                }
            }
        }
    }
    return false;
}

bool EnemyBullet15Collision(sHitRect PlyRect, EnemyBullet5 Bullet[], int size)
{
    for (int i = 0; i < EnemyBulletNum; i++)
    {
        if (Bullet[i].shotflg == true)
        {
            if (Bullet[i].lx >= PlyRect.worldLX && Bullet[i].lx <= PlyRect.worldRX || Bullet[i].rx >= PlyRect.worldLX && Bullet[i].rx <= PlyRect.worldRX)
            {
                if (Bullet[i].ly >= PlyRect.worldLY && Bullet[i].ly <= PlyRect.worldRY || Bullet[i].ry >= PlyRect.worldLY && Bullet[i].ry <= PlyRect.worldRY)
                {
                    Bullet[i].shotflg = false;  //当たったら球を消す
                    return true;
                }
            }
        }
    }
    
    return false;
}

void ItemCollision()
{
    //パワーアイテムの判定
    if (UpItemFlg == true)
    {
        if (UpItemX >= PlayCharaX && UpItemX <= PlayCharaX + PlaySize)
        {
            if (UpItemY >= PlayCharaY && UpItemY <= PlayCharaY + PlaySize)
            {
                //フラグを下ろす
                UpItemFlg = false;
                //ショットレベル増加
                ShotLevel++;
                //獲得サウンド再生
                PlaySoundMem(GetSound, DX_PLAYTYPE_BACK);
                //エフェクトフラグをたてる
                BuffEffectFlg = true;
            }
        }
    }
    //ボムの判定
    if ( BombItemFlg == true)
    {
        if (BombItemX >= PlayCharaX && BombItemX <= PlayCharaX + PlaySize)
        {
            if (BombItemY >= PlayCharaY && BombItemY <= PlayCharaY + PlaySize)
            {
                //フラグを下ろす
                BombItemFlg = false;
                //ボム増加
                PlayBomb++;
                //獲得サウンド再生
                PlaySoundMem(GetSound, DX_PLAYTYPE_BACK);
            }
        }
    }
}