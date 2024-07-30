#include <iostream>
#include <cstring>

namespace worker {
    char name[10];
    int overtime;
    void Show(char na[], int ot) {
        std::cout << "name : " << na << ", overtime : " << ot << std::endl;
    }
}

namespace student {
    char name[10];
    float score;
    void Show(char na[], float sc) {
        std::cout << "name : " << na << ", score : " << sc << std::endl;
    }
}

int main()
{
    using student::name;
    using student::score;

    strcpy(name, "Kim");
    score = 91.1f;
    student::Show(name, score);

    return 0;
}