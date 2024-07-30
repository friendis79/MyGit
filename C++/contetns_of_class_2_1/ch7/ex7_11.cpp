#include <iostream>
#include <limits>
#include <cstring>
using namespace std;

class Car
{
    private:
        int number;
        string owner;
    public:
        Car();
        Car(int n, string m);
        void showCar() const ;
        void getCar();
};

Car::Car()
{
    number = 0;
    owner = " ";
    cout << "�⺻ ������ ȣ��" << endl;
}

Car::Car(int n, string m)
{
    number = n;
    owner = m;
    cout << "�Ϲ� ������ ȣ��" << endl;
}

void Car::showCar() const
{
    cout << "��ȣ " << number << ", ������: " << owner << endl;
}

void Car::getCar()
{
    char name[20];
    cout << "���� ��ȣ�� �Է��ϼ��� : " ;
    cin >> number;
    fflush(stdin); // ���� ����
    // cin.ignore();
    // getchar();

    cout << "�����ָ� �Է��ϼ��� : " ;
    cin.getline(name, 20);
    owner = name;
}

int main()
{
    Car *pcar = new Car; // ��ü�� ���� ����
    pcar->getCar();
    pcar->showCar();
    delete pcar; // ��ü�� ����
}