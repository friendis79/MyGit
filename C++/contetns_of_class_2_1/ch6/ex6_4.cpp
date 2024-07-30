#include <iostream>
using namespace std;

class Vehicle
{
    private :
        int number;
        int year;

    public :
        Vehicle(int num, int yr); // 생성자
        ~Vehicle(); // 소멸자
        void ShowVehicle() const ;
};

//생성자에 디폴트 매개변수 지정, 초기화 섹션 사용
Vehicle::Vehicle(int n=0, int y=0):number(n), year(y)
{
}

Vehicle::~Vehicle()
{
}

void Vehicle::ShowVehicle() const{
    cout << "Number : " << number << ", Year : " << year << endl ;
}

int main()
{
    Vehicle v1;
    Vehicle v2(1234);
    Vehicle v3(1234, 2012);
    v1.ShowVehicle();
    v2.ShowVehicle();
    v3.ShowVehicle();
}