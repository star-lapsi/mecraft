#include<stdio.h>
int name_get(char *n)
{
    gets(n);
}
int file_read(void)
{
    char file_name_c[255],file_str[255];
    FILE *fp=NULL;
        printf("Please input the name of file:\n");
        gets(file_name_c);
        fp=fopen(file_name_c,"r");
        while(fgets(file_str,255,(FILE*)fp)!=NULL)
        printf("%s",file_str);
        fclose(fp);
        return 0;
}
int file_build(void)
{
    char file_name_1[255];
    FILE *fp=NULL;
    printf("Please input the name of new file:\n");
    gets(file_name_1);
    fp=fopen(file_name_1,"w");
    printf("New file created!\n");
    fclose(fp);
}
int file_write(void)
{
    char file_name_w[255],file_c='\0';
    FILE *fp=NULL;
    printf("Please input the name of file:\n");
    gets(file_name_w);
    fp=fopen(file_name_w,"w+");
    printf("Please input something:\n");
    while(scanf("%c",&file_c)!=EOF)
    fputc(file_c,fp);
    fclose(fp);
}
int file_copy(void)
{
    char file_name_1[255],file_name_2[255],file_str[255];
    FILE *fp=NULL,*fp_c=NULL;
    printf("Please input the name of old file:\n");
    gets(file_name_1);
    fp=fopen(file_name_1,"r");
    printf("Please input the name of new file:\n");
    gets(file_name_2);
    fp_c=fopen(file_name_2,"w");
    while(fgets(file_str,255,(FILE*)fp)!=NULL)
    fputs(file_str,fp_c);
    fclose(fp);
    fclose(fp_c);
}
int main()
{
    int a=0,b=0,temp=0,choise=0;
    while(1)
    {
        b=choise;
        printf("What do you want to do?\n");
        printf("1 - Read a file.\n");
        printf("2 - Build a file.\n");
        printf("3 - Write a file.\n");
        printf("4 - Copy a file.\n");
        printf("Other - Close whole APP.\n");
        scanf("%d",&a);
        temp=getchar();
        switch (a)
        {
            case 1:
            {
                file_read();
                break;
            }
            case 2:
            {
                file_build();
                break;
            }
            case 3:
            {
                file_write();
                break;
            }
            case 4:
            {
                file_copy();
                break;
            }
            default: 
            {
                b=1;
                choise=0;
            }
        }
        while(!b)
        {
            printf("Do you want continue?\n");
            printf("0 - Quit the Application.\n");
            printf("1 - Continue using.\n");
            scanf("%d",&b);
            temp=getchar();
            if(b)
                {   
                    if(b!=1) printf("Error!\n");   
                    choise=1;
                }
            else 
                choise=0;
        }
        if(!choise) break;
    }
    return 0;
}