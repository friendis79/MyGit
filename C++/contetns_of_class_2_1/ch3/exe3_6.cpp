#include <iostream>
using namespace std;

int main()
{
    short int a = 0x8006, b = 0x0007; // ����� �̵�
    short int c, d, e, f;

    c = a >> 1;
    d = b >> 1;
    e = a << 1;
    f = b << 1;

    printf("a = %08x, %d\n", a, a);
    printf("b = %08x, %d\n", b, b);

    printf("a >> 1 --> %08x, %d\n", c, c); // ������ 2
    printf("b >> 1 --> %08x, %d\n", d, d); // ������ 2
    printf("a << 1 --> %08x, %d\n", e, e); // ���ϱ� 2
    // ��ȣ�� ���� --> ����÷ο� �߻�, ����� Ʋ��
    printf("b << 1 --> %08x, %d\n", f, f ); // ���ϱ� 2

    return 0;
}