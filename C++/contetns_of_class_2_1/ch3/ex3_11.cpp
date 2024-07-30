#include <iostream>
using namespace std;

int main()
{
    int score;
    cout << "점수를 입력하세요(0 ~ 100): " ;
    cin >> score;

    if (score >= 60)
    cout << "합격입니다." << endl;
    else
    cout << "불합격입니다." << endl;

    return 0;
}