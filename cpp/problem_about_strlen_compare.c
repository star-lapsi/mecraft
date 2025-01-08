#include<stdio.h>
#include<string.h>
void test(char *bb, char *cc);
int main()
{
	char b[10]="bb",c[20]="ccc";
	test(b,c);
	return 0;
}
void test(char *bb, char *cc)
{
	int a=0;
	int x=0,x1=0,x2=0;
	while(a < strlen(bb) - strlen(cc) && a > -1)
	{
		x = (a < strlen(bb) - strlen(cc) && a > -1);
		x1 = a < strlen(bb) - strlen(cc);
		x2 = a > -1;
		printf("%d %u %d %d %d\n",a,strlen(bb)-strlen(cc),x,x1,x2);
		a++;
	}
}

/*
这个程序会出现无限循环，虽然从语句来说循环应该是不会运行的。出现问题的主要原因大概是，
表达式“strlen(bb)-strlen(cc)”本身被视为某种无符号整数类型，因此无法和a这个一般整数类型进行比较。
实际上前者由于不能是负数而导致数值极高，因此while的判断始终为真，所以出现了无限循环。
所以如果在前者用（int）来强制约束数据，这个循环就可以正常工作，或者将前者和a进行运算，也可以强制约束类型。
不过比较奇怪的是，按照我查找的表格，strlen本身应该是int类型的。
补充：经过确认，在ming64的库中，strlen本身来自于一个特殊的形式"size t"，参考一些资料，size t是sizeof运算符
返回的类型，通常是unsighed int也就是无符号整型，这样一来结果就可以理解了。
这类问题在未来搞判断语句的时候需要认真关注。
*/