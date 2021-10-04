#include<stdio.h>
#include<string.h>
//变量结构体内容：
//va_na为变量名，type_na为变量类型，type_flag为变量类型标识；
//va_val为变量值，fm_val标准值，lo_val变量长度；
struct variaty0
{
    char va_na[100];
    char va_tp[100];
    int va_flag;
    char va_val[100];
    int fm_val;
    int lo_val;
};
//文件结构体内容：
//ft_name为文件类型，ft_long为文件类型长度，ft_flag为文件类型标识，1为整形串，2为字符串，3为复合型；
struct file_type
{
    char ft_name[100];
    int ft_flag;
    int ft_long;
};
//输入模块判定函数；
int input_ck(char val)
{
    if(val=='<') return 1;
    else if(val=='#') return 2;
    else if(val=='{') return 3;
    else return 0;
}
//报错信息输出函数；
int err_pr(int err)
{
    switch (err)
    {
    case 1:
        printf("无法找到该文件类型！\n");
        break;
    case 2:
        printf("变量名包含非法字符！\n");
        break;
    case 3:
        printf("变量类型不存在！\n");
        break;
    case 4:
        break;
    default:
        break;
    }
}
//文件类型读取标准化函数；
char ft_read(char val)
{
    if(val=='>') return '\0';
    else return val;
}
//文件类型读取校验函数，依据具体类型返回检验结果，返回-1的情况为检验失败；
int ft_check(char arr[])
{
    puts(arr);
    if(strcmp(arr,"numbers")==0) return 1;
    else if(strcmp(arr,"strings")==0) return 2;
    else if(strcmp(arr,"mixs")==0) return 3;
    else return -1;
}
//变量名读取标准化函数；
char vn_read(char val)
{
    if(val==':') return '\0';
    else return val; 
}
//变量类型读取标准化函数；
char vt_read(char val)
{
    if(val==';') return '\0';
    else return val;
}
//该函数用于校验变量名是否符合规则，变量名异常返回0，OK返回1；
int va_name_check(char arr[])
{
    int i,flag=1;
    puts(arr);
    for(i=0;i<strlen(arr);i++)
    if((arr[i]<='Z'&&arr[i]>='A')||(arr[i]<='z'&&arr[i]>='a')||(arr[i]<='9'&&arr[i]>='0')) flag=1;
    else
    {
        flag=0;
        break;
    }
    return flag;
}
//该函数用于校验变量类型是否符合规则，如果类型正确返回具体标识，类型错误返回0；
int va_type_check(char arr[])
{
    int ans=0;
    puts(arr);
    if(strcmp(arr,"integer")==0) ans=1;
    if(strcmp(arr,"float")==0) ans=2;
    if(strcmp(arr,"char")==0) ans=3;
    if(strcmp(arr,"string")==0) ans=4;
    if(strcmp(arr,"addr")==0) ans=5;
    return ans;
}
int main()
{
    struct variaty0 var[1000];
    struct file_type ft;
    char ch[2];
    //临时字符缓存，ch[0]为默认缓存，ch[1]为转义缓存；
    char tmp_f[100],tmp_vn[100],tmp_vt[100],tmp_va[100],va_va[100];
    //tmp_f为文件状态缓存数组；
    //tmp_vn为变量名缓存数组；
    //tmp_vt为变量类型缓存数组；
    int re_flag=0,vn_flag=0,va_flag=0,ma_flag=0,err_flag=0; 
    //re_flag为主状态标识，用于确定当前读写模块（0为待读入、1为文件类型、2为变量声明、3为变量赋值）；
    //vn_flag为子状态标识，用于确定具体模块内读写区域；
    //ma_flag为读取顺序标识，用于确定当前读入的变量数量；
    //err_flag为错误标识，用于反馈错误类型，默认情况下，文件类型错误、变量不存在等都属于错误情况，都要进行退出；
    int ft_key=0,vn_key=0,vt_key=0,vv_key=0,va_key=0;
    //ft_key为文件类型读取循环体，用于将文件类型字符串录入缓存；
    //vn_key为变量名读取循环体，用于将变量名字符串录入缓存；
    //vt_key为变量类型读取循环体，用于将变量类型字符串录入缓存；
    int vn_wr=0,vt_wr=0,vn_rd=0,vv_rd=0;
    int se_flag=0,vard_flag=0;
    while(scanf("%c",&ch[0])!=EOF)
    //单字符读入模式，后期需要考虑修改为流模式；
    {
        if(re_flag==-1) //主状态标识为-1时，程序进入报错退出流程；
        {
            err_pr(err_flag);
            break;
        }
        if(re_flag==0) re_flag=input_ck(ch[0]); //主状态标识为0时，程序进入待命状态；
        else if(re_flag==1) //主状态标识为1时，程序读取文件类型标识；
        {
            tmp_f[ft_key++]=ft_read(ch[0]);
            if(ch[0]=='>') //读取完成，退出文件类型标识读取，进行内容转录；
            {
                ft.ft_flag=ft_check(tmp_f);
                ft.ft_long=strlen(tmp_f);
                strcpy(tmp_f,ft.ft_name);
                re_flag=0;
            }
            if(ft.ft_flag==-1) //文件类型读取报错流程；
            {
                err_flag=1;
                re_flag=-1;
            }
        }
        else if(re_flag==2) //主状态标识为2时，程序读取变量名和变量类型；
        {
            if(ch[0]<='z' && ch[0]>='a' && vn_flag==0) vn_flag=1; //读取到第一个小写字母时开始启动变量名读取；
            if(vn_flag==1) tmp_vn[vn_key++]=vn_read(ch[0]);
            else if(vn_flag==2) tmp_vt[vt_key++]=vt_read(ch[0]);
            if(ch[0]==':' && vn_flag==1) //当读取到字符“:”时，完成该行的变量名读取，校验变量名并写入缓存；
            {
                if(va_name_check(tmp_vn)==0) //变量名报错流程；
                {
                    err_flag=2;
                    re_flag=-1;
                }
                else
                {
                    strcpy(var[ma_flag].va_na,tmp_vn);
                    vn_flag=2;
                }
                vn_key=0;
            }
            if(ch[0]==';' && vn_flag==2) //当读取到结尾符号“;”时，完成该行的变量类型读取，主状态及子状态标识清零；
            {
                if(va_type_check(tmp_vt)==0) //变量类型报错流程；
                {
                    err_flag=3;
                    re_flag=-1;
                }
                else
                {
                    var[ma_flag].va_flag=va_type_check(tmp_vt);
                    strcpy(var[ma_flag++].va_tp,tmp_vt);
                    re_flag=0;
                    vn_flag=0;
                }
                vt_key=0;
            }    
        }
        else if(re_flag==3) //主状态标识为3时，程序读取变量名和变量值；
        {
            if(ch[0]=='}')
            {
                re_flag=0;
                va_flag=0;
            }
            if(va_flag==1)
            {
                if(ch[0]=='"') vn_rd=!vn_rd;
                if(vn_rd==1) tmp_va[vv_key++]=ch[0];
                else if(vn_rd==0)
                {
                    tmp_va[vv_key]='\0';
                    while(strcmp(tmp_va,var[se_flag].va_na)!=0 && se_flag<=ma_flag) se_flag++;
                    vard_flag=se_flag;
                }
                if(ch[0]==':') va_flag=2;
            }
            if(va_flag==2)
            {
                if(ch[0]=='"') vv_rd=!vv_rd;
                if(vv_rd==1) va_va[va_key++]=ch[0];
                else if(vn_rd==0)
                {
                    va_va[va_key]='\0';
                    strcpy(var[vard_flag].va_val,va_va);
                }
                if (ch[0]==';') va_flag=0;
            }
        }
    }
    printf("The Application is closed!\n");
}