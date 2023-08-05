#include"DxLib.h"
#include"title.h"

int BackImg;			//背景の画像ハンドル
int Logo2;				//タイトルロゴの画像ハンドル
int TextImg;				//テキスト画像ハンドル
int FlgCnt = 0;
bool Flg = false;

void TitleScreenDraw()
{
	//描画
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