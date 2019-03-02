/* 两个水桶，容积分别为7升和3升，有无限多的水，问如何能获得2升的水? */
#include <stdio.h>

// assert Bucket1 > Bucket2
#define Bucket1 7
#define Bucket2 3

#define Target 2

#define MAX (Bucket1+1)*(Bucket2+1)

const int BucketMAX[3] = {Bucket1, Bucket2};
int Current[2]; // = {0, 0};

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

    Current[0] = 0;
    Current[1] = 0;

    for(j=0;j<=Bucket1;j++)
        for(i=0;i<=Bucket2;i++)
        {
            stats[j][i] = -1;
        }

    /* 桶的状态 0 0 */
    stats[0][0] = 0;
}

void settrack(int idx, int lnum, int b1, int b2, int upb1, int upb2)
{
    track[idx][0] = lnum;
    track[idx][1] = b1;
    track[idx][2] = b2;
    track[idx][3] = upb1;
    track[idx][4] = upb2;
}

/* fromidx或toidx为-1代表无穷水桶 */
int TransferTo(int fromidx, int toidx, int lnum, int tidx)
{
    int after[2] = {Current[0],Current[1]};
    if(fromidx==-1) // 填满toidx
    {
        after[toidx-1] = BucketMAX[toidx-1];

        if(stats[after[0]][after[1]]==-1)
        {
            stats[after[0]][after[1]] = lnum+1;
            printf("\t将桶%d装满\n", toidx);
            printf("\t第%d层，此时水桶水量: %d %d\n", lnum+1, after[0], after[1]);
            settrack(tidx, lnum+1, after[0], after[1], Current[0], Current[1]);
            return 1;
        }
    }
    else if(toidx==-1) // 倒空fromidx
    {
        after[fromidx-1] = 0;
        if(stats[after[0]][after[1]]==-1)
        {
            stats[after[0]][after[1]] = lnum+1;
            printf("\t将桶%d倒空\n", fromidx);
            printf("\t第%d层，此时水桶水量: %d %d\n", lnum+1, after[0], after[1]);
            settrack(tidx, lnum+1, after[0], after[1], Current[0], Current[1]);
            return 1;
        }
    }
    else // 互相倒水
    {
        int from  = Current[fromidx-1];
        int to    = Current[toidx-1];
        int toMax = BucketMAX[toidx-1];
        if(to<toMax)
        {
            int res = toMax-to;
            if(from>=res)
            {
                from = from-res;
                to = toMax;
            }
            else
            {
                to = from+to;
                from = 0;
            }
            res = to-(Current[toidx-1]);
            after[fromidx-1] = from;
            after[toidx-1] = to;

            if(stats[after[0]][after[1]]==-1)
            {
                stats[after[0]][after[1]] = lnum+1;
                printf("\t将桶%d %d升倒入桶%d\n", fromidx, res, toidx);
                printf("\t第%d层，此时水桶水量: %d %d\n", lnum+1, after[0], after[1]);
                settrack(tidx, lnum+1, after[0], after[1], Current[0], Current[1]);
                return 1;
            }
        }
    }
    return 0;
}

int Transfer(int lnum, int *trackidx)
{
    int idx = *trackidx;
    int flag = 0;
    
    printf("第%d层时桶水量: %d %d\n", lnum, Current[0], Current[1]);

    if(Current[0]==0) // 桶1是空的情况
    {
        /* 填满桶1 */
        flag = TransferTo(-1, 1, lnum, idx);
        idx = idx + flag;
    }
    else /* 桶1非空 */
    {
        /* 倒空桶1 */
        flag = TransferTo(1, -1, lnum, idx);
        idx = idx + flag;

        /* 填满桶1 */
        if(Current[0]<Bucket1)
        {
            flag = TransferTo(-1, 1, lnum, idx);
            idx = idx + flag;
        }

        /* 桶1倒入桶2 */
        if(Current[1]<Bucket2)
        {
            flag = TransferTo(1, 2, lnum, idx);
            idx = idx + flag;
        }
    }

    if(Current[1]==0) // 桶2是空的情况
    {
        /* 填满桶2 */
        flag = TransferTo(-1, 2, lnum, idx);
        idx = idx + flag;
    }
    else /* 桶2非空 */
    {
        /* 倒空桶2 */
        flag = TransferTo(2, -1, lnum, idx);
        idx = idx + flag;

        /* 填满桶2 */
        if(Current[1]<Bucket2)
        {
            flag = TransferTo(-1, 2, lnum, idx);
            idx = idx + flag;
        }

        /* 桶2倒入桶1 */
        if(Current[0]<Bucket1)
        {
            flag = TransferTo(2, 1, lnum, idx);
            idx = idx + flag;
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
    
    init();

    int lnum = 0;
    int trackidx = 1;

    while(1)
    {
        int flag = 0;
        for(k=0;k<MAX;k++)
        {
            if(track[k][0]==lnum)
            {
                Current[0] = track[k][1];
                Current[1] = track[k][2];
                flag = flag + Transfer(lnum, &trackidx);
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


