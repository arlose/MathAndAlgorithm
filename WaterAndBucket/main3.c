/* 有3个水桶的容量为8升，5升和3升。 8升水桶里面装满了水。如果利用另外两个桶，得到4升水？ (没有无限水) */
#include <stdio.h>

// assert Bucket1 > Bucket2 > Bucket3
#define Bucket1 8
#define Bucket2 5
#define Bucket3 3

#define Target1 4
#define Target2 4

int stats[Bucket1+1][Bucket2+1][Bucket3+1];

void Change(int * b1, int * b2, int * b3)
{
    int tmp1 = *b1;
    int tmp2 = *b2;
    int tmp3 = *b3;

    if(tmp1!=0) /* 桶1非空 */
    {
        /* 桶1倒入桶2 */
        if(tmp2<Bucket2)
        {
            int res2 = Bucket2-tmp2;
            if(tmp1>=res2)
            {
                tmp1 = tmp1-res2;
                tmp2 = Bucket2;
            }
            else
            {
                tmp2 = tmp1+tmp2;
                tmp1 = 0;
            }
            res2 = tmp2-(*b2);
            if(stats[tmp1][tmp2][tmp3]==0)
            {
                stats[tmp1][tmp2][tmp3] = 1;
                *b1 = tmp1;
                *b2 = tmp2;
                printf("将桶1 %d升倒入桶2\n", res2);
                return;
            }
        }

        tmp1 = *b1;
        tmp2 = *b2;
        tmp3 = *b3;
        /* 桶1倒入桶3 */
        if(tmp3<Bucket3)
        {
            int res3 = Bucket3-tmp3;
            if(tmp1>=res3)
            {
                tmp1 = tmp1-res3;
                tmp3 = Bucket3;
            }
            else
            {
                tmp3 = tmp1+tmp3;
                tmp1 = 0;
            }
            res3 = tmp3-(*b3);
            if(stats[tmp1][tmp2][tmp3]==0)
            {
                stats[tmp1][tmp2][tmp3] = 1;
                *b1 = tmp1;
                *b3 = tmp3;
                printf("将桶1 %d升倒入桶3\n", res3);
                return;
            }
        }
    }

    /* 复原假设 */
    tmp1 = *b1;
    tmp2 = *b2;
    tmp3 = *b3;

    if(tmp2!=0) /* 桶2非空 */
    {
        /* 桶2倒入桶1 */
        if(tmp1<Bucket1)
        {
            int res1 = Bucket1-tmp1;
            if(tmp2>=res1)
            {
                tmp1 = Bucket1;
                tmp2 = tmp2-res1;
            }
            else
            {
                tmp1 = tmp1+tmp2;
                tmp2 = 0;
            }
            res1 = tmp1-(*b1);
            if(stats[tmp1][tmp2][tmp3]==0)
            {
                stats[tmp1][tmp2][tmp3] = 1;
                *b1 = tmp1;
                *b2 = tmp2;
                printf("将桶2 %d升倒入桶1\n", res1);
                return;
            }
        }
        tmp1 = *b1;
        tmp2 = *b2;
        tmp3 = *b3;
        /* 桶2倒入桶3 */
        if(tmp3<Bucket3)
        {
            int res3 = Bucket3-tmp3;
            if(tmp2>=res3)
            {
                tmp2 = tmp2-res3;
                tmp3 = Bucket3;
            }
            else
            {
                tmp3 = tmp2+tmp3;
                tmp2 = 0;
            }
            res3 = tmp3-(*b3);
            if(stats[tmp1][tmp2][tmp3]==0)
            {
                stats[tmp1][tmp2][tmp3] = 1;
                *b2 = tmp2;
                *b3 = tmp3;
                printf("将桶2 %d升倒入桶3\n", res3);
                return;
            }
        }
    }

    /* 复原假设 */
    tmp1 = *b1;
    tmp2 = *b2;
    tmp3 = *b3;

    if(tmp3!=0) /* 桶3非空 */
    {
        /* 桶3倒入桶1 */
        if(tmp1<Bucket1)
        {
            int res1 = Bucket1-tmp1;
            if(tmp3>=res1)
            {
                tmp1 = Bucket1;
                tmp3 = tmp3-res1;
            }
            else
            {
                tmp1 = tmp1+tmp3;
                tmp3 = 0;
            }
            res1 = tmp1-(*b1);
            if(stats[tmp1][tmp2][tmp3]==0)
            {
                stats[tmp1][tmp2][tmp3] = 1;
                *b1 = tmp1;
                *b3 = tmp3;
                printf("将桶3 %d升倒入桶1\n", res1);
                return;
            }
        }
        tmp1 = *b1;
        tmp2 = *b2;
        tmp3 = *b3;
        /* 桶3倒入桶2 */
        if(tmp2<Bucket2)
        {
            int res2 = Bucket2-tmp2;
            if(tmp3>=res2)
            {
                tmp3 = tmp3-res2;
                tmp2 = Bucket2;
            }
            else
            {
                tmp2 = tmp3+tmp2;
                tmp3 = 0;
            }
            res2 = tmp2-(*b2);
            if(stats[tmp1][tmp2][tmp3]==0)
            {
                stats[tmp1][tmp2][tmp3] = 1;
                *b3 = tmp3;
                *b2 = tmp2;
                printf("将桶3 %d升倒入桶2\n", res2);
                return;
            }
        }
    }
}

int main()
{
    int b1 = Bucket1;
    int b2 = 0;
    int b3 = 0;
     
    /* 桶的状态 8 0 0 */
    stats[b1][b2][b3] = 1;

    int lastb1 = -1;
    int lastb2 = -1;
    int lastb3 = -1;

    while(1)
    {
        //printf("上次水桶水量: %d %d %d\n", b1, b2, b3);
        if((lastb1==b1)&&(lastb2==b2)&&(lastb3==b3))
        {
            break;
        }
        lastb1 = b1;
        lastb2 = b2;
        lastb2 = b3;
        Change(&b1, &b2, &b3);
        printf("此时水桶水量: %d %d %d\n", b1, b2, b3);
        if(b1==Target1&&b2==Target2)
            break;
        
    }
    return 0;
}


