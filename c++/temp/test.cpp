#include "test.h"

struct Student {
	string name;
	int age;
	int score;
};

void out(Student s)
{
	cout << "string 的大小是" << sizeof(string) << endl;
	cout << "name = " << s.name << " age = " << s.age << " score = " << s.score << endl;
	cout <<"s 的地址是 " <<(int) & s << "\t name的地址是 " << (int)&s.name << "\t age的地址是" << (int)&s.age << "\t score的地址是" << (int)&s.score << endl;
}

void test()
{
	cout << (char)(5) << endl;
	Student s1 {"wb",25,90};
	Student s2 = { "lj",24,91 };
	Student arr[] = {
		{"ww",1,2},
		{"ll",3,4}
	};
	cout << "Student 的大小为" << sizeof(Student) << endl;
	Student* p1 = &s1;
	Student* p2 = arr;
	int* p3 = &(arr->age);
	cout << p1 << "\t" << p1->age << endl;
	cout << p2 << "\t" << (int) & p2[0].name - (int) & p2[1] << endl;
	cout << (int) p2<< "\t"<<(int)(p2+1) << endl;
	cout << (p2+1)->name << endl;//指针只可以指向Student（36字节） 数组的每个头地址，不能单独指向里面的属性的地址。
	cout << p3<<"\t"<<p3+1 << "\t" << *p3<<"\t"<<*(p3+1) << endl;//实验证明，int型的指针可以访问int型变量的内存地址的内容
	out(s1);
	out(s2);
	system("pause");
}