#include <iostream>
#include <cstring>
using namespace std;

namespace worker {
    char name[10];
    int overtimel;
    void Show(char na[], int ot) {
        cout << "name : " << na << ", overtime : " << ot << endl;
    }
}

namespace student{
    char name[10];
    float score;
    void Show(char na[], float sc) {
        cout << "name : " << na << ", score : " << sc << endl;
    }
}

int main()
{
    using namespace student;

    strcpy(name, "Kim");
    score = 91.1f;
    Show(name, score);
}