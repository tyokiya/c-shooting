#pragma once

/// <summary>
/// プレイヤーのエフェクトの初期化
/// </summary>
void PlyEfectInit();

/// <summary>
/// 敵のエフェクトの初期化
/// </summary>
void EnemyEfectInit();

/// <summary>
/// エフェクトの描画
/// </summary>
/// <param name="efect">描画するエフェクト</param>
/// <param name="num">描画するエフェクトの配列番号</param>
/// <param name="x">描画する中心座標x</param>
/// <param name="y">描画する中心座標y</param>
void EfectDraw(int efect[], int num, float x, float y);