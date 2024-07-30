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
    Car(int n, string m); // ������, ����Լ�
    void showCar() const; // ����Լ�
    void printCar(const Car car[], int n) const; // ����Լ��� ����
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
    cout << "��ȣ: " << number << ", ������: " << owner << endl;
}

void Car::printCar(const Car car[], int n) const
{
    int i;
    for (i = 0; i < n; i++)
        cout << "car[" << i << "] ==> " << car[i].number << ", " << car[i].owner << endl;
        cout << "���� ��� : " << car[i].cnt << endl; // ���� ������ cnt ���
}

int main()
{
    Car car[3] = {Car(1234, "Kim"), Car(2345, "Hong"), Car(3456, "Lee")};
    car[0].showCar(); // ����Լ��̹Ƿ� ��ü�� �Բ� ���
    car[0].printCar(car, 3);
    cout << endl;
}