#include <iostream>
using namespace std;
const double PI = 3.14159;

int main()
{
    int num=0;
    double a, b, area;
    do {
        cout << "==================================" << endl ;
        cout << " 1. 삼각형의 넓이구하기 " << endl ;
        cout << " 2. 사각형의 넓이구하기 " << endl ;
        cout << " 3. 원의 넓이구하기 " << endl ;
        cout << " 9. 끝내기 " << endl ;
        cout << "==================================" << endl ;
        cout << "원하는 도형을 선택하세요: " ; 
        cin >> num;
        switch (num) {
        case 1: 
        case 2:
            cout << "밑면의 길이를 입력하세요: " ;
            cin >> a;
            cout << "높이를 입력하세요: " ;
            cin >> b ;
        break ;

        case 3:
            cout << "반지름을 입력하세요: " ;
            cin >> a;
        break ;

        case 9:
            cout << "감사합니다." << endl ;
        return 0 ;

        default:
        cout << "입력을 잘못하였습니다! " << endl << endl ;
        continue;
    }
    switch (num) {
        case 1: 
            area = a * b / 2;
        break ;

        case 2:
            area = a * b;
        break ;

        case 3:
            area = PI * a * a;
        }
    cout << "area = " << area << endl << endl;
    } while (num != 9);

    return 0;
}