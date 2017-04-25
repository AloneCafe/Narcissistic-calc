//水仙花数是指一个 n 位数 ( n>=3 ),它的每个位上的数字的 n 次幂之和等于它本身。 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//自定义数据类型TYPE 
typedef unsigned long long int TYPE;

//自编的巨大整数求幂函数。因为math.h中的pow取值范围偏小，其不适用于此算法。 
TYPE big_pow(TYPE x, TYPE y)
{
	TYPE i, n = 1;
	
	//循环乘y次x，结果赋给n。 
	for(i = 1; i <= y; i++)
	{
		n *= x;
	}
	
	return n;
} 

//计算出数值的每位数，存放到数组中。a是数组指针，num是数值本身，bit是位数。 
void getBit(TYPE *a, TYPE num, TYPE bit) 
{	
	TYPE i;	//循环变量 
	
	//循环将每一位数从数值中提取出来，放到对应的数组元素中。 
	for(i = 0; i < bit; i++)
	{
		a[i] = (num % big_pow(10, i + 1)) / big_pow(10, i);
	}
}

//计算存储每一位数的数组，求出水仙花数。a是数组指针，bit是位数。函数返回sum，即结果。 
TYPE calcNumber(TYPE *a, TYPE bit)
{
	TYPE i;	//循环变量 
	TYPE sum = 0;	//总和 
	
	//循环计算每一位的bit次方，然后将结果累加成sum。 
	for(i = 0; i < bit; i++)
	{
		sum += big_pow(a[i], bit);
	}
	
	return sum;	//函数返回sum 
}

int main()
{ 	
	TYPE num;	//数值
	TYPE total = 0;	//计数器 
	TYPE bit = 3;	//当前位数
	TYPE max_bit;	//最大位数 
	TYPE *a;		//存放每位数的数组
	
	//提示信息，输入max_bit，即最大位数。 
	printf("==========水仙花数穷举法计算程序==========\n请输入计算的最大位数：");
	scanf("%d", &max_bit);
	
	//分配max_bit个元素数据类型大小的内存空间 
	a = (TYPE *)malloc(sizeof(TYPE) * max_bit);
	
	//输出首次计算的位数提示信息 
	printf("\n%d位数的水仙花数：\n", bit);
	//从100开始，循环到10的max_bit + 1次方，即最大数的界限。bit = 3，即位数初始值为3。 
	for(num = 100; num < big_pow(10, max_bit) && bit <= max_bit; num++)
	{
		//计算出数值的每位数，存放到数组中。a是数组指针，num是数值本身，bit是位数。
		getBit(a, num, bit);
		
		//计算存储每一位数的数组，求出水仙花数。a是数组指针，bit是位数。
		//比较num的值和运算结果，若相等则是水仙花数 
		if(num == calcNumber(a, bit))
		{
			total++; 
			printf("%d\n", num);
		}
		
		//若num进位，即等于10的bit次方，则位数bit加1。 
		if(num == big_pow(10, bit))
		{
			bit++;
			
			//输出位数提示信息 
			printf("\n%d位数的水仙花数：\n", bit);
		}
	}
	
	//提示信息 
	printf("\n\n全部计算完成！\n");
	printf("%d位数以内共有%d个水仙花数\n\n", bit, total);
	
	//释放内存空间 
	free(a);
	system("pause");
	
	return 0;
}
