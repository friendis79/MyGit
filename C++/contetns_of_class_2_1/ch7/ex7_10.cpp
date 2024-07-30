#include <iostream>
#include <cstring>
using namespace std;

class Car
{
private:
    int number;
    string owner;
    static int cnt;

public:
    Car(int n, string m); // 생성자, 멤버함수
    void showCar() const; // 멤버함수
    void printCar(const Car car[], int n) const; // 멤버함수로 변경
};

int Car::cnt = 0;

Car::Car(int n, string m)
{
    number = n;
    owner = m;
    cnt++;
}

void Car::showCar() const
{
    cout << "번호: " << number << ", 소유주: " << owner << endl;
}

void Car::printCar(const Car car[], int n) const
{
    int i;
    for (i = 0; i < n; i++)
        cout << "car[" << i << "] ==> " << car[i].number << ", " << car[i].owner << endl;
        cout << "차량 대수 : " << car[i].cnt << endl; // 현재 차량의 cnt 출력
}

int main()
{
    Car car[3] = {Car(1234, "Kim"), Car(2345, "Hong"), Car(3456, "Lee")};
    car[0].showCar(); // 멤버함수이므로 객체와 함께 사용
    car[0].printCar(car, 3);
    cout << endl;
}