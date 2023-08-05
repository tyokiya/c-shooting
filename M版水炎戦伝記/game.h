
#pragma once

#include"DxLib.h"

#define GameSceneCount			3	//ゲームシーンのかず
#define GameSceneNameMax		20	//ゲームシーンの文字数マックス

//列挙体

//ゲームシーン
enum GameScene
{
	TitleScene,	//タイトル
	PlayScene,	//プレイ
	ResultScene	//リザルト
};

//外部のグルーバル変数
extern enum GameScene NowGameScene;	//現在のゲームシーン

 //外部のプロトタイプ宣言
 void TitleInit(void);		//タイトル初期化
 void TitleCtrl(void);		//タイトル管理
 void TitleProc(void);		//タイトル処理
 void TitleDraw(void);		//タイトル描画
						  
 void PlayInit(void);			//プレイ初期化
 void PlayCtrl(void);			//プレイ管理
 void PlayProc(void);			//プレイ処理
 void PlayDraw(void);			//プレイ描画

 void ResultInit(void);		//リザルト初期化
 void ResultCtrl(void);		//リザルト管理
 void ResultProc(void);		//リザルト処理
 void ResultDraw(void);		//リザルト描画