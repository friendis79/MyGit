// 클래스가 다른 클래스의 freind 클래스로 되는 경우

#include <iostream>
#include <string>
using namespace std;

class Point
{
    private:
        int px; // private 멤버
        int py; // private 멤버

    public:
        Point(int x=0, int y=0) : px(x), py(y) {}
        void showPoint() const
        {
        cout << "점의 위치: x = " << px << ", y = " << py << endl;
        }

        friend class Circle;
};

class Circle
{
    
    private:
        Point center; // 멤버 객체
        int radius;
        
    public:
        Circle(Point cen, int rad=0):center(cen), radius(rad){}
        ~Circle() {};
        void showCircle() 
        {
        cout << "중심점: (x = " << center.px << ", y = " << center.py << ")";
        // Point 클래스의 private 멤버 변수 px와 py를 사용하기 위하여 Point 클래스에서 Circle 클래스를 friend 클래스로 선언
        cout << " 반지름: " << radius << endl;
        }
};

int main()
{
    Point cen(5, 7);
    cen.showPoint();
    
    Circle cir1(cen, 10);
    cir1.showCircle();
}
