#include <stdio.h>

int main()
{
    int m;
    printf("输入奇数m:");
    scanf("%d", &m);
    while(m % 2 == 0) scanf("%d", &m);
    int a[m][m];
    int i;
    int col,row;

    col = (m-1)/2;
    row = 0;

    a[row][col] = 1; //第一行中间为1

    for(i = 2; i <= m*m; i++) // i比i-1行减1,列加1，i-1是m倍数则行加1列不变
    {
        if((i-1)%m == 0 )
        {
            row++;
        }
        else
        {
            row--;
            row = (row+m)%m;
            col ++;
            col %= m;
        }
        a[row][col] = i;
    }
    for(row = 0;row<m;row++)
    {
        for(col = 0;col < m; col ++)
        {
            printf("%6d",a[row][col]);
        }
        printf("\n");
    }
    return 0;
}