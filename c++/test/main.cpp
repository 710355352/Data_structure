#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class person
{
public:
	int age;
	char name[64];
	person() :age(78), name("张三老大爷") {};
};


void test()
{
	person p;
	person pp;
	p.age = 10;
	fstream ofs;
	ofs.open("test.txt", ios::trunc | ios::out | ios::binary | ios::in );
	if (ofs.is_open())
	{
		ofs << (const char *) & p;
		//ofs.write((const char*)&p, sizeof(person));
	}
	ofs >> (char*)&pp;
	//ofs.read((char*)&pp, sizeof(p));
	cout << pp.age << endl;
	ofs.close();
	
}

int main()
{
    test();
	system("pause");
	return 0;
}
