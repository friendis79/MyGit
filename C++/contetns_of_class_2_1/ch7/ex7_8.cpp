#include <iostream>
using namespace std;

class Car
{
    private:
        int number; // 일반 멤버변수
        
    public:
        static int count; // 정적 멤버변수
        Car(int n);
        void showCar();
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

int main()
{
    Car c1(1234);
    c1.showCar();
    cout << "등록대수: " << c1.count << endl;

    Car c2(2345);
    c2.showCar();
    cout << "등록대수: " << c2.count << endl;
    
    Car c3(3456);
    c3.showCar();
    cout << "등록대수: " << c3.count << endl;
}
