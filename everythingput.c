#include<stdio.h>
int main()
{
    char b='\0',file_name[255];
    FILE *fp=NULL;
    int temp;
    printf("Please input the file name you want to write:\n");
    gets(file_name);
    temp=getchar();
    printf("Please input the word you want to write:\n");
    fp=fopen(file_name,"w");
    while(scanf("%c",&b)!=EOF)
    {
        fprintf(fp,&b);
    }
    fclose(fp);
}