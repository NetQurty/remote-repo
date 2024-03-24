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
void update(char** temp, int index, int n,int flag)//������һ�е�Q������������
{
    //�����У�ΪQʱ�������ܹ�������λ�ü�һ������Ϊ�Ա��������������ٷ��ûʺ�
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
    if (index == n)//�к��Ѿ�Ϊn
    {
        //��temp�����е����ݸ��Ƶ�����������ȥ
        retstring[list] = (char**)calloc(n, sizeof(char*));//��Ϊn
        for (int i = 0; i < index; i++)//����n��
        {
            retstring[list][i] = (char*)calloc((n + 1), sizeof(char));//ÿһi����n�У��ַ������һλ��'\0' 
            retstring[list][i] = (char*)memcpy(retstring[list][i], temp[i], (n + 1) * sizeof(char));//����
        }
        (*returnColumnSizes)[list] = index;
        list++;
        return ;
    }
     
    for (int i = 0; i < n; i++)
    {
        //��ǰλ��δ���ʺ󹥻���
        if (judge[index][i] == 0)
        {
            temp[index][i] = 'Q';//�ݴ������λ�÷��ûʺ�
            update(temp, index, n,1);//Ϊ��һ��Q���ܹ������ķ�Χ��ֵ
            index++;//�кż�һ
            backtracking(n, returnColumnSizes, index);//����ݹ�
            index--;//����
            update(temp, index, n,-1);
            temp[index][i] = '.';//����
        }
    }
}
char*** solveNQueens(int n, int* returnSize, int** returnColumnSizes)
{
    extern char*** retstring;
    extern char** temp;
    extern int list;
    extern int** judge;
    //���ٷ������飬����ʼ��
    retstring = (char***)calloc(MAXINT, sizeof(char**));
    //�ݴ�������Ϊn�У�������ÿ�г�ʼ��Ϊ��ָ��
    temp = (char**)calloc(n, sizeof(char*));
    //�ݴ�������������Ϊn+1
    for (int i = 0; i < n; i++)
    {
        temp[i] = (char*)calloc((n + 1), sizeof(char));
        for (int j = 0; j < n; j++)
        {
            temp[i][j] = '.';
        }
    }
    //�ж���������
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
            printf("%d�ʺ�ĵ�%d�ֽⷨ: \n", n, i + 1);
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
        printf("%d �ʺ�Ľⷨ��%d��:\n", i+1,arr[i]);
    }
}4