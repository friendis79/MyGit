#include <iostream>
using namespace std;

class Car
{
    private:
        int number; // �Ϲ� �������
        static int count; // ���� �������

    public:
        Car(int n);
        void showCar(); // �Ϲ� ����Լ�
        static int GetCount(); // ���� ����Լ�
};

int Car::count = 0; // ���� ������� counter�� �ʱ�ȭ

Car::Car(int n)
{
    number = n;
    count++;
}

void Car::showCar()
{
    cout << "��ȣ: " << number << endl;
}

int Car::GetCount()
{
    return count;
}

int main()
{
    Car c1(1234);
    c1.showCar();
    cout << "��ϴ��: " << Car::GetCount() << endl ;

    Car c2(2345);
    c2.showCar();
    cout << "��ϴ��: " << Car::GetCount() << endl ;
    
    Car c3(3456);
    c3.showCar();
    cout << "��ϴ��: " << Car::GetCount() << endl ;
}