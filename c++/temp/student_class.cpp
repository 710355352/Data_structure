#include "student_class.h"

class person;



class person
{
public:
	int a;
	int b;
	person()
	{
		this->a = 10;
		this->b = 10;
	}
	person operator+(person& p2)
	{
		person temp;
		temp.a = this->a + p2.a;
		temp.b = this->b + p2.b;
		return temp;
	}
	/*person operator+(int num)
	{
		person temp;
		temp.a = this->a + num;
		temp.b = this->b + num;
		return temp;
	}*/

	person& operator++()
	{
		this->a++;
		this->b++;
		return *this;
	}
	person operator++(int)
	{
		cout << this << "\t"<< this->a << endl;
		person temp = *this;
		++*this;
		return temp;
	}
	void showlist()
	{
		cout << "person" << endl;
	}
};

person operator+(int num,person &p1)
{
	person temp;
	temp.a = p1.a + num;
	temp.b = p1.b + num;
	return temp;
}

ostream& operator<<(ostream& out, const person& p1)
{
	cout << "a = " << p1.a << ",b= " << p1.b;
	return cout;
}

class Student : public person
{
public:
	string name;
	int id;
	void showInfo()
	{
		cout << "name is " << name << " ,id is " << id << endl;
	}
	void setId(int iid)
	{
		id = iid;
	}
	void showlist(int a)
	{
		cout << "student" << endl;
	}
};

void class_test()
{
	Student s;
	int a = 1;
	s.a = a;
	cout << s.a << endl;
	s.person::a = 1;
	cout << s.a << endl;
	s.person::showlist();

	/*Student s1;
	s1.id = 5;
	s1.name = "aaa";
	s1.showInfo();*/
	//cout << "Student::name is" << Student::name << " ,id is " << Student::id << endl;//报错为非静态成员变量必须与特定对象对应。
	system("pause");
}


