
#pragma once

#include"DxLib.h"

#define GameSceneCount			3	//�Q�[���V�[���̂���
#define GameSceneNameMax		20	//�Q�[���V�[���̕������}�b�N�X

//�񋓑�

//�Q�[���V�[��
enum GameScene
{
	TitleScene,	//�^�C�g��
	PlayScene,	//�v���C
	ResultScene	//���U���g
};

//�O���̃O���[�o���ϐ�
extern enum GameScene NowGameScene;	//���݂̃Q�[���V�[��

 //�O���̃v���g�^�C�v�錾
 void TitleInit(void);		//�^�C�g��������
 void TitleCtrl(void);		//�^�C�g���Ǘ�
 void TitleProc(void);		//�^�C�g������
 void TitleDraw(void);		//�^�C�g���`��
						  
 void PlayInit(void);			//�v���C������
 void PlayCtrl(void);			//�v���C�Ǘ�
 void PlayProc(void);			//�v���C����
 void PlayDraw(void);			//�v���C�`��

 void ResultInit(void);		//���U���g������
 void ResultCtrl(void);		//���U���g�Ǘ�
 void ResultProc(void);		//���U���g����
 void ResultDraw(void);		//���U���g�`��