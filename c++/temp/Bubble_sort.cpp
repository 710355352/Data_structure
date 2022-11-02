#include "Bubble_sort.h"
#define len 20
void bubble_sort()
{
	
	cout << "这是一个冒泡排序算法！！" << endl;
	cout << "随机初始化一个容量为" << len << "的数组" << endl;
	cout << "数组为:\n";
	int arr[len];
	for (int* i = arr; i <= &arr[len - 1]; ++i)
	{
		*i = rand() % 20;
		cout << *i << "   ";
	}
	cout << endl;
	for (int i = 0; i < len; ++i)
	{
		int temp = 0;
		for (int* j = arr; j <= &arr[len - 2 - i]; ++j)
		{
			temp = *j;
			if (*j < *(j + 1))
			{
				continue;
			}
			else
			{
				*j = *(j + 1);
				*(j + 1) = temp;
			}
		}
	}
	cout << "冒泡排序后，数组为:\n";
	for (int* i = arr; i <= &arr[len - 1]; ++i)
	{
		cout << *i << "   ";
	}
	cout << endl;
	system("pause");
}