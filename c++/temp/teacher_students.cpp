#include "teacher_students.h"

struct Student
{
	string name;
	int age = 0;
	int score = 0;
};

struct Teahcer
{
	string name;
	int id = 0;
	int age = 0;
	Student stuArr[5];

};

void print_Stu(Student stuArr[], int len)
{
	for (int i = 0; i < len; ++i)
	{
		cout << "The " << i + 1 << " students' name is " << stuArr[i].name << ", age is "
			<< stuArr[i].age << ", score is " << stuArr[i].score << endl;
	}

}

void init_Student(Student* stu)
{
	stu->age = rand() % 10 + 10;
	stu->score = rand() % 50 + 50;
	stu->name = (char)(rand()%26 + 65);

	for (int i = 0; i < 5; ++i)
	{
		stu->name += (char)(rand() % 26 + 97);
	}

}

void init_Teacher(Teahcer* tea, bool sort = false)
{
	tea->age = rand() % 10 + 50;
	tea->id = rand() % 10000;
	tea->name = (char)(rand()%26 + 65);

	for (int i = 0; i < 5; ++i)
	{
		tea->name += (char)(rand() % 26 + 97);
	}
	cout << "This teacher's name is " << tea->name << ", and his age is " << tea->age
		<< ", his id is " << tea->id << " and he has 5 students : " << endl;
	
	
	for (int i = 0; i < 5; ++i)
	{
		init_Student(&(tea->stuArr[i]));
	}
	int len = sizeof(tea->stuArr) / sizeof(tea->stuArr[0]);
	cout << "ÅÅĞòÇ°£º" << endl;
	print_Stu(tea->stuArr, len);
	cout << "ÅÅĞòºó£º" << endl;
	if (sort)
	{
		for (int i = 0; i < len; ++i)
		{
			for (Student* p = tea->stuArr; p < &(tea->stuArr[len - 1]) - i; ++p)
			{
				Student temp;
				if (p->score < (p + 1)->score)
				{
					temp = *p;
					*p = *(p + 1);
					*(p + 1) = temp;
				}
			}
		}
	}
	print_Stu(tea->stuArr, len);
	cout << endl;
}

void teacher_student()
{
	cout << "This exe will show 5 teachers and every teacher's 5 students: " << endl << endl;
	srand(time(NULL));
	Teahcer tea[5];
	for (int i = 0; i < 5; ++i)
	{
		init_Teacher(&(tea[i]),true);
	}
	system("pause");
}