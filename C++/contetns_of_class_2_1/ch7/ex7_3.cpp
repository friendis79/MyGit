#include <iostream>
using namespace std;

class Car
{
    private:
        int number;
        int year;

    public:
        Car():number(0), year(0) {};
        Car(int n, int y):number(n), year(y) {};
        void showCar();
};

void Car::showCar()
{
    cout << "��ȣ: " << number << ", �⵵: " << year << endl;
}

void print1(Car c[]) // ��ü �迭�� ���޹޴� ���
{
    int i;
    for (i=0; i<3; i++) 
    {
        cout << "car[" << i << "].showCar() ==> " ;
        c[i].showCar();
    }
}

void print2(Car *c) // ��ü �����ͷ� ���޹޴� ���
{
    int i;
    for (i=0; i<3; i++) 
    {
        cout << "(car + " << i << ")->showCar() ==> " ;
        (c + i)->showCar();
    }
}

int main()
{
    Car car[3] = { Car(), Car(1234, 2011), Car(2345, 2012)};
    print1(car); // ��ü �迭�� �̸��� ����
    cout << endl;
    print2(car); // ��ü �迭�� �̸��� ����
}
