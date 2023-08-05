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
/// リザルトのエフェクトの初期化
/// </summary>
void ResultEffectInit();

/// <summary>
/// エフェクトの描画
/// </summary>
/// <param name="efect">描画するエフェクト</param>
/// <param name="num">描画するエフェクトの配列番号</param>
/// <param name="x">描画する中心座標x</param>
/// <param name="y">描画する中心座標y</param>
/// <param name="size">描画するサイズ倍率</param>
void EfectDraw(int efect[], int num, float x, float y, float size);

/// <summary>
/// エフェクトのカウント数チェック
/// </summary>
/// <param name="cnt">エフェクトカウント</param>
/// <param name="flg">エフェクトフラグ</param>
/// <param name="maxframenum">エフェクトの最大フレーム数</param>
void EffectCountCheck(int& cnt, bool& flg, int maxframenum);