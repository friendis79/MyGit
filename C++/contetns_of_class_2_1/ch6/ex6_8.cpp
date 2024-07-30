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
            cout << "기본 생성자 호출" << endl;
            number = 0;
            owner = NULL;
        }

        Vehicle(int n, const char* na) { // 일반 생성자
            cout << "일반 생성자 호출" << endl;
            number = n;
            owner = new char[strlen(na)+1];
            strcpy_s(owner, strlen(na)+1, na);
        }

        Vehicle(const Vehicle &src) { // 복사 생성자
            cout << "복사 생성자 호출" << endl;
            number = src.number;
            owner = new char[strlen(src.owner)+1];
            strcpy_s(owner, strlen(src.owner)+1, src.owner);
        }

        ~Vehicle() {
            cout << "소멸자 호출" << endl;
            delete[] owner;
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
    Vehicle x(1234, "Kim"); // 일반 생성자 호출
    Vehicle y = x; // 복사 생성자 호출
    Vehicle z(x); // 복사 생성자 호출

    cout << "x ==> " ;
    x.show();

    cout << "y ==> " ;
    y.show();

    cout << "z ==> " ;
    z.show();

    cout << " ----------x.set( )--------- " << endl;

    x.set(2345, "Hong");
    cout << "x ==> " ;
    x.show();

    cout << "y ==> " ;
    y.show();
    
    cout << "z ==> " ;
    z.show();
}
