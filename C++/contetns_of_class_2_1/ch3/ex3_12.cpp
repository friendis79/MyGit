#include <iostream>
using namespace std;

int main()
{
    int score;
    char grade;
    cout << "점수를 입력하세요(0 ~ 100): " ;
    cin >> score;

        switch (score/10) 
        {
        case 10:
        case 9 :
            grade = 'A';
        break ;

        case 8 :
            grade = 'B';
        break ;

        case 7 :
            grade = 'C';
        break ; 

        case 6 : 
            grade = 'D';
        break ;

        default :
        grade = 'F'; 
        }

    cout << grade << " 학점입니다." << endl; 

    return 0;
}