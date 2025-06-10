#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <limits>

using namespace std;

__int128 gcd(__int128 a, __int128 b) {
    while (b != 0) {
        __int128 temp = b;
        b = a % b;
        a = temp;
    }
    return a < 0 ? -a : a;
}

pair<__int128, __int128> add_fractions(const pair<__int128, __int128>& a, const pair<__int128, __int128>& b) {
    __int128 numerator = a.first * b.second + b.first * a.second;
    __int128 denominator = a.second * b.second;
    __int128 common_divisor = gcd(numerator, denominator);
    
    return {numerator / common_divisor, denominator / common_divisor};
}

__int128 factorial(__int128 k) {
    if (k <= 1) return 1;
    
    __int128 result = 1;
    for (__int128 i = 2; i <= k; ++i) {
        result *= i;
    }
    return result;
}

__int128 combinations(__int128 k, __int128 n) {
    if (n < 0 || n > k) return 0;
    return factorial(k) / (factorial(n) * factorial(k - n));
}

__int128 stirling_second_kind(__int128 n, __int128 k) {
    if (k == 0 && n == 0) return 1;
    if (k == 0 || n < k) return 0;
    
    __int128 sum = 0;
    for (__int128 i = 0; i <= k; ++i) {
        __int128 sign = (k - i) % 2 == 0 ? 1 : -1;
        __int128 term = sign * combinations(k, i);
        
        __int128 power = 1;
        for (__int128 j = 0; j < n; ++j) {
            power *= i;
        }
        
        term *= power;
        sum += term;
    }
    
    return sum / factorial(k);
}

pair<__int128, __int128> calculate_series_sum(__int128 a, __int128 b) {
    pair<__int128, __int128> sum = {0, 1};
    
    for (__int128 k = 0; k <= a; ++k) {
        __int128 numerator = stirling_second_kind(a, k) * factorial(k) * b;

        __int128 denominator = 1;
        for (__int128 i = 0; i <= k; ++i) {
            denominator *= (b - 1);
        }
        
        pair<__int128, __int128> term = {numerator, denominator};
        sum = add_fractions(sum, term);
    }
    
    return sum;
}

void print_int128(__int128 value) {
    cout << static_cast<long long>(value);
}

int main() {
    int a, b;
    cout << "Введите a и b: ";
    cin >> a >> b;

    if (b <= 1) {
        cout << "infinity" << endl;
        return 0;
    }

    auto result = calculate_series_sum(a, b);
    
    cout << "Результат: ";
    print_int128(result.first);
    cout << "/";
    print_int128(result.second);
    cout << endl;

    return 0;
}