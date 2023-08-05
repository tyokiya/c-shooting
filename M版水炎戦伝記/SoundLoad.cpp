#include"DxLib.h"
#include "SoundLoad.h"

//�T�E���h�n���h���O���[�o���ϐ�
extern int PlayerShotSound;
extern int BombSound;
extern int EnemySound1;
extern int EnemySound2;
extern int GetSound;
extern int EnemySound3;        //�ړ���
extern int EnemySound4;
extern int EnemySound5;
extern int EnemySound6;
extern int SordSound;
extern int DamageSound;                //��e�T�E���h�n���h��
extern int DownSE;             //���j���̃T�E���h�n���h��
extern int EnemyBombSound;     //�G�̔����T�E���h�n���h��

void LoadPlySound()
{
	//�T�E���h�ǂݍ���
	PlayerShotSound = LoadSoundMem("sound/player/shot.mp3");
	BombSound = LoadSoundMem("sound/player/bomb2.mp3");
	GetSound = LoadSoundMem("sound/player/item.mp3");
	DamageSound = LoadSoundMem("sound/player/damage.mp3");
	//���ʂ̐ݒ�
	ChangeVolumeSoundMem(30 + 60, PlayerShotSound);
	ChangeVolumeSoundMem(80 + 60, BombSound);
	ChangeVolumeSoundMem(110 + 60, GetSound);
	ChangeVolumeSoundMem(80 + 60, DamageSound);
}

void LoadEnemySound()
{
	//�T�E���h�ǂݍ���
	EnemySound1 = LoadSoundMem("sound/enemy/se_flame2.mp3");
	EnemySound2 = LoadSoundMem("sound/enemy/sound2.mp3");
	EnemySound3 = LoadSoundMem("sound/enemy/koto.mp3");
	EnemySound4 = LoadSoundMem("sound/enemy/frame.mp3");
	EnemySound5 = LoadSoundMem("sound/enemy/sound3.mp3");
	EnemySound6 = LoadSoundMem("sound/enemy/sound4.mp3");
	SordSound = LoadSoundMem("sound/enemy/sord.mp3");
	DownSE = LoadSoundMem("sound/enemy/downSE.mp3");
	EnemyBombSound = LoadSoundMem("sound/enemy/bomb.mp3");
	//���ʂ̐ݒ�
	ChangeVolumeSoundMem(40 + 60, EnemySound1);
	ChangeVolumeSoundMem(80 + 60, EnemySound2);
	ChangeVolumeSoundMem(120 + 60, EnemySound3);
	ChangeVolumeSoundMem(60 + 60, EnemySound4);
	ChangeVolumeSoundMem(50 + 60, EnemySound5);
	ChangeVolumeSoundMem(60 + 60, EnemySound6);
	ChangeVolumeSoundMem(150 + 60, SordSound);
	ChangeVolumeSoundMem(90 + 60, DownSE);
	ChangeVolumeSoundMem(75 + 60, EnemyBombSound);
}

