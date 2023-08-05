#include"DxLib.h"
#define _USE_MATH_DEFINES
#include<Windows.h>
#include<math.h>
#include"player.h"
#include"stage.h"
#include"enemy.h"
#include "collision.h"
#include"item.h"
#include"game.h"
#include"title.h"
#include"effect.h"
#include"text.h"

//変数宣言
bool EnemyFlg;			//敵が登場してるかのフラグ
int frame;						//フレーム数のカウント
bool PlyHitFlg ;			//プレイヤーの被弾フラグ
bool EnemyHitFlg;		//敵の被弾フラグ
bool ShieldFlg;			//シールドフラグ
int TimeTextImg;				//時間テキストのイメージハンドル
int ButtonSound;				//スタート音のサウンドハンドル

int BGMSound;					//BGMのサウンドハンドル
bool BGMFlg;					//BGMの再生中フラグ

int BuffEffectCnt;				//エフェクトカウント
bool BuffEffectFlg;					//エフェクトフラグ
extern int BuffEffect[15];			//エフェクト(グローバル変数)

extern int ResultEffect[15];   //リザルトエフェクト
int ResultEffectCnt;				//タイトルエフェクトカウント
bool ResultEffectFlg;				//タイトルエフェクトフラグ
int ResultEffectTimer;					//リザルトタイマー

int GameOverBackImg;					//ゲームオーバー背景画像ハンドル
int GameClearBackImg;					//ゲームクリア背景画像ハンドル
int RogoImg;							//ロゴ画像ハンドル

int Time;						//時間
int TimeFrame;
bool TimeFlg;					//時間表示フラグ
int EffectSound;				//エフェクトサウンドハンドル

extern sHitRect EnemyHit;      //敵のヒット判定構造体(グローバル変数)
extern sHitRect PlyHit;		   //自機の自機のヒット判定構造体(グローバル変数)
extern shot playershot[PShotNum];//プレイヤーの弾の構造体配列(グローバル変数)
extern shot playershot2[PShotNum];
extern shot playershot3[PShotNum];
extern EnemyBullet Bullet1[EnemyBulletNum];        //ランダム弾(グローバル変数)
extern EnemyBullet Bullet2[EnemyBulletNum];        //自機狙い弾(グローバル変数)
extern EnemyBullet Bullet3[EnemyBulletNum];        //円形弾(グローバル変数)
extern EnemyBullet Bullet4[EnemyBulletNum];        //バレット4(グローバル変数)
extern EnemyBullet5 Bullet5[EnemyBulletNum];        //縦長弾(グローバル変数)
extern EnemyBullet Bullet6[EnemyBulletNum];        //壁からの弾(グローバル変数)
extern EnemyBullet Bullet7[EnemyBulletNum];        //魔法陣からの弾(グローバル変数)
extern EnemyBullet Bullet8[EnemyBulletNum];        //魔法陣からの弾(グローバル変数)
extern EnemyBullet Bullet9[EnemyBulletNum];        //円形弾(グローバル変数)

extern int DeathTime;								//プレイヤーの死亡時のフレーム(グローバル変数)
extern int EnemyHp[HpGauge];						//敵HPの配列(3ゲージ分)
extern int PlayLife;								//プレイヤーのライフ数
extern float HitCircleX;     //当たり判定サークルの中心座標x(グローバル変数)
extern float HitCircleY;     //当たり判定サークルの中心座標y(グローバル変数)

extern int Bullet1Img, Bullet2Img, Bullet3Img, Bullet4Img, Bullet5Img;

extern bool RevivalFlg;								//プレイヤーの復活エフェクト
extern int PlyRevivalEffect[10];//エフェクトのグローバル変数
extern int RevivalCnt;     //エフェクトカウント
extern int EmySlashingEffect[10];//敵の斬撃エフェクト
extern int EmySlashingCnt;            //エフェクトカウント
extern bool EmySlashingFlg;           //エフェクトフラグ
extern double EnemyX, EnemyY;		  //敵の座標

extern int TextCnt;            //表示テキストの識別カウント

extern int DownTimeFlg;			//敵の撃破フラグ

//グローバル変数
enum GameScene NowGameScene;	//現在のゲームシーン

//コントローラー
int PadInputTitle;				

bool ResultChangeFlg;			//リザルトの切り替えフラグ
int ResultTime;					//リザルトに表示させる時間
bool ResultTimeFlg;				//リザルトタイムフラグ

extern int BackImg;			//背景の画像ハンドル
extern int Logo2;				//タイトルロゴの画像ハンドル
extern int TextImg;				//テキスト画像ハンドル


//ゲームシーンの名前
char GameSceneNmae[GameSceneCount][GameSceneNameMax]
{
	"タイトル画面",
	"プレイ画面",
	"リザルト画面"
};

//関数

//タイトル初期化
void TitleInit(void)
{
	//画像読み込み
	BackImg = LoadGraph("image/back.jpg");
	Logo2 = LoadGraph("image/logo2.png");
	TextImg = LoadGraph("image/font.png");
	ButtonSound = LoadSoundMem("sound/bgm/button01a.mp3");
	ChangeVolumeSoundMem(80, ButtonSound);
	return;
}
//タイトル管理
void TitleCtrl(void)
{
	TitleProc();
	TitleDraw();
	return;
}
//タイトル処理
void TitleProc(void)
{
	//パッド入力設定
	PadInputTitle = GetJoypadInputState(DX_INPUT_KEY_PAD1);  //キーの読み込み

	//シーン切り替え
	if ((PadInputTitle & PAD_INPUT_3) != 0)
	{
		//サウンドの再生
		PlaySoundMem(ButtonSound, DX_PLAYTYPE_BACK);

		//シーン初期化
		PlayInit();

		//シーン切り替え
		NowGameScene = PlayScene;

		//すぐに切り替える
		return;
	}

	return;
}
//タイトル描画
void TitleDraw(void)
{
	TitleScreenDraw();

	return;
}

//プレイ初期化
void PlayInit(void)
{
	//ステージの初期化
	StageInit();

	//プレイヤー情報の初期化
	PlayerInit();

	//敵情報の初期化
	EnemyInit();

	//アイテム情報初期化
	ItemInit();

	//フレーム初期化
	frame = 0;
	TimeFrame = 0;

	//画像読み込み
	TimeTextImg = LoadGraph("image/TimeText.png");

	//サウンド読み込み
	BGMSound = LoadSoundMem("sound/bgm/battleBGM.mp3");
	ChangeVolumeSoundMem(50 + 60, BGMSound);
	BGMFlg = false;

	//カウント初期化
	BuffEffectCnt = 0;				//エフェクトカウント
	
	//テキストイメージ初期化
	TextInit();

	//フラグ初期化
	EnemyFlg = false;
	PlyHitFlg = false;			//プレイヤーの被弾フラグ
	EnemyHitFlg = false;		//敵の被弾フラグ
	ShieldFlg = false;			//シールドフラグ
	BuffEffectFlg = false;					//エフェクトフラグ

	Time = 0;						//時間

	ResultChangeFlg = false;		//リザルトフラグの初期化

	ResultTimeFlg = false;
	ResultTime = 0;

	return;
}
//プレイ管理
void PlayCtrl(void)
{
	PlayProc();
	PlayDraw();

	return;
}
//プレイ処理
void PlayProc(void)
{
	//シーン切り替え
	if (ResultChangeFlg == true || PlayLife == 0) //プレイヤーのhpが0または敵のhpが0で切り替え
	{
		//BGMを止める
		StopSoundMem(BGMSound);

		//シーン初期化
		ResultInit();

		//シーン切り替え
		NowGameScene = ResultScene;

		//すぐに切り替える
		return;
	}

	return;
}
//プレイ描画
void PlayDraw(void)
{
	//BGMの再生
	if (BGMFlg == false)
	{
		PlaySoundMem(BGMSound, DX_PLAYTYPE_LOOP);
		//フラグを立てる
		BGMFlg = true;
	}

	//被弾フラグの初期化
	PlyHitFlg = false;
	EnemyHitFlg = false;
	//シールドフラグを死亡から2秒後に下ろす
	if (DeathTime + 120 == frame)
	{
		ShieldFlg = false;
		DeathTime = 0;
	}
	else if (frame == 0)
	{
		ShieldFlg = false;
		DeathTime = 0;
	}

	//敵のスライドイン処理(フラグが立ってない場合のみ)
	if (EnemyFlg == false)
	{
		EnemyIn(EnemyFlg);
	}

	//ステージの描画
	StageDraw();

	//プレイヤー更新
	PlayerUpdate(frame);

	//敵の情報更新
	EnemyUpdate(frame);
	
	//アイテム情報更新
	ItemUpdate();

	//アイテムの当たり判定
	ItemCollision();

	//自弾と敵の衝突判定
	if (DownTimeFlg == false)
	{
		if (EnemyHitFlg == false)
		{
			EnemyHitFlg = PlyBulletCollision(playershot, PShotNum, EnemyHit);
		}
		else
		{
			PlyBulletCollision2(playershot, PShotNum, EnemyHit);
		}
		if (EnemyHitFlg == false)
		{
			EnemyHitFlg = PlyBulletCollision(playershot2, PShotNum, EnemyHit);
		}
		else
		{
			PlyBulletCollision2(playershot2, PShotNum, EnemyHit);
		}
		if (EnemyHitFlg == false)
		{
			EnemyHitFlg = PlyBulletCollision(playershot3, PShotNum, EnemyHit);
		}
		else
		{
			PlyBulletCollision2(playershot3, PShotNum, EnemyHit);
		}
	}
	
	
	//無敵時間じゃないかの判定
	if (ShieldFlg == false)
	{
		//敵のライフカウントは1
		//敵と自機の衝突判定
		if (PlyHitFlg == false)
		{
			PlyHitFlg = EnemyCollisionJudge(PlyHit, EnemyHit);
		}

		//ランダム弾1と自機の衝突判定
		if (PlyHitFlg == false)
		{
			PlyHitFlg = EnemyBullet1Collision(PlyHit, Bullet1, EnemyBulletNum);
		}

		//自機狙い弾2と自機の衝突判定
		if (PlyHitFlg == false)
		{
			PlyHitFlg = EnemyBullet1Collision(PlyHit, Bullet2, EnemyBulletNum);
		}

		//円形弾と自機の衝突判定
		if (PlyHitFlg == false)
		{
			PlyHitFlg = EnemyBullet1Collision(PlyHit, Bullet3, EnemyBulletNum);
		}

		//敵のライフカウントは2
		//バレット4(円形弾)と自機の衝突判定
		if (PlyHitFlg == false)
		{
			PlyHitFlg = EnemyBullet1Collision(PlyHit, Bullet4, EnemyBulletNum);
		}
		//バレット5(縦長)の当たり判定
		if (PlyHitFlg == false)
		{
			PlyHitFlg = EnemyBullet15Collision(PlyHit, Bullet5, EnemyBulletNum);
		}
		//バレット6(壁弾)と自機の衝突判定
		if (PlyHitFlg == false)
		{
			PlyHitFlg = EnemyBullet1Collision(PlyHit, Bullet6, EnemyBulletNum);
		}
		//バレット7(魔法陣弾)と自機の衝突判定
		if (PlyHitFlg == false)
		{
			PlyHitFlg = EnemyBullet1Collision(PlyHit, Bullet7, EnemyBulletNum);
		}
		//バレット8(魔法陣弾)と自機の衝突判定
		if (PlyHitFlg == false)
		{
			PlyHitFlg = EnemyBullet1Collision(PlyHit, Bullet8, EnemyBulletNum);
		}
		//バレット9(円形)と自機の衝突判定
		if (PlyHitFlg == false)
		{
			PlyHitFlg = EnemyBullet1Collision(PlyHit, Bullet9, EnemyBulletNum);
		}
	}
	
	
	//プレイヤーの被弾処理
	if (PlyHitFlg == true)
	{
		PlyHitEffect(frame);
		//シールドフラグを立てる
		ShieldFlg = true;
	}

	//敵の被弾処理
	if (EnemyHitFlg == true)
	{
		EnemyHitEfect();
	}

	//無敵時間はシールドの描画
	if (ShieldFlg == true)
	{
		ShieldDraw();
	}

	//プレイヤーを描画
	PlayerDraw();

	//アイテム描画
	ItemDraw();

	//復活エフェクトを描画
	if (RevivalFlg == true)
	{
		EfectDraw(PlyRevivalEffect, RevivalCnt, HitCircleX, HitCircleY, 1.0);
	}

	//フラグが立っている場合エフェクト描画
	if (BuffEffectFlg == true)
	{
		EfectDraw(BuffEffect, BuffEffectCnt, HitCircleX, HitCircleY, 1.0);
	}
	if (BuffEffectFlg == true && frame % 5 == 0)
	{
		//カウントの追加
		EffectCountCheck(BuffEffectCnt, BuffEffectFlg, 15);
	}

	//敵を描画
	EnemyDraw();

	//斬撃エフェクトフラグが立っていたらエフェクト再生
	if (EmySlashingFlg == true)
	{
		EfectDraw(EmySlashingEffect, EmySlashingCnt, EnemyX + EnemySizeX / 2, EnemyY + EnemySizeY / 2, 0.7);
	}
	//エフェクトカウント増加
	if (EmySlashingFlg == true && frame % 5 == 0)
	{
		EffectCountCheck(EmySlashingCnt, EmySlashingFlg, 10);
	}

	//自弾の描画
	ShotDisplay();

	//バレットの描画
	BulletDraw();

	//ステータス表示
	StatusDraw();

	//敵のhpゲージの表示
	DrawMeter();
	

	//テキスト描画
	TextDraw(TextCnt);

	//時間表示
	DrawExtendGraph(995, 70, 1150, 130, TimeTextImg, TRUE);
	DrawFormatString(1010, 120, GetColor(0, 0, 0), "%d:%.2d", Time / 60, Time % 60);
	//フレーム表示
	//DrawFormatString(0, 0, GetColor(0, 0, 0), "%d", frame);
	//DrawFormatString(0, 0, GetColor(0, 0, 0), "%d", EnemyHp[0]);
	//画面初期化
	ScreenFlip();

	//敵が登場したらフレームカウントの増加
	if (EnemyFlg == true)
	{
		frame++;
		TimeFrame++;
		if (TimeFrame % 60 == 0)
		{
			Time++;
		}
	}
	if (EnemyHp[0] == 0 && ResultTimeFlg == false)
	{
		ResultTime = Time;
		ResultTimeFlg = true;
	}
	return;
}

//リザルト初期化
void ResultInit(void)
{
	//エフェクト初期化
	ResultEffectInit();

	ResultEffectCnt = 0;				//タイトルエフェクトカウント
	ResultEffectFlg = true;				//タイトルエフェクトフラグ
	ResultEffectTimer = frame;
	TimeFlg = false;					//フラグ初期化
	//画像読み込み
	GameOverBackImg = LoadGraph("image/gameoverimg.png");
	GameClearBackImg = LoadGraph("image/clear.png");
	RogoImg = LoadGraph("image/rogo.png");

	//サウンド読み込み
	EffectSound = LoadSoundMem("sound/bgm/se_kaminari02.mp3");
	
	//音量設定
	ChangeVolumeSoundMem(80, EffectSound);

	return;
}
//リザルト管理
void ResultCtrl(void)
{
	ResultProc();
	ResultDraw();

	return;
}
//リザルト処理
void ResultProc(void)
{
	//パッド入力設定
	PadInputTitle = GetJoypadInputState(DX_INPUT_KEY_PAD1);  //キーの読み込み
	//シーン切り替え
	if ((PadInputTitle & PAD_INPUT_2) != 0)
	{
		//サウンドの再生
		PlaySoundMem(ButtonSound, DX_PLAYTYPE_BACK);

		//シーン初期化
		PlayInit();

		//シーン切り替え
		NowGameScene = TitleScene;

		//すぐに切り替える
		return;
	}

	return;
}
//リザルト描画
void ResultDraw(void)
{
	//フラグが立っている間はカットイン処理
	/*
	if (ResultEffectFlg == true)
	{
		EfectDraw(ResultEffect, ResultEffectCnt, 720, 450, 1.0);
		if (ResultEffectTimer % 5 == 0)
		{
			
			//カウントの追加
			ResultEffectCnt++;
			//最大値になったら初期化
			if (ResultEffectCnt > 15)
			{
				ResultEffectCnt = 0;
				ResultEffectFlg = false;
				ResultEffectTimer = 0;
			}
		}
		if (ResultEffectTimer % 25 == 0)
		{
			//サウンドの停止
			StopSoundMem(EffectSound);
			//サウンドの再生
			PlaySoundMem(EffectSound, DX_PLAYTYPE_BACK);
		}
		
	}
	
	else
	{*/
		//クリアかゲームオーバーの判定
		if (EnemyHp[0] <= 0)
		{
			//クリア画面描画
			DrawGraph(0, 0, GameClearBackImg, TRUE);
			SetFontSize(175);
			if (ResultEffectTimer % 25 == 0)
			{
				if (TimeFlg == true)
				{
					TimeFlg = false;
				}
				else
				{
					TimeFlg = true;
				}
			}
			//クリア時間表示
			if (TimeFlg == true)
			{
				DrawFormatString(480, 400, GetColor(255, 255, 255), "%d:%.2d", ResultTime / 60, ResultTime % 60);
			}
			//ロゴの表示
			DrawGraph(300, 600, RogoImg, TRUE);
		}
		else
		{
			//ゲームオーバー画面描画
			DrawGraph(0, 0, GameOverBackImg, TRUE);
			if (ResultEffectTimer % 25 == 0)
			{
				if (TimeFlg == true)
				{
					TimeFlg = false;
				}
				else
				{
					TimeFlg = true;
				}
			}
			//ロゴの表示
			if (TimeFlg == true)
			{
				DrawGraph(300, 600, RogoImg, TRUE);
			}
			
		}
	/*}*/
	ResultEffectTimer++;
	return;
}




