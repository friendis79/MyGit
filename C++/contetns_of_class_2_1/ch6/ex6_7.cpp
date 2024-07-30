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

        Vehicle(int n, const char* m) { // 일반 생성자
            cout << "일반 생성자 호출" << endl;
            number = n;
            owner = new char[strlen(m)+1];
            strcpy_s(owner, strlen(m)+1, m);
        }

        void set(int n, const char *m) {
            number = n;
            strcpy_s(owner, strlen(m)+1, m);
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

    cout << " ----------x.set( )--------- " << endl;

    x.set(2345, "Hong");

    cout << "x ==> " ;
    x.show();

    cout << "y ==> " ;
    y.show() ;
}
