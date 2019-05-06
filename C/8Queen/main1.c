#include <stdio.h>

#define NUM 8
#define MAX(a,b) (a)>(b)?(a):(b)
#define MIN(a,b) (a)<(b)?(a):(b)

int Data[NUM][NUM];
/* 保存每行皇后的位置 */
int Trace[NUM];

void init()
{
    for(int j=0;j<NUM;j++)
        for(int i=0;i<NUM;i++)
            Data[j][i]=0;

    for(int j=0;j<NUM;j++)
    {
        Trace[j] = -1;
    }
    
}

int isValid(int x, int y)
{
    int i,j;
    int max = 0;
    if(y==0)
    {
        return 1;
    }
    /* 检查竖直方向 */
    for(j=0;j<y;j++)
    {
        if(Data[j][x]==1)
        {
            //printf("V: %d %d %d %d\n", y, x, j, x);
            return 0;
        }
            
    }
    /* 检查斜向左上方向 */
    max = MIN(x, y);
    for(i=1;i<=max;i++)
    {
        if(Data[y-i][x-i]==1)
        {
            //printf("L: %d %d %d %d\n", y, x, y-i, x-i);
            return 0;
        }
    }
    /* 检查斜向右上方向 */
    max = MIN(NUM-x-1,y);
    for(i=1;i<=max;i++)
    {
        if(Data[y-i][x+i]==1)
        {
            //printf("R: %d %d %d %d\n", y, x, y-i, x+i);
            return 0;
        }
    }
    return 1;
}

void setQueen(int x, int y)
{
    //printf("set %d %d\n", y, x);
    Data[y][x]=1;
}

void clearQueen(int x, int y)
{
    //printf("clear %d %d\n", y, x);
    Data[y][x]=0;
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

int findPlace(int n, int start)
{
    int i;
    int setflag = 0;
    for(i=start;i<NUM;i++)
    {
        if(isValid(i, n))
        {
            setQueen(i, n);
            Trace[n] = i;
            setflag = 1;
            printResult();
            printf("^^^^^^^^^^^^%d %d^^^^^^^^^^^^^^^^^\n", i, n);
            break;
        }
    }
    return setflag;
}

void fillQueen(int n, int start)
{
    int i;
    int setflag=0;
    if(n==0)
    {
        setQueen(0,0);
        Trace[0] = 0;
        return ;
    }
    printf("-------%d %d-----------\n", n-1, start);
    fillQueen(n-1, 0);
    setflag = findPlace(n-1, 0);
    if(setflag==0)
    {
        printf("*************%d %d****************\n", Trace[n-2], n-2);
        clearQueen(Trace[n-2], n-2);
        printResult();
        printf("*************%d %d****************\n", Trace[n-2]+1, n-2);
        //fillQueen(n-2, Trace[n-2]+1);
        setflag = findPlace(n-2, Trace[n-2]+1);
        //fillQueen(n, 0);
        return ;
    }

    return ;
}

int main()
{
    init();
    fillQueen(7, 0);
    printResult();
    return 0;
}