#include<Windows.h>
#include "DxLib.h"
#include"player.h"
#include"stage.h"
#include"enemy.h"
#include "collision.h"
#include"item.h"
#include"game.h"


int WINAPI WinMain(HINSTANCE hIstans, HINSTANCE hPrevInstans, LPSTR lpCmdLibe, int nCmdshow)
{
	//----------------------------------// 
	//基本設定
	//----------------------------------// 

	//ChangeWindowMode(TRUE);				//ウィンドウモードにする
	DxLib_Init();						//ライブラリを初期化 Initialise
	SetMainWindowText("水炎戦伝記");	//ウィンドウの名称
	SetDrawScreen(DX_SCREEN_BACK);		//背景をセットする
	SetGraphMode(1440, 900, 16);			//ウィンドウのサイズとカラーモードを決める
	

	extern enum GameScene NowGameScene;	//現在のゲームシーン
	// 画面の更新時間の管理用変数
	LONGLONG nowCount, prevCount;                      // マイクロ秒(100万分の1秒単位で時刻取得)
	nowCount = prevCount = GetNowHiPerformanceCount();
	float fixedDeltaTime = 1.0f / 60.0f;               // 60分の1秒 = 0.01666...秒
	float waitFrameTime = 15500;                       // 16000マイクロ秒 = 16ミリ秒 = 0.016秒

	//最初のシーンはタイトルから
	NowGameScene = TitleScene;
	TitleInit();
	//メインループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// deltaTime計測
		float deltaTime;
		nowCount = GetNowHiPerformanceCount();
		deltaTime = (nowCount - prevCount) / 1000000.0f;

		//画面更新処理
		ClearDrawScreen();
		

		//シーン切り替え
		switch (NowGameScene)
		{
		case TitleScene:
			TitleCtrl();
			break;
		case PlayScene:
			PlayCtrl();
			break;
		case ResultScene:
			ResultCtrl();
			break;
		default:
			break;
		}

		//60FPS待ち
		while (GetNowHiPerformanceCount() - nowCount < waitFrameTime)
		{
			;
		}

		prevCount = nowCount;
	}

	//----------------------------------// 
	//終了
	//----------------------------------// 

	DxLib_End();
	return 0;
}