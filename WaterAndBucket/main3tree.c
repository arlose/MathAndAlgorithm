/* 有3个水桶的容量为8升，5升和3升。 8升水桶里面装满了水。如果利用另外两个桶，得到4升水？ (没有无限水) */
#include <stdio.h>

// assert Bucket1 > Bucket2 > Bucket3
#define Bucket1 8
#define Bucket2 5
#define Bucket3 3

#define Target1 4
#define Target2 4

#define MAX (Bucket1+1)*(Bucket2+1)*(Bucket3+1)

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
    for(k=0;k<=Bucket1;k++)
        for(j=0;j<=Bucket2;j++)
            for(i=0;i<=Bucket3;i++)
            {
                stats[k][j][i] = -1;
            }
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

int Transfer(int b1, int b2, int b3, int lnum, int *trackidx)
{
    int init1 = b1;
    int init2 = b2;
    int init3 = b3;

    int tmp1 = b1;
    int tmp2 = b2;
    int tmp3 = b3;

    int idx = *trackidx;
    
    printf("第%d层时桶水量: %d %d %d\n", lnum, init1, init2, init3);

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
            res2 = tmp2-(init2);
            if(stats[tmp1][tmp2][tmp3]==-1)
            {
                stats[tmp1][tmp2][tmp3] = lnum+1;
                printf("\t将桶1 %d升倒入桶2\n", res2);
                printf("\t第%d层，此时水桶水量: %d %d %d\n", lnum+1, tmp1, tmp2, tmp3);
                settrack(idx, lnum+1, tmp1, tmp2, tmp3, init1, init2, init3);
                idx++;
            }
        }
        /*复原*/
        tmp1 = init1;
        tmp2 = init2;
        tmp3 = init3;
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
            res3 = tmp3-(init3);
            if(stats[tmp1][tmp2][tmp3]==-1)
            {
                stats[tmp1][tmp2][tmp3] = lnum+1;
                printf("\t将桶1 %d升倒入桶3\n", res3);
                printf("\t第%d层，此时水桶水量: %d %d %d\n", lnum+1, tmp1, tmp2, tmp3);
                settrack(idx, lnum+1, tmp1, tmp2, tmp3, init1, init2, init3);
                idx++;
            }
        }
    }

    /*复原*/
    tmp1 = init1;
    tmp2 = init2;
    tmp3 = init3;

    if(tmp2!=0) /* 桶2非空 */
    {
        /* 桶2倒入桶1 */
        if(tmp1<Bucket1)
        {
            int res1 = Bucket1-tmp1;
            if(tmp2>=res1)
            {
                tmp2 = tmp2-res1;
                tmp1 = Bucket1;
            }
            else
            {
                tmp1 = tmp1+tmp2;
                tmp2 = 0;
            }
            res1 = tmp1-(init1);
            if(stats[tmp1][tmp2][tmp3]==-1)
            {
                stats[tmp1][tmp2][tmp3] = lnum+1;
                printf("\t将桶2 %d升倒入桶1\n", res1);
                printf("\t第%d层，此时水桶水量: %d %d %d\n", lnum+1, tmp1, tmp2, tmp3);
                settrack(idx, lnum+1, tmp1, tmp2, tmp3, init1, init2, init3);
                idx++;
            }
        }
        /*复原*/
        tmp1 = init1;
        tmp2 = init2;
        tmp3 = init3;
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
            res3 = tmp3-(init3);
            if(stats[tmp1][tmp2][tmp3]==-1)
            {
                stats[tmp1][tmp2][tmp3] = lnum+1;
                printf("\t将桶2 %d升倒入桶3\n", res3);
                printf("\t第%d层，此时水桶水量: %d %d %d\n", lnum+1, tmp1, tmp2, tmp3);
                settrack(idx, lnum+1, tmp1, tmp2, tmp3, init1, init2, init3);
                idx++;
            }
        }
    }

    /*复原*/
    tmp1 = init1;
    tmp2 = init2;
    tmp3 = init3;

    if(tmp3!=0) /* 桶3非空 */
    {
        /* 桶3倒入桶1 */
        if(tmp1<Bucket1)
        {
            int res1 = Bucket1-tmp1;
            if(tmp3>=res1)
            {
                tmp3 = tmp3-res1;
                tmp1 = Bucket1;
            }
            else
            {
                tmp1 = tmp1+tmp3;
                tmp3 = 0;
            }
            res1 = tmp1-(init1);
            if(stats[tmp1][tmp2][tmp3]==-1)
            {
                stats[tmp1][tmp2][tmp3] = lnum+1;
                printf("\t将桶3 %d升倒入桶1\n", res1);
                printf("\t第%d层，此时水桶水量: %d %d %d\n", lnum+1, tmp1, tmp2, tmp3);
                settrack(idx, lnum+1, tmp1, tmp2, tmp3, init1, init2, init3);
                idx++;
            }
        }
        /*复原*/
        tmp1 = init1;
        tmp2 = init2;
        tmp3 = init3;
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
            res2 = tmp2-(init2);
            if(stats[tmp1][tmp2][tmp3]==-1)
            {
                stats[tmp1][tmp2][tmp3] = lnum+1;
                printf("\t将桶3 %d升倒入桶2\n", res2);
                printf("\t第%d层，此时水桶水量: %d %d %d\n", lnum+1, tmp1, tmp2, tmp3);
                settrack(idx, lnum+1, tmp1, tmp2, tmp3, init1, init2, init3);
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
    int b1 = Bucket1;
    int b2 = 0;
    int b3 = 0;
    
    init();

    /* 桶的状态 8 0 0 */
    stats[b1][b2][b3] = 0;

    int lnum = 0;
    int trackidx = 1;

    while(1)
    {
        int flag = 0;
        for(k=0;k<MAX;k++)
        {
            if(track[k][0]==lnum)
            {
                flag = flag + Transfer(track[k][1], track[k][2], track[k][3], lnum, &trackidx);
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



