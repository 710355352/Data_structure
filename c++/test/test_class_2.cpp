#pragma once
#include "test_class_2.h"
using namespace test022;

class test022::test
{
public:
	int a = 3;
	int b = 4;
	test()  { cout << "����class test_2 �ɹ���\n"; };

};

void test022::test02()
{
	test022::test t;

}