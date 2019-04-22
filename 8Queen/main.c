#include <stdio.h>

#define NUM 8

int Data[NUM][NUM];
int record[NUM][NUM];

void init()
{
    for(int j=0;j<NUM;j++)
        for(int i=0;i<NUM;i++)
            Data[j][i]=0;
}

int isValid(int x, int y)
{
    int i,j;
    /* 检查竖直方向 */
    for(j=0;j<y;j++)
    {
        if(Data[j][x]==1)
        {
            printf("V: %d %d\n", j, x);
            return 0;
        }
            
    }
    /* 检查斜向左上方向 */
    for(i=1;i<x;i++)
    {
        if(Data[y-i][x-i]==1)
        {
            printf("L: %d %d\n", y-i, x-i);
            return 0;
        }
    }
    /* 检查斜向右上方向 */
    for(i=x+1;i<NUM;i++)
    {
        if(Data[y-i+x][i]==1)
        {
            printf("R: %d %d\n", j-i+x, i);
            return 0;
        }
    }
    return 1;
}

void setQueen(int x, int y)
{
    printf("set %d %d\n", y, x);
    Data[y][x]=1;
}

void printResult()
{
    for(int j=0;j<NUM;j++)
    {
        for(int i=0;i<NUM;i++)
        {
            printf("%d ", Data[j][i]);
        }
        printf("\n");
    }
        
    return ;
}

int main()
{
    int flag = 0;
    Data[0][0] = 1;
    for(int y=1;y<NUM;y++)
    {
        flag = 0;
        for(int x=0;x<NUM;x++)
        {
            if(isValid(x,y)==1)
            {
                setQueen(x,y);
                flag = 1;
                break;
            }
        }
            
        flag = 1;
    }
    printResult();

    printf("Done!\n");
    return 0;
}