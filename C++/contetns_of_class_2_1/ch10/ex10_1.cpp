#include <iostream>
using namespace std;
class Vehicle // ��� Ŭ����
{
    protected:
        int number ;
    public:
        Vehicle(int n):number(n) { };
        void show() const ;
};

void Vehicle::show() const
{
    cout << "Vehicle::show() ==> " ;
    cout << "��ȣ: " << number << endl ;
}

class Bus:public Vehicle // �Ļ� Ŭ����
{
    private:
        int person;
    public:
        Bus(int n, int p):Vehicle(n) { person = p; };
        void show() const ;
};

void Bus::show() const
{
    cout << "Bus::show() ==> " ;
    cout << "��ȣ: " << number << ", �°���: " << person << endl ;
}
int main()
{
    Vehicle *pv1, *pv2, v(1234);
    Bus *pb1, *pb2, b(2345, 10);
    pv1 = &v;
    pv1->show();
    pb1 = &b;
    pb1->show();
    cout << endl;
    

    cout << "��ĳ���� : �ڽ� Ŭ���������� �θ� Ŭ���������� ��ȯ." << endl;
    pv2 = pb1; // �� ĳ���� : �ڵ����� �� ��ȯ
    pv2->show();
    pv2 = &b; // �� ĳ����
    pv2->show();
    cout << endl;

    cout << "�ٿ�ĳ���� : �θ� Ŭ���������� �ڽ� Ŭ���������� ��ȯ."<< endl;
    // pb2 = pv2; // �ٿ� ĳ�������� ���� �߻�
    // pb2= &v; // �ٿ� ĳ�������� ���� �߻�
    pb2 = (Bus *)&v; // �����(����) �� ��ȯ�� �Ͽ��� �Ѵ�.
    pb2->show();

    return 0;
}
