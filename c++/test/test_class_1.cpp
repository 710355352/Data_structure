#include "test_class_1.h"

class test
{
public:
	int a = 1;
	int b = 2;
	test() { cout << "调用class test_1 成功！\n"; };

};
void test01()
{
	test t;
}