#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#define N 11
#define MAXINT 40000
char*** retstring;
char** temp;
int list;
int** judge;
void update(char** temp, int index, int n,int flag)//更新上一行的Q所攻击的区域
{
    //检测该行，为Q时，将其能攻击到的位置加一，即该为以被攻击到，不可再放置皇后
    for (int i = 0; i < n; i++)
    {
        if (temp[index][i] == 'Q')
        {
            for (int j = index; j < n; j++)
            {
                judge[j][i]+=flag;
                if (i + j - index < n)
                {
                    judge[j][i + j - index]+=flag;
                }
                if (i - (j - index) >= 0)
                {
                    judge[j][i - (j - index)]+=flag;
                }
            }
            break;
        }
    }
}
void backtracking(int n, int** returnColumnSizes, int index)
{
    if (index == n)//行号已经为n
    {
        //将temp数组中的内容复制到返回数组中去
        retstring[list] = (char**)calloc(n, sizeof(char*));//行为n
        for (int i = 0; i < index; i++)//开辟n行
        {
            retstring[list][i] = (char*)calloc((n + 1), sizeof(char));//每一i行有n列，字符串最后一位存'\0' 
            retstring[list][i] = (char*)memcpy(retstring[list][i], temp[i], (n + 1) * sizeof(char));//拷贝
        }
        (*returnColumnSizes)[list] = index;
        list++;
        return ;
    }
     
    for (int i = 0; i < n; i++)
    {
        //当前位置未被皇后攻击到
        if (judge[index][i] == 0)
        {
            temp[index][i] = 'Q';//暂存数组该位置放置皇后
            update(temp, index, n,1);//为上一行Q所能攻击到的范围赋值
            index++;//行号加一
            backtracking(n, returnColumnSizes, index);//进入递归
            index--;//回溯
            update(temp, index, n,-1);
            temp[index][i] = '.';//回溯
        }
    }
}
char*** solveNQueens(int n, int* returnSize, int** returnColumnSizes)
{
    extern char*** retstring;
    extern char** temp;
    extern int list;
    extern int** judge;
    //开辟返回数组，并初始化
    retstring = (char***)calloc(MAXINT, sizeof(char**));
    //暂存数组设为n行，并将其每行初始化为空指针
    temp = (char**)calloc(n, sizeof(char*));
    //暂存数组列数设置为n+1
    for (int i = 0; i < n; i++)
    {
        temp[i] = (char*)calloc((n + 1), sizeof(char));
        for (int j = 0; j < n; j++)
        {
            temp[i][j] = '.';
        }
    }
    //判断数组设置
    judge = (int**)calloc(n, sizeof(int*));
    for (int i = 0; i < n; i++)
    {
        judge[i] = (int*)calloc(n, sizeof(int));
    }
    *returnColumnSizes = (int*)calloc(MAXINT, sizeof(int));
    list = 0;
    backtracking(n, returnColumnSizes, 0);
    *returnSize = list;
    for (int i = 0; i < n; i++)
    {
        free(temp[i]);
        temp[i] = NULL;
        free(judge[i]);
        judge[i] = NULL;
    }
    temp = NULL;
    judge = NULL;
    return retstring;
}
int main()
{
    int arr[N] = { 0 };
    for (int n = 1; n <= N; n++)
    {
        int size = 0;
        int* sizearr = NULL;
        char*** str1 = solveNQueens(n, &size, &sizearr);
        for (int i = 0; i < size; i++)
        {
            printf("%d皇后的第%d种解法: \n", n, i + 1);
            for (int j = 0; j < sizearr[i]; j++)
            {
                printf("%s\n", str1[i][j]);
            }
            printf("\n");
        }
        arr[n-1] = size;
    }
    for (int i = 0; i < N; i++)
    {
        printf("%d 皇后的解法有%d种:\n", i+1,arr[i]);
    }
}4