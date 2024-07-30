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
    cout << "기본 생성자 호출" << endl;
}

Car::Car(int n, string m)
{
    number = n;
    owner = m;
    cout << "일반 생성자 호출" << endl;
}

void Car::showCar() const
{
    cout << "번호 " << number << ", 소유주: " << owner << endl;
}

void Car::getCar()
{
    char name[20];
    cout << "차량 번호를 입력하세요 : " ;
    cin >> number;
    fflush(stdin); // 버퍼 비우기
    // cin.ignore();
    // getchar();

    cout << "소유주를 입력하세요 : " ;
    cin.getline(name, 20);
    owner = name;
}

int main()
{
    Car *pcar = new Car; // 객체의 동적 생성
    pcar->getCar();
    pcar->showCar();
    delete pcar; // 객체의 제거
}