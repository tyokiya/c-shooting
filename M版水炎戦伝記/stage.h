#pragma once

//�萔             
const int WindowMaxX = 1440;  //�E�B���h�E�̂��̍ő�l
const int WindowMaxY = 900;   //�E�B���h�E��y�̍ő�l
const int BrockPattern = 2; //�w�i�̃u���b�N�p�^�[����
const int GameWindowX1 = 40; //�Q�[����ʂ̃t���[�����W
const int GameWindowX2 = 1000;
const int GameWindowY = 900;
const int BlockSize = 64;    //�u���b�N�̑傫��
//�z�u�ł���u���b�N�̍ő吔
const int BlockMaxX = 960 / BlockSize;  //x
const int BlockMaxY = 900 / BlockSize;  //y

//�X�e�[�W�̏�����
void StageInit();

//�X�e�[�W�̕`��
void StageDraw();