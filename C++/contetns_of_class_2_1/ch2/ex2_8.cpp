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
    strcpy(worker::name, "Hong");
    worker::overtime = 15;
    worker::Show(worker::name, worker::overtime);

    return 0;
}