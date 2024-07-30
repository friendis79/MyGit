#include <iostream>
using namespace std;

int main()
{
    int score[5] = {82, 93, 91, 80, 73};
    int total = 0;
    double average;

    for (int i=0; i<5; i++)
        total += score[i];

    average = (double)total / 5.0;
    
    cout << "total = " << total << endl;
    cout << "average = " << average << endl;

    return 0;
}