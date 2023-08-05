#include"DxLib.h"
#include"stage.h"

//�ϐ�
int i, j;                    //���[�v�J�E���g
int BackImgBase;             //�x�[�X�ƂȂ�w�i
int BlockImg[BrockPattern];  //�v���C��ʂ̔w�i
int LineColor;               //���̐F
int Logo;                    //�^�C�g�����S

/// <summary>
/// �}�b�v���̏�����
/// </summary>
void StageInit()
{
    //�摜�̓ǂݍ���
    BackImgBase = LoadGraph("image/backimg.png");
    BlockImg[0] = LoadGraph("image/block0.bmp");
    BlockImg[1] = LoadGraph("image/block1.bmp");
    LineColor = GetColor(105, 105, 105);
    Logo = LoadGraph("image/logo.png");
}

/// <summary>
/// �}�b�v�̕`��
/// </summary>
void StageDraw()
{
    //�x�[�X�w�i�̕\��
    DrawExtendGraph(0, 0, WindowMaxX, WindowMaxY, BackImgBase, FALSE);
    
    //�u���b�N��~���l�߂�
    for (i = 0; i < BlockMaxY; i++)
    {
        for (j = 0; j < BlockMaxX; j++)
        {
            DrawGraph(j * BlockSize + GameWindowX1, i * BlockSize, BlockImg[(i + j) % 2], false);
        }
    }
    //���E���̕\��
    DrawLine(GameWindowX1 - 5, 0, GameWindowX1 - 5, WindowMaxY, LineColor, 10);
    DrawLine(GameWindowX2, 0, GameWindowX2, WindowMaxY, LineColor, 10);
    DrawLine(GameWindowX1, WindowMaxY - 5, GameWindowX2, WindowMaxY - 5, LineColor, 10);

    //�^�C�g�����S�̕`��
    DrawExtendGraph(1000, 420, 1440, 900, Logo, true);
}










