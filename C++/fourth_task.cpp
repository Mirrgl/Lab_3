#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

const int MIN_VALUE = -1e9; // Константа для инициализации минимального значения

int main() {
    // Ввод данных
    int n, m;
    cin >> n >> m;
    
    // Проверка корректности входных данных
    if (n <= 0 || m <= 0 || n <= m) {
        cerr << "Неправильный ввод" << endl;
        return 1;
    }

    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }

    // Вычисление префиксных сумм
    vector<int> prefix(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        prefix[i] = prefix[i - 1] + nums[i - 1];
    }

    vector<int> dp(n + 1, 0);
    dp[n] = 0; // Базовый случай - нет чисел для выбора

    for (int i = n - 1; i >= 0; --i) {
        int max_diff = MIN_VALUE;
        int max_k = min(m, n - i); // Максимальное количество чисел, которое можно взять

        for (int k = 1; k <= max_k; ++k) {
            int current_sum = prefix[i + k] - prefix[i];
            int current_diff = current_sum - dp[i + k];
            
            if (current_diff > max_diff) {
                max_diff = current_diff;
            }
        }
        dp[i] = max_diff;
    }

    // Определение победителя
    if (dp[0] > 0) {
        cout << "1" << endl; // Павел выиграл
    } else {
        cout << "0" << endl; // Павел проиграл или ничья
    }

    return 0;
}