#pragma once
#include"DxLib.h"

//定数
const int PShotNum = 50;    //プレイヤーの弾の配列数
const int CharaPatarn = 2;  //キャラクターの配列数
const int InitalPositionX = 420;    //キャラクターの初期x座標
const int InitalPositionY = 700;    //キャラクターの初期y座標
const int PlayInitalLife = 3;       //プレイヤーの初期ライフ数(3)
const int PlayInitalBomb = 3;       //プレイヤーの初期ボム数(3)
const int PlaySize = 100;           //キャラクターのサイズ
const int PlayerDamage = 200;        //プレイヤー弾のダメージ量(2)
const int Radius = 8;       //当たり判定の半径

//弾関連
const int ShotWidth = 20;   //弾の幅
const int ShotSpeed = 10;   //弾のスピード

//プロトタイプ宣言

/// <summary>
/// プレイヤーの情報を初期化
/// </summary>
void PlayerInit();

/// <summary>
/// プレイヤーの情報更新
/// </summary>
/// <param name="frame">現在のフレーム数</param>
void PlayerUpdate(int frame);

/// <summary>
/// プレイヤーの描画
/// </summary>
void PlayerDraw();

/// <summary>
/// プレイヤーのステータスの描画
/// </summary>
void StatusDraw();

/// <summary>
/// シールドの描画
/// </summary>
void ShieldDraw();

/// <summary>
/// プレイヤーの弾初期化
/// </summary>
void PShotInit();

/// <summary>
/// 弾の追加
/// </summary>
/// <param name="ShotCnt">弾の配列番号</param>
void ShotAddition();

/// <summary>
/// 弾の移動
/// </summary>
void ShotMove();

/// <summary>
/// 弾の描画
/// </summary>
void ShotDisplay();

/// <summary>
/// 被弾時の処理
/// </summary>
void PlyHitEffect(int frame);

//自弾の構造体
struct shot
{
    bool shotflg;   //発射中かどうか
    double x;       //x座標
    double y;       //y座標
    int width, height;//画像の幅と高さ
};

