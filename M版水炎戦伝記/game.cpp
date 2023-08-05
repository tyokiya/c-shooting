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

//�ϐ��錾
bool EnemyFlg;			//�G���o�ꂵ�Ă邩�̃t���O
int frame;						//�t���[�����̃J�E���g
bool PlyHitFlg ;			//�v���C���[�̔�e�t���O
bool EnemyHitFlg;		//�G�̔�e�t���O
bool ShieldFlg;			//�V�[���h�t���O
int TimeTextImg;				//���ԃe�L�X�g�̃C���[�W�n���h��
int ButtonSound;				//�X�^�[�g���̃T�E���h�n���h��

int BGMSound;					//BGM�̃T�E���h�n���h��
bool BGMFlg;					//BGM�̍Đ����t���O

int BuffEffectCnt;				//�G�t�F�N�g�J�E���g
bool BuffEffectFlg;					//�G�t�F�N�g�t���O
extern int BuffEffect[15];			//�G�t�F�N�g(�O���[�o���ϐ�)

extern int ResultEffect[15];   //���U���g�G�t�F�N�g
int ResultEffectCnt;				//�^�C�g���G�t�F�N�g�J�E���g
bool ResultEffectFlg;				//�^�C�g���G�t�F�N�g�t���O
int ResultEffectTimer;					//���U���g�^�C�}�[

int GameOverBackImg;					//�Q�[���I�[�o�[�w�i�摜�n���h��
int GameClearBackImg;					//�Q�[���N���A�w�i�摜�n���h��
int RogoImg;							//���S�摜�n���h��

int Time;						//����
int TimeFrame;
bool TimeFlg;					//���ԕ\���t���O
int EffectSound;				//�G�t�F�N�g�T�E���h�n���h��

extern sHitRect EnemyHit;      //�G�̃q�b�g����\����(�O���[�o���ϐ�)
extern sHitRect PlyHit;		   //���@�̎��@�̃q�b�g����\����(�O���[�o���ϐ�)
extern shot playershot[PShotNum];//�v���C���[�̒e�̍\���̔z��(�O���[�o���ϐ�)
extern shot playershot2[PShotNum];
extern shot playershot3[PShotNum];
extern EnemyBullet Bullet1[EnemyBulletNum];        //�����_���e(�O���[�o���ϐ�)
extern EnemyBullet Bullet2[EnemyBulletNum];        //���@�_���e(�O���[�o���ϐ�)
extern EnemyBullet Bullet3[EnemyBulletNum];        //�~�`�e(�O���[�o���ϐ�)
extern EnemyBullet Bullet4[EnemyBulletNum];        //�o���b�g4(�O���[�o���ϐ�)
extern EnemyBullet5 Bullet5[EnemyBulletNum];        //�c���e(�O���[�o���ϐ�)
extern EnemyBullet Bullet6[EnemyBulletNum];        //�ǂ���̒e(�O���[�o���ϐ�)
extern EnemyBullet Bullet7[EnemyBulletNum];        //���@�w����̒e(�O���[�o���ϐ�)
extern EnemyBullet Bullet8[EnemyBulletNum];        //���@�w����̒e(�O���[�o���ϐ�)
extern EnemyBullet Bullet9[EnemyBulletNum];        //�~�`�e(�O���[�o���ϐ�)

extern int DeathTime;								//�v���C���[�̎��S���̃t���[��(�O���[�o���ϐ�)
extern int EnemyHp[HpGauge];						//�GHP�̔z��(3�Q�[�W��)
extern int PlayLife;								//�v���C���[�̃��C�t��
extern float HitCircleX;     //�����蔻��T�[�N���̒��S���Wx(�O���[�o���ϐ�)
extern float HitCircleY;     //�����蔻��T�[�N���̒��S���Wy(�O���[�o���ϐ�)

extern int Bullet1Img, Bullet2Img, Bullet3Img, Bullet4Img, Bullet5Img;

extern bool RevivalFlg;								//�v���C���[�̕����G�t�F�N�g
extern int PlyRevivalEffect[10];//�G�t�F�N�g�̃O���[�o���ϐ�
extern int RevivalCnt;     //�G�t�F�N�g�J�E���g
extern int EmySlashingEffect[10];//�G�̎a���G�t�F�N�g
extern int EmySlashingCnt;            //�G�t�F�N�g�J�E���g
extern bool EmySlashingFlg;           //�G�t�F�N�g�t���O
extern double EnemyX, EnemyY;		  //�G�̍��W

extern int TextCnt;            //�\���e�L�X�g�̎��ʃJ�E���g

extern int DownTimeFlg;			//�G�̌��j�t���O

//�O���[�o���ϐ�
enum GameScene NowGameScene;	//���݂̃Q�[���V�[��

//�R���g���[���[
int PadInputTitle;				

bool ResultChangeFlg;			//���U���g�̐؂�ւ��t���O
int ResultTime;					//���U���g�ɕ\�������鎞��
bool ResultTimeFlg;				//���U���g�^�C���t���O

extern int BackImg;			//�w�i�̉摜�n���h��
extern int Logo2;				//�^�C�g�����S�̉摜�n���h��
extern int TextImg;				//�e�L�X�g�摜�n���h��


//�Q�[���V�[���̖��O
char GameSceneNmae[GameSceneCount][GameSceneNameMax]
{
	"�^�C�g�����",
	"�v���C���",
	"���U���g���"
};

//�֐�

//�^�C�g��������
void TitleInit(void)
{
	//�摜�ǂݍ���
	BackImg = LoadGraph("image/back.jpg");
	Logo2 = LoadGraph("image/logo2.png");
	TextImg = LoadGraph("image/font.png");
	ButtonSound = LoadSoundMem("sound/bgm/button01a.mp3");
	ChangeVolumeSoundMem(80, ButtonSound);
	return;
}
//�^�C�g���Ǘ�
void TitleCtrl(void)
{
	TitleProc();
	TitleDraw();
	return;
}
//�^�C�g������
void TitleProc(void)
{
	//�p�b�h���͐ݒ�
	PadInputTitle = GetJoypadInputState(DX_INPUT_KEY_PAD1);  //�L�[�̓ǂݍ���

	//�V�[���؂�ւ�
	if ((PadInputTitle & PAD_INPUT_3) != 0)
	{
		//�T�E���h�̍Đ�
		PlaySoundMem(ButtonSound, DX_PLAYTYPE_BACK);

		//�V�[��������
		PlayInit();

		//�V�[���؂�ւ�
		NowGameScene = PlayScene;

		//�����ɐ؂�ւ���
		return;
	}

	return;
}
//�^�C�g���`��
void TitleDraw(void)
{
	TitleScreenDraw();

	return;
}

//�v���C������
void PlayInit(void)
{
	//�X�e�[�W�̏�����
	StageInit();

	//�v���C���[���̏�����
	PlayerInit();

	//�G���̏�����
	EnemyInit();

	//�A�C�e����񏉊���
	ItemInit();

	//�t���[��������
	frame = 0;
	TimeFrame = 0;

	//�摜�ǂݍ���
	TimeTextImg = LoadGraph("image/TimeText.png");

	//�T�E���h�ǂݍ���
	BGMSound = LoadSoundMem("sound/bgm/battleBGM.mp3");
	ChangeVolumeSoundMem(50 + 60, BGMSound);
	BGMFlg = false;

	//�J�E���g������
	BuffEffectCnt = 0;				//�G�t�F�N�g�J�E���g
	
	//�e�L�X�g�C���[�W������
	TextInit();

	//�t���O������
	EnemyFlg = false;
	PlyHitFlg = false;			//�v���C���[�̔�e�t���O
	EnemyHitFlg = false;		//�G�̔�e�t���O
	ShieldFlg = false;			//�V�[���h�t���O
	BuffEffectFlg = false;					//�G�t�F�N�g�t���O

	Time = 0;						//����

	ResultChangeFlg = false;		//���U���g�t���O�̏�����

	ResultTimeFlg = false;
	ResultTime = 0;

	return;
}
//�v���C�Ǘ�
void PlayCtrl(void)
{
	PlayProc();
	PlayDraw();

	return;
}
//�v���C����
void PlayProc(void)
{
	//�V�[���؂�ւ�
	if (ResultChangeFlg == true || PlayLife == 0) //�v���C���[��hp��0�܂��͓G��hp��0�Ő؂�ւ�
	{
		//BGM���~�߂�
		StopSoundMem(BGMSound);

		//�V�[��������
		ResultInit();

		//�V�[���؂�ւ�
		NowGameScene = ResultScene;

		//�����ɐ؂�ւ���
		return;
	}

	return;
}
//�v���C�`��
void PlayDraw(void)
{
	//BGM�̍Đ�
	if (BGMFlg == false)
	{
		PlaySoundMem(BGMSound, DX_PLAYTYPE_LOOP);
		//�t���O�𗧂Ă�
		BGMFlg = true;
	}

	//��e�t���O�̏�����
	PlyHitFlg = false;
	EnemyHitFlg = false;
	//�V�[���h�t���O�����S����2�b��ɉ��낷
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

	//�G�̃X���C�h�C������(�t���O�������ĂȂ��ꍇ�̂�)
	if (EnemyFlg == false)
	{
		EnemyIn(EnemyFlg);
	}

	//�X�e�[�W�̕`��
	StageDraw();

	//�v���C���[�X�V
	PlayerUpdate(frame);

	//�G�̏��X�V
	EnemyUpdate(frame);
	
	//�A�C�e�����X�V
	ItemUpdate();

	//�A�C�e���̓����蔻��
	ItemCollision();

	//���e�ƓG�̏Փ˔���
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
	
	
	//���G���Ԃ���Ȃ����̔���
	if (ShieldFlg == false)
	{
		//�G�̃��C�t�J�E���g��1
		//�G�Ǝ��@�̏Փ˔���
		if (PlyHitFlg == false)
		{
			PlyHitFlg = EnemyCollisionJudge(PlyHit, EnemyHit);
		}

		//�����_���e1�Ǝ��@�̏Փ˔���
		if (PlyHitFlg == false)
		{
			PlyHitFlg = EnemyBullet1Collision(PlyHit, Bullet1, EnemyBulletNum);
		}

		//���@�_���e2�Ǝ��@�̏Փ˔���
		if (PlyHitFlg == false)
		{
			PlyHitFlg = EnemyBullet1Collision(PlyHit, Bullet2, EnemyBulletNum);
		}

		//�~�`�e�Ǝ��@�̏Փ˔���
		if (PlyHitFlg == false)
		{
			PlyHitFlg = EnemyBullet1Collision(PlyHit, Bullet3, EnemyBulletNum);
		}

		//�G�̃��C�t�J�E���g��2
		//�o���b�g4(�~�`�e)�Ǝ��@�̏Փ˔���
		if (PlyHitFlg == false)
		{
			PlyHitFlg = EnemyBullet1Collision(PlyHit, Bullet4, EnemyBulletNum);
		}
		//�o���b�g5(�c��)�̓����蔻��
		if (PlyHitFlg == false)
		{
			PlyHitFlg = EnemyBullet15Collision(PlyHit, Bullet5, EnemyBulletNum);
		}
		//�o���b�g6(�ǒe)�Ǝ��@�̏Փ˔���
		if (PlyHitFlg == false)
		{
			PlyHitFlg = EnemyBullet1Collision(PlyHit, Bullet6, EnemyBulletNum);
		}
		//�o���b�g7(���@�w�e)�Ǝ��@�̏Փ˔���
		if (PlyHitFlg == false)
		{
			PlyHitFlg = EnemyBullet1Collision(PlyHit, Bullet7, EnemyBulletNum);
		}
		//�o���b�g8(���@�w�e)�Ǝ��@�̏Փ˔���
		if (PlyHitFlg == false)
		{
			PlyHitFlg = EnemyBullet1Collision(PlyHit, Bullet8, EnemyBulletNum);
		}
		//�o���b�g9(�~�`)�Ǝ��@�̏Փ˔���
		if (PlyHitFlg == false)
		{
			PlyHitFlg = EnemyBullet1Collision(PlyHit, Bullet9, EnemyBulletNum);
		}
	}
	
	
	//�v���C���[�̔�e����
	if (PlyHitFlg == true)
	{
		PlyHitEffect(frame);
		//�V�[���h�t���O�𗧂Ă�
		ShieldFlg = true;
	}

	//�G�̔�e����
	if (EnemyHitFlg == true)
	{
		EnemyHitEfect();
	}

	//���G���Ԃ̓V�[���h�̕`��
	if (ShieldFlg == true)
	{
		ShieldDraw();
	}

	//�v���C���[��`��
	PlayerDraw();

	//�A�C�e���`��
	ItemDraw();

	//�����G�t�F�N�g��`��
	if (RevivalFlg == true)
	{
		EfectDraw(PlyRevivalEffect, RevivalCnt, HitCircleX, HitCircleY, 1.0);
	}

	//�t���O�������Ă���ꍇ�G�t�F�N�g�`��
	if (BuffEffectFlg == true)
	{
		EfectDraw(BuffEffect, BuffEffectCnt, HitCircleX, HitCircleY, 1.0);
	}
	if (BuffEffectFlg == true && frame % 5 == 0)
	{
		//�J�E���g�̒ǉ�
		EffectCountCheck(BuffEffectCnt, BuffEffectFlg, 15);
	}

	//�G��`��
	EnemyDraw();

	//�a���G�t�F�N�g�t���O�������Ă�����G�t�F�N�g�Đ�
	if (EmySlashingFlg == true)
	{
		EfectDraw(EmySlashingEffect, EmySlashingCnt, EnemyX + EnemySizeX / 2, EnemyY + EnemySizeY / 2, 0.7);
	}
	//�G�t�F�N�g�J�E���g����
	if (EmySlashingFlg == true && frame % 5 == 0)
	{
		EffectCountCheck(EmySlashingCnt, EmySlashingFlg, 10);
	}

	//���e�̕`��
	ShotDisplay();

	//�o���b�g�̕`��
	BulletDraw();

	//�X�e�[�^�X�\��
	StatusDraw();

	//�G��hp�Q�[�W�̕\��
	DrawMeter();
	

	//�e�L�X�g�`��
	TextDraw(TextCnt);

	//���ԕ\��
	DrawExtendGraph(995, 70, 1150, 130, TimeTextImg, TRUE);
	DrawFormatString(1010, 120, GetColor(0, 0, 0), "%d:%.2d", Time / 60, Time % 60);
	//�t���[���\��
	//DrawFormatString(0, 0, GetColor(0, 0, 0), "%d", frame);
	//DrawFormatString(0, 0, GetColor(0, 0, 0), "%d", EnemyHp[0]);
	//��ʏ�����
	ScreenFlip();

	//�G���o�ꂵ����t���[���J�E���g�̑���
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

//���U���g������
void ResultInit(void)
{
	//�G�t�F�N�g������
	ResultEffectInit();

	ResultEffectCnt = 0;				//�^�C�g���G�t�F�N�g�J�E���g
	ResultEffectFlg = true;				//�^�C�g���G�t�F�N�g�t���O
	ResultEffectTimer = frame;
	TimeFlg = false;					//�t���O������
	//�摜�ǂݍ���
	GameOverBackImg = LoadGraph("image/gameoverimg.png");
	GameClearBackImg = LoadGraph("image/clear.png");
	RogoImg = LoadGraph("image/rogo.png");

	//�T�E���h�ǂݍ���
	EffectSound = LoadSoundMem("sound/bgm/se_kaminari02.mp3");
	
	//���ʐݒ�
	ChangeVolumeSoundMem(80, EffectSound);

	return;
}
//���U���g�Ǘ�
void ResultCtrl(void)
{
	ResultProc();
	ResultDraw();

	return;
}
//���U���g����
void ResultProc(void)
{
	//�p�b�h���͐ݒ�
	PadInputTitle = GetJoypadInputState(DX_INPUT_KEY_PAD1);  //�L�[�̓ǂݍ���
	//�V�[���؂�ւ�
	if ((PadInputTitle & PAD_INPUT_2) != 0)
	{
		//�T�E���h�̍Đ�
		PlaySoundMem(ButtonSound, DX_PLAYTYPE_BACK);

		//�V�[��������
		PlayInit();

		//�V�[���؂�ւ�
		NowGameScene = TitleScene;

		//�����ɐ؂�ւ���
		return;
	}

	return;
}
//���U���g�`��
void ResultDraw(void)
{
	//�t���O�������Ă���Ԃ̓J�b�g�C������
	/*
	if (ResultEffectFlg == true)
	{
		EfectDraw(ResultEffect, ResultEffectCnt, 720, 450, 1.0);
		if (ResultEffectTimer % 5 == 0)
		{
			
			//�J�E���g�̒ǉ�
			ResultEffectCnt++;
			//�ő�l�ɂȂ����珉����
			if (ResultEffectCnt > 15)
			{
				ResultEffectCnt = 0;
				ResultEffectFlg = false;
				ResultEffectTimer = 0;
			}
		}
		if (ResultEffectTimer % 25 == 0)
		{
			//�T�E���h�̒�~
			StopSoundMem(EffectSound);
			//�T�E���h�̍Đ�
			PlaySoundMem(EffectSound, DX_PLAYTYPE_BACK);
		}
		
	}
	
	else
	{*/
		//�N���A���Q�[���I�[�o�[�̔���
		if (EnemyHp[0] <= 0)
		{
			//�N���A��ʕ`��
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
			//�N���A���ԕ\��
			if (TimeFlg == true)
			{
				DrawFormatString(480, 400, GetColor(255, 255, 255), "%d:%.2d", ResultTime / 60, ResultTime % 60);
			}
			//���S�̕\��
			DrawGraph(300, 600, RogoImg, TRUE);
		}
		else
		{
			//�Q�[���I�[�o�[��ʕ`��
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
			//���S�̕\��
			if (TimeFlg == true)
			{
				DrawGraph(300, 600, RogoImg, TRUE);
			}
			
		}
	/*}*/
	ResultEffectTimer++;
	return;
}




