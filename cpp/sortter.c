//version 1.0
#include<stdio.h>
int swat_n(int *a,int *b)
{
    int tmp;
    tmp=*a;
    *a=*b;
    *b=tmp;
    return 0;
}
//冒泡排序基本逻辑
//1. 外循环：位置变量从第一个元素向前循环到结尾，位置变量知识待排位置；
//2. 内循环：从最后一个元素开始，向前检索到位置变量，当出现小数在大数后面时交换位置；
int bubble_s(int num,int ele[])
{
    int f1,f2;
    for(f1=0;f1<num;f1++)
    {
        for(f2=num-1;f2>f1;f2--)
        if(ele[f2]<ele[f2-1]) swat_n(ele+f2,ele+f2-1);
    }
    return 0;
}
//选择排序基本逻辑
//1. 外循环：位置变量从第一个元素向前循环到结尾，位置变量指示待排位置；
//2. 内循环：从位置变量开始向后检索，找到最小值位置，并与位置变量所在元素交换位置；
int choose_s(int num,int ele[])
{
    int f1,f2,min,flag=0;
    for(f1=0;f1<num;f1++)
    {
        min=ele[f1];
        flag=f1;
        for(f2=f1;f2<num;f2++)
        if(min>ele[f2]) 
        {
            min=ele[f2];
            flag=f2;
        }
        swat_n(ele+f1,ele+flag);
    }
    return 0;
}
//快速排序基本逻辑
//1. 外循环：当后循环标识大于前循环标识时，循环开始；
//2. 后循环：当中位值后面的数值小于中位值时，和中位值交换位置；
//3. 前循环：当中位值前面的数值大于中位值时，和中位值交换位置；
//4. 完成内外循环后，继续分别排序起点和中位值以及中位值和结尾之间两部分数列；
int quick_s(int be,int en,int ele[])
{
    int i=be,j=en,mid=(be+en)/2;
    if(be>=en) return 0;
    while(i<j)
    {
        while((ele[j]>=ele[mid])&&(j>mid)) j--;
        if(ele[j]<ele[mid])
        {
            swat_n(ele+j,ele+mid);
            mid=j;
        }
        while((ele[i]<=ele[mid])&&(i<mid)) i++;
        if(ele[i]>ele[mid])
        {
            swat_n(ele+i,ele+mid);
            mid=i;
        }
    }
    quick_s(be,i-1,ele);
    quick_s(i+1,en,ele);
    return 0;
}
//顺序插入排序基本逻辑
//1. 外循环：位置变量从第二个元素向后循环到结尾，位置变量对应数值为待排数；
//2. 前后边界判定；
//3. 对比循环：对比已排数列和待排数值，找到比待排数值大的位置记录；
//4. 插入循环：将已排数列中后面部分数列后移一位，将待排数值插入；
int insert_s(int num, int ele[])
{
    int f1=0,f2=0,f3=0,temp=ele[0];
    for(f1=1;f1<num;f1++)
    {
        if(ele[f1]<ele[0]) f2=0;
        else if(ele[f1]>ele[f1-1]) f2=f1;
        else
        {
            f2=0;
            while(ele[f2]<ele[f1] && f1>f2) f2++;
        }
        temp=ele[f1];
        for(f3=f1;f3>f2;f3--)
        ele[f3]=ele[f3-1];
        ele[f2]=temp;
    }
    return 0;
}
//二分插入排序基本逻辑
//1. 外循环：位置变量从第二个元素向后循环到结尾，位置变量对应数值为待排数；
//2. 前后边界判定；
//3. 对比循环：取已排数列中位值及后继值与待排数对比，如果满足则退出，不满足则依据对比结果进一步取分割两部分的中位值进一步对比；
//4. 插入循环：将已排数列中后面部分数列后移一位，将待排数值插入；
int insert_sc(int num,int ele[])
{
    int f1,f2,f3,temp=ele[0];
    for(f1=1;f1<num;f1++)
    {
        if(ele[f1]<ele[0]) f2=-1;
        else if(ele[f1]>=ele[f1-1]) f2=f1-1;
        else
        {
            f2=(f1-1)/2;
            f3=f2;
            while(ele[f1]>=ele[f2+1]||ele[f1]<ele[f2])
            {
                if(f3/2>0) f3=f3/2;
                if(ele[f1]>=ele[f2+1]) f2=f2+f3;
                else if(ele[f1]<ele[f2]) f2=f2-f3;
            }
        }
        temp=ele[f1];
        for(f3=f1;f3>f2+1;f3--)
        ele[f3]=ele[f3-1];
        ele[f2+1]=temp;
    }
}
//二分插入排序（改进）基本逻辑
//1. 外循环：位置变量从第二个元素向后循环到结尾，位置变量对应数值为待排数；
//2. 前后边界判定；
//3. 对比循环：设置区间起始点为已排数列一头一尾，对比区间中位值和待排数，缩小区间直到区间间隔为前后两个数，记录前数位置；
//4. 插入循环：将已排数列中后面部分数列后移以为，将待排数值插入；
int insert_sc2(int num,int ele[])
{
    int i,j,k,temp;
    for(i=1;i<num;i++)
    {
        if(ele[i]<ele[0]) j=-1;
        else if(ele[i]>ele[i-1]) j=i-1;
        else
        {
            j=0;
            k=i-1;
            while((k-j)>1)
            {
                if(ele[(k+j)/2]>=ele[i]) k=(k+j)/2;
                else j=(k+j)/2;
            }
        }
        temp=ele[i];
        for(k=i;k>j+1;k--)
        ele[k]=ele[k-1];
        ele[j+1]=temp;
    }
}
//分组插入排序基本逻辑
//1. 组别循环：从0开始，到分组数结束，记录各组别的起始位置；
//2. 组内外循环：位置变量从小组第二个数字开始，按照分组值向后循环直到数组结尾，位置变量对应数值为待排数；
//3. 组内边界判定；
//4. 组内对比循环：对比已排数列和待排数值，找到比待排数大的数值位置并记录；
//5. 组内插入循环：将已排数列中找到位置后续的数值向后在组内移一位，将待排数值插入；
int insert_sg(int num,int ele[],int gap)
{
    int time,i,j,k,temp;
    for(time=0;time<gap;time++)
    {
        for(i=time+gap;i<num;i=i+gap)
        {
            if(ele[i]<ele[time]) j=time;
            else if(ele[i]>ele[i-gap]) j=i;
            else
            {
                j=time;
                while(ele[j]<ele[i] && i>j) j=j+gap;
            }
            temp=ele[i];
            for(k=i;k>j;k=k-gap)
            ele[k]=ele[k-gap]; 
            ele[j]=temp;
        }
    }
}
//希尔排序主函数
//分组循环：分组值设定为数组长度一半，并持续二分，分组值作为参数参与分组插入排序；
int shell_s(int num,int ele[])
{
    int f1,par=num/2;
    while(par!=0)
    {
        insert_sg(num,ele,par);
        par=par/2;
    }
    return 0;
}
//归并排序基本逻辑
//分循环：
//并循环：
int merge_s(int num,int ele[])
{

}
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
    printf("8 - Merge Sort\n");
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
            quick_s(0,n-1,a);
            break;
        }
        case 4:
        {
            insert_s(n,a);
            break;
        }
        case 5:
        {
            insert_sc(n,a);
            break;
        }
        case 6:
        {
            insert_sc2(n,a);
            break;
        }
        case 7:
        {
            shell_s(n,a);
            break;
        }
        case 8;
        {
            merge_s(n,a);
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