#include <iostream>
using namespace std;
class Vehicle
{
    private:
        int number;
    public:
        Vehicle(int n):number(n) { cout << "Vehicle ������" << endl;};
        void Show() const ;
};

void Vehicle::Show() const
{
    cout << "��ȣ: " << number << endl;
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
    cout << "Truck ������" << endl;
    cargo = c;
}

void Truck::displayTruck()
{
    Show();
    cout << "ȭ�� ���緮: " << cargo << endl;
}

int main()
{
    Vehicle v(1234);
    v.Show();
    cout << endl;
    
    Truck t(7890, 5); // Truck�� protected ���
    // t.Show(); // t.Show(): Ŭ���� �ܺο��� ���� �Ұ�
    t.displayTruck();
    cout << endl;
}
