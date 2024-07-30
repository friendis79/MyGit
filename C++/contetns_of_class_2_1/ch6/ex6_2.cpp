#include <iostream>
#include <cstring>
using namespace std;

class Vehicle
{
    char *name; // 접근 지정자를 지정하지 않으면 private가 된다. 
    int year;

    public :
        void Register(char *nm, int yr) ;

        void ShowNumber() const {
            cout << "Name : " << name << endl;
        };

        void ShowYear() const {
            cout << "Year : " << year << endl;
        };
};

void Vehicle::Register(char *nm, int yr) {
    int c = strlen(nm);
    name = new char[c+1];
    strcpy_s(name, c+1, nm);
    year = yr;
}
int main()
{
    Vehicle v1;
    char *nm;
    int y;

    cout << "차량번호와 연식을 입력하세요: " ;
    cin >> *nm >> y;

    v1.Register(nm, y);
    v1.ShowNumber();
    v1.ShowYear();
}