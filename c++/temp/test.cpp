#include "test.h"

struct Student {
	string name;
	int age;
	int score;
};

void out(Student s)
{
	cout << "string �Ĵ�С��" << sizeof(string) << endl;
	cout << "name = " << s.name << " age = " << s.age << " score = " << s.score << endl;
	cout <<"s �ĵ�ַ�� " <<(int) & s << "\t name�ĵ�ַ�� " << (int)&s.name << "\t age�ĵ�ַ��" << (int)&s.age << "\t score�ĵ�ַ��" << (int)&s.score << endl;
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
	cout << "Student �Ĵ�СΪ" << sizeof(Student) << endl;
	Student* p1 = &s1;
	Student* p2 = arr;
	int* p3 = &(arr->age);
	cout << p1 << "\t" << p1->age << endl;
	cout << p2 << "\t" << (int) & p2[0].name - (int) & p2[1] << endl;
	cout << (int) p2<< "\t"<<(int)(p2+1) << endl;
	cout << (p2+1)->name << endl;//ָ��ֻ����ָ��Student��36�ֽڣ� �����ÿ��ͷ��ַ�����ܵ���ָ����������Եĵ�ַ��
	cout << p3<<"\t"<<p3+1 << "\t" << *p3<<"\t"<<*(p3+1) << endl;//ʵ��֤����int�͵�ָ����Է���int�ͱ������ڴ��ַ������
	out(s1);
	out(s2);
	system("pause");
}