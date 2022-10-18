using namespace std;
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <conio.h>
int main()
{
    int i;
    srand(time(NULL));
    string namee[3] = {"a","b","c"};
    cout<<namee<<"\t"<<namee+3<<endl;//这里输出的是地址
    system("pause");
    vector<string> name(namee,namee+3);
    while(true)
    {   
        system("cls");
        i = rand()%3;
        cout<<"Name is:"<<name[i]<<endl;
        if(kbhit()) break;
    }
    system("pause");
}