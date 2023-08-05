#include "DxLib.h"
#include"enemy.h"
#define _USE_MATH_DEFINES
#include<math.h>

void EnemyBulletDraw(EnemyBullet bullet[], int size,int img)
{
    for (int i = 0; i < EnemyBulletNum; i++)
    {
        if (bullet[i].shotflg == true)
        {
            DrawExtendGraph(bullet[i].x, bullet[i].y, bullet[i].x + bullet[i].width, bullet[i].y + bullet[i].height, img, TRUE);
        }
    }
}

void EnemyBulletDraw2(EnemyBullet5 bullet[], int size, int img)
{
    for (int i = 0; i < EnemyBulletNum; i++)
    {
        if (bullet[i].shotflg == true)
        {
            DrawRotaGraph(bullet[i].x, bullet[i].y, 1, bullet[i].angle - (90 * (M_PI / 180)), img, TRUE, FALSE);
        }
    }
}
