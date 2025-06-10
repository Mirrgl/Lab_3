#include "tests.h"

int main() {
    random_device rand_source;
    mt19937_64 rand_gen(rand_source());

    // Генерирует простые числа с помощью решета Эратосфена
    auto prime_numbers = generate_primes(SIEVE);
    cout << "Решето Эратосфена:" << endl << prime_numbers << endl;

    cout << endl;

    int bit_size = 0;
    while (true) {
        cout << "Ввод количества битов (минимум 6 бит): ";
        cin >> bit_size;
        if (bit_size >= 6) {
            break;
        }
        cout << "Неправильный ввод" << endl;
    }
    
    cout << endl;

    // Генерация простых чисел
    auto miller_primes = miller_prime_gen(bit_size, prime_numbers, rand_gen);
    int non_prime_count = count_if(miller_primes.begin(), miller_primes.end(), [](const auto& pair) { return !pair.second; });
    cout << "Миллер:" << endl << miller_primes << endl << "Количество непростых чисел: " << non_prime_count << endl;

    cout << endl;

    auto poklington_primes = poklington_prime_gen(bit_size, prime_numbers, rand_gen);
    non_prime_count = count_if(poklington_primes.begin(), poklington_primes.end(), [](const auto& pair) { return !pair.second; });
    cout << "Поклингтон:" << endl << poklington_primes << endl << "Количество непростых чисел: " << non_prime_count << endl;

    cout << endl;

    auto gost_primes = gost_prime_gen(bit_size, prime_numbers, rand_gen);
    non_prime_count = count_if(gost_primes.begin(), gost_primes.end(), [](const auto& pair) { return !pair.second; });
    cout << "ГОСТ Р 34.10-94:" << endl << gost_primes << endl << "Количество непростых чисел: " << non_prime_count << endl;

    return 0;
}