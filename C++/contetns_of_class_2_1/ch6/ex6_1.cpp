#include <iostream>
using namespace std;

class Rectangle // 클래스 선언
{
    private : // 멤버변수의 접근 지정자: private
        int width;
        int height;
    public : // 멤버함수의 접근 지정자: public
        void GetRect(int w, int h);
        void ShowRect();
};

void Rectangle::GetRect(int w, int h) // 메서드를 분리하여 정의
{
    width = w;
    height = h;
}

void Rectangle::ShowRect() // 메서드를 분리하여 정의
{
    cout << "width = " << width << ", height = " << height << endl;
}

int main()
    {
    Rectangle r; // 객체 선언
    // r.width = 5; // 컴파일 오류
    // r.height = 4; // 컴파일 오류
    // 멤버변수는 private이므로 직접 접근은 안 된다. 

    int i, j;

    cin >> i >> j;

    r.GetRect(i, j); // 메서드를 사용
    r.ShowRect(); // 메서드를 사용

    return 0;
}
