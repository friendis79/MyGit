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
    cout << "���� �ð�(�� ��): ";
    cin >> entranceHour >> entranceMinute;
    cout << "���� �ð�(�� ��): ";
    cin >> exitHour >> exitMinute;

    double totalPrice = ticket.calculatePrice(entranceHour, entranceMinute, exitHour, exitMinute);
    cout << "�̿� �ð�: " << exitHour - entranceHour << "�ð� " << exitMinute - entranceMinute << "��" << endl;
    cout << "�� ���: " << totalPrice << "��" << endl;

    return 0;
}