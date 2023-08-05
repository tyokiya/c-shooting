#include "DxLib.h"
#include"text.h"

int TextImg1,TextImg2,TextImg3,TextImg4,TextImg5,TextImg6;		//テキストイメージ


void TextInit()
{
	TextImg1 = LoadGraph("image/text1.png");
	TextImg2 = LoadGraph("image/text2.png");
	TextImg3 = LoadGraph("image/text3.png");
	TextImg4 = LoadGraph("image/text4.png");
	TextImg5 = LoadGraph("image/text5.png");
	TextImg6 = LoadGraph("image/text6.png");
}

void TextDraw(int num)
{
	switch (num)
	{
	case 1:
		DrawGraph(200, 700, TextImg1, TRUE);
		break;
	case 2:
		DrawGraph(200, 700, TextImg2, TRUE);
		break;
	case 3:
		DrawGraph(200, 700, TextImg3, TRUE);
		break;
	case 4:
		DrawGraph(200, 700, TextImg4, TRUE);
		break;
	case 5:
		DrawGraph(200, 700, TextImg5, TRUE);
		break;
	case 6:
		DrawGraph(200, 700, TextImg6, TRUE);
		break;
	}
}