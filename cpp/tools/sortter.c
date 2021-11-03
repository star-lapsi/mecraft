//version 1.0
#include<stdio.h>
#include"sorting.h"
int main()
{
    int a[10000],ch=0,gchar=0,i=0,n=0;
    printf("Welcome to Sort-Algorithm Express!\n");
    printf("Please Choose the Algorithm:\n");
    printf("1 - Bubble Sort\n");
    printf("2 - Choise Sort\n");
    printf("3 - Quick Sort\n");
    printf("4 - Insert Sort\n");
    printf("5 - Insert Dichotomy Sort\n");
    printf("6 - Better Insert Dichotomy Sort\n");
    printf("7 - Shell Sort\n");
    printf("8 - Merge Insert Sort\n");
    printf("9 - Merge Sort\n");
    printf("Other - Quit\n");
    scanf("%d",&ch);
    gchar=getchar();
    printf("Please input number of array.\n");
    scanf("%d",&n);
    printf("Please input all numbers in the array.\n");
    for(i=0;i<n;i++)
    scanf("%d",&a[i]);
    gchar=getchar();
    switch(ch)
    {
        case 1:
        {
            bubble_sorting(n,a);
            break;
        }
        case 2:
        {
            choose_sorting(n,a);
            break;
        }
        case 3:
        {
            quick_sorting(0,n-1,a);
            break;
        }
        case 4:
        {
            insert_sorting(n,a);
            break;
        }
        case 5:
        {
            insert_binary_sorting(n,a);
            break;
        }
        case 6:
        {
            insert_binary_im_sorting(n,a);
            break;
        }
        case 7:
        {
            shell_sorting(n,a);
            break;
        }
        case 8:
        {
            merge_insert_sorting(0,n-1,a);
            break;
        }
        case 9:
        {
            merge_sorting(0,n-1,a);
            break;
        }
        default:
        {
            break;
        }
    }
    printf("Sorting result is:\n");
    for(i=0;i<n;i++)
    printf("%d ",a[i]);
    printf("\n");
    return 0;
}