#include <math.h>
#include "DxLib.h"
#include"player.h"
#include"collision.h"
#include"stage.h"
#include"SoundLoad.h"
#include"enemy.h"
#include"effect.h"

//�ϐ��錾
int PlayCharaImg[CharaPatarn];//�L�����N�^�[�̔z��
int LifeImg;                 //�v���C���[���C�t�̃C���[�W�摜
int BombImg;                 //�v���C���[�{���̃C���[�W�摜
double PlayCharaX;   //�v���C���[��x���W
double PlayCharaY;   //�v���C���[��y���W
int PlayLife;       //�v���C���[�̃��C�t��
int PlayBomb;       //�v���C���[�̃{����
int PlayFlg;      //�v���C���[�摜�̂̔z��ԍ��̃t���O
double DefoSpeed;            //�f�t�H���g�̑��x
double SlowSpeed;            //�X���[���[�h�̑��x
float PlyHitSizeX = 15;      //�����蔻��T�C�Y��
float PlyHitSizeY = 15;      //�����蔻��T�C�Y����
int DeathTime;           //���S���̃t���[��
int ShotLevel;           //�v���C���[�̒e�����x��
int LifeTextImg, BombTextImg;//�e�L�X�g�摜�n���h��

sHitRect PlyHit;      //���@�̃q�b�g����\����

shot playershot[PShotNum];//�v���C���[�̒e�̍\���̔z��
shot playershot2[PShotNum];
shot playershot3[PShotNum];
int ShotCnt = 0;            //�e�̔z��ԍ����w���J�E���g
int ShotCnt2 = 0;
int ShotCnt3 = 0;
int playershotImg;          //�e�̉摜�n���h��
int ShieldImg;              //�V�[���h�̉摜�n���h��

//�����蔻��T�[�N���̒��S���W
float HitCircleX;     //x
float HitCircleY;     //y
int CircleColor;        //�~�̐F
int CircleColor2;
int FontColor;          //�t�H���g�̐F

//���֘A
int PlayerShotSound;            //�T�E���h�n���h��
int BombSound;                  //�{���������̃T�E���h
int GetSound;                   //�A�C�e���̊l���T�E���h�n���h��
int DamageSound;                //��e�T�E���h�n���h��

//�R���g���[���[
int PadInput;

int BombTime;                   //�{���������̎��Ԍv��

//�G�t�F�N�g�̃O���[�o���ϐ�
extern int PlyEfect1[11], PlyRevivalEffect[10];

int PlyEfectCnt,RevivalCnt;     //�G�t�F�N�g�J�E���g
bool PlyEfectFlg, RevivalFlg;       //�G�t�F�N�g�t���O

void PlayerInit()
{
    PlayCharaImg[0] = LoadGraph("image/player1(100).png");   //������
    PlayCharaImg[1] = LoadGraph("image/player2(100).png");   //�E����
    LifeImg = LoadGraph("image/heart.png");                  //���C�t�摜�̓ǂݍ���
    BombImg = LoadGraph("image/star.png");                   //�{���摜�ǂݍ���
    ShieldImg = LoadGraph("image/foam.png");                 //�V�[���h�摜�̓ǂݍ���
    LifeTextImg = LoadGraph("image/LifeText.png");
    BombTextImg = LoadGraph("image/BombText.png");

    PlayFlg = 0;                    //�t���O�̏�����
    PlayCharaX = InitalPositionX;   //�v���C���[�̏���x���W
    PlayCharaY = InitalPositionY;   //�v���C���[�̏���y���W
    PlayLife = PlayInitalLife;      //�v���C���[�̃��C�t�ݒ�
    PlayBomb = PlayInitalBomb;      //�v���C���[�̃{���ݒ� 
         
    HitCircleX = PlayCharaX + PlaySize / 2 - 2;   //�����蔻��̒��S���W
    HitCircleY = PlayCharaY + PlaySize / 2 + 5;
    PlyinitRect(PlyHit, PlyHitSizeX, PlyHitSizeY,HitCircleX,HitCircleY);   //�v���C���[�̓����蔻��\���̐ݒ�
    CircleColor = GetColor(139, 0, 0);    //���F
    CircleColor2 = GetColor(211, 211, 211);    //�ԐF
    FontColor = GetColor(238, 130, 238);        //�s���N�F

    DeathTime = 0;           //���S���̃t���[��
    ShotLevel = 1;           //�v���C���[�̒e�����x��
    BombTime = 0;

    PlyEfectCnt, RevivalCnt = 0;     //�G�t�F�N�g�J�E���g������
    //�t���O������
    PlyEfectFlg, RevivalFlg = false;


    //�v���C���[�̒e������
    PShotInit();

    //�T�E���h�ǂݍ���
    LoadPlySound();

    //�G�t�F�N�g�̏�����
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
    //���͐��̃J�E���g
    int hitcnt = 0;

    //X���̏���
    PadInput = GetJoypadInputState(DX_INPUT_KEY_PAD1);  //�L�[�̓ǂݍ���

    //�΂߂ɓ��͂���Ă邩�̃J�E���g
    if ((PadInput & PAD_INPUT_RIGHT) != 0)
    {
            hitcnt++;
    }
    else if ((PadInput & PAD_INPUT_LEFT) != 0) //�X���[�Ȃ��ŉ�����Ă�ꍇ
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

    if (hitcnt == 1)//���E�㉺�̑��x�ݒ�
    {
        DefoSpeed = 5;            //�f�t�H���g�̑��x
        SlowSpeed = 3;            //�X���[���[�h�̑��x
    }
    else if (hitcnt == 2)//�΂߂̑��x
    {
        DefoSpeed = sqrt(50) / 2;            //�f�t�H���g�̑��x
        SlowSpeed = sqrt(18) / 2;            //�X���[���[�h�̑��x
    }
    
    //�E�̑���
    if ((PadInput & PAD_INPUT_RIGHT) != 0 && (PadInput & PAD_INPUT_5) == 0) //�X���[�Ȃ��ŉ�����Ă�ꍇ
    {
        if (PlayCharaX < GameWindowX2 - PlaySize + 15)
        {
            PlayCharaX += DefoSpeed;
            HitCircleX += DefoSpeed;
            PlayFlg = 1;
        }
    }
    else if ((PadInput & PAD_INPUT_RIGHT) != 0 && (PadInput & PAD_INPUT_5) != 0) //�X���[����ŉ�����Ă�ꍇ
    {
        if (PlayCharaX < GameWindowX2 - PlaySize + 15)
        {
            PlayCharaX += SlowSpeed;
            HitCircleX += SlowSpeed;
            PlayFlg = 1;
        }
    }
    //���̑���
    else if ((PadInput & PAD_INPUT_LEFT) != 0 && (PadInput & PAD_INPUT_5) == 0) //�X���[�Ȃ��ŉ�����Ă�ꍇ
    {
        if (PlayCharaX > GameWindowX1 -15)
        {
            PlayCharaX -= DefoSpeed;
            HitCircleX -= DefoSpeed;
            PlayFlg = 0;
        }
    }
    else if ((PadInput & PAD_INPUT_LEFT) != 0 && (PadInput & PAD_INPUT_5) != 0) //�X���[����ŉ�����Ă�ꍇ
    {
        if (PlayCharaX > GameWindowX1 - 15)
        {
            PlayCharaX -= SlowSpeed;
            HitCircleX -= SlowSpeed;
            PlayFlg = 0;
        }
    }
    //Y���̏���
    //��̑���
    if ((PadInput & PAD_INPUT_UP) != 0 && (PadInput & PAD_INPUT_5) == 0) //�X���[�Ȃ��ŉ�����Ă�ꍇ
    {
        if (PlayCharaY > 0)
        {
            PlayCharaY -= DefoSpeed;
            HitCircleY -= DefoSpeed;
        }
    }
    else if ((PadInput & PAD_INPUT_UP) != 0 && (PadInput & PAD_INPUT_5) != 0) //�X���[����ŉ�����Ă�ꍇ
    {
        if (PlayCharaY > 0)
        {
            PlayCharaY -= SlowSpeed;
            HitCircleY -= SlowSpeed;
        }
    }
    //���̑���
    else if ((PadInput & PAD_INPUT_DOWN) != 0 && (PadInput & PAD_INPUT_5) == 0) //�X���[�Ȃ��ŉ�����Ă�ꍇ
    {
        if (PlayCharaY < GameWindowY - PlaySize - 8)
        {
            PlayCharaY += DefoSpeed;
            HitCircleY += DefoSpeed;
        }
    }
    else if ((PadInput & PAD_INPUT_DOWN) != 0 && (PadInput & PAD_INPUT_5) != 0) //�X���[����ŉ�����Ă�ꍇ
    {
        if (PlayCharaY < GameWindowY - PlaySize - 8)
        {
            PlayCharaY += SlowSpeed;
            HitCircleY += SlowSpeed;
        }
    }

    //�����蔻��̍X�V
    PlyRectUpdate(PlyHit, HitCircleX, HitCircleY);

    //a�{�^���������ꂽ��e�𔭎�(3�t���[���Ɉꔭ)
    if ((PadInput & PAD_INPUT_3) != 0 && frame % 3 == 0 && frame != 0)
    {
        ShotAddition();
        if (ShotCnt == PShotNum)
        {
            ShotCnt = 0;//�J�E���g������
        }
        if (ShotCnt2 == PShotNum)
        {
            ShotCnt2 = 0;//�J�E���g������
        }
        if (ShotCnt3 == PShotNum)
        {
            ShotCnt3 = 0;//�J�E���g������
        }
        //�V���b�g���̍Đ�
        PlaySoundMem(PlayerShotSound, DX_PLAYTYPE_BACK);
    }

    //R1�̃L�[���͊m�F
    if ((PadInput & PAD_INPUT_6) != 0 && PlayBomb > 0)
    {
        //�O��̃{����������1�b�ȏ�o�߂������̊m�F
        if (frame >= BombTime + 60)
        {
            //�{���̔���
            EnemyBulletReset();
            //�{���̌������炷
            PlayBomb--;
            //�{���̎��Ԍv��
            BombTime = frame;
            //�T�E���h�̍Đ�
            PlaySoundMem(BombSound, DX_PLAYTYPE_BACK);
            //�G�t�F�N�g�t���O�𗧂Ă�
            PlyEfectFlg = true;
        }
    }
    
    //�G�t�F�N�g�̕`��
    if (PlyEfectFlg == true)
    {
        EfectDraw(PlyEfect1, PlyEfectCnt, HitCircleX, HitCircleY, 1.0);
    }
    //�G�t�F�N�g�t���O�������Ă��邩�̊m�F
    if (PlyEfectFlg == true && frame % 5 == 0)
    {
        //�J�E���g�̒ǉ�
        EffectCountCheck(PlyEfectCnt, PlyEfectFlg, 11);
    }
    
    //�����G�t�F�N�g�������Ă��邩�̊m�F
    if (RevivalFlg == true && frame % 5 == 0)
    {
        //�J�E���g�̒ǉ�
        EffectCountCheck(RevivalCnt, RevivalFlg, 10);
    }
    ShotMove();
}

void ShotAddition()
{
    //�V���b�g���x���P
    if (ShotLevel == 1)
    {
        playershot[ShotCnt].shotflg = true;
        //�e���ˏo�������W
        playershot[ShotCnt].x = PlayCharaX + 40;
        playershot[ShotCnt].y = PlayCharaY - 10;
        ShotCnt++;
    }
    //�V���b�g���x��2
    if (ShotLevel == 2)
    {
        playershot[ShotCnt].shotflg = true;
        //�e���ˏo�������W
        playershot[ShotCnt].x = PlayCharaX + 40;
        playershot[ShotCnt].y = PlayCharaY - 10;
        ShotCnt++;
        playershot2[ShotCnt2].shotflg = true;
        //�e���ˏo�������W
        playershot2[ShotCnt2].x = PlayCharaX + 40;
        playershot2[ShotCnt2].y = PlayCharaY - 10;
        ShotCnt2++;
        playershot3[ShotCnt3].shotflg = true;
        //�e���ˏo�������W
        playershot3[ShotCnt3].x = PlayCharaX + 40;
        playershot3[ShotCnt3].y = PlayCharaY - 10;
        ShotCnt3++;
    }
    
}

void PlayerDraw()
{
    DrawGraph(PlayCharaX,PlayCharaY, PlayCharaImg[PlayFlg], TRUE);
    //�q�b�g�T�[�N���̕`��
    DrawCircle(HitCircleX, HitCircleY, Radius, CircleColor2, TRUE);
    DrawCircle(HitCircleX, HitCircleY, Radius, CircleColor, FALSE,4);
    //�q�b�g�{�b�N�X�`��
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
    //���C�t�̕\��
    DrawExtendGraph(995, 190, 1155, 250, LifeTextImg, TRUE);
    //DrawString(1010, 200, "Player", FontColor);
    for (int l = 0; l < PlayLife; l++)
    {
        DrawExtendGraph((l * 35) + 1000, 225, (l * 35) + 1050, 275, LifeImg, true);
    }
    //�{���\��
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
            //�e�̈ړ�
            playershot[i].y -= ShotSpeed;
            if (playershot[i].y < -10)
            {
                //��ʊO�ɏo����t���O������
                playershot[i].shotflg = false;
            }
        }
        if (playershot2[i].shotflg == true)
        {
            //�e�̈ړ�
            playershot2[i].y -= ShotSpeed;
            playershot2[i].x -= 1;
            if (playershot2[i].y < -10 || playershot2[i].x < 40 || playershot2[i].x + ShotWidth > 1000)
            {
                //��ʊO�ɏo����t���O������
                playershot2[i].shotflg = false;
            }
        }
        if (playershot3[i].shotflg == true)
        {
            //�e�̈ړ�
            playershot3[i].y -= ShotSpeed;
            playershot3[i].x += 1;
            if (playershot3[i].y < -10 || playershot3[i].x < 40 || playershot3[i].x + ShotWidth > 1000)
            {
                //��ʊO�ɏo����t���O������
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
    PlayLife--;     //���C�t�̌���
    //�����ʒu�ւ̈ړ�
    PlayCharaX = InitalPositionX;
    PlayCharaY = InitalPositionY;
    //�����蔻��̒��S���W
    HitCircleX = PlayCharaX + PlaySize / 2 - 2;   
    HitCircleY = PlayCharaY + PlaySize / 2 + 5;
    DeathTime = frame;
    PlayBomb = PlayInitalBomb;      //�v���C���[�̃{���Đݒ�

    //��e�T�E���h�Đ�
    PlaySoundMem(DamageSound, DX_PLAYTYPE_BACK);

    //�����G�t�F�N�g�t���O�����Ă�
    RevivalFlg = true;
}