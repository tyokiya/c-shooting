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
/// �G�t�F�N�g�̕`��
/// </summary>
/// <param name="efect">�`�悷��G�t�F�N�g</param>
/// <param name="num">�`�悷��G�t�F�N�g�̔z��ԍ�</param>
/// <param name="x">�`�悷�钆�S���Wx</param>
/// <param name="y">�`�悷�钆�S���Wy</param>
void EfectDraw(int efect[], int num, float x, float y);