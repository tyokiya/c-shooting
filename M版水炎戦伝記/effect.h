#pragma once

/// <summary>
/// �v���C���[�̃G�t�F�N�g�̏�����
/// </summary>
void PlyEfectInit();

/// <summary>
/// �G�̃G�t�F�N�g�̏�����
/// </summary>
void EnemyEfectInit();

/// <summary>
/// ���U���g�̃G�t�F�N�g�̏�����
/// </summary>
void ResultEffectInit();

/// <summary>
/// �G�t�F�N�g�̕`��
/// </summary>
/// <param name="efect">�`�悷��G�t�F�N�g</param>
/// <param name="num">�`�悷��G�t�F�N�g�̔z��ԍ�</param>
/// <param name="x">�`�悷�钆�S���Wx</param>
/// <param name="y">�`�悷�钆�S���Wy</param>
/// <param name="size">�`�悷��T�C�Y�{��</param>
void EfectDraw(int efect[], int num, float x, float y, float size);

/// <summary>
/// �G�t�F�N�g�̃J�E���g���`�F�b�N
/// </summary>
/// <param name="cnt">�G�t�F�N�g�J�E���g</param>
/// <param name="flg">�G�t�F�N�g�t���O</param>
/// <param name="maxframenum">�G�t�F�N�g�̍ő�t���[����</param>
void EffectCountCheck(int& cnt, bool& flg, int maxframenum);