#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    char flower[20]; // 문자열을 저장할 배열
    char *ptr; // 문자열을 가리키는 포인터

    // 문자열 "freesia"를 flower 배열에 복사
    strcpy(flower, "freesia");
    cout << "1. flower : " << flower << endl; // 출력: 1. flower : freesia
    ptr = flower; // ptr 포인터에 flower 배열의 주소를 할당
    cout << "2. ptr : " << ptr << endl << endl; // 출력: 2. ptr : freesia

    // 문자열 "rose"를 ptr이 가리키는 위치에 복사
    strcpy(ptr, "rose");
    cout << "3. ptr : " << ptr << endl << endl; // 출력: 3. ptr : rose

    // 문자열 "mary"를 flower 배열에 이어서 복사
    strcat(flower, "mary");
    cout << "4. flower : " << flower << endl; // 출력: 4. flower : rosemary
    ptr = flower; // ptr 포인터에 flower 배열의 주소를 할당
    strcat(ptr, " perfume"); // ptr이 가리키는 위치에 " perfume"를 이어서 복사
    cout << "5. ptr : " << ptr << endl; // 출력: 5. ptr : rosemary perfume
    cout << "ptr 문자열의 길이는 " << strlen(ptr) << endl << endl; // 출력: ptr 문자열의 길이는 18
    
    return 0;
}
