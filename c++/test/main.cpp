#include<iostream>
using namespace std;
//#include "test_class_2.h"

class base
{
public:
	base() : i(1), val(2),con_i(3) {};
	mutable int i;
	const int con_i;
	static int s_val;
	int val;
	
	int test()
	{
		cout << "this ��λ��" << this << endl;
		cout << "��Ա���� (�ɱ�i) ��λ��" << &i << endl;
		cout << "��Ա���� (con_i) ��λ��" << &con_i << endl;
		cout << "��̬��Ա���� (s_val) ��λ��" << &s_val << endl;
		
		printf("��̬��Ա���� (s_test) ��λ�� %p \n", &base::s_test);
		return con_i;
	}
	static void s_test()
	{
		

	}
};
int base::s_val = 0;
int global = 0;
const int* fun()
{
	const int* a = new int(5);
	cout << *a << endl;
	return a;
}
const char fun01()
{
	const char a = "a"[0];
	return a;
}

int print(int a , int = 1 )
{
	cout << a << endl;
	return a;
}

int print(int a)
{
	cout << "askljfk" << endl;
	return 0;
}

void test(int& a) { cout << "int &a" << endl; }
void test(const int& a) { cout << "const int & a" << endl; }

int main()
{
	typedef int a;
	a b = 5;
	extern int a;
	cout << a <<endl;

	system("pause");

	return 0;
}