#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int adde(int *n0,int *n1)
{
    int val ;
    val = *n0 + *n1;
    return val;
}
int sub(int *n0,int *n1)
{
    int val = *n0 - *n1;
    return val;
}

float divi(int*n0,int *n1)
{
    float val = (float) *n0 / *n1;
    return val;
}

float mul(int *n0,int *n1)
{
    float val = (float) *n0 * (float) *n1;
    return val;
}


int main()
{
    int n0,n1;

    printf("input n0 \n");
    scanf("%d",&n0);
    printf("input n1 \n");
    scanf("%d",&n1);
    float val;
    char opt;
    printf("input option ");
    scanf(" %c", &opt);
    printf("Your Option = %c\n", opt);
    
    switch (opt)
    {
        case '+':
        val = adde(&n0,&n1);
        printf(" result =  %d",(int) val);
        return 0;
            break;
        case '-':
            val = sub(&n0,&n1);
        printf("result = %d",(int) val);
        return 0;
            break;
        case '/':
            val = divi(&n0,&n1);
           printf("result = %f",val);
           return 0;
            break;
        case '*':
            val = mul(&n0,&n1);
           printf("result = %f",val);
           return 0;
            break;
        default:
        return 0;
            break;
    }
    
}