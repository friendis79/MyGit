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

    Vehicle(int n, const char* m) { // 일반 생성자
        number = n;
        int c = strlen(m);
        owner = new char[c+1];
        strcpy_s(owner, c+1, m);
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
    Vehicle x(1234, "Kim");
    cout << "x ==> ";
    x.show();

    Vehicle y;
    y = x;
    cout << "y ==> ";
    y.show() ;

    x.set(2345, "Hong");

    cout << " ----------x.set( )--------- " << endl;
    
    cout << "x ==> ";
    x.show();

    cout << "y ==> ";
    y.show() ;
}