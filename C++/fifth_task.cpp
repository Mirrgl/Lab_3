#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

double calculateTemperature(double Tk, double Ts, double r, double t) {
    return Ts + (Tk - Ts) * exp(-r * t);
}

int main() {
    double Tk, Ts, r;
    int time_limit;

    cout << "Введите начальную температуру кофе (Tk, в градусах Цельсия): ";
    cin >> Tk;
    cout << "Введите температуру окружающей среды (Ts, в градусах Цельсия): ";
    cin >> Ts;
    cout << "Введите коэффициент остывания (r, обычно 0.01-0.1): ";
    cin >> r;
    cout << "Введите конечное время (в минутах): ";
    while(true) {
        cin >> time_limit;
        if (time_limit > 0) {break;}
        cout << "Время должно быть положительным" << endl;
    }

    vector<double> times;
    vector<double> temperatures;
    for (int i = 0; i <= time_limit; i++) {
        times.push_back(i);
        temperatures.push_back(calculateTemperature(Tk, Ts, r, i));
    }

    cout << "Время (мин)\tТемпература (°C)" << endl;

    for (int t = 0; t <= time_limit; t++) {
        cout << fixed << setprecision(4) << setw(16) << left << t << temperatures[t] << endl;
    }

    return 0;
}