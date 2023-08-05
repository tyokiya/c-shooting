#include"DxLib.h"
#include"stage.h"

//変数
int i, j;                    //ループカウント
int BackImgBase;             //ベースとなる背景
int BlockImg[BrockPattern];  //プレイ画面の背景
int LineColor;               //線の色
int Logo;                    //タイトルロゴ

/// <summary>
/// マップ情報の初期化
/// </summary>
void StageInit()
{
    //画像の読み込み
    BackImgBase = LoadGraph("image/backimg.png");
    BlockImg[0] = LoadGraph("image/block0.bmp");
    BlockImg[1] = LoadGraph("image/block1.bmp");
    LineColor = GetColor(105, 105, 105);
    Logo = LoadGraph("image/logo.png");
}

/// <summary>
/// マップの描画
/// </summary>
void StageDraw()
{
    //ベース背景の表示
    DrawExtendGraph(0, 0, WindowMaxX, WindowMaxY, BackImgBase, FALSE);
    
    //ブロックを敷き詰める
    for (i = 0; i < BlockMaxY; i++)
    {
        for (j = 0; j < BlockMaxX; j++)
        {
            DrawGraph(j * BlockSize + GameWindowX1, i * BlockSize, BlockImg[(i + j) % 2], false);
        }
    }
    //境界線の表示
    DrawLine(GameWindowX1 - 5, 0, GameWindowX1 - 5, WindowMaxY, LineColor, 10);
    DrawLine(GameWindowX2, 0, GameWindowX2, WindowMaxY, LineColor, 10);
    DrawLine(GameWindowX1, WindowMaxY - 5, GameWindowX2, WindowMaxY - 5, LineColor, 10);

    //タイトルロゴの描画
    DrawExtendGraph(1000, 420, 1440, 900, Logo, true);
}










