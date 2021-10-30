//高精度加法器
//功能说明：对于两个高精度的数字串进行加法计算（默认加法计算），数字为通用浮点型字符串，允许带有符号。
#include<stdio.h>
#include<string.h>
#include<math.h>
//数组倒置函数；
void swap_order(char arr[])
{
    int i,tmp;
    for(i=0;i<(strlen(arr)/2);i++)
    {
        tmp=arr[strlen(arr)-1-i];
        arr[strlen(arr)-1-i]=arr[i];
        arr[i]=tmp;
    }
}
//字符串对比函数，当第一个字符串逆序大于第二个字符串时返回1，否则返回-1；
int string_cmp_ba(char arr1[], char arr2[])
{
    int cmp_loop=strlen(arr1)-1;
    while(cmp_loop>=0 && arr1[cmp_loop]>=arr2[cmp_loop]) cmp_loop--;
    if(cmp_loop>=0) return -1;
    else return 1;
}
//字符串交换函数，将输入的两个字符串内容交换；
void string_swap(char arr1[], char arr2[])
{
    int str_loop;
    char swap_temp;
    for(str_loop=0;str_loop<strlen(arr1);str_loop++)
    {
        swap_temp=arr1[str_loop];
        arr1[str_loop]=arr2[str_loop];
        arr2[str_loop]=swap_temp;
    }
}
//小数点未知选取函数；
int point_get(char arr[])
{
    int ptpos_loop=strlen(arr)-1;
    while(ptpos_loop!=0 && arr[ptpos_loop]!='.')
    ptpos_loop--;
    return ptpos_loop;
}
//获取数值的正负号信息，1为负数，0为正数；
int sign_get(char *p_arr)
{
    if(*p_arr=='-') return 1;
    else return 0;
}
//字符串符号调整函数，四个函数入口：要调整符号的字符串、调整类型（+为增加，-为删除）、符号内容、位置；
void symbol_process(char arr[], char pro_tag, char sign_tag, int pos)
{
    int pro_loop,flag;
    if(pro_tag=='-')
    {
        pro_loop=0;
        while(pro_loop<strlen(arr) && arr[pro_loop]!=sign_tag) pro_loop++;
        flag=pro_loop;
        for(pro_loop=flag;pro_loop<strlen(arr);pro_loop++)
        arr[pro_loop]=arr[pro_loop+1];
    }
    else if(pro_tag=='+')
    {
        pro_loop=strlen(arr);
        while(pro_loop>pos) 
        {
            arr[pro_loop]=arr[pro_loop-1];
            pro_loop--;
        }
        arr[pos]=sign_tag;
    }
}
//补零函数，三个入口：要补零的高精度数字字符串、补零数量、补零方向；
void zero_process(char arr[],char symbol, int num, char flag)
{
    int ze_loop;
    if(symbol=='+')
    {
        if(flag=='i')
        {
            for(ze_loop=num-1;ze_loop>=0;ze_loop--)
            arr[strlen(arr)+ze_loop]='0';
        }
        else if(flag=='f')
        {
            for(ze_loop=strlen(arr);ze_loop>=0;ze_loop--)
            arr[ze_loop+num]=arr[ze_loop];
            for(ze_loop=num-1;ze_loop>=0;ze_loop--)
            arr[ze_loop]='0';
        }
    }
    else if(symbol=='-')
    {
        if(flag=='i')
        {
            for(ze_loop=0;ze_loop<num;ze_loop++)
            arr[strlen(arr)-1]='\0';
        }
        else if(flag=='f')
        {
            for(ze_loop=0;ze_loop<strlen(arr)-num;ze_loop++)
            arr[ze_loop]=arr[ze_loop+num];
            for(ze_loop=0;ze_loop<num;ze_loop++)
            arr[strlen(arr)-1]='\0';
        }
    }
}
//取加法函数，arr1和arr2为加数被加数，arr3为结果；
//取加法函数在对齐小数点的情况下开始计算，分为两种情况：二者都有数时结果为进位和，仅有其中之一有值时结果为有值一方和进位和；
void haa_plus(char arr1[], char arr2[], char arr3[])
{
    int i=0,car=0;
    while(i<strlen(arr1))
    {
        if((car+arr1[i]-'0'+arr2[i]-'0')>9)
        {
            arr3[i]=car+arr1[i]-'0'+arr2[i]-10;
            car=1;
            i++;
        }
        else if((car+arr1[i]-'0'+arr2[i]-'0')<=9)
        {
            arr3[i]=car+arr1[i]-'0'+arr2[i];
            car=0;
            i++;
        }
    }
    if(car==1)
    {
        arr3[strlen(arr3)]='1';
        car=0;
    }
    arr3[strlen(arr3)]='\0';
}
//取减法函数，arr1为被减数，arr2为减数，arr3为结果；
//减法处理流程：另存数组符号信息，去除符号并比对大小，并用大数减去小数，
void haa_sub(char arr1[], char arr2[], char arr3[])
{
    int i=0,car=0;
    if(string_cmp_ba(arr1,arr2)<0) string_swap(arr1,arr2);
    while(i<strlen(arr1))
    {
        if((car+arr1[i])>=arr2[i])
        {
            arr3[i]=car+arr1[i]-arr2[i]+'0';
            i++;
            car=0;
        }
        else
        {
            arr3[i]=10+car+arr1[i]-arr2[i]+'0';
            i++;
            car=-1;
        }
    }
    arr3[strlen(arr1)]='\0';
}
//计算函数，arr1和arr2为加数及被加数；
//计算包含三种情况：两个都是正数则相加取正，一正一负则取剪，两个都是负数则相加取副；
void calculate_arr(char arr1[], char arr2[], char arr3[])
{
    int int_pt_arr1,int_pt_arr2,int_pt_arr3;
    int float_pt_arr1,float_pt_arr2,float_pt_arr3;
    int sign_arr1,sign_arr2;
    int cal_lp,zeck_int,zeck_float;
    sign_arr1=sign_get(arr1);
    if(sign_arr1==1) symbol_process(arr1,'-','-',0);
    sign_arr2=sign_get(arr2);
    if(sign_arr2==1) symbol_process(arr2,'-','-',0);
    swap_order(arr1);
    swap_order(arr2); 
    float_pt_arr1=point_get(arr1);
    float_pt_arr2=point_get(arr2);
    float_pt_arr3=float_pt_arr1>float_pt_arr2?float_pt_arr1:float_pt_arr2;
    int_pt_arr1=strlen(arr1)-1-float_pt_arr1;
    int_pt_arr2=strlen(arr2)-1-float_pt_arr2;
    int_pt_arr3=int_pt_arr1>int_pt_arr2?int_pt_arr1:int_pt_arr2;
    if(int_pt_arr1>int_pt_arr2) 
        zero_process(arr2,'+',int_pt_arr1-int_pt_arr2,'i');
    else 
        zero_process(arr1,'+',int_pt_arr2-int_pt_arr1,'i');
    if(float_pt_arr1>float_pt_arr2)
        zero_process(arr2,'+',float_pt_arr1-float_pt_arr2,'f');
    else
        zero_process(arr1,'+',float_pt_arr2-float_pt_arr1,'f');
    symbol_process(arr1,'-','.',0);
    symbol_process(arr2,'-','.',0);
    if(sign_arr1==sign_arr2) 
        haa_plus(arr1,arr2,arr3);
    else
        haa_sub(arr1,arr2,arr3);
    zeck_float=0;
    while(arr3[zeck_float]=='0')    zeck_float++;
    zero_process(arr3,'-',zeck_float,'f');
    float_pt_arr3=float_pt_arr3-zeck_float;
    zeck_int=0;
    cal_lp=strlen(arr3)-1;
    while(arr3[cal_lp]=='0')
    {
        cal_lp--;
        zeck_int++;
    }
    zero_process(arr3,'-',zeck_int,'i');
    int_pt_arr3=int_pt_arr3-zeck_int;
    if(sign_arr1==1) arr3[strlen(arr3)]='-';
    if(float_pt_arr3>0) symbol_process(arr3,'+','.',float_pt_arr3);
    swap_order(arr3);
}
void main()
{
    char ele1[1000],ele2[1000],ans[1000];
    gets(ele1);     //第一个数值获取；
    gets(ele2);     //第二个数值获取；
    calculate_arr(ele1,ele2,ans);     //进行数值相加计算，结果保存到结果字符串内；
    puts(ans);
}