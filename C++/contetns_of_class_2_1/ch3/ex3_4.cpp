#include <iostream>
using namespace std;

int main()
{
    unsigned short a = 0x1234, b = 0x5678, m = 0xff00, c ,d, e, f;
    c = a & m;
    d = b & ~m;
    e = c | d;
    f = m ^ ~m;

    printf("c = %04x\n", c);
    printf("d = %04x\n", d);
    printf("e = %04x\n", e);
    printf("f = %04x\n", f);

    return 0;
}