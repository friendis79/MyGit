#include <iostream>
using namespace std;

class Car
{
    private:
        int number; // �Ϲ� �������
        
    public:
        static int count; // ���� �������
        Car(int n);
        void showCar();
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

int main()
{
    Car c1(1234);
    c1.showCar();
    cout << "��ϴ��: " << c1.count << endl;

    Car c2(2345);
    c2.showCar();
    cout << "��ϴ��: " << c2.count << endl;
    
    Car c3(3456);
    c3.showCar();
    cout << "��ϴ��: " << c3.count << endl;
}
