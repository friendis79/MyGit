#include <iostream>
#include <cstring>
using namespace std;

class Vehicle
{
    private :
        int number;
        char *owner;

    public :
        Vehicle() { // 기본 생성자
            number = 0;
            owner = NULL;
        }

        Vehicle(int n, const char* na) { // 일반 생성자
            number = n;
            owner = new char[strlen(na)+1];
            strcpy_s(owner, strlen(na)+1, na);
        }

        ~Vehicle() {
            delete [] owner;
        }

        void CopyVehicle(const Vehicle &src)
        {
            number = src.number;
            delete [] owner;
            owner = new char[strlen(src.owner)+1] ;
            strcpy_s(owner, strlen(src.owner)+1, src.owner);
        }

        void set(int n, const char *na) {
            number = n;
            delete [] owner;
            owner = new char[strlen(na)+1];
            strcpy_s(owner, strlen(na)+1, na);
        }

        void show() {
            cout << "number : " << number << ", owner : " << owner ;
            cout << endl;
        }

};

int main()
{
    Vehicle x(1234, "Kim");
    
    cout << "x ==> " ;
    x.show();

    Vehicle y(5678, "Park");
    
    y.CopyVehicle(x);
    cout << "y ==> " ;
    y.show();

    cout << " ----------x.set( )--------- " << endl ;

    x.set(2345, "Hong");
    cout << "x ==> " ;
    x.show();

    cout << "y ==> " ;
    y.show();
}
