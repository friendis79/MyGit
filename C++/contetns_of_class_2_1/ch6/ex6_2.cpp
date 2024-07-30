#include <iostream>
#include <cstring>
using namespace std;

class Vehicle
{
    char *name; // ���� �����ڸ� �������� ������ private�� �ȴ�. 
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

    cout << "������ȣ�� ������ �Է��ϼ���: " ;
    cin >> *nm >> y;

    v1.Register(nm, y);
    v1.ShowNumber();
    v1.ShowYear();
}