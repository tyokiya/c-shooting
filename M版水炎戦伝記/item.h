#pragma once

//定数
const int ItemSize = 25;						//アイテムのサイズ
const int ItemMoveSpeed = 2;					//アイテムの移動速度

/// <summary>
/// アイテム情報初期化
/// </summary>
void ItemInit();

/// <summary>
/// アイテム情報更新
/// </summary>
void ItemUpdate();

/// <summary>
/// アイテムの移動
/// </summary>
void ItemMove();

/// <summary>
/// アイテム描画
/// </summary>
void ItemDraw();