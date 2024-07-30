#include <iostream>
using namespace std;

int main()
{
    unsigned short a = 0x8006, b = 0x0007; // 논리적 이동
    unsigned short c, d, e, f;

    c = a >> 1;
    d = b >> 1;
    e = a << 1;
    f = b << 1;

    printf("a = %08x, %u\n", a, a);
    printf("b = %08x, %u\n", b, b);

    printf("a >> 1 --> %08x, %u\n", c, c); // 우측으로 이동
    printf("b >> 1 --> %08x, %u\n", d, d); // 우측으로 이동
    printf("a << 1 --> %08x\n", e); // 좌측으로 이동
    printf("b << 1 --> %08x\n", f ); // 좌측으로 이동

    return 0;
}