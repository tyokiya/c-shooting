#pragma once
#include"DxLib.h"

//�萔
const int PShotNum = 50;    //�v���C���[�̒e�̔z��
const int CharaPatarn = 2;  //�L�����N�^�[�̔z��
const int InitalPositionX = 420;    //�L�����N�^�[�̏���x���W
const int InitalPositionY = 700;    //�L�����N�^�[�̏���y���W
const int PlayInitalLife = 3;       //�v���C���[�̏������C�t��(3)
const int PlayInitalBomb = 3;       //�v���C���[�̏����{����(3)
const int PlaySize = 100;           //�L�����N�^�[�̃T�C�Y
const int PlayerDamage = 200;        //�v���C���[�e�̃_���[�W��(2)
const int Radius = 8;       //�����蔻��̔��a

//�e�֘A
const int ShotWidth = 20;   //�e�̕�
const int ShotSpeed = 10;   //�e�̃X�s�[�h

//�v���g�^�C�v�錾

/// <summary>
/// �v���C���[�̏���������
/// </summary>
void PlayerInit();

/// <summary>
/// �v���C���[�̏��X�V
/// </summary>
/// <param name="frame">���݂̃t���[����</param>
void PlayerUpdate(int frame);

/// <summary>
/// �v���C���[�̕`��
/// </summary>
void PlayerDraw();

/// <summary>
/// �v���C���[�̃X�e�[�^�X�̕`��
/// </summary>
void StatusDraw();

/// <summary>
/// �V�[���h�̕`��
/// </summary>
void ShieldDraw();

/// <summary>
/// �v���C���[�̒e������
/// </summary>
void PShotInit();

/// <summary>
/// �e�̒ǉ�
/// </summary>
/// <param name="ShotCnt">�e�̔z��ԍ�</param>
void ShotAddition();

/// <summary>
/// �e�̈ړ�
/// </summary>
void ShotMove();

/// <summary>
/// �e�̕`��
/// </summary>
void ShotDisplay();

/// <summary>
/// ��e���̏���
/// </summary>
void PlyHitEffect(int frame);

//���e�̍\����
struct shot
{
    bool shotflg;   //���˒����ǂ���
    double x;       //x���W
    double y;       //y���W
    int width, height;//�摜�̕��ƍ���
};

