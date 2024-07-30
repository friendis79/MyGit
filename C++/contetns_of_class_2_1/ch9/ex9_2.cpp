#include <iostream>
using namespace std;
class Vehicle
{
    private:
        int number;
    public:
        Vehicle(int n):number(n) { cout << "Vehicle 생성자" << endl;};
        void Show() const ;
};

void Vehicle::Show() const
{
    cout << "번호: " << number << endl;
}

class Truck:protected Vehicle
{
    private:
        int cargo;
    public:
        Truck(int n, int c);
        void displayTruck();
};

Truck::Truck(int n, int c):Vehicle(n)
{
    cout << "Truck 생성자" << endl;
    cargo = c;
}

void Truck::displayTruck()
{
    Show();
    cout << "화물 적재량: " << cargo << endl;
}

int main()
{
    Vehicle v(1234);
    v.Show();
    cout << endl;
    
    Truck t(7890, 5); // Truck은 protected 상속
    // t.Show(); // t.Show(): 클래스 외부에서 접근 불가
    t.displayTruck();
    cout << endl;
}
