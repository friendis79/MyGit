#include <iostream>
#include <cstring>
using namespace std;
class Student
{
    protected:
        int id;
        char *name;
        int score;

    public:
        Student(int num, char *na, int sco);
        void showStudent() {
        cout << "id: " << id << ", name: " << name << ", score: " << score;
        }
};

Student::Student(int num, char *na, int sco)
{
    id = num;
    score = sco;
    name = new char[strlen(na)+1];
    strcpy_s(name, strlen(na)+1, na);
}

class Worker
{
    protected:
        int salary;
    public:
        Worker(int sal) : salary(sal) { };
        void showSalary() {
        cout << "salary: " << salary;
        }
};

class Wstudent :public Student, public Worker
{
    public:
    Wstudent(int num, char* na, int sco, int sal);
    };
    Wstudent::Wstudent(int num, char* na, int sco, int sal)
    : Student(num, na, sco), Worker(sal)
    {
};
int main()
{
    Wstudent wstu1(1234, "Hong Gildong", 87, 1850000);
    cout << "wstu1 ==> " ;
    wstu1.showStudent() ;
    cout << ", " ;
    wstu1.showSalary();
    cout << endl;
}
