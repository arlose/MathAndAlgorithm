#include "stdio.h"

#define M 5 // 25宫

int HFdata[M][M];

void init()
{
    for(int j=0;j<M;j++)
        for(int i=0;i<M;i++)
        {
            HFdata[j][i]=0;
        }
}

void printHF()
{
    for(int j=0;j<M;j++)
    {
        for(int i=0;i<M;i++)
        {
            printf("%4d ", HFdata[j][i]);
        }
        printf("\n");
    }
        
}

int main()
{
    int i = M>>1;
    int j = 0;

    init();

    for(int k=1;k<=M*M;k++)
    {
        HFdata[j][i] = k;
        i = (i+1)%M;
        j = (j-1+M)%M;
        if(HFdata[j][i]!=0)
        {
            i = (i-1+M)%M;
            j = (j+2)%M;
        }
    }

    printHF();
    return 0;
}