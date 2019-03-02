/* 有3个水桶的容量为8升，5升和3升。 8升水桶里面装满了水。如果利用另外两个桶，得到4升水？ (没有无限水) */
#include <stdio.h>

// assert Bucket1 > Bucket2 > Bucket3
#define Bucket1 8
#define Bucket2 5
#define Bucket3 3

#define Target1 4
#define Target2 4
#define Target3 0

#define MAX (Bucket1+1)*(Bucket2+1)*(Bucket3+1)

const int BucketMAX[3] = {Bucket1, Bucket2, Bucket3};
const int Target[3] = {Target1, Target2, Target3};
int Current[3]; // = {Bucket1, 0, 0};

/* 记录是否遇到该状态，达到该状态则置为层数，初始为-1 */
int stats[Bucket1+1][Bucket2+1][Bucket3+1];

/* 分层记录状态转移树，从初始状态开始分层 用7个数来记录：当前层号，当前b1，当前b2，当前b3，上一层b1，上一层b2, 上一层b3
本例状态树如下：
                800
            350      503
        323     053      530
    620                      233
        602                      251
            152                      701
                143                      710
                    440                      413

初始状态值        0 8 0 0 -1 -1 -1
本例第一层        1 3 5 0 8 0 0     1 5 0 3 8 0 0
本例第二层        2 3 2 3 3 5 0     2 0 5 3 3 5 0     2 5 3 0 5 0 3
本例第三层        3 6 2 0 3 2 3     3 2 3 3 5 3 0
........
 */
int track[MAX][7];

void init()
{
    int i;
    int j;
    int k;
    for(i=0; i<MAX; i++)
    {
        track[i][0] = -1;
        track[i][1] = -1;
        track[i][2] = -1;
        track[i][3] = -1;
        track[i][4] = -1;
        track[i][5] = -1;
        track[i][6] = -1;

    }
    track[0][0] = 0;
    track[0][1] = Bucket1;
    track[0][2] = 0;
    track[0][3] = 0;

    Current[0] = Bucket1;
    Current[1] = 0;
    Current[2] = 0;

    for(k=0;k<=Bucket1;k++)
        for(j=0;j<=Bucket2;j++)
            for(i=0;i<=Bucket3;i++)
            {
                stats[k][j][i] = -1;
            }

    /* 桶的状态 8 0 0 */
    stats[Bucket1][0][0] = 0;
}

void settrack(int idx, int lnum, int b1, int b2, int b3, int upb1, int upb2, int upb3)
{
    track[idx][0] = lnum;
    track[idx][1] = b1;
    track[idx][2] = b2;
    track[idx][3] = b3;
    track[idx][4] = upb1;
    track[idx][5] = upb2;
    track[idx][6] = upb3;
}

int TransferTo(int fromidx, int toidx, int lnum, int tidx)
{
    int from  = Current[fromidx-1];
    int to    = Current[toidx-1];
    int toMax = BucketMAX[toidx-1];

    int after[3] = {Current[0],Current[1],Current[2]};

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

        if(stats[after[0]][after[1]][after[2]]==-1)
        {
            stats[after[0]][after[1]][after[2]] = lnum+1;
            printf("\t将桶%d %d升倒入桶%d\n", fromidx, res, toidx);
            printf("\t第%d层，此时水桶水量: %d %d %d\n", lnum+1, after[0], after[1], after[2]);
            settrack(tidx, lnum+1, after[0], after[1], after[2], Current[0], Current[1], Current[2]);
            return 1;
        }
    }
    return 0;
}

int Transfer(int lnum, int *trackidx)
{
    int idx = *trackidx;
    int flag = 0;
    
    printf("第%d层时桶水量: %d %d %d\n", lnum, Current[0], Current[1], Current[2]);

    if(Current[0]!=0) /* 桶1非空 */
    {
        /* 桶1倒入桶2 */
        flag = TransferTo(1, 2, lnum, idx);
        idx = idx + flag;
        /* 桶1倒入桶3 */
        flag = TransferTo(1, 3, lnum, idx);
        idx = idx + flag;
    }

    if(Current[1]!=0) /* 桶2非空 */
    {
        /* 桶2倒入桶3 */
        flag = TransferTo(2, 3, lnum, idx);
        idx = idx + flag;
        /* 桶2倒入桶1 */
        flag = TransferTo(2, 1, lnum, idx);
        idx = idx + flag;
    }

    if(Current[2]!=0) /* 桶3非空 */
    {
        /* 桶3倒入桶1 */
        flag = TransferTo(3, 1, lnum, idx);
        idx = idx + flag;
        /* 桶3倒入桶2 */
        flag = TransferTo(3, 2, lnum, idx);
        idx = idx + flag;
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
                Current[2] = track[k][3], 
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
