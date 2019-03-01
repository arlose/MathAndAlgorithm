/* 两个水桶，容积分别为7升和3升，有无限多的水，问如何能获得2升的水? */
#include <stdio.h>

// assert Bucket1 > Bucket2
#define Bucket1 7
#define Bucket2 3

#define Target 2

#define MAX (Bucket1+1)*(Bucket2+1)

/* 记录是否遇到该状态，达到该状态则置为层数，初始为-1 */
int stats[Bucket1+1][Bucket2+1];
/* 分层记录状态转移树，从初始状态开始分层 用5个数来记录：当前层号，当前b1，当前b2，上一层b1，上一层b2 
本例状态树如下：
                00
            70      03
        43      73      30
    40                      33
        13                      60
            10                      63
                01                      72
                    71                      02
                        53                      20
                            50                      23

初始状态值        0 0 0 -1 -1
本例第一层        1 7 0 0 0     1 0 3 0 0
本例第二层        2 4 3 7 0     2 7 3 7 0      2 3 0 0 3
本例第三层        3 4 0 4 3     3 3 3 3 0
........
 */
int track[MAX][5];

void init()
{
    int i;
    int j;
    for(i=0; i<MAX; i++)
    {
        track[i][0] = -1;
        track[i][1] = -1;
        track[i][2] = -1;
        track[i][3] = -1;
        track[i][4] = -1;
    }
    track[0][0] = 0;
    track[0][1] = 0;
    track[0][2] = 0;

    for(j=0;j<=Bucket1;j++)
        for(i=0;i<=Bucket2;i++)
        {
            stats[j][i] = -1;
        }
}

void settrack(int idx, int lnum, int b1, int b2, int upb1, int upb2)
{
    track[idx][0] = lnum;
    track[idx][1] = b1;
    track[idx][2] = b2;
    track[idx][3] = upb1;
    track[idx][4] = upb2;
}

int Transfer(int b1, int b2, int lnum, int *trackidx)
{
    int init1 = b1;
    int init2 = b2;

    int tmp1 = b1;
    int tmp2 = b2;

    int idx = *trackidx;
    
    printf("第%d层时桶水量: %d %d\n", lnum, init1, init2);

    if(tmp1==0) // 桶1是空的情况
    {
        /* 填满桶1 */
        if(stats[Bucket1][tmp2]==-1)
        {
            tmp1 = Bucket1;
            stats[Bucket1][tmp2] = lnum+1;
            printf("\t将桶1装满\n");
            printf("\t第%d层，此时水桶水量: %d %d\n", lnum+1, tmp1, tmp2);
            settrack(idx, lnum+1, tmp1, tmp2, init1, init2);
            idx++;
        }

        /*复原*/
        tmp1 = init1;
        tmp2 = init2;

        /* 用桶2填桶1 */
        if(tmp2!=0)
        {
            tmp1 = tmp2;
            tmp2 = 0;
            if(stats[tmp1][tmp2]==-1)
            {
                stats[tmp1][tmp2] = lnum+1;
                printf("\t将桶2 %d升倒入桶1\n", tmp1);
                printf("\t第%d层，此时水桶水量: %d %d\n", lnum+1, tmp1, tmp2);
                settrack(idx, lnum+1, tmp1, tmp2, init1, init2);
                idx++;
            }
        }
    }
    else /* 桶1非空 */
    {
        /* 倒空桶1 */
        if(stats[0][tmp2]==-1)
        {
            stats[0][tmp2] = lnum+1;
            tmp1 = 0;
            printf("\t将桶1倒空\n");
            printf("\t第%d层，此时水桶水量: %d %d\n", lnum+1, tmp1, tmp2);
            settrack(idx, lnum+1, tmp1, tmp2, init1, init2);
            idx++;
        }

        /*复原*/
        tmp1 = init1;
        tmp2 = init2;

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
            res2 = tmp2-(init2);
            if(stats[tmp1][tmp2]==-1)
            {
                stats[tmp1][tmp2] = lnum+1;
                printf("\t将桶1 %d升倒入桶2\n", res2);
                printf("\t第%d层，此时水桶水量: %d %d\n", lnum+1, tmp1, tmp2);
                settrack(idx, lnum+1, tmp1, tmp2, init1, init2);
                idx++;
            }
        }
    }

    /*复原*/
    tmp1 = init1;
    tmp2 = init2;

    if(tmp2==0) // 桶2是空的情况
    {
        /* 填满桶2 */
        if(stats[tmp1][Bucket2]==-1)
        {
            stats[tmp1][Bucket2] = lnum+1;
            tmp2 = Bucket2;
            printf("\t将桶2装满\n");
            printf("\t第%d层，此时水桶水量: %d %d\n", lnum+1, tmp1, tmp2);
            settrack(idx, lnum+1, tmp1, tmp2, init1, init2);
            idx++;
        }

        /*复原*/
        tmp1 = init1;
        tmp2 = init2;
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
            if(stats[tmp1][tmp2]==-1)
            {
                stats[tmp1][tmp2] = lnum+1;
                printf("\t将桶1 %d升倒入桶2\n", tmp2);
                printf("\t第%d层，此时水桶水量: %d %d\n", lnum+1, tmp1, tmp2);
                settrack(idx, lnum+1, tmp1, tmp2, init1, init2);
                idx++;
            }
        }
    }
    else /* 桶2非空 */
    {
        /* 倒空桶2 */
        if(stats[tmp1][0]==-1)
        {
            stats[tmp1][0] = lnum+1;
            tmp2 = 0;
            printf("\t将桶2倒空\n");
            printf("\t第%d层，此时水桶水量: %d %d\n", lnum+1, tmp1, tmp2);
            settrack(idx, lnum+1, tmp1, tmp2, init1, init2);
            idx++;
        }

        /*复原*/
        tmp1 = init1;
        tmp2 = init2;

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
            res1 = tmp1-(init1);
            if(stats[tmp1][tmp2]==-1)
            {
                stats[tmp1][tmp2] = lnum+1;
                printf("\t将桶2 %d升倒入桶1\n", res1);
                printf("\t第%d层，此时水桶水量: %d %d\n", lnum+1, tmp1, tmp2);
                settrack(idx, lnum+1, tmp1, tmp2, init1, init2);
                idx++;
            }
        }
    }
    if(*trackidx == idx) // 没有下一层了
        return 0;
    else
        *trackidx = idx;
    return 1;
}

int main()
{
    int k;
    int b1 = 0;
    int b2 = 0;
    
    init();

    /* 桶的状态 0 0 */
    stats[b1][b2] = 0;

    int lnum = 0;
    int trackidx = 1;

    while(1)
    {
        int flag = 0;
        for(k=0;k<MAX;k++)
        {
            if(track[k][0]==lnum)
            {
                flag = flag + Transfer(track[k][1], track[k][2], lnum, &trackidx);
            }
            if(track[k][0]==-1)
            {
                printf("-----------------------------------\n");
                break;
            }
        }
        lnum++;
        if(flag==0)
        {
            printf("没有更多可能情况了\n");
            break;
        }
    }
    return 0;
}


