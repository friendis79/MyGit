#include <iostream>

using namespace std;

class Ticket {
private:
    double baseFee;
    double additionalFeePerHour;
    double discountRate;
    
public:
    Ticket(double base, double additional, double discount) {
        baseFee = base;
        additionalFeePerHour = additional;
        discountRate = discount;
    }

    double calculatePrice(int entranceHour, int entranceMinute, int exitHour, int exitMinute) {
        int totalEntranceMinutes = entranceHour * 60 + entranceMinute;
        int totalExitMinutes = exitHour * 60 + exitMinute;
        int totalMinutes = totalExitMinutes - totalEntranceMinutes;
        double totalHours = static_cast<double>(totalMinutes) / 60.0;
        double totalFee = baseFee + (totalHours - 2) * additionalFeePerHour;

        if (entranceHour < 12) {
            totalFee *= (1 - discountRate);
        }

        return totalFee;
    }
};

int main() {
    Ticket ticket(10000, 1000, 0.3);

    int entranceHour, entranceMinute, exitHour, exitMinute;
    cout << "입장 시간(시 분): ";
    cin >> entranceHour >> entranceMinute;
    cout << "나간 시간(시 분): ";
    cin >> exitHour >> exitMinute;

    double totalPrice = ticket.calculatePrice(entranceHour, entranceMinute, exitHour, exitMinute);
    cout << "이용 시간: " << exitHour - entranceHour << "시간 " << exitMinute - entranceMinute << "분" << endl;
    cout << "총 요금: " << totalPrice << "원" << endl;

    return 0;
}