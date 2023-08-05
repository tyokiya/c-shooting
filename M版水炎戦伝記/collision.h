#pragma once
#include "player.h"
#include"enemy.h"

// �����蔻���`
struct sHitRect
{
	float w;		// �������`���s�N�Z����
	float h;        // �������`�����s�N�Z����
	float worldLX;  // �����蔻�荶��X���W
	float worldLY;  // �����蔻�荶��Y���W
	float worldRX;  // �����蔻��E��X���W
	float worldRY;  // �����蔻��E��Y���W
	float CenterX;	//�����蔻��̒��Sx
	float CenterY;	//�����蔻��̒��Sy
};

/// <summary>
/// �v���C���[�̓����蔻��̐ݒ�
/// </summary>
/// <param name="Rect">�����������������蔻��萔</param>
/// <param name="w">�����蔻��̕�</param>
/// <param name="h">�����蔻�荂��</param>
/// <param name="CenterPointX">�q�b�g�T�[�N���̒��S���Wx</param>
/// <param name="CenterPointY">�q�b�g�T�[�N���̒��S���Wy</param>
void PlyinitRect(sHitRect& Rect, float w, float h, float CenterPointX, float CenterPointY);

/// <summary>
/// �G�̓����蔻��ݒ�
/// </summary>
/// <param name="Rect">�����������������蔻��萔</param>
/// <param name="w">�����蔻��̕�</param>
/// <param name="h">�����蔻�荂��</param>
/// <param name="CenterPointX">����̍��Wx</param>
/// <param name="CenterPointY">����̍��Wy</param>
void EnemyInitRect(sHitRect& Rect, float w, float h, float EnemyX, float EnemyY);

/// <summary>
/// �v���C���[�̓����蔻��̍X�V
/// </summary>
/// <param name="CenterPointX">�q�b�g�T�[�N���̒��S���Wx</param>
/// <param name="CenterPointY">�q�b�g�T�[�N���̒��S���Wy</param>
void PlyRectUpdate(sHitRect& Rect, float CenterPointX, float CenterPointY);

/// <summary>
/// �G�̓����蔻��X�V
/// </summary>
/// <param name="CenterPointX">����̍��Wx</param>
/// <param name="CenterPointY">����̍��Wy</param>
void EnemyRectUpdate(sHitRect& Rect, double EnemyX, double EnemyY);

/// <summary>
/// ���@�ƓG�̏Փ˔���
/// </summary>
/// <param name="PlyRect">���@�̓����蔻��\����</param>
/// <param name="EnemyRect">�G�̓����蔻��\����</param>
bool EnemyCollisionJudge(sHitRect PlyRect, sHitRect EnemyRect);

/// <summary>
/// ���e�ƓG�̏Փ˔���
/// </summary>
/// <param name="playerBullet">���e�̓����蔻��\���̔z��</param>
/// <param name="size">�z��̃T�C�Y</param>
/// <param name="EnemyHit">�G�̓����蔻��\����</param>
bool PlyBulletCollision(shot playershot[], int size, sHitRect EnemyHit);

/// <summary>
/// ���e�ƓG�̏Փ˔���(�Ԃ�l�Ȃ�)
/// </summary>
/// <param name="playerBullet">���e�̓����蔻��\���̔z��</param>
/// <param name="size">�z��̃T�C�Y</param>
/// <param name="EnemyHit">�G�̓����蔻��\����</param>
void PlyBulletCollision2(shot playerBullet[], int size, sHitRect EnemyHit);

/// <summary>
/// ���@�ƓG�e1�̏Փ˔���
/// </summary>
/// <param name="PlyRect">���@�̓����蔻��\����</param>
/// <param name="Bullet">�G�e�̓����蔻��</param>
/// <param name="size">�T�C�Y</param>
bool EnemyBullet1Collision(sHitRect PlyRect, EnemyBullet Bullet[], int size);

/// <summary>
/// ���@�ƓG�e4�̓���Փ˔���
/// </summary>
/// <param name="PlyRect">���@�̓����蔻��\����</param>
/// <param name="Bullet">�G�e�̓����蔻��</param>
/// <param name="size">�T�C�Y</param>
bool EnemyBullet15Collision(sHitRect PlyRect, EnemyBullet5 Bullet[], int size);

/// <summary>
/// �A�C�e���̓����蔻��
/// </summary>
void ItemCollision();
