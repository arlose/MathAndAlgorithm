/* 两个水桶，容积分别为7升和3升，有无限多的水，问如何能获得2升的水? */
#include <stdio.h>

// assert Bucket1 > Bucket2
#define Bucket1 7
#define Bucket2 3

#define Target 2

int stats[Bucket1+1][Bucket2+1];

void Change(int * b1, int * b2)
{
    int tmp1 = *b1;
    int tmp2 = *b2;

    if(tmp1==0) // 桶1是空的情况
    {
        /* 填满桶1 */
        if(stats[Bucket1][tmp2]==0)
        {
            stats[Bucket1][tmp2] = 1;
            *b1 = Bucket1;
            printf("将桶1装满\n");
            return;
        }

        /* 用桶2填桶1 */
        if(tmp2!=0)
        {
            tmp1 = tmp2;
            tmp2 = 0;
            if(stats[tmp1][tmp2]==0)
            {
                stats[tmp1][tmp2] = 1;
                *b1 = tmp1;
                *b2 = 0;
                printf("将桶2 %d升倒入桶1\n", tmp1);
                return;
            }
        }
    }
    else /* 桶1非空 */
    {
        /* 倒空桶1 */
        if(stats[0][tmp2]==0)
        {
            stats[0][tmp2] = 1;
            *b1 = 0;
            printf("将桶1倒空\n");
            return;
        }
        /* 桶1倒入桶2 */
        if(tmp2>0&&tmp2<Bucket2)
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
            if(stats[tmp1][tmp2]==0)
            {
                stats[tmp1][tmp2] = 1;
                *b1 = tmp1;
                *b2 = tmp2;
                printf("将桶1 %d升倒入桶2\n", res2);
                return;
            }
        }
    }

    /* 复原假设 */
    tmp1 = *b1;
    tmp2 = *b2;

    if(tmp2==0) // 桶2是空的情况
    {
        /* 填满桶2 */
        if(stats[tmp1][Bucket2]==0)
        {
            stats[tmp1][Bucket2] = 1;
            *b2 = Bucket2;
            printf("将桶2装满\n");
            return;
        }

        /* 用桶1填桶2 */
        if(tmp1!=0)
        {
            if(tmp1>Bucket2)
            {
                tmp2 = Bucket2;
                tmp1 = tmp1-Bucket2;
            }
            else
            {
                tmp2 = tmp1;
                tmp1 = 0;
            }
            if(stats[tmp1][tmp2]==0)
            {
                stats[tmp1][tmp2] = 1;
                *b1 = tmp1;
                *b2 = tmp2;
                printf("将桶1 %d升倒入桶2\n", tmp2);
                return;
            }
        }
    }
    else /* 桶2非空 */
    {
        /* 倒空桶2 */
        if(stats[tmp1][0]==0)
        {
            stats[tmp1][0] = 1;
            *b2 = 0;
            printf("将桶2倒空\n");
            return;
        }
        /* 桶2倒入桶1 */
        if(tmp1>0&&tmp1<Bucket1)
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
            if(stats[tmp1][tmp2]==0)
            {
                stats[tmp1][tmp2] = 1;
                *b1 = tmp1;
                *b2 = tmp2;
                printf("将桶2 %d升倒入桶1\n", res1);
                return;
            }
        }
    }
}

int main()
{
    int b1 = 0;
    int b2 = 0;
    
    /* 桶的状态 0 0 */
    stats[b1][b2] = 1;

    int lastb1 = -1;
    int lastb2 = -1;

    while(1)
    {
        //printf("上次水桶水量: %d %d\n", b1, b2);
        if((lastb1==b1)&&(lastb2==b2))
        {
            break;
        }
        lastb1 = b1;
        lastb2 = b2;
        Change(&b1, &b2);
        printf("此时水桶水量: %d %d\n", b1, b2);
        if(b1==Target||b2==Target)
            break;
        
    }
    return 0;
}


