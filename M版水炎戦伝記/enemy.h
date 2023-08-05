#pragma once

//定数
const int InitEnemyX = 420;         //敵の初期x座標
const int InitEnemyY = -200;        //敵の初期y座標
const int EnemySizeX = 140;         //敵の大きさ(横)
const int EnemySizeY = 210;         //敵の大きさ(縦)
const int HpGauge = 3;              //敵のhpゲージ数(3ゲージ)
const int EnemyBulletNum = 5000;           //敵の弾の配列数

//弾関連の定数
const int Bullet1Widh = 25;             //バレット1，2，3の幅と高さ
const int Bullet5Widh = 25;             //バレット4の幅
const int Bullet5Height = 38;           //バレット4の高さ

//敵弾の構造体
struct EnemyBullet
{
    bool shotflg;  //発射中かどうか
    float x;       //x座標
    float y;       //y座標
    float vx;      //移動量x
    float vy;      //移動量y
    float width, height;//画像の幅と高さ
    float angle;      //角度
    int speed;      //速度
};

struct EnemyBullet5
{
    bool shotflg;  //発射中かどうか
    float x;       //x座標
    float y;       //y座標
    float vx;      //移動量x
    float vy;      //移動量y
    int width, height;//画像の幅と高さ
    float angle;      //角度
    int speed;      //速度
    float rx, ry, lx, ly;//当たり判定矩形の角の座標
};

/// <summary>
/// 敵の情報を初期化
/// </summary>
void EnemyInit();

/// <summary>
/// 敵の弾の初期化
/// </summary>
void EnemyBulletInit();

/// <summary>
/// 敵を描画
/// </summary>
void EnemyDraw();

/// <summary>
/// 敵のスライドイン処理
/// </summary>
/// <param name="EnemyFlg">敵が登場してるかのフラグ</param>
void EnemyIn(bool& EnemyFlg);

/// <summary>
/// 敵の情報更新
/// </summary>
/// <param name="frame">現在のフレーム数</param>
void EnemyUpdate(int& frame);

/// <summary>
/// 敵の被弾時の処理
/// </summary>
void EnemyHitEfect();

/// <summary>
/// 敵のhpゲージの表示
/// </summary>
void DrawMeter();

/// <summary>
/// 敵の攻撃パターン１
/// </summary>
/// <param name="frame">現在のフレーム数</param>
void AttackPattern1(int frame);

/// <summary>
/// 敵の攻撃パターン2
/// </summary>
/// <param name="frame">現在のフレーム数</param>
void AttackPattern2(int frame);

/// <summary>
/// 敵の攻撃パターン3
/// </summary>
/// <param name="frame">現在のフレーム数</param>
void AttackPattern3(int frame);

/// <summary>
/// 敵の攻撃パターン4
/// </summary>
/// <param name="frame">現在のフレーム数</param>
void AttackPattern4(int frame);

/// <summary>
/// 敵の攻撃パターン5
/// </summary>
/// <param name="frame">現在のフレーム数</param>
void AttackPattern5(int frame);

/// <summary>
/// 敵の攻撃パターン6
/// </summary>
/// <param name="frame">現在のフレーム数</param>
void AttackPattern6(int frame);

/// <summary>
/// 敵の移動
/// </summary>
void EnemyMove();

/// <summary>
/// バレット1の追加
/// </summary>
/// <param name="x">敵の座標x</param>
/// <param name="y">敵の座標y</param>
void Bullet1Add(double x, double y);

/// <summary>
/// バレット2の追加
/// </summary>
/// <param name="x">敵の座標x</param>
/// /// <param name="y">敵の座標y</param>
void Bullet2Add(double x, double y);

/// <summary>
/// バレット3の追加
/// </summary>
/// <param name="x">敵の中心座標x</param>
/// <param name="y">敵の中心座標y</param>
void Bullet3Add(double x, double y);

/// <summary>
/// バレット4の追加
/// </summary>
/// <param name="x">敵の中心座標x</param>
/// <param name="y">敵の中心座標y</param>
void Bullet4Add(double x, double y);

/// <summary>
/// バレット5の追加
/// </summary>
/// <param name="x">敵の中心座標x</param>
/// <param name="y">敵の中心座標y</param>
void Bullet5Add(double x, double y);

/// <summary>
/// バレット6の追加
/// </summary>
/// <param name="x">発射する壁の座標x</param>
/// <param name="y">発射する壁の座標y</param>
/// <param name="vx">加速度ｘ</param>
/// <param name="vy">加速度ｙ</param>
void Bullet6Add(float x, float y, float vx, float vy);

/// <summary>
/// バレット7(魔法陣自機狙い)の追加
/// </summary>
/// <param name="x">発射する壁の座標x</param>
/// <param name="y">発射する壁の座標y</param>
void Bullet7Add(float x, float y);

/// <summary>
/// バレット8(魔法陣自機狙い)の追加
/// </summary>
/// <param name="x">発射する壁の座標x</param>
/// <param name="y">発射する壁の座標y</param>
void Bullet8Add(float x, float y);

/// <summary>
/// バレット9(円状)の追加
/// </summary>
/// <param name="x">敵の中心座標x</param>
/// <param name="y">敵の中心座標y</param>
void Bullet9Add(double x, double y);

/// <summary>
/// バレットの移動
/// </summary>
/// <param name="Bullet">弾の構造体配列</param>
/// <param name="size">サイズ</param>
/// <param name="widh">弾の幅</param>
/// <param name="hight">弾の高さ</param>
void EnemyBulletMove(EnemyBullet Bullet[], int size, int widh, int hight);

/// <summary>
/// バレット5の移動
/// </summary>
/// <param name="Bullet">弾の構造体配列</param>
/// <param name="size">サイズ</param>
/// <param name="widh">弾の幅</param>
/// <param name="hight">弾の高さ</param>
void EnemyBulletMove5(EnemyBullet5 Bullet[], int size, int widh, int hight);

/// <summary>
/// バレットの描画
/// </summary>
void BulletDraw();

/// <summary>
/// ボムの発動
/// </summary>
void EnemyBulletReset();

/// <summary>
/// 敵を消す
/// </summary>
void EnemyDisappear(int& frame);

/// <summary>
/// 敵の撃破モーション
/// </summary>
void DownMotion(int frame);