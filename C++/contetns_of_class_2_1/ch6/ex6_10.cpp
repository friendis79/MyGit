#include <iostream>
using namespace std;
class Vehicle
{
private :
    int number;
    int year;

public :
    Vehicle(int number=0, int year=0);
    ~Vehicle();
    void ShowVehicle() const ;
};

Vehicle::Vehicle(int number, int year)
{
    this->number = number;
    // this->number의 number는 멤버변수 number이고, // 뒤의 number는 객체 생성할 때 주는 값이다. this->year = year;
    // this->year의 year는 멤버변수 year이고, // 뒤의 year는 객체 생성할 때 주는 값이다. 
}

Vehicle::~Vehicle()
{
}

void Vehicle::ShowVehicle() const {
    cout << "Number : " << this->number << ", Year : "<< this->year << endl;
}

int main()
{
    Vehicle v1(1234, 2012);
    cout << "v1.ShowVehicle()" << "==> " ;
    v1.ShowVehicle() ;

    cout << endl;
    
    Vehicle *pv;
    pv = &v1;
    cout << "pv->ShowVehicle()" << "==> " ;
    pv->ShowVehicle() ;
}
