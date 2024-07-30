#include <iostream>
#include <cstring>
using namespace std;

class Vehicle // �⺻ Ŭ����
{
    private:
        int number;
    public:
        Vehicle(int n):number(n) { // �⺻ Ŭ������ ������
        cout << "Vehicle ������" << endl;
    };
    ~Vehicle() { // �⺻ Ŭ������ �Ҹ���
    cout << "Vehicle �Ҹ���, " << number << endl;
    };
    void ShowNumber() const ;
};

void Vehicle::ShowNumber() const
{
    cout << "��ȣ: " << number << endl;
}

class Truck:public Vehicle // �Ļ� Ŭ����
{
    private:
        int cargo;
    public:
        Truck(int n, int c):Vehicle(n) { // �Ļ� Ŭ������ ������
        cargo = c;
        cout << "Truck ������" << endl;
        }
        ~Truck() { // �Ļ� Ŭ������ �Ҹ���
        cout << "Truck �Ҹ���, " << cargo << endl;
        }
        void ShowCargo() const ;
};

void Truck::ShowCargo() const
{
    cout << "ȭ��: " << cargo << endl;
}

int main()
{
    Vehicle v(1234);
    v.ShowNumber();
    cout << endl;
    
    Truck t(7890, 5); // Truck�� public ���
    t.ShowNumber();
    t.ShowCargo();
    cout << endl;
}