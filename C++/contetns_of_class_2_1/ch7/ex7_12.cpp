// has - a relationship

#include <iostream>
#include <string>
using namespace std;

class CPU
{
    private:
        string cpuname;
        float speed;

    public:
        CPU(string cn, float sp) : cpuname(cn), speed(sp) {}
        void show() const
         {
        cout << "processor name : " << cpuname << ", speed : " \
        << speed << " GHz" << endl;
        }
};

class Computer
{
    private:
        CPU c_cpu; // 멤버 객체
        int m_size;

    public:
        Computer(CPU cpu1, int size): c_cpu(cpu1), m_size(size) {}
        ~Computer() {};
        void show() 
        {
        c_cpu.show();
        cout << "memory : " << m_size << " GB" << endl;
        }
};

int main()
{
    CPU mycpu("Intel i9", 3.3f);
    Computer mycom(mycpu, 32);
    mycom.show();
}