#include<DxLib.h>
#include "effect.h"
#include"player.h"

//�G�t�F�N�g�̕ϐ�
int PlyEfect1[11];      //�v���C���[�G�t�F�N�g�P
int EmyJumpEffect[7];   //�G�̃W�����v�G�t�F�N�g
int EmyDownEffect[9];   //�G�̃_�E���G�t�F�N�g
int BuffEffect[15];		//�o�t�G�t�F�N�g(�O���[�o���ϐ�)
int ResultEffect[15];   //���U���g�G�t�F�N�g
int EmyShotEffect1[25]; //�G�̍U���G�t�F�N�g1
int PlyRevivalEffect[10];//�v���C���[�̕����G�t�F�N�g
int EmySlashingEffect[10];//�G�̎a���G�t�F�N�g
int MagicEffect1[30];      //���@�w�G�t�F�N�g1
int MagicEffect2[30];      //���@�w�G�t�F�N�g2
int MagicEffect3[16];      //���@�w�G�t�F�N�g3

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
    //�J�E���g�̒ǉ�
    cnt++;
    //�ő�l�ɂȂ����珉����
    if (cnt > maxframenum)
    {
        //�J�E���g������
        cnt = 0;
        //�t���O�����낷
        flg = false;
    }
}