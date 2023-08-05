#pragma once

//�萔
const int InitEnemyX = 420;         //�G�̏���x���W
const int InitEnemyY = -200;        //�G�̏���y���W
const int EnemySizeX = 140;         //�G�̑傫��(��)
const int EnemySizeY = 210;         //�G�̑傫��(�c)
const int HpGauge = 3;              //�G��hp�Q�[�W��(3�Q�[�W)
const int EnemyBulletNum = 5000;           //�G�̒e�̔z��

//�e�֘A�̒萔
const int Bullet1Widh = 25;             //�o���b�g1�C2�C3�̕��ƍ���
const int Bullet5Widh = 25;             //�o���b�g4�̕�
const int Bullet5Height = 38;           //�o���b�g4�̍���

//�G�e�̍\����
struct EnemyBullet
{
    bool shotflg;  //���˒����ǂ���
    float x;       //x���W
    float y;       //y���W
    float vx;      //�ړ���x
    float vy;      //�ړ���y
    float width, height;//�摜�̕��ƍ���
    float angle;      //�p�x
    int speed;      //���x
};

struct EnemyBullet5
{
    bool shotflg;  //���˒����ǂ���
    float x;       //x���W
    float y;       //y���W
    float vx;      //�ړ���x
    float vy;      //�ړ���y
    int width, height;//�摜�̕��ƍ���
    float angle;      //�p�x
    int speed;      //���x
    float rx, ry, lx, ly;//�����蔻���`�̊p�̍��W
};

/// <summary>
/// �G�̏���������
/// </summary>
void EnemyInit();

/// <summary>
/// �G�̒e�̏�����
/// </summary>
void EnemyBulletInit();

/// <summary>
/// �G��`��
/// </summary>
void EnemyDraw();

/// <summary>
/// �G�̃X���C�h�C������
/// </summary>
/// <param name="EnemyFlg">�G���o�ꂵ�Ă邩�̃t���O</param>
void EnemyIn(bool& EnemyFlg);

/// <summary>
/// �G�̏��X�V
/// </summary>
/// <param name="frame">���݂̃t���[����</param>
void EnemyUpdate(int& frame);

/// <summary>
/// �G�̔�e���̏���
/// </summary>
void EnemyHitEfect();

/// <summary>
/// �G��hp�Q�[�W�̕\��
/// </summary>
void DrawMeter();

/// <summary>
/// �G�̍U���p�^�[���P
/// </summary>
/// <param name="frame">���݂̃t���[����</param>
void AttackPattern1(int frame);

/// <summary>
/// �G�̍U���p�^�[��2
/// </summary>
/// <param name="frame">���݂̃t���[����</param>
void AttackPattern2(int frame);

/// <summary>
/// �G�̍U���p�^�[��3
/// </summary>
/// <param name="frame">���݂̃t���[����</param>
void AttackPattern3(int frame);

/// <summary>
/// �G�̍U���p�^�[��4
/// </summary>
/// <param name="frame">���݂̃t���[����</param>
void AttackPattern4(int frame);

/// <summary>
/// �G�̍U���p�^�[��5
/// </summary>
/// <param name="frame">���݂̃t���[����</param>
void AttackPattern5(int frame);

/// <summary>
/// �G�̍U���p�^�[��6
/// </summary>
/// <param name="frame">���݂̃t���[����</param>
void AttackPattern6(int frame);

/// <summary>
/// �G�̈ړ�
/// </summary>
void EnemyMove();

/// <summary>
/// �o���b�g1�̒ǉ�
/// </summary>
/// <param name="x">�G�̍��Wx</param>
/// <param name="y">�G�̍��Wy</param>
void Bullet1Add(double x, double y);

/// <summary>
/// �o���b�g2�̒ǉ�
/// </summary>
/// <param name="x">�G�̍��Wx</param>
/// /// <param name="y">�G�̍��Wy</param>
void Bullet2Add(double x, double y);

/// <summary>
/// �o���b�g3�̒ǉ�
/// </summary>
/// <param name="x">�G�̒��S���Wx</param>
/// <param name="y">�G�̒��S���Wy</param>
void Bullet3Add(double x, double y);

/// <summary>
/// �o���b�g4�̒ǉ�
/// </summary>
/// <param name="x">�G�̒��S���Wx</param>
/// <param name="y">�G�̒��S���Wy</param>
void Bullet4Add(double x, double y);

/// <summary>
/// �o���b�g5�̒ǉ�
/// </summary>
/// <param name="x">�G�̒��S���Wx</param>
/// <param name="y">�G�̒��S���Wy</param>
void Bullet5Add(double x, double y);

/// <summary>
/// �o���b�g6�̒ǉ�
/// </summary>
/// <param name="x">���˂���ǂ̍��Wx</param>
/// <param name="y">���˂���ǂ̍��Wy</param>
/// <param name="vx">�����x��</param>
/// <param name="vy">�����x��</param>
void Bullet6Add(float x, float y, float vx, float vy);

/// <summary>
/// �o���b�g7(���@�w���@�_��)�̒ǉ�
/// </summary>
/// <param name="x">���˂���ǂ̍��Wx</param>
/// <param name="y">���˂���ǂ̍��Wy</param>
void Bullet7Add(float x, float y);

/// <summary>
/// �o���b�g8(���@�w���@�_��)�̒ǉ�
/// </summary>
/// <param name="x">���˂���ǂ̍��Wx</param>
/// <param name="y">���˂���ǂ̍��Wy</param>
void Bullet8Add(float x, float y);

/// <summary>
/// �o���b�g9(�~��)�̒ǉ�
/// </summary>
/// <param name="x">�G�̒��S���Wx</param>
/// <param name="y">�G�̒��S���Wy</param>
void Bullet9Add(double x, double y);

/// <summary>
/// �o���b�g�̈ړ�
/// </summary>
/// <param name="Bullet">�e�̍\���̔z��</param>
/// <param name="size">�T�C�Y</param>
/// <param name="widh">�e�̕�</param>
/// <param name="hight">�e�̍���</param>
void EnemyBulletMove(EnemyBullet Bullet[], int size, int widh, int hight);

/// <summary>
/// �o���b�g5�̈ړ�
/// </summary>
/// <param name="Bullet">�e�̍\���̔z��</param>
/// <param name="size">�T�C�Y</param>
/// <param name="widh">�e�̕�</param>
/// <param name="hight">�e�̍���</param>
void EnemyBulletMove5(EnemyBullet5 Bullet[], int size, int widh, int hight);

/// <summary>
/// �o���b�g�̕`��
/// </summary>
void BulletDraw();

/// <summary>
/// �{���̔���
/// </summary>
void EnemyBulletReset();

/// <summary>
/// �G������
/// </summary>
void EnemyDisappear(int& frame);

/// <summary>
/// �G�̌��j���[�V����
/// </summary>
void DownMotion(int frame);