#include <iostream>
using namespace std;

class Car
{
    private:
        int number; // 일반 멤버변수
        static int count; // 정적 멤버변수

    public:
        Car(int n);
        void showCar(); // 일반 멤버함수
        static int GetCount(); // 정적 멤버함수
};

int Car::count = 0; // 정적 멤버변수 counter의 초기화

Car::Car(int n)
{
    number = n;
    count++;
}

void Car::showCar()
{
    cout << "번호: " << number << endl;
}

int Car::GetCount()
{
    return count;
}

int main()
{
    Car c1(1234);
    c1.showCar();
    cout << "등록대수: " << Car::GetCount() << endl ;

    Car c2(2345);
    c2.showCar();
    cout << "등록대수: " << Car::GetCount() << endl ;
    
    Car c3(3456);
    c3.showCar();
    cout << "등록대수: " << Car::GetCount() << endl ;
}