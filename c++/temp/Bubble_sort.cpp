#include "Bubble_sort.h"
#define len 20
void bubble_sort()
{
	
	cout << "����һ��ð�������㷨����" << endl;
	cout << "�����ʼ��һ������Ϊ" << len << "������" << endl;
	cout << "����Ϊ:\n";
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
	cout << "ð�����������Ϊ:\n";
	for (int* i = arr; i <= &arr[len - 1]; ++i)
	{
		cout << *i << "   ";
	}
	cout << endl;
	system("pause");
}