#include <DxLib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "calculation.h"
#include"enemy.h"

void ChangeRadian(EnemyBullet bullet[], int size, int BulletCnt, int angle)
{
    bullet[BulletCnt].angle = angle * (M_PI / 180);
}

void ChangeRadian2(EnemyBullet5 bullet[], int size, int BulletCnt, int angle)
{
    bullet[BulletCnt].angle = angle * (M_PI / 180);
}