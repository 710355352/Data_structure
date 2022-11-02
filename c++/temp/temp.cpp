#include <iostream>
#include <stdio.h>
using namespace std;
#define len  20
//#include "Bubble_sort.h"
//#include "Ë®ÏÉ»¨Êý.h"
//#include "test.h"
//#include "teacher_students.h"
//#include "student_class.h"
namespace wb {
	void fun() {};
}
class A {
public:
	static int n;
	A() {
		for (int* i = li; i < &li[num]; ++i)
		{
			n += 1;
			*i = 1;
		}
	}
	enum {num = 5};
	int li[num];
};
int A::n = 1;
constexpr int nuu = 5;
int main()
{	
	//bubble_sort();
	//shuixianhua();
	//test();
	extern void teacher_student();
	teacher_student();
	//class_test();
	A b;
	extern int a;
	extern void test();
	for (int i = 0; i < A::num; ++i)
	{
		cout << b.li[i] << endl;
	}
	cout <<"a is " << a << endl;
	cout << sizeof(5) << endl;
    system("pause");
    return 0;

}