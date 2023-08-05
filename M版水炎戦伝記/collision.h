#pragma once
#include "player.h"
#include"enemy.h"

// 当たり判定矩形
struct sHitRect
{
	float w;		// 当たり矩形幅ピクセル数
	float h;        // 当たり矩形高さピクセル数
	float worldLX;  // 当たり判定左上X座標
	float worldLY;  // 当たり判定左上Y座標
	float worldRX;  // 当たり判定右下X座標
	float worldRY;  // 当たり判定右下Y座標
	float CenterX;	//当たり判定の中心x
	float CenterY;	//当たり判定の中心y
};

/// <summary>
/// プレイヤーの当たり判定の設定
/// </summary>
/// <param name="Rect">初期化したい当たり判定定数</param>
/// <param name="w">当たり判定の幅</param>
/// <param name="h">当たり判定高さ</param>
/// <param name="CenterPointX">ヒットサークルの中心座標x</param>
/// <param name="CenterPointY">ヒットサークルの中心座標y</param>
void PlyinitRect(sHitRect& Rect, float w, float h, float CenterPointX, float CenterPointY);

/// <summary>
/// 敵の当たり判定設定
/// </summary>
/// <param name="Rect">初期化したい当たり判定定数</param>
/// <param name="w">当たり判定の幅</param>
/// <param name="h">当たり判定高さ</param>
/// <param name="CenterPointX">左上の座標x</param>
/// <param name="CenterPointY">左上の座標y</param>
void EnemyInitRect(sHitRect& Rect, float w, float h, float EnemyX, float EnemyY);

/// <summary>
/// プレイヤーの当たり判定の更新
/// </summary>
/// <param name="CenterPointX">ヒットサークルの中心座標x</param>
/// <param name="CenterPointY">ヒットサークルの中心座標y</param>
void PlyRectUpdate(sHitRect& Rect, float CenterPointX, float CenterPointY);

/// <summary>
/// 敵の当たり判定更新
/// </summary>
/// <param name="CenterPointX">左上の座標x</param>
/// <param name="CenterPointY">左上の座標y</param>
void EnemyRectUpdate(sHitRect& Rect, double EnemyX, double EnemyY);

/// <summary>
/// 自機と敵の衝突判定
/// </summary>
/// <param name="PlyRect">自機の当たり判定構造体</param>
/// <param name="EnemyRect">敵の当たり判定構造体</param>
bool EnemyCollisionJudge(sHitRect PlyRect, sHitRect EnemyRect);

/// <summary>
/// 自弾と敵の衝突判定
/// </summary>
/// <param name="playerBullet">自弾の当たり判定構造体配列</param>
/// <param name="size">配列のサイズ</param>
/// <param name="EnemyHit">敵の当たり判定構造体</param>
bool PlyBulletCollision(shot playershot[], int size, sHitRect EnemyHit);

/// <summary>
/// 自弾と敵の衝突判定(返り値なし)
/// </summary>
/// <param name="playerBullet">自弾の当たり判定構造体配列</param>
/// <param name="size">配列のサイズ</param>
/// <param name="EnemyHit">敵の当たり判定構造体</param>
void PlyBulletCollision2(shot playerBullet[], int size, sHitRect EnemyHit);

/// <summary>
/// 自機と敵弾1の衝突判定
/// </summary>
/// <param name="PlyRect">自機の当たり判定構造体</param>
/// <param name="Bullet">敵弾の当たり判定</param>
/// <param name="size">サイズ</param>
bool EnemyBullet1Collision(sHitRect PlyRect, EnemyBullet Bullet[], int size);

/// <summary>
/// 自機と敵弾4の特殊衝突判定
/// </summary>
/// <param name="PlyRect">自機の当たり判定構造体</param>
/// <param name="Bullet">敵弾の当たり判定</param>
/// <param name="size">サイズ</param>
bool EnemyBullet15Collision(sHitRect PlyRect, EnemyBullet5 Bullet[], int size);

/// <summary>
/// アイテムの当たり判定
/// </summary>
void ItemCollision();
