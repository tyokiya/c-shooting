#include "DxLib.h"
#include"item.h"
#include"enemy.h"

extern int LifeCnt;									//�GHP�̃J�E���g(�O���[�o���ϐ�)
extern int frame;									//�t���[����(�O���[�o���ϐ�)
extern int EnemyHp[HpGauge];						//�GHP�̔z��(3�Q�[�W��)(�O���[�o���ϐ�)

int UpItemImg;										//�p���[�A�b�v�A�C�e���摜�ϐ�
bool UpItemFlg;										//�p���[�A�b�v�A�C�e���̐����t���O
int UpItemX, UpItemY;								//�p���[�A�b�v�A�C�e���̍��Wx,y
int BombItemImg;									//�{���̉摜�ϐ�
bool BombItemFlg;									//�{���̐����t���O
int BombItemX, BombItemY;							//�{���̍��Wx,y
bool itemFlg;										//�A�C�e���t���O
bool DisplayFlg;									//�\���t���O

void ItemInit()
{
	//�摜�ǂݍ���
	UpItemImg = LoadGraph("image/item.png");
	BombItemImg = LoadGraph("image/bomb.png");

	//�t���O������
	UpItemFlg = false;
	BombItemFlg = false;
	itemFlg = false;
	DisplayFlg = false;

	//�������W�ǉ�
	UpItemX = 480;
	UpItemY = -15;

	BombItemX = 480;
	BombItemY = -15;
}

void ItemUpdate()
{
	//�p���[�A�b�v�A�C�e���h���b�v
	if (LifeCnt == 2 && frame == 1550)
	{
		//�t���O�𗧂Ă�
		UpItemFlg = true;
	}

	//�t���O�������Ă�ꍇ�ړ�
	if (UpItemFlg == true)
	{
		ItemMove();
	}

	//�{�X��1�Q�[�W�ڂ�0�Ȃ�����{�����h���b�v
	if (EnemyHp[2] <= 0 && itemFlg == false)
	{
		BombItemFlg = true;
		itemFlg = true;
	}
	//�t���O�������Ă�ꍇ�ړ�
	if (BombItemFlg == true)
	{
		ItemMove();
	}
}

void ItemMove()
{
	if (UpItemFlg == true)
	{
		UpItemY += ItemMoveSpeed;
	}
	if (BombItemFlg == true)
	{
		BombItemY += ItemMoveSpeed;
	}
}

void ItemDraw()
{
	//�t���O�������Ă�ꍇ�̂ݕ`��
	if (UpItemFlg == true)
	{
		//10�t���[�����ƂɃt���O�؂�ւ�
		if (frame % 10 == 0)
		{
			if (DisplayFlg == false)
			{
				DisplayFlg = true;
			}
			else
			{
				DisplayFlg = false;
			}
		}
		if (DisplayFlg == true)
		{
			DrawExtendGraph(UpItemX, UpItemY, UpItemX + ItemSize, UpItemY + ItemSize, UpItemImg, TRUE);
		}
	}
	if (BombItemFlg == true)
	{
		//10�t���[�����ƂɃt���O�؂�ւ�
		if (frame % 10 == 0)
		{
			if (DisplayFlg == false)
			{
				DisplayFlg = true;
			}
			else
			{
				DisplayFlg = false;
			}
		}
		if (DisplayFlg == true)
		{
			DrawExtendGraph(BombItemX, BombItemY, BombItemX + ItemSize, BombItemY + ItemSize, BombItemImg, TRUE);
		}
	}
}