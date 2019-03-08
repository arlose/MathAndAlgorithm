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

int main()
{
    int k = 0;
    int count = 0;
    int x, y;
    int doneflag = 0;

    for(k=0;k<NUM;k++)
    {
        init();
        int traceidx = 0;
        int findflag = 1; // 1表示该行可以放皇后
        printf("----------------%d----------------\n", k);
        Data[0][k] = 1;

        Trace[traceidx] = k;
        traceidx++;
        y = 1;
        for(;y<NUM;y++)
        {
            //printf("-----------------%d %d-------------------\n",y, traceidx);

            if(findflag==1)
                x=0;
            findflag = 0;
            for(;x<NUM;x++)
            {
                if(isValid(x,y)==1)
                {
                    setQueen(x,y);
                    Trace[traceidx] = x;
                    traceidx++;
                    findflag = 1;
                    if(traceidx==NUM)
                    {
                        printResult();
                        printf("###################%d####################\n", ++count);
                        traceidx--;
                        clearQueen(Trace[traceidx],traceidx);
                        //printResult();
                        //printf("--------------------------\n");
                        findflag = 0;
                    }
                    break;
                }
            }
            if(findflag==0)
            {
                //printf("no space %d %d\n", y, traceidx);
                //printResult();
                traceidx--;
                clearQueen(Trace[traceidx],traceidx);
                y=traceidx-1; // 抵消y++
                x=Trace[traceidx]+1;
                if(y==-1)
                {
                    doneflag = 1;
                    break;
                }
            }

        }  
    }

    printf("There are %d types of answers!\n", count);
    return 0;
}