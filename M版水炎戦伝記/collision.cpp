#include "DxLib.h"
#include"player.h"
#include"collision.h"
#include"player.h"
#include"enemy.h"
#include"stage.h"

extern bool EnemySurvivalFlg;						//�G�̐����t���O(�O���[�o���ϐ�)
extern int DeathTime;								//�v���C���[�̎��S���̃t���[��(�O���[�o���ϐ�)
extern double PlayCharaX;                           //�v���C���[��x���W(�O���[�o���ϐ�)
extern double PlayCharaY;                           //�v���C���[��y���W(�O���[�o���ϐ�)

extern bool UpItemFlg;								//�p���[�A�b�v�A�C�e���̐����t���O(�O���[�o���ϐ�)
extern int UpItemX, UpItemY;						//�p���[�A�b�v�A�C�e���̍��Wx,y(�O���[�o���ϐ�)
extern int BombItemX, BombItemY;					//�{���̍��Wx,y(�O���[�o���ϐ�)
extern bool BombItemFlg;							//�{���̐����t���O(�O���[�o���ϐ�)

extern int PlayLife;                                //�v���C���[�̃��C�t��(�O���[�o���ϐ�)
extern int PlayBomb;                                //�v���C���[�̃{����(�O���[�o���ϐ�)
extern int ShotLevel;                               //�v���C���[�̒e�����x��(�O���[�o���ϐ�)
extern int GetSound;                                //�A�C�e���l�����̃T�E���h(�O���[�o���ϐ�)

extern int EnemyHp[HpGauge];   //�GHP�̔z��(3�Q�[�W��)(�O���[�o���ϐ�)
extern int LifeCnt;            //�GHP�̃J�E���g(�O���[�o���ϐ�)

extern float HitCircleX;     //x
extern float HitCircleY;     //y

extern int frame;                           //�t���[��
extern bool BuffEffectFlg;					//�G�t�F�N�g�t���O(�O���[�o���ϐ�)

void PlyinitRect(sHitRect& Rect, float w, float h, float CenterPointX, float CenterPointY)
{
    //�����蔻��̃s�N�Z����
    Rect.w = w;
    Rect.h = h;
    //�q�b�g�T�[�N����`����A�����̍��W,���S���W
    Rect.worldLX = CenterPointX - (w / 2);                  //�q�b�g�T�[�N���̍��゘
    Rect.worldLY = CenterPointY - (h / 2);                  //�q�b�g�T�[�N���̍��゙
    Rect.worldRX = CenterPointX + (w / 2);                  //�q�b�g�T�[�N���݂̂�������
    Rect.worldRY = CenterPointY + (h / 2);                  //�q�b�g�T�[�N���̉E����
    Rect.CenterX = Rect.worldLX + ((Rect.worldRX - Rect.worldLX) / 2);//�q�b�g�T�[�N���̃Z���^�[��
    Rect.CenterY = Rect.worldLY + ((Rect.worldRY - Rect.worldLY) / 2);//�q�b�g�T�[�N���̃Z���^�[��
}

void EnemyInitRect(sHitRect& Rect, float w, float h, float EnemyX, float EnemyY)
{
    //�����蔻��̃s�N�Z����
    Rect.w = w;
    Rect.h = h;
    //�q�b�g�{�b�N�X����A�����̍��W
    Rect.worldLX = EnemyX + 20;             //�q�b�g�{�b�N�̍��゘
    Rect.worldLY = EnemyY;                  //�q�b�g�{�b�N�̍��゙
    Rect.worldRX = EnemyX + 130;            //�q�b�g�{�b�N�X�̉E����
    Rect.worldRY = EnemyY + h;              //�q�b�g�{�b�N�X�̉E��y
}

void PlyRectUpdate(sHitRect& Rect, float CenterPointX, float CenterPointY)
{
    //�q�b�g�T�[�N����`����A�����̍��W�̍X�V
    Rect.worldLX = CenterPointX - (Rect.w / 2);
    Rect.worldLY = CenterPointY - (Rect.h / 2);
    Rect.worldRX = CenterPointX + (Rect.w / 2);
    Rect.worldRY = CenterPointY + (Rect.h / 2);
}


void EnemyRectUpdate(sHitRect& Rect, double EnemyX, double EnemyY)
{
    //�q�b�g�{�b�N�X����A�����̍��W�̍X�V
    Rect.worldLX = EnemyX;                     
    Rect.worldLY = EnemyY;                      
    Rect.worldRX = EnemyX + EnemySizeX;         
    Rect.worldRY = EnemyY + Rect.h;             
}


bool EnemyCollisionJudge(sHitRect PlyRect, sHitRect EnemyRect)
{
        if (EnemySurvivalFlg == true)
        {
            if (PlyRect.worldLX >= EnemyRect.worldLX && PlyRect.worldLX <= EnemyRect.worldRX || PlyRect.worldRX >= EnemyRect.worldLX && PlyRect.worldRX <= EnemyRect.worldRX)      //x���W�̏Փˊm�F
            {
                if (PlyRect.worldLY >= EnemyRect.worldLY && PlyRect.worldLY <= EnemyRect.worldRY || PlyRect.worldRY >= EnemyRect.worldLY && PlyRect.worldRY <= EnemyRect.worldRY)  //y���W�̏Փˊm�F
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
                if (playerBullet[i].x >= EnemyHit.worldLX && playerBullet[i].x <= EnemyHit.worldRX)     //x���W�̏Փˊm�F
                {
                    if (playerBullet[i].y >= EnemyHit.worldLY && playerBullet[i].y <= EnemyHit.worldRY)  //y���W�̏Փˊm�F
                    {
                        playerBullet[i].shotflg = false;  //���������狅������
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
                if (playerBullet[i].x >= EnemyHit.worldLX && playerBullet[i].x <= EnemyHit.worldRX)     //x���W�̏Փˊm�F
                {
                    if (playerBullet[i].y >= EnemyHit.worldLY && playerBullet[i].y <= EnemyHit.worldRY)  //y���W�̏Փˊm�F
                    {
                        playerBullet[i].shotflg = false;  //���������狅������
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
                    Bullet[i].shotflg = false;  //���������狅������
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
                    Bullet[i].shotflg = false;  //���������狅������
                    return true;
                }
            }
        }
    }
    
    return false;
}

void ItemCollision()
{
    //�p���[�A�C�e���̔���
    if (UpItemFlg == true)
    {
        if (UpItemX >= PlayCharaX && UpItemX <= PlayCharaX + PlaySize)
        {
            if (UpItemY >= PlayCharaY && UpItemY <= PlayCharaY + PlaySize)
            {
                //�t���O�����낷
                UpItemFlg = false;
                //�V���b�g���x������
                ShotLevel++;
                //�l���T�E���h�Đ�
                PlaySoundMem(GetSound, DX_PLAYTYPE_BACK);
                //�G�t�F�N�g�t���O�����Ă�
                BuffEffectFlg = true;
            }
        }
    }
    //�{���̔���
    if ( BombItemFlg == true)
    {
        if (BombItemX >= PlayCharaX && BombItemX <= PlayCharaX + PlaySize)
        {
            if (BombItemY >= PlayCharaY && BombItemY <= PlayCharaY + PlaySize)
            {
                //�t���O�����낷
                BombItemFlg = false;
                //�{������
                PlayBomb++;
                //�l���T�E���h�Đ�
                PlaySoundMem(GetSound, DX_PLAYTYPE_BACK);
            }
        }
    }
}