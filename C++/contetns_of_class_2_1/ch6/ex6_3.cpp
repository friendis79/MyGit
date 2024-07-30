#include <iostream>
using namespace std;

class Vehicle
{
    private :
        int number;
        int year;
    public :

        Vehicle(); // 기본 생성자
        Vehicle(int num, int yr); // 일반 생성자
        ~Vehicle(); // 소멸자
        void ShowVehicle() const ;
};

Vehicle::Vehicle()
{
    cout << "Vehicle constructor" << endl;
    number = 0, year = 0;
}

Vehicle::Vehicle(int num, int yr)
{
    cout << "Vehicle constructor with number and year" << endl;
    number = num;
    year = yr;
}

Vehicle::~Vehicle()
{
    cout << "Vehicle destructor of " << number << endl;
}

void Vehicle::ShowVehicle() const
{
    cout << "Number : " << number << ", Year : " << year << endl;
}

int main()
{
    // 기본 생성자 호출시에는 v1()과 같이 괄호를 사용해서는 안 된다. 
    Vehicle v1;
    Vehicle v2(1234, 2012);
    v1.ShowVehicle();
    v2.ShowVehicle();
}
