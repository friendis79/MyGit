// ��ü�� ������ ���� ���޷� ��ü ����

#include <iostream>
using namespace std;

class Rectangle
{
    private :
        int width;
        int height;

    public :
        Rectangle():width(0), height(0) {};
        Rectangle(int w, int h):width(w), height(h) {};
        void showRectangle();
};

void Rectangle::showRectangle()
{
    cout << "width : " << width << ", height : " << height << endl;
}

void copyRectangle(Rectangle &des, const Rectangle &src)
{
    des = src;
}

int main()
{
    Rectangle rect1(10, 5), rect2(20, 12);

    cout << "(copyRectangle()�Լ� ȣ�� ����)rect1 ==> " ;
    rect1.showRectangle();

    cout << "(copyRectangle()�Լ� ȣ�� ����)rect2 ==> " ;
    rect2.showRectangle();

    cout << endl;
    copyRectangle(rect2, rect1);

    cout << "(copyRectangle()�Լ� ȣ�� ����)rect1 ==> " ;
    rect1.showRectangle();

    cout << "(copyRectangle()�Լ� ȣ�� ����)rect2 ==> " ;
    rect2.showRectangle();
    
    return 0;
}
