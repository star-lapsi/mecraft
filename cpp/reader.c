#include<stdio.h>
#include<string.h>
struct variaty0
{
    char va_name[100];
    char va_type[100];
    int va_type;
    char va_value[100];
    int va_value;
};
int file_type_c(char arr[])
{
    int ans=0;
    puts(arr);
    if(strcmp(arr,"numbers")==0) ans=1;
    if(strcmp(arr,"strings")==0) ans=2;
    if(strcmp(arr,"mixs")==0) ans=3;
    if(ans==0) printf("Wrong File Type!\n");
    return ans;
}
int va_name_ck(char inp_ch)
{
    if((inp_ch<='Z'&&inp_ch>='A')||(inp_ch<='z'&&inp_ch>='a')||(inp_ch<='0'&&inp_ch>='1'))
    return 1;
    else
    {
        printf("Wrong Variaty Name!\n");
        return 0;
    }
}
int va_type_ck(char inp_ch)
{
    if(inp_ch<='z'&&inp_ch>='a')
        return 1;
    else
    {
        printf("Wrong Variaty Type!\n");
        return 0;
    }
}
int variaty_type_c(char arr[])
{
    int ans=0;
    if(strcmp(arr,"integer")==0) ans=1;
    if(strcmp(arr,"float")==0) ans=2;
    if(strcmp(arr,"char")==0) ans=3;
    if(strcmp(arr,"string")==0) ans=4;
    if(strcmp(arr,"addr")==0) ans=5;
    if(ans==0) printf("Wrong Variaty Type!\n");
    return ans;
}
int main()
{
    struct variaty0 va_arr[1000];
    int ft_flag=0,ft=0,ft_ans=1;        //ft_flag为文件类型读取进度标识；ft为读取标识；ft_ans为文件类型结果；
    int va_be=0,va_en=0,va_flag1=0,va_flag2=0,va_tag=0,va_ans=0;   //va_be、va_en为变量单行读取进度标识；va_flag1为变量名读取标识；va_flag2为变量类型读取标识；va_tag为变量切换标识；
    char ch,f_type[20],va_type[20],va_name[100];
    while(scanf("%c",&ch)!=EOF)
    {
        if(ch=='>') 
        {
            ft_flag=0;
            ft_ans=file_type_c(f_type);
            f_type[ft]='\0';
        }
        if(ft_flag==1) f_type[ft++]=ch;
        if(ch=='<') ft_flag=1;
        if(ft_ans==0) break; 
        if(ch==';')
        {
            va_arr[va_tag].va_name[va_flag2]='\0';
            va_be=0;
            va_en=0;
            va_ans=variaty_type_c(va_arr[va_tag].va_value);
            va_tag++;
        }
        if(ch==':')
        {
            va_arr[va_tag].va_name[va_flag1]='\0';
            va_flag2=0;
            va_be=0;
            va_en=1;
        }
        if(ch=='#')
        {
            va_flag1=0;
            va_be=1;
            va_en=0;
        }
        if(va_be==1 && va_name_ck(ch)==1)
            va_arr[va_tag].va_name[va_flag1++]=ch;
        if(va_en==1 && va_type_ck(ch)==1)
            va_arr[va_tag].va_name[va_flag2++]=ch;
        if(va_ans==0) break;

}