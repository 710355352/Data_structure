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
		cout << "this 的位置" << this << endl;
		cout << "成员变量 (可变i) 的位置" << &i << endl;
		cout << "成员常量 (con_i) 的位置" << &con_i << endl;
		cout << "静态成员变量 (s_val) 的位置" << &s_val << endl;
		
		printf("静态成员函数 (s_test) 的位置 %p \n", &base::s_test);
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