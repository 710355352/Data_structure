#include <iostream>
// #include <stdio.h>
#include <math.h>
using namespace std;
#include "ˮ�ɻ���.h"
int weishu(int a)
{
	int ans = 0;
	while ( pow(10,ans) <= a)
	{
		ans++;
	}
	return ans;
}

int* number(int a)
{
	int *num = new int[10];
	int wei = weishu(a);
	int this_lo = 0;
	for (int *i = num; i <= &num[wei]; ++i)
	{
		if (a)
		{
			this_lo = a % 10;
			a -= this_lo;
			a /= 10;
			*i = this_lo;
			//cout << i << "++++" << *i << endl;
		}
		else
		{
			*i = 11;
			break;
		}
	}
	
	//cout << num <<"\t" << *num << endl;

	return num;

}

void shuixianhua()
{	
	int low = 0, high = 0;
	cout << "����һ��ˮ�ɻ����оٵĳ���\n������������ѯ��ˮ�ɻ��������ޣ�";cin >> low;
	cout << "������ˮ�ɻ��������ޣ�"; cin >> high;
	int num = weishu(high);
	//cout << "high��λ���ǣ�" << num << endl;
	int start = low;
	int* li;
	/*for (int i = 0; i < 10; ++i)
	{
		cout << li[i] << endl;
	}
	for (int* index = li; index < &li[num]; ++index)
	{
		cout << index << "\t" << *index << endl;
		cout << li << "\t" << *li << endl;
	}*/
	cout << "\nˮ�ɻ������У�" ;
	for (int start = low; start < high+1; ++start)
	{
		
		li = number(start);
		//cout << start << "\t";
		int temp = start;
		int wei = weishu(start);
		for(int *index = li;index <= &li[wei];++index)
		{	
			if (*index == 11)
			{
				break;
			}
			//cout << *li << "\t";
			temp -= *index * *index * *index;
			
			
		}
		if (!temp) { cout << start << "   "; }
		delete [] li;
		//delete li;
		//cout << temp << endl;

	}
	cout << "\n\n������!!" << endl;


	system("pause");
}