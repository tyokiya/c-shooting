#include"DxLib.h"
#include"title.h"

int BackImg;			//�w�i�̉摜�n���h��
int Logo2;				//�^�C�g�����S�̉摜�n���h��
int TextImg;				//�e�L�X�g�摜�n���h��
int FlgCnt = 0;
bool Flg = false;

void TitleScreenDraw()
{
	//�`��
	DrawExtendGraph(0, 0, 1440, 900, BackImg, true);
	DrawExtendGraph(320, 0, 1120, 900, Logo2, true);
	if (FlgCnt % 20 == 0)
	{
		if (Flg == true)
		{
			Flg = false;
		}
		else
		{
			Flg = true;
		}
	}

	if (Flg == true)
	{
		DrawExtendGraph(300, 600, 1100, 900, TextImg, true);
	}
	FlgCnt++;
	if (FlgCnt >= 1000)
	{
		FlgCnt = 0;
	}
}