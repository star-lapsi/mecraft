#include<stdio.h>
int bubble_s(int num,int ele[])
{
    int f1,f2,temp,parm;
    int *key;
    key=ele;
    parm=num;
    for(f1=0;f1<parm;f1++)
    {
        for(f2=parm-1;f2>f1;f2--)
        if(*(key+f2)<*(key+f2-1))
        {
            temp=*(key+f2);
            *(key+f2)=*(key+f2-1);
            *(key+f2-1)=temp;
        }
    }
    printf("Sorting result is:\n");
    for(f1=0;f1<parm;f1++)
    printf("%d ",*(key+f1));
    printf("\n");
    return 0;
}
int choose_s(int num,int ele[])
{
    int f1,f2,temp,min,flag=0,parm=num;
    int *key;
    key=ele;
    min=*key;
    for(f1=0;f1<parm;f1++)
    {
        min=*(key+f1);
        flag=f1;
        for(f2=f1;f2<parm;f2++)
        if(min>*(key+f2)) 
        {
            min=*(key+f2);
            flag=f2;
        }
        temp=*(key+f1);
        *(key+f1)=min;
        *(key+flag)=temp;
    }
    printf("Sorting result is:\n");
    for(f1=0;f1<parm;f1++)
    printf("%d ",*(key+f1));
    printf("\n");
    return 0;
}
int quick_sort_core(int be,int en,int arr[])
{
    int *row;
    int i,j,mid,temp;
    row=arr;
    i=be;
    j=en;
    mid=(be+en)/2;
    if(be>=en) return 0;
    while(i<j)
    {
        while((*(row+j)>=*(row+mid))&&(j>mid)) j--;
        if(*(row+j)<*(row+mid))
        {
            temp=*(row+j);
            *(row+j)=*(row+mid);
            *(row+mid)=temp;
            mid=j;
        }
        while((*(row+i)<=*(row+mid))&&(i<mid)) i++;
        if(*(row+i)>*(row+mid))
        {
            temp=*(row+i);
            *(row+i)=*(row+mid);
            *(row+mid)=temp;
            mid=i;
        }
    }
    quick_sort_core(be,i-1,row);
    quick_sort_core(i+1,en,row);
    return 0;
}
int quick_s(int num,int ele[])
{
    int f1=0,parm=num;
    int *key;
    key=ele;
    quick_sort_core(f1,parm-1,key);
    printf("Sorting result is:\n");
    for(f1=0;f1<parm;f1++)
    printf("%d ",*(key+f1));
    printf("\n");
    return 0;
}
int shell_s(int num,int ele[])
{
    return 0;
}
int main()
{
    int a[10000],ch=0,gchar=0,i=0,n=0;
    printf("Welcome to Sort-Algorithm Express!\n");
    printf("Please Choose the Algorithm:\n");
    printf("1 - Bubble Sorting\n");
    printf("2 - Choise Sorting\n");
    printf("3 - Quick Sorting\n");
    printf("4 - Shell Sorting\n");
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
            bubble_s(n,a);
            break;
        }
        case 2:
        {
            choose_s(n,a);
            break;
        }
        case 3:
        {
            quick_s(n,a);
            break;
        }
        case 4:
        {
            shell_s(n,a);
            break;
        }
        default:
        {
            break;
        }
    }
    return 0;
}