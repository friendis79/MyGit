#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

struct DataType {
    int x;
    int y;
    double dist() const { return std::sqrt(x*x + y*y); }
    const std::string str() const { return std::to_string(x) + ',' + std::to_string(y); }
};

bool operator<(const DataType& d1, const DataType& d2) { return d1.dist() < d2.dist(); }

std::ostream& operator<<(std::ostream& os, const DataType& d)
{
    os << d.str();
    return os;
}

template<typename T>
bool fnPredicator(const T& val1, const T& val2)
{
    return val1 < val2;
}

struct FOPredicator {
    template<typename T>
    bool operator()(const T& val1, const T& val2) const
    {
        return val1 < val2;
    }
};

using VecDataType = std::vector<DataType>;
using namespace std;

int main()
{
    auto print = [](const VecDataType& d, const string& strMsg = "") {
            cout << strMsg;
            copy(begin(d), end(d), ostream_iterator<DataType>(cout, " "));
            cout << endl;
        };

    VecDataType vecData {{7,2}, {1,3}, {2,6}, {3,2}, {5,1}, {1,1}};

    print(vecData, "Container Elements:");

    sort(begin(vecData), end(vecData), fnPredicator<DataType>);
    print(vecData, "After ascending order by a predicate function:");
    sort(begin(vecData), end(vecData), [](const DataType& d1, const DataType& d2) { return d1.dist() > d2.dist(); } );
    print(vecData, "After descending order by a lambda expression:");
    sort(begin(vecData), end(vecData), FOPredicator());
    print(vecData, "After ascending order by a function object:");
    return 0;
}