#include <iostream>
using namespace std;

class Vehicle
{
private :
    int number;
    int year;
    
public :
    Vehicle(int num=0, int yr=0);
    ~Vehicle();
    void ShowVehicle() const ;
};

Vehicle::Vehicle(int n, int y):number(n), year(y)
{
}

Vehicle::~Vehicle(){
}

void Vehicle::ShowVehicle() const {
    cout << "Number : " << number << ", Year : " << year << endl;
}

int main()
{
    Vehicle v1(1234, 2012);
    Vehicle v2;

    cout << "v1.ShowVehicle()" << "==> " ;
    v1.ShowVehicle();

    cout << "v2.ShowVehicle()" << "==> " ;
    v2.ShowVehicle();

    cout << endl;

    Vehicle *pv;

    pv = &v1;
    cout << "pv->ShowVehicle()" << "==> " ;
    pv->ShowVehicle() ;

    pv = &v2;
    cout << "pv->ShowVehicle()" << "==> " ;
    pv->ShowVehicle() ;
}
