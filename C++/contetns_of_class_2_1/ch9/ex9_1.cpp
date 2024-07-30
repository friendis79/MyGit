#include <iostream>
#include <cstring>
using namespace std;

class Vehicle // 기본 클래스
{
    private:
        int number;
    public:
        Vehicle(int n):number(n) { // 기본 클래스의 생성자
        cout << "Vehicle 생성자" << endl;
    };
    ~Vehicle() { // 기본 클래스의 소멸자
    cout << "Vehicle 소멸자, " << number << endl;
    };
    void ShowNumber() const ;
};

void Vehicle::ShowNumber() const
{
    cout << "번호: " << number << endl;
}

class Truck:public Vehicle // 파생 클래스
{
    private:
        int cargo;
    public:
        Truck(int n, int c):Vehicle(n) { // 파생 클래스의 생성자
        cargo = c;
        cout << "Truck 생성자" << endl;
        }
        ~Truck() { // 파생 클래스의 소멸자
        cout << "Truck 소멸자, " << cargo << endl;
        }
        void ShowCargo() const ;
};

void Truck::ShowCargo() const
{
    cout << "화물: " << cargo << endl;
}

int main()
{
    Vehicle v(1234);
    v.ShowNumber();
    cout << endl;
    
    Truck t(7890, 5); // Truck은 public 상속
    t.ShowNumber();
    t.ShowCargo();
    cout << endl;
}