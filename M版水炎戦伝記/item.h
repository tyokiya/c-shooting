#pragma once

//�萔
const int ItemSize = 25;						//�A�C�e���̃T�C�Y
const int ItemMoveSpeed = 2;					//�A�C�e���̈ړ����x

/// <summary>
/// �A�C�e����񏉊���
/// </summary>
void ItemInit();

/// <summary>
/// �A�C�e�����X�V
/// </summary>
void ItemUpdate();

/// <summary>
/// �A�C�e���̈ړ�
/// </summary>
void ItemMove();

/// <summary>
/// �A�C�e���`��
/// </summary>
void ItemDraw();