#pragma once

//定数             
const int WindowMaxX = 1440;  //ウィンドウのｘの最大値
const int WindowMaxY = 900;   //ウィンドウのyの最大値
const int BrockPattern = 2; //背景のブロックパターン数
const int GameWindowX1 = 40; //ゲーム画面のフレーム座標
const int GameWindowX2 = 1000;
const int GameWindowY = 900;
const int BlockSize = 64;    //ブロックの大きさ
//配置できるブロックの最大数
const int BlockMaxX = 960 / BlockSize;  //x
const int BlockMaxY = 900 / BlockSize;  //y

//ステージの初期化
void StageInit();

//ステージの描画
void StageDraw();