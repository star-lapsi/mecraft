#include<stdio.h>
#include<string.h>
//变量结构体内容：
//va_na为变量名，type_na为变量类型，type_flag为变量类型标识，va_val为变量值；
struct variaty0
{
    char va_na[100];
    char va_tp[100];
    int va_flag;
    char va_val[100];
};
//文件结构体内容：
//ft_name为文件类型，ft_flag为文件类型标识，1为整形串，2为字符串，3为复合型；
struct file_type
{
    char ft_name[100];
    int ft_flag;
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
        printf("未找到该变量！\n");
        break;
    case 5:
        printf("变量值与变量类型不符！\n");
        break;
    case 6:
        printf("变量值和文件类型不符！\n");
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
    //puts(arr); 调试用；
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
//该函数用于校验变量名是否符合规则，变量名异常返回-1，OK返回1；
int va_name_check(char arr[])
{
    int i,flag=1;
    //puts(arr); 调试用；
    for(i=0;i<strlen(arr);i++)
    if((arr[i]<='Z'&&arr[i]>='A')||(arr[i]<='z'&&arr[i]>='a')||(arr[i]<='9'&&arr[i]>='0')) flag=1;
    else
    {
        flag=-1;
        break;
    }
    return flag;
}
//该函数用于校验变量类型是否符合规则，如果类型正确返回具体标识，类型错误返回-1；
int va_type_check(char arr[])
{
    int ans=-1;
    //puts(arr);  调试用；
    if(strcmp(arr,"integer")==0) ans=0;
    if(strcmp(arr,"float")==0) ans=1;
    if(strcmp(arr,"string")==0) ans=2;
    if(strcmp(arr,"addr")==0) ans=3;
    return ans;
}
//文件名和变量类型匹配校验函数，如果匹配成功，返回0，否则返回-1；
int va_ft_check(char arr[],int flag)
{
    if(flag==1 && va_type_check(arr)==2) return -1;
    else if(flag==2 && (va_type_check(arr)==0 || va_type_check(arr)==1 || va_type_check(arr)==3)) return -1;
    else return 0;
}
//待赋值变量名读取标准化函数；
char vv_read(char val)
{
    if(val=='"') return '\0';
    else return val;
}
//赋值结果读取标准化函数；
char va_read(char val)
{
    if(val=='"') return '\0';
    else return val;
}
//变量名查找函数，找到后返回变量位置值，若未找到则返回-1；
int vn_search(char arr[], struct variaty0 *point, int num)
{
    int i=0;
    //puts(arr); 调试用；
    //puts(point->va_na); 调试用；
    while(i<num && strcmp(arr,point[i].va_na)!=0) i++;
    if(i<num) return i;
    else return -1;
}
//变量值校验函数，返回校验结果，0为校验通过，-1为校验错误；
int va_value_check(int flag, char arr[])
{
    int i,tag=0,ptag=0;
    //puts(arr); 调试用；
    if(flag==0)
    {
        for(i=0;i<strlen(arr);i++)
        if(arr[i]>'9' || arr[i]<'0') 
        {
            tag=1;
            break;
        }
        if(tag) return -1;
        else return 0;
    }
    else if(flag==1)
    {
        for(i=0;i<strlen(arr);i++)
        if(arr[i]>'9' || arr[i]<'0')
        {
            tag=1;
            break;
        }
        else if(arr[i]=='.') ptag++;
        if(tag==1 || ptag!=1) return -1;
        else return 0;
    }
    else if(flag==3)
    {
        for (i=0;i<strlen(arr);i++)
        if(arr[i]<'0' || (arr[i]>'9' && arr[i]<'A') || (arr[i]>'Z' && arr[i]<'a') || arr[i]>'z')
        {
            tag=1;
            break;
        }
        if(tag) return -1;
        else return 0;    
    }
    else if(flag==2) return 0;
}
//读取内容输出函数，将读取到的动态数据内容输出到文件；
int date_op(struct file_type *p1, struct variaty0 *p2,int num)
{
    FILE *fp=NULL;
    int i=0;
    fp=fopen("date01.txt","w+");
    fputs("<",fp);
    fputs(p1->ft_name,fp);
    fputs(">\n",fp);
    for(i=0;i<num;i++)
    {
        fputs("# ",fp);
        fputs(p2[i].va_na,fp);
        fputs(":",fp);
        fputs(p2[i].va_tp,fp);
        fputs(";\n",fp);
    }
    fputs("{\n",fp);
    for(i=0;i<num;i++)
    {
        fputs("\t\"",fp);
        fputs(p2[i].va_na,fp);
        fputs("\":\"",fp);
        fputs(p2[i].va_val,fp);
        fputs("\";\n",fp);
    }
    fputs("}\n",fp);
    fclose(fp);
}
int main()
{
    struct variaty0 var[1000];
    struct file_type ft;
    char ch[2];
    //临时字符缓存，ch[0]为默认缓存，ch[1]为转义缓存；
    char tmp_f[100],tmp_vn[100],tmp_vt[100],tmp_vv[100],tmp_va[100];
    //tmp_f为文件状态缓存数组；
    //tmp_vn为变量名缓存数组；
    //tmp_vt为变量类型缓存数组；
    //tmp_vv为带赋值变量名称缓存数组；
    //tmp_va为赋值结果名称缓存数组；
    int re_flag=0,vn_flag=0,va_flag=0,ma_flag=0,se_flag=0,err_flag=0; 
    //re_flag为主状态标识，用于确定当前读写模块（0为待读入、1为文件类型、2为变量声明、3为变量赋值）；
    //vn_flag为子状态标识，用于确定具体模块内读写区域；
    //ma_flag为读取顺序标识，用于确定当前读入的变量数量；
    //err_flag为错误标识，用于反馈错误类型，默认情况下，文件类型错误、变量不存在等都属于错误情况，都要进行退出；
    //se_flag为查找变量名循环体，当找到对应的变量名时标记位置，未找到则标注-1；
    int ft_key=0,vn_key=0,vt_key=0,vv_key=0,va_key=0;
    //ft_key为文件类型读取循环体，用于将文件类型字符串录入缓存；
    //vn_key为变量名读取循环体，用于将变量名字符串录入缓存；
    //vt_key为变量类型读取循环体，用于将变量类型字符串录入缓存；
    //vv_key为待赋值变量名称读取循环体，用于将待赋值变量名进行缓存；
    //va_key为变量赋值读取循环体，用于将赋值结果进行缓存；
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
                strcpy(ft.ft_name,tmp_f);
                re_flag=0;
                ft_key=0;
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
                if(va_name_check(tmp_vn)==-1) //变量名报错流程；
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
                if(va_type_check(tmp_vt)==-1) //变量类型报错流程；
                {
                    err_flag=3;
                    re_flag=-1;
                }
                else if(va_ft_check(tmp_vt,ft.ft_flag)==-1) //变量类型和文件类型不匹配报错流程；
                {
                    err_flag=6;
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
            if(va_flag==0 && ch[0]=='"') va_flag=1; //开始变量名读取；
            else 
            {
                if(va_flag==1) tmp_vv[vv_key++]=vv_read(ch[0]);
                if(va_flag==1 && ch[0]=='"') //结束变量名读取，并对缓存进行校验；
                {
                    va_flag=2;
                    se_flag=vn_search(tmp_vv,var,ma_flag); 
                    if(se_flag==-1)
                    {
                        re_flag==-1;
                        err_flag==4;
                    }
                    vv_key=0;
                }
            }
            if(va_flag==2 && ch[0]==':') va_flag=3;
            if(va_flag==3 && ch[0]=='"') va_flag=4;
            else 
            {
                if(va_flag==4) tmp_va[va_key++]=va_read(ch[0]);
                if(va_flag==4 && ch[0]=='"') //结束变量值读取，并对缓存进行校验；
                    if(va_value_check(var[se_flag].va_flag,tmp_va)==-1) //校验变量值如果存在异常，则提示报错并退出循环；
                    {
                        va_key=0;
                        re_flag=-1;
                        va_flag=0;
                        err_flag=5;
                    }
                    else
                    {
                        strcpy(var[se_flag].va_val,tmp_va);
                        va_key=0;
                        va_flag=5;
                        se_flag=0;
                    }
            }
            if(va_flag==5 && ch[0]==';') va_flag=0;
            if(va_flag==0 && ch[0]=='}') re_flag=0;
        }
        if(ch[0]=='}') break;
    }
    date_op(&ft,var,ma_flag);
    printf("The Application is closed!\n");
}