#include<DxLib.h>
#include "efect.h"
#include"player.h"

//�G�t�F�N�g�̕ϐ�
int PlyEfect1[11];      //�v���C���[�G�t�F�N�g�P
int EmyJumpEffect[7];   //�G�̃W�����v�G�t�F�N�g

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