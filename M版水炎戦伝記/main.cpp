#include<Windows.h>
#include "DxLib.h"
#include"player.h"
#include"stage.h"
#include"enemy.h"
#include "collision.h"
#include"item.h"
#include"game.h"


int WINAPI WinMain(HINSTANCE hIstans, HINSTANCE hPrevInstans, LPSTR lpCmdLibe, int nCmdshow)
{
	//----------------------------------// 
	//��{�ݒ�
	//----------------------------------// 

	//ChangeWindowMode(TRUE);				//�E�B���h�E���[�h�ɂ���
	DxLib_Init();						//���C�u������������ Initialise
	SetMainWindowText("������`�L");	//�E�B���h�E�̖���
	SetDrawScreen(DX_SCREEN_BACK);		//�w�i���Z�b�g����
	SetGraphMode(1440, 900, 16);			//�E�B���h�E�̃T�C�Y�ƃJ���[���[�h�����߂�
	

	extern enum GameScene NowGameScene;	//���݂̃Q�[���V�[��
	// ��ʂ̍X�V���Ԃ̊Ǘ��p�ϐ�
	LONGLONG nowCount, prevCount;                      // �}�C�N���b(100������1�b�P�ʂŎ����擾)
	nowCount = prevCount = GetNowHiPerformanceCount();
	float fixedDeltaTime = 1.0f / 60.0f;               // 60����1�b = 0.01666...�b
	float waitFrameTime = 15500;                       // 16000�}�C�N���b = 16�~���b = 0.016�b

	//�ŏ��̃V�[���̓^�C�g������
	NowGameScene = TitleScene;
	TitleInit();
	//���C�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// deltaTime�v��
		float deltaTime;
		nowCount = GetNowHiPerformanceCount();
		deltaTime = (nowCount - prevCount) / 1000000.0f;

		//��ʍX�V����
		ClearDrawScreen();
		

		//�V�[���؂�ւ�
		switch (NowGameScene)
		{
		case TitleScene:
			TitleCtrl();
			break;
		case PlayScene:
			PlayCtrl();
			break;
		case ResultScene:
			ResultCtrl();
			break;
		default:
			break;
		}

		//60FPS�҂�
		while (GetNowHiPerformanceCount() - nowCount < waitFrameTime)
		{
			;
		}

		prevCount = nowCount;
	}

	//----------------------------------// 
	//�I��
	//----------------------------------// 

	DxLib_End();
	return 0;
}