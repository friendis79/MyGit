#include <iostream>
using namespace std;

inline int abs2(int y) // 인라인 함수
{
    int m;

    if (y < 0)
        m = -y; 
    else
        m = y;

    return m;
}

int abs3(int z) // 일반 함수
{
    int m;

    if (z < 0)
        m= -z; 

    else
        m = z;

    return m;
} 

int main(int argc, char* argv[])
{ 
    int a = -15, m1, m2, m3;

    m2 = abs2(a);
    cout << "(인라인 함수) a = " << a << ", m2 = " << m2 << endl;

    m3 = abs3(a);
    cout << "(일반 함수) a = " << a << ", m3 = " << m3 << endl;

    return 0;
}