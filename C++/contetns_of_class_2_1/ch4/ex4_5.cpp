#include <iostream>
using namespace std;

int main()
{
    int i = 100;
    void* pv = &i;
        // void* 자료형은 모든 자료형을 가리킬 수 있으므로, 
        // 형 변환 없이도 &i의 값을 보관할 수 있다. 

    // int* pi = pv; // 오류
    int* pi = (int*)pv;
    // 보관하고 있는 주소를 int를 가리키는 주소로 사용하기 위해
    // 명시적으로 형 변환하여야 한다. 
    
    cout << "*pi = " << *pi << endl;
    
    return 0;
}