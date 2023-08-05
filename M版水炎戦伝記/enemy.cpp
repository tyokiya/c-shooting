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

//�ϐ�
int EnemyImg;           //�G�̉摜
double EnemyX;          //�G��x���W
double EnemyY;          //�G��y���W
double EnemyMoveX;         //�G�̏c���ړ���
double EnemyMoveY;         ////�G�̉����ړ���
int EnemyHp[HpGauge];   //�GHP�̔z��(3�Q�[�W��)
int LifeCnt;            //�GHP�̃J�E���g
int Life0Color, Life1Color, Life2Color; //�e���C�t����hp�o�[�̐F
bool EnemySurvivalFlg;                  //�G�̐����t���O
int HpTextImg;                                  //�e�L�X�g�摜�n���h��

int Bullet4AngleCnt = 0;                        //�o���b�g�S�̃A���O���̒ǉ����J�E���g

float EnemyHitSizeX = 100;      //�G�̓����蔻��T�C�Y��(�摜�T�C�X��140)
float EnemyHitSizeY = 150;      //�G�̓����蔻��T�C�Y����

int DownX, DownY;               //�_�E�����̍��Wx

extern bool EnemyFlg;			//�G���o�ꂵ�Ă邩�̃t���O

//�e
EnemyBullet Bullet1[EnemyBulletNum];        //�����_���e
EnemyBullet Bullet2[EnemyBulletNum];        //���@�_���e
EnemyBullet Bullet3[EnemyBulletNum];        //�~�`�e
EnemyBullet Bullet4[EnemyBulletNum];
EnemyBullet5 Bullet5[EnemyBulletNum];       //�c���e
EnemyBullet Bullet6[EnemyBulletNum];         //�ǂ���̔���
EnemyBullet Bullet7[EnemyBulletNum];         //���@�w����̎��@�_��1
EnemyBullet Bullet8[EnemyBulletNum];         //���@�w����̎��@�_��2
EnemyBullet Bullet9[EnemyBulletNum];         //�G�̉~�`�e
EnemyBullet Bullet10[EnemyBulletNum];         //�G�̃����_���e

//�摜�n���h��
int Bullet1Img, Bullet2Img, Bullet3Img, Bullet4Img, Bullet5Img, Bullet6Img,Bullet7Img,Bullet8Img,Bullet9Img,Bullet10Img;             
int HitEfectImg;
int MeterImg;               //���[�^�[�t���[���̃C���[�W�n���h��

int Bullet1Cnt, Bullet2Cnt, Bullet3Cnt, Bullet4Cnt, Bullet5Cnt, Bullet6Cnt, Bullet7Cnt, Bullet8Cnt, Bullet9Cnt, Bullet10Cnt = 0;     //�e���̃J�E���g
int EnemyMoveSpeedX, EnemyMoveSpeedY;   //�G�̈ړ����x
bool Bullet2flg;                        //�o���b�g2�̃t���O
bool Atack2Flg;                 //�U��2�̃t���O
bool LifeFlg2;
bool LifeFlg3;
bool LifeFlg1;
bool AttackPattern3Flg;         //�U���p�^�[��3�̃t���O
bool MoveFlg;                   //�u�Ԉړ��̃t���O
bool MoveFlg2;
bool RightFlg, LeftFlg;  //���E�̈ړ��t���O
bool UpFlg, DownFlg;     //�㉺�̈ړ��t���O

bool LineFlg;                           //�G�̍U���ド�C���̃t���O
int LineFrame;                                  //�U���������̃t���[�������L������
int LineX1, LineY1, LineX2, LineY2;                               //�����������̈ꎞ�I�v���C���[���W�̋L���̈�

//�T�E���h�n���h��
int Bullet1Sound;       
int EnemySound1;
int EnemySound2;
int EnemySound3;        //�ړ���
int EnemySound4;
int EnemySound5;        //����
int EnemySound6;
int SordSound;          //���̉�
int DownSE;             //���j���̃T�E���h�n���h��
int EnemyBombSound;     //�G�̔����T�E���h�n���h��

sHitRect EnemyHit;      //�G�̃q�b�g����\����

int TextCnt;            //�\���e�L�X�g�̎��ʃJ�E���g

//�v���C���[���W�O���[�o���ϐ�
extern double PlayCharaX;   //�v���C���[��x���W
extern double PlayCharaY;   //�v���C���[��y���W
extern sHitRect PlyHit;		   //���@�̎��@�̃q�b�g����\����(�O���[�o���ϐ�)

//�v���C���[�̃G�t�F�N�g�O���[�o���ϐ�
extern int PlyEfect1[11];
extern int PlyEfectCnt;
extern bool PlyEfectFlg;

extern int BombTime;                   //�{���������̎��Ԍv��

//�G�t�F�N�g�O���[�o���ϐ�
extern int EmyJumpEffect[7];            //�G�̃W�����v�G�t�F�N�g
extern int EmyDownEffect[9];            //�G�̃_�E���G�t�F�N�g
extern int EmyShotEffect1[25];          //�G�̍U���G�t�F�N�g1
extern int EmySlashingEffect[10];       //�G�̎a���G�t�F�N�g
extern int MagicEffect1[30];            //���@�w�G�t�F�N�g1
extern int MagicEffect2[30];            //���@�w�G�t�F�N�g2
extern int MagicEffect3[16];            //���@�w�G�t�F�N�g3

int EmyJumpEfectCnt, DownEffectCnt, EmyShotEffect1Cnt,EmySlashingCnt,Magic1Cnt,Magic2Cnt,Magic3Cnt;            //�G�t�F�N�g�J�E���g
bool EmyJumpEfectFlg, DownEffectFlg,EmyShotEffect1Flg, EmySlashingFlg,Magic1Flg,Magic2Flg,Magic3Flg;           //�G�t�F�N�g�t���O

extern bool ShieldFlg;			//�V�[���h�t���O

extern bool ResultChangeFlg;			//���U���g�̐؂�ւ��t���O

int EnemyDownTime;                      //�G��|�����t���[����
int DownTimeFlg;

void EnemyInit()
{
    EnemyImg = LoadGraph("image/enemy1.png");     //�G�摜�̓ǂݍ���
    MeterImg = LoadGraph("image/meter.png");        //���[�^�[�摜�ǂݍ���
    EnemyX = InitEnemyX;        //�G�̏���x���W
    EnemyY = InitEnemyY;        //�G�̏���y���W
    //�GHP�̐ݒ�
    for (int i = 0; i < HpGauge; i++)
    {
        EnemyHp[i] = 1000;
    }
    EnemyInitRect(EnemyHit, EnemyHitSizeX, EnemyHitSizeY, EnemyX, EnemyY);      //�G�̓����蔻��\���̐ݒ�
    //���C�t�J�E���g�̏����ݒ�
    LifeCnt = 2;
    //HP�o�[�̐F�ݒ�
    Life0Color = GetColor(255, 0, 0);
    Life1Color = GetColor(0, 255, 0);
    Life2Color = GetColor(0, 255, 255);

    //�G�t�F�N�g�摜�̓ǂݍ���
    HitEfectImg = LoadGraph("image/efect.png");
    HpTextImg = LoadGraph("image/HPText.png");

    //�ړ��ʏ�����
    EnemyMoveX = 5;         //�G�̏c���ړ���
    EnemyMoveY = 2;         ////�G�̉����ړ���

    //�t���O������
    EnemySurvivalFlg = true;                  //�G�̐����t���O
    Atack2Flg = false;                 //�U��2�̃t���O
    LifeFlg2 = false;
    LifeFlg3 = false;
    LifeFlg1 = false;
    AttackPattern3Flg = true;         //�U���p�^�[��3�̃t���O
    MoveFlg = false;                   //�u�Ԉړ��̃t���O
    MoveFlg2 = false;
    RightFlg = false, LeftFlg = true;  //���E�̈ړ��t���O
    UpFlg = false, DownFlg = true;     //�㉺�̈ړ��t���O
    LineFlg = false;                           //�G�̍U���ド�C���̃t���O

    EnemyDownTime = 0;
    DownTimeFlg = false;

    EmyJumpEfectCnt, DownEffectCnt, EmyShotEffect1Cnt, EmySlashingCnt, Magic1Cnt, Magic2Cnt, Magic3Cnt = 0;     //�G�t�F�N�g�J�E���g
    EmyJumpEfectFlg, DownEffectFlg, EmyShotEffect1Flg, EmySlashingFlg, Magic1Flg, Magic2Flg, Magic3Flg = false;                   //�G�t�F�N�g�t���O

    //�G�̒e���̏�����
    EnemyBulletInit();

    //�T�E���h�n���h���ǂݍ���
    LoadEnemySound();

    //�G�t�F�N�g������
    EnemyEfectInit();
}

void EnemyBulletInit()
{
    //�t���O������
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
    Bullet5Img = LoadGraph("image/shot3.png");      //�c���e
    Bullet6Img = LoadGraph("image/shot3.png");
}

void EnemyDraw()
{
    if (EnemySurvivalFlg == true)
    {
        DrawGraph(EnemyX, EnemyY, EnemyImg, TRUE);
    }
    //�q�b�g�{�b�N�X�`��
    //DrawLine(EnemyHit.worldLX, EnemyHit.worldLY, EnemyHit.worldLX + EnemyHit.w, EnemyHit.worldLY, GetColor(255, 0, 0));
    //DrawLine(EnemyHit.worldRX, EnemyHit.worldRY, EnemyHit.worldRX - EnemyHit.w, EnemyHit.worldRY, GetColor(255, 0, 0));
}

void EnemyIn(bool& EnemyFlg)
{
    if (EnemyY < 0)
    {
        EnemyY++;   //���W�̒ǉ�
        TextCnt = 1;
    }
    else
    {
        //���W��0�𒴂������_�Ńt���O���𗧂Ă�
        EnemyFlg = true;
    }
}

void EnemyUpdate(int& frame)
{
    if (EnemyFlg == true)
    {
        //�e�L�X�g�J�E���g������
        TextCnt = 0;
    }
    //LifeCnt = 1;

    //�ړ��ʏ�����
    EnemyMoveSpeedX = 0;
    EnemyMoveSpeedY = 0;
    //�U��1
    if (LifeCnt == 2 && frame < 1550 && frame > 0)
    {
        //�����t���O�𗧂Ă�
        EnemySurvivalFlg == true;
        AttackPattern1(frame);
    }

    //�o���b�g1�̈ړ�
    EnemyBulletMove(Bullet1, EnemyBulletNum, Bullet1Widh, Bullet1Widh);
    //�o���b�g2�̈ړ�
    EnemyBulletMove(Bullet2, EnemyBulletNum, Bullet1Widh, Bullet1Widh);

    //�C���^�[�o�����͐����t���O�����낷
    if (LifeCnt == 2 && frame >= 1550 && frame < 1650)
    {
        EnemySurvivalFlg = false;
        //�e�L�X�g�J�E���g�ǉ�
        TextCnt = 2;
    }

    //�o���b�g1�C2�̃J�E���g������
    if (frame == 1649)
    {
        Bullet1Cnt = NULL;
        Bullet2Cnt = NULL;
    }

    //�U��2(hp0�ɂȂ�܂ōU��)
    if (LifeCnt == 2 && frame >= 1650)
    {
        //�����t���O�𗧂Ă�
        EnemySurvivalFlg = true;
        AttackPattern2(frame);
    }

    //�o���b�g3�̈ړ�
    EnemyBulletMove(Bullet3, EnemyBulletNum, Bullet1Widh, Bullet1Widh);

    //hp��0�ɂȂ����������
    if (EnemyHp[2] <= 0 && LifeFlg2 == false)
    {
        //�_�E���G�t�F�N�g�t���O�𗧂Ă�
        DownEffectFlg = true;
        //�_�E�����̍��W������
        DownX = EnemyX + EnemySizeX / 2;
        DownY = EnemyY + EnemySizeY / 2;
        EnemyDisappear(frame);
        //�t���O�𗧂Ă�
        LifeFlg2 = true;
        //�\�����̒e������
        EnemyBulletReset();
    }

    if (EnemyHp[2] <= 0 && EnemySurvivalFlg == false && EnemyHp[1] == 1000)
    {
        //�e�L�X�g�J�E���g�ǉ�
        TextCnt = 3;
    }

    //�ēo��
    if (LifeCnt == 1 && frame == 240 && MoveFlg2 == false)
    {
        //�t���O�𗧂Ă�
        EnemySurvivalFlg = true;
        MoveFlg2 = true;
        //���S�ֈړ�
        EnemyX = InitEnemyX;
        EnemyY = 0;
        //�ړ���
        PlaySoundMem(EnemySound3, DX_PLAYTYPE_BACK);
        //�ړ��ʏ�����
        EnemyMoveX = 0;
        EnemyMoveY = 0;
        //�G�t�F�N�g�t���O�����Ă�
        EmyShotEffect1Flg = true;
    }

    //�U���p�^�[��3
    if (LifeCnt == 1 && frame > 300 && EnemyHp[1] > 500)
    {
        AttackPattern3(frame);
    }
    //�o���b�g4�̈ړ�
    EnemyBulletMove(Bullet4, EnemyBulletNum, Bullet1Widh, Bullet1Widh);

    //��x������
    if (EnemyHp[1] <= 500 && MoveFlg == false)
    {
        EnemyDisappear(frame);
        //�t���O�𗧂Ă�
        MoveFlg = true;
        //�\�����̒e������
        EnemyBulletReset();
    }
    if (EnemyHp[1] <= 500 && EnemyHp[1] == 1000 && EnemySurvivalFlg == false)
    {
        //�e�L�X�g�J�E���g�ǉ�
        TextCnt = 4;
    }
    //�ēo��
    if (frame == 60 && LifeCnt == 1 && EnemyHp[1] <= 500)
    {
        //�t���O�𗧂Ă�
        EnemySurvivalFlg = true;
        //���S�ֈړ�
        EnemyX = InitEnemyX;
        EnemyY = 0;
        //�ړ���
        PlaySoundMem(EnemySound3, DX_PLAYTYPE_BACK);
    }

    //�U���p�^�[��4
    if (LifeCnt == 1 && EnemyHp[1] <= 500 && frame >= 70)
    {
        AttackPattern4(frame);
    }
    //�o���b�g5�̈ړ�
    EnemyBulletMove5(Bullet5, EnemyBulletNum, Bullet5Widh, Bullet5Height);

    //hp��0�ɂȂ����������
    if (EnemyHp[1] <= 0 && LifeFlg3 == false)
    {
        //�_�E���G�t�F�N�g�t���O�𗧂Ă�
        DownEffectFlg = true;
        //�_�E�����̍��W������
        DownX = EnemyX + EnemySizeX / 2;
        DownY = EnemyY + EnemySizeY / 2;
        EnemyDisappear(frame);
        LifeFlg3 = true;
        //�\�����̒e������
        EnemyBulletReset();
    }

    if (EnemyHp[1] <= 0 && EnemyHp[1] == 1000 && EnemySurvivalFlg == false)
    {
        //�e�L�X�g�J�E���g�ǉ�
        TextCnt = 5;
    }

    //�ēo��
    if (frame == 60 && LifeCnt == 0 && EnemyHp[0] >= 500)
    {
        //�t���O�𗧂Ă�
        EnemySurvivalFlg = true;
        //����ֈړ�
        EnemyX = 40;
        EnemyY = 0;
        //�ړ���
        PlaySoundMem(EnemySound3, DX_PLAYTYPE_BACK);
    }

    //�U���p�^�[��5
    if (LifeCnt == 0 && EnemyHp[0] > 500 && frame >= 70)
    {
        AttackPattern5(frame);
    }
    //�o���b�g6�̈ړ�
    EnemyBulletMove(Bullet6, EnemyBulletNum, Bullet1Widh, Bullet1Widh);

    //��x������
    if (LifeFlg1 == false && EnemyHp[0] <= 500)
    {
        EnemyDisappear(frame);
        //�t���O�𗧂Ă�
        LifeFlg1 = true;
        //�\�����̒e������
        EnemyBulletReset();
    }

    if (EnemyHp[0] == 500 && EnemySurvivalFlg == false)
    {
        //�e�L�X�g�J�E���g�ǉ�
        TextCnt = 6;
    }

    //�ēo��
    if (frame == 60 && LifeCnt == 0 && EnemyHp[0] <= 500)
    {
        //�t���O�𗧂Ă�
        EnemySurvivalFlg = true;
        //���S�ֈړ�
        EnemyX = InitEnemyX;
        EnemyY = 0;
        //�ړ���
        PlaySoundMem(EnemySound3, DX_PLAYTYPE_BACK);
        //�ړ��ʂ̐ݒ�
        EnemyMoveX = 3;
        EnemyMoveY = 3;
    }

    //�U���p�^�[��6
    if (LifeCnt == 0 && EnemyHp[0] <= 500 && frame > 60)
    {
        AttackPattern6(frame);
    }

    //�o���b�g7,8�̈ړ�
    EnemyBulletMove(Bullet7, EnemyBulletNum, Bullet1Widh, Bullet1Widh);
    EnemyBulletMove(Bullet8, EnemyBulletNum, Bullet1Widh, Bullet1Widh);
    //�o���b�g9�̈ړ�
    EnemyBulletMove(Bullet9, EnemyBulletNum, Bullet1Widh, Bullet1Widh);

    //�_�E���t���O�������Ă�����G�t�F�N�g�Đ�
    if (DownEffectFlg == true)
    {
        EfectDraw(EmyDownEffect, DownEffectCnt, DownX, DownY, 2.0);
    }
    //�G�t�F�N�g�J�E���g����
    if (DownEffectFlg == true && frame % 5 == 0)
    {
        EffectCountCheck(DownEffectCnt, DownEffectFlg, 9);
    }

    //�G�̓����蔻��X�V
    EnemyRectUpdate(EnemyHit, EnemyX, EnemyY);

    //���j���̃t���[�������Ƃ�
    if (EnemyHp[0] == 0 && DownTimeFlg == false)
    {
        EnemyDownTime = frame;
        //�t���O�𗧂Ă�
        DownTimeFlg = true;
        EnemyBulletReset();
    }

    //�|������̏���
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
    //�e�L�X�g�摜�`��
    DrawExtendGraph(1000, -20, 1200, 72, HpTextImg, TRUE);

    //���[�^�[�摜�`��
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
    //�ړ����x�̐ݒ�
    EnemyMoveSpeedX = 3;
    EnemyMoveSpeedY = 1;
    //�G�̈ړ���(��)
    if (EnemyX <= 5)
    {
        EnemyMoveX = EnemyMoveSpeedX;
    }
    if (EnemyX + EnemySizeX >= 995)
    {
        EnemyMoveX = -EnemyMoveSpeedX;
    }
    //�G�̈ړ���(�c)
    if (EnemyY < 1)
    {
        EnemyMoveY = EnemyMoveSpeedY;
    }
    if (EnemyY > 100)
    {
        EnemyMoveY = -EnemyMoveSpeedY;
    }

    //�G�̈ړ�
    EnemyMove();

    //Bullet1�̒ǉ�
    if (frame % 2 == 0)
    {
        Bullet1Add(EnemyX, EnemyY);
        //�J�E���g�ǉ�
        Bullet1Cnt++;
        //�z��̃J�E���g���ő�l�ɂȂ����珉����
        if (Bullet1Cnt > EnemyBulletNum)
        {
            Bullet1Cnt = 0;
        }
    }

    //2�t���[���Ɉ��V���b�g���Đ�(�o���b�g1)
    if (frame % 2)
    {
        //�V���b�g���̍Đ�
        PlaySoundMem(EnemySound1, DX_PLAYTYPE_BACK);
    }

    //�o���b�g2�t���O��10�t���[�����Ɛ؂�ւ�
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

    //Bullet2�̒ǉ�(5�t���[�����Ɣ���)
    if (Bullet2flg == true && frame % 5 == 0)
    {
        Bullet2Add(EnemyX, EnemyY);
        //�J�E���g�ǉ�
        Bullet2Cnt++;
    }
    //�z��̃J�E���g���ő�l�ɂȂ����珉����
    if (Bullet2Cnt > EnemyBulletNum)
    {
        Bullet2Cnt = 0;
    }
}

void AttackPattern2(int frame)
{
    //�ړ����x�̐ݒ�
    if (Atack2Flg == false)//���ڂ͒�ʒu�ւ̏u�Ԉړ�
    {
        EnemyX = 50;
        EnemyY = 50;
        //�t���O�𗧂Ă�
        Atack2Flg = true;
    }
    else                   //���ڈȍ~��200�Â̈ړ�
    {
        EnemyMoveX = 200;
        EnemyMoveY = 0;

    }
    //2�b��1��u�Ԉړ�
    if (frame % 120 == 0)
    {
        //�G�t�F�N�g�t���O�𗧂Ă�
        EmyJumpEfectFlg = true;

        //�G�̈ړ�
        EnemyMove();
        //�Q�[���t���[�����s�����Ƃ����ꍇ�����l�ɖ߂�
        if (EnemyX > GameWindowX2 - EnemySizeX)
        {
            EnemyX = 50;
        }
        //�ړ���
        PlaySoundMem(EnemySound3, DX_PLAYTYPE_BACK);
    }
    if (frame % 60 == 0)
    {
        //�~�`�e�ǉ�
        Bullet3Add(EnemyX + (EnemySizeX / 2), EnemyY + (EnemySizeY / 2));


        //���ˉ��̍Đ�
        PlaySoundMem(EnemySound2, DX_PLAYTYPE_BACK);
    }

    //�W�����v�G�t�F�N�g�̕`��
    if (EmyJumpEfectFlg == true)
    {
        EfectDraw(EmyJumpEffect, EmyJumpEfectCnt, EnemyX + 60, EnemyY + 190, 1.0);
    }
    //�G�t�F�N�g�t���O�������Ă��邩�̊m�F
    if (EmyJumpEfectFlg == true && frame % 5 == 0)
    {
        EffectCountCheck(EmyJumpEfectCnt, EmyJumpEfectFlg, 7);
    }
}

void AttackPattern3(int frame)
{
    //�ړ���
    if (frame % 720 == 0)
    {
        EnemyMoveX = -400;
        EnemyMoveY = 0;
        //�G�̈ړ�
        EnemyMove();
        //��ʊO�ɍs���ĂȂ����̔���
        if (EnemyX <= 40 || EnemyX >= 1000 - EnemySizeX)
        {
            EnemyX = InitEnemyX;
        }
    }
    else if (frame % 360 == 0)
    {
        EnemyMoveX = 200;
        EnemyMoveY = 0;
        //�G�̈ړ�
        EnemyMove();
        //��ʊO�ɍs���ĂȂ����̔���
        if (EnemyX <= 40 || EnemyX >= 1000 - EnemySizeX)
        {
            EnemyX = InitEnemyX;
        }
    }

    //�V���b�g�G�t�F�N�g�`��
    if (EmyShotEffect1Flg == true)
    {
        DrawExtendGraph(40, 0, 1000, 900, EmyShotEffect1[EmyShotEffect1Cnt], true);
    }
    //�G�t�F�N�g�t���O�������Ă��邩�̊m�F
    if (EmyShotEffect1Flg == true && frame % 3 == 0)
    {
        //�J�E���g�̒ǉ�
        EffectCountCheck(EmyShotEffect1Cnt, EmyShotEffect1Flg, 24);
    }

    if (frame % 10 == 0 && AttackPattern3Flg == true)
    {
        //1�Â��炵�Ȃ���~�`�ɔ���
        //�e�̒ǉ�
        Bullet4Add(EnemyX + (EnemySizeX / 2), EnemyY + (EnemySizeY / 2));
        //�z�񐔂��ő�ɂȂ����珉����
        if (Bullet4Cnt > EnemyBulletNum)
        {
            Bullet4Cnt = 0;
        }
        //���ˉ��Đ�
        PlaySoundMem(EnemySound4, DX_PLAYTYPE_BACK);
    }
    if (frame % 120 == 0)
    {
        AttackPattern3Flg = false;  //�ˏo�̃N�[���^�C��
    }
    if (frame % 180 == 0)
    {
        AttackPattern3Flg = true;   //�Ďˏo
    }
}

void AttackPattern4(int frame)
{
    //�c���e�̔���
    if (frame % 60 == 0)
    {
        Bullet5Add(EnemyX + (EnemySizeX / 2), EnemyY + (EnemySizeY / 2));
        //�z�񐔂��ő�ɂȂ����珉����
        if (Bullet5Cnt > EnemyBulletNum)
        {
            Bullet5Cnt = 0;
        }
        //���ˉ��Đ�
        PlaySoundMem(EnemySound5, DX_PLAYTYPE_BACK);
    }

    //�G�̈ړ�
    //���ֈړ�
    if (LeftFlg == true)
    {
        EnemyMoveX = -5;
        //���ֈړ�
        if (DownFlg == true)
        {
            EnemyMoveY = 5;
        }
        else if (UpFlg == true) //��ֈړ�
        {
            EnemyMoveY = -5;
        }
    }
    //�E�ֈړ�
    if (RightFlg == true)
    {
        EnemyMoveX = 5;
        //���ֈړ�
        if (DownFlg == true)
        {
            EnemyMoveY = 5;
        }
        else if (UpFlg == true) //��ֈړ�
        {
            EnemyMoveY = -5;
        }
    }
    //�G�̈ړ�
    EnemyMove();
    //��ʊO�ɍs�����Ƃ��Ă��Ȃ����̊m�F
    if (EnemyX <= GameWindowX1)
    {
        //�t���O�̓���ւ�
        LeftFlg = false;
        RightFlg = true;
    }
    else if (EnemyX + EnemySizeX >= GameWindowX2)
    {
        //�t���O�̓���ւ�
        LeftFlg = true;
        RightFlg = false;
    }
    if (EnemyY + EnemySizeY >= 900)
    {
        //�t���O�̓���ւ�
        UpFlg = true;
        DownFlg = false;
    }
    else if (EnemyY <= 0)
    {
        //�t���O�̓���ւ�
        UpFlg = false;
        DownFlg = true;
    }
}

void AttackPattern5(int frame)
{
    float v;          //���K���p�ϐ�
    int moveSpeed = 20;  //�ړ����x
    int randx, randy;
    //�ړ����钼����\�����A�؍��ݍU��
    if (frame % 160 == 0 && LineFlg == false)
    {
        //�G�̒��S����v���C���[�܂ł̒������������߂�
        EnemyMoveX = (PlyHit.worldLX - EnemySizeX / 2) - EnemyX;
        EnemyMoveY = (PlyHit.worldLY - EnemySizeY / 2) - EnemyY;
        v = sqrt(EnemyMoveX * EnemyMoveX + EnemyMoveY * EnemyMoveY);//���K��
        //�����x�v�Z
        EnemyMoveX = (EnemyMoveX / v) * moveSpeed;
        EnemyMoveY = (EnemyMoveY / v) * moveSpeed;
        //�t���O�𗧂ăt���[�������L������
        LineFlg = true;
        LineFrame = frame;
        //���W�̋L��
        LineX1 = EnemyX + EnemySizeX / 2;
        LineY1 = EnemyY + EnemySizeY / 2;
        LineX2 = PlyHit.worldLX;
        LineY2 = PlyHit.worldLY;
    }
    //�\�����Ԓ��̓��C����\��
    if (LineFlg == true)
    {
        if (frame % 2 == 0)
        {
            DrawLine(LineX1, LineY1, LineX2, LineY2, GetColor(255, 0, 0), 3);
        }

    }

    //�T�E���h�Đ�
    if (LineFrame + 30 == frame)
    {
        PlaySoundMem(SordSound, DX_PLAYTYPE_BACK);
    }

    //�G�̈ړ�
    if (LineFrame + 30 <= frame && LineFlg == true)
    {
        //�G�t�F�N�g�t���O�𗧂Ă�
        EmySlashingFlg = true;

        EnemyMove();
        //��ʊO�ɍs�����Ƃ��Ă��Ȃ����̊m�F
        if (EnemyX <= GameWindowX1 || EnemyX + EnemySizeX >= GameWindowX2)
        {
            //�t���O�����낷
            LineFlg = false;
        }
        if (EnemyY + EnemySizeY >= 900 || EnemyY <= 0)
        {
            //�t���O�����낷
            LineFlg = false;
        }
    }
    //��3�ʂ��烉���_���Œe�𔭎�
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
    //���@�w�̃t���O�̊m�F
    if (Magic1Flg == false && Magic2Flg == false)
    {
        //�G�t�F�N�g�t���O�𗧂Ă�
        Magic1Flg = true;
        Magic2Flg = true;
        //Magic3Flg = true;
    }

    //�G�t�F�N�g�`��
    if (Magic1Flg == true && Magic2Flg == true)
    {
        //�`��
        EfectDraw(MagicEffect1, Magic1Cnt, 140, 450, 1.0);
        EfectDraw(MagicEffect2, Magic2Cnt, 900, 450, 1.0);
        //EfectDraw(MagicEffect3, Magic3Cnt, 140, 450, 2.0);
    }

    //�G�t�F�N�g�J�E���g�ǉ�
    if (Magic1Flg == true && Magic2Flg == true && frame % 5 == 0)
    {
        Magic1Cnt++;
        Magic2Cnt++;
        Magic3Cnt++;
        if (Magic1Cnt == 30 && Magic2Cnt == 30)
        {
            //�J�E���g������
            Magic1Cnt = 0;
            Magic2Cnt = 0;
        }
        if (Magic3Cnt == 16)
        {
            //�J�E���g������
            Magic3Cnt = 0;
        }
    }

    //���@�w����̒e�ǉ�
    if (frame % 30 == 0)
    {
        Bullet7Add(140, 450);
    }
    if (frame % 45 == 0)
    {
        Bullet8Add(900, 450);
    }

    //�~�`��ɒe�𔭎�
    //�e�̒ǉ�
    if (frame % 60 == 0)
    {
        //���ˉ��Đ�
        PlaySoundMem(EnemySound6, DX_PLAYTYPE_BACK);
        Bullet9Add(EnemyX + (EnemySizeX / 2), EnemyY + (EnemySizeY / 2));
    }

    //�z�񐔂��ő�ɂȂ����珉����
    if (Bullet9Cnt > EnemyBulletNum)
    {
        Bullet9Cnt = 0;
    }
    //���ˉ��Đ�
    PlaySoundMem(EnemySound4, DX_PLAYTYPE_BACK);

    //�ړ�
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
    //�l�̒ǉ�
    EnemyX += EnemyMoveX;
    EnemyY += EnemyMoveY;
}

void Bullet1Add(double x, double y)
{
    Bullet1[Bullet1Cnt].shotflg = true;                         //�����t���O
    Bullet1[Bullet1Cnt].x = x;                                  //���W��
    Bullet1[Bullet1Cnt].y = y + 50;                             //���W��
    Bullet1[Bullet1Cnt].angle = rand() % 360;                  //�p�x
    Bullet1[Bullet1Cnt].speed = 5;                              //���x

    Bullet1[Bullet1Cnt].vx = cos(Bullet1[Bullet1Cnt].angle) * Bullet1[Bullet1Cnt].speed;    //�����xx
    Bullet1[Bullet1Cnt].vy = sin(Bullet1[Bullet1Cnt].angle) * Bullet1[Bullet1Cnt].speed;    //�����xy
}

void Bullet2Add(double x, double y)
{
    float v;          //���K���p�ϐ�
    Bullet2[Bullet2Cnt].shotflg = true;                         //�����t���O
    Bullet2[Bullet2Cnt].x = x + EnemySizeX;                     //���W��
    Bullet2[Bullet2Cnt].y = y + 50;                             //���W��
    Bullet2[Bullet2Cnt].vx = PlyHit.worldLX - Bullet2[Bullet2Cnt].x;                    //�����xx
    Bullet2[Bullet2Cnt].vy = PlyHit.worldLY - Bullet2[Bullet2Cnt].y;                    //�����xy
    Bullet2[Bullet2Cnt].speed = 3;                              //���x
    v = sqrt(Bullet2[Bullet2Cnt].vx * Bullet2[Bullet2Cnt].vx + Bullet2[Bullet2Cnt].vy * Bullet2[Bullet2Cnt].vy);//���K��

    Bullet2[Bullet2Cnt].vx = (Bullet2[Bullet2Cnt].vx / v) * Bullet2[Bullet2Cnt].speed;      //�����xx
    Bullet2[Bullet2Cnt].vy = (Bullet2[Bullet2Cnt].vy / v) * Bullet2[Bullet2Cnt].speed;      //�����xy

}

void Bullet3Add(double x, double y)
{
    for (int i = 0; i < 360; i += 10)
    {
        Bullet3[Bullet3Cnt].shotflg = true;            //�����t���O
        Bullet3[Bullet3Cnt].x = x;                     //���˂��钆�S���W���W��
        Bullet3[Bullet3Cnt].y = y;                     //���˂��钆�S���W���Wy
        Bullet3[Bullet3Cnt].speed = 2;                 //���x
        ChangeRadian(Bullet3, EnemyBulletNum, Bullet3Cnt, i);            //�p�x
        Bullet3[Bullet3Cnt].vx = cos(Bullet3[Bullet3Cnt].angle) * Bullet3[Bullet3Cnt].speed;    //�����xx
        Bullet3[Bullet3Cnt].vy = sin(Bullet3[Bullet3Cnt].angle) * Bullet3[Bullet3Cnt].speed;    //�����xy
        //�o���b�g3�̃J�E���g�ǉ�
        Bullet3Cnt++;
        //�z��̃J�E���g���ő�l�ɂȂ����珉����
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
            Bullet4[Bullet4Cnt].shotflg = true;                        //�����t���O
            Bullet4[Bullet4Cnt].x = x;                                  //���˂��钆�S���W���W��
            Bullet4[Bullet4Cnt].y = y;                                  //���˂��钆�S���W���Wy
            Bullet4[Bullet4Cnt].speed = 3;                              //���x
            ChangeRadian(Bullet4, EnemyBulletNum, Bullet4Cnt, i + Bullet4AngleCnt);                //�p�x(���W�A��)
            Bullet4[Bullet4Cnt].vx = cos(Bullet4[Bullet4Cnt].angle) * Bullet4[Bullet4Cnt].speed;    //�����xx
            Bullet4[Bullet4Cnt].vy = sin(Bullet4[Bullet4Cnt].angle) * Bullet4[Bullet4Cnt].speed;    //�����xy
            //�z��J�E���g�̑���
            Bullet4Cnt++;
            //�z��̃J�E���g���ő�l�ɂȂ����珉����
            if (Bullet4Cnt > EnemyBulletNum)
            {
                Bullet4Cnt = 0;
            }
        }
    }
    //�A���O���J�E���g�̒ǉ�
    Bullet4AngleCnt += 2;
}

void Bullet5Add(double x, double y)
{
    for (int i = 0; i < 360; i++)
    {
        if (i % 20 == 0)
        {
            Bullet5[Bullet5Cnt].shotflg = true;                        //�����t���O
            Bullet5[Bullet5Cnt].x = x;                                  //���˂��钆�S���W���W��
            Bullet5[Bullet5Cnt].y = y;                                  //���˂��钆�S���W���Wy
            Bullet5[Bullet5Cnt].speed = 2;                              //���x
            ChangeRadian2(Bullet5, EnemyBulletNum, Bullet5Cnt, i);                              //�p�x(���W�A��)
            Bullet5[Bullet5Cnt].vx = cos(Bullet5[Bullet5Cnt].angle) * Bullet5[Bullet5Cnt].speed;    //�����xx
            Bullet5[Bullet5Cnt].vy = sin(Bullet5[Bullet5Cnt].angle) * Bullet5[Bullet5Cnt].speed;    //�����xy
            //��`�̐���
            Bullet5[Bullet5Cnt].lx = x - 6;
            Bullet5[Bullet5Cnt].ly = y - 6;
            Bullet5[Bullet5Cnt].rx = x + 6;
            Bullet5[Bullet5Cnt].ry = y + 6;
            //�z��J�E���g�̑���
            Bullet5Cnt++;
        }
    }
}

void Bullet6Add(float x, float y, float vx, float vy)
{
    Bullet6[Bullet6Cnt].shotflg = true;                        //�����t���O
    Bullet6[Bullet6Cnt].x = x;                                  //���˂���W���W��
    Bullet6[Bullet6Cnt].y = y;                                  //���˂���W���Wy
    Bullet6[Bullet6Cnt].vx = vx;                                 //�����xx
    Bullet6[Bullet6Cnt].vy = vy;                                 //�����xy
    //�z��J�E���g�̑���
    Bullet6Cnt++;
    //�z��̃J�E���g���ő�l�ɂȂ����珉����
    if (Bullet6Cnt > EnemyBulletNum)
    {
        Bullet6Cnt = 0;
    }
}

void Bullet7Add(float x, float y)
{
    float v;          //���K���p�ϐ�
    Bullet7[Bullet7Cnt].shotflg = true;                         //�����t���O
    Bullet7[Bullet7Cnt].x = x;                     //���W��
    Bullet7[Bullet7Cnt].y = y;                             //���W��
    Bullet7[Bullet7Cnt].vx = PlyHit.worldLX - Bullet7[Bullet7Cnt].x;                    //�����xx
    Bullet7[Bullet7Cnt].vy = PlyHit.worldLY - Bullet7[Bullet7Cnt].y;                    //�����xy
    Bullet7[Bullet7Cnt].speed = 3;                              //���x
    v = sqrt(Bullet7[Bullet7Cnt].vx * Bullet7[Bullet7Cnt].vx + Bullet7[Bullet7Cnt].vy * Bullet7[Bullet7Cnt].vy);//���K��

    Bullet7[Bullet7Cnt].vx = (Bullet7[Bullet7Cnt].vx / v) * Bullet7[Bullet7Cnt].speed;      //�����xx
    Bullet7[Bullet7Cnt].vy = (Bullet7[Bullet7Cnt].vy / v) * Bullet7[Bullet7Cnt].speed;      //�����xy
    //�z��J�E���g�̑���
    Bullet7Cnt++;
    //�z��̃J�E���g���ő�l�ɂȂ����珉����
    if (Bullet7Cnt > EnemyBulletNum)
    {
        Bullet7Cnt = 0;
    }
}

void Bullet8Add(float x, float y)
{
    float v;          //���K���p�ϐ�
    Bullet8[Bullet8Cnt].shotflg = true;                         //�����t���O
    Bullet8[Bullet8Cnt].x = x;                     //���W��
    Bullet8[Bullet8Cnt].y = y;                             //���W��
    Bullet8[Bullet8Cnt].vx = PlyHit.worldLX - Bullet8[Bullet8Cnt].x;                    //�����xx
    Bullet8[Bullet8Cnt].vy = PlyHit.worldLY - Bullet8[Bullet8Cnt].y;                    //�����xy
    Bullet8[Bullet8Cnt].speed = 3;                              //���x
    v = sqrt(Bullet8[Bullet8Cnt].vx * Bullet8[Bullet8Cnt].vx + Bullet8[Bullet8Cnt].vy * Bullet8[Bullet8Cnt].vy);//���K��

    Bullet8[Bullet8Cnt].vx = (Bullet8[Bullet8Cnt].vx / v) * Bullet8[Bullet8Cnt].speed;      //�����xx
    Bullet8[Bullet8Cnt].vy = (Bullet8[Bullet8Cnt].vy / v) * Bullet8[Bullet8Cnt].speed;      //�����xy
    //�z��J�E���g�̑���
    Bullet8Cnt++;
    //�z��̃J�E���g���ő�l�ɂȂ����珉����
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
            Bullet9[Bullet9Cnt].shotflg = true;                        //�����t���O
            Bullet9[Bullet9Cnt].x = x;                                  //���˂��钆�S���W���W��
            Bullet9[Bullet9Cnt].y = y;                                  //���˂��钆�S���W���Wy
            Bullet9[Bullet9Cnt].speed = 3;                              //���x
            ChangeRadian(Bullet9, EnemyBulletNum, Bullet9Cnt, i + Bullet4AngleCnt);                //�p�x(���W�A��)
            Bullet9[Bullet9Cnt].vx = cos(Bullet9[Bullet9Cnt].angle) * Bullet9[Bullet9Cnt].speed;    //�����xx
            Bullet9[Bullet9Cnt].vy = sin(Bullet9[Bullet9Cnt].angle) * Bullet9[Bullet9Cnt].speed;    //�����xy
            //�z��J�E���g�̑���
            Bullet9Cnt++;
            //�z��̃J�E���g���ő�l�ɂȂ����珉����
            if (Bullet4Cnt > EnemyBulletNum)
            {
                Bullet4Cnt = 0;
            }
        }
    }
    //�A���O���J�E���g�̒ǉ�(�o���b�g4���痬�p)
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
            //��ʊO�ŏ���
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
            //��`�̍X�V
            Bullet5[i].lx += Bullet[i].vx;
            Bullet5[i].ly += Bullet[i].vy;
            Bullet5[i].rx += Bullet[i].vx;
            Bullet5[i].ry += Bullet[i].vy;
            //��ʊO�ŏ���
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
    //���ׂẴo���b�g�t���O�����낷
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
    //�ړ���
    //PlaySoundMem(EnemySound3, DX_PLAYTYPE_BACK);
    //���j�T�E���h
    PlaySoundMem(DownSE, DX_PLAYTYPE_BACK);
    //�t���[����������
    frame = 0;
    ShieldFlg = false;
    //�G�t�F�N�g�J�E���g������
    PlyEfectCnt = 0;
    PlyEfectFlg = false;
    //�v���C���[�̃{���v���^�C��������
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
            //�������Đ�
            PlaySoundMem(EnemyBombSound, DX_PLAYTYPE_BACK);
        }
    }
    else
    {
        //���U���g�t���O�𗧂Ă�
        ResultChangeFlg = true;
    }   
}