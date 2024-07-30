#include <iostream>
using namespace std;
class Vehicle // 기반 클래스
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
    cout << "번호: " << number << endl ;
}

class Bus:public Vehicle // 파생 클래스
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
    cout << "번호: " << number << ", 승객수: " << person << endl ;
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
    

    cout << "업캐스팅 : 자식 클래스형에서 부모 클래스형으로 변환." << endl;
    pv2 = pb1; // 업 캐스팅 : 자동으로 형 변환
    pv2->show();
    pv2 = &b; // 업 캐스팅
    pv2->show();
    cout << endl;

    cout << "다운캐스팅 : 부모 클래스형에서 자식 클래스형으로 변환."<< endl;
    // pb2 = pv2; // 다운 캐스팅으로 오류 발생
    // pb2= &v; // 다운 캐스팅으로 오류 발생
    pb2 = (Bus *)&v; // 명시적(강제) 형 변환을 하여야 한다.
    pb2->show();

    return 0;
}
