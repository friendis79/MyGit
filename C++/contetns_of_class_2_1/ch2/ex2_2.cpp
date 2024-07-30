#include <iostream>
using namespace std;

int main()
{
    char str1[6] = {'k', 'o', 'r', 'e', 'a', '\0'}; // 문자열
    char str2[6] = {"korea"}; // 문자열
    char str3[5] = {'k', 'o', 'r', 'e', 'a'}; // 문자의 집합
//  char str4[5] = {"korea"}; //오류

    cout << "str1 : " << str1 << endl;
    cout << "str2 : " << str2 << endl;
    // str3은 null 종료 문자('\0')가 없는 문자의 집합으로, 예상치 않은 결과가 발생할 수 있음
    cout << "str3 : " << str3 << endl;
    

    cout << "str3 : ";
    for (int i = 0; i < 5; i++)
        cout << str3 [i];
    cout << endl;

    return 0;
}