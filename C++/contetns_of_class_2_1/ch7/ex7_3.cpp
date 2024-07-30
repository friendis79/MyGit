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
    cout << "번호: " << number << ", 년도: " << year << endl;
}

void print1(Car c[]) // 객체 배열로 전달받는 경우
{
    int i;
    for (i=0; i<3; i++) 
    {
        cout << "car[" << i << "].showCar() ==> " ;
        c[i].showCar();
    }
}

void print2(Car *c) // 객체 포인터로 전달받는 경우
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
    print1(car); // 객체 배열의 이름을 전달
    cout << endl;
    print2(car); // 객체 배열의 이름을 전달
}
