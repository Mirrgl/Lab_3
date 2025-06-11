#include "tests.h"

int find_gcd(int x, int y) {
    while (y != 0) {
        int temp = x % y;
        x = y;
        y = temp;
    }
    return x;
}

int ceil_division(double numerator, double denominator) {
    return static_cast<int>(ceil(numerator / denominator));
}

template <typename T>
T modular_mult(T x, T y, T modulus) {
    __int128 product = static_cast<__int128>(x) * y;
    return static_cast<T>(product % modulus);
}

int mod_pow(int base, int exp, int modulus) {
    int result = 1;
    base = ((base % modulus) + modulus) % modulus;

    while (exp > 0) {
        if (exp & 1) result = modular_mult(result, base, modulus);
        base = modular_mult(base, base, modulus);
        exp >>= 1;
    }
    return result;
}

int bit_length(int number) {
    return number == 0 ? 0 : static_cast<int>(log2(number)) + 1;
}

int pick_random_prime(const vector<int>& prime_list, mt19937_64& generator) {
    uniform_int_distribution<int> distribution(0, prime_list.size() - 1);
    return prime_list[distribution(generator)];
}

vector<int> generate_primes(int limit) {
    if (limit < 2) return {};

    vector<bool> is_prime(limit + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i * i <= limit; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= limit; j += i) {
                is_prime[j] = false;
            }
        }
    }

    vector<int> primes;
    for (int i = 2; i <= limit; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }

    return primes;
}

bool primality_check(int number, int iterations, const vector<int>& factors, mt19937_64& generator) {
    if (number < 2) return false;
    if (number == 2 || number == 3) return true;

    uniform_int_distribution<int> distribution(2, number - 1);
    set<int> test_bases = {2};
    while (test_bases.size() < iterations) {
        test_bases.insert(distribution(generator));
    }

    for (int base : test_bases) {
        if (mod_pow(base, number - 1, number) != 1) {
            return false;
        }
    }

    for (int factor : factors) {
        bool all_unity = true;
        for (int base : test_bases) {
            if (mod_pow(base, (number - 1) / factor, number) != 1) {
                all_unity = false;
                break;
            }
        }
        if (all_unity) {
            return false;
        }
    }
    return true;
}

bool poklington_check(int number, int iterations, const vector<int>& factors, mt19937_64& generator) {
    if (number < 2) return false;

    uniform_int_distribution<int> distribution(2, number - 1);
    set<int> test_bases;
    while (test_bases.size() < iterations) {
        test_bases.insert(distribution(generator));
    }

    for (int base : test_bases) {
        if (mod_pow(base, number - 1, number) != 1) {
            return false;
        }
        
    }

    for (int base : test_bases) {
        bool all_unity = true;
        for (int factor : factors) {
            if (mod_pow(base, (number - 1) / factor, number) == 1) {
                all_unity = false;
                break;
            }
        }
        if (all_unity) {
            return true;
        }
    }
    return false;
}

bool miller_rabin_test(int number, mt19937_64& generator) {
    if (number < 2) return false;
    if (number == 2 || number == 3) return true;
    if (number % 2 == 0) return false;

    int s = 0, t = number - 1;
    while (t % 2 == 0) {
        t /= 2;
        s++;
    }

    int iterations = static_cast<int>(log2(number));
    uniform_int_distribution<int> distribution(2, number - 2);

    for (int i = 0; i < iterations; i++) {
        int base = distribution(generator);
        int x = mod_pow(base, t, number);

        if (x == 1 || x == number - 1) continue;

        bool is_composite = true;
        for (int j = 0; j < s - 1; j++) {
            x = mod_pow(x, 2, number);
            if (x == 1) return false;
            if (x == number - 1) {
                is_composite = false;
                break;
            }
        }
        if (is_composite) return false;
    }
    return true;
}



vector<pair<int, bool>> miller_prime_gen(int bit_size, const vector<int>& prime_list, mt19937_64& generator) {
    vector<pair<int, bool>> results;

    while (results.size() < NUMBER_OF_PRIMES) {
        int product = 1;
        vector<int> factors;

        while (bit_length(product) != bit_size - 1) {
            int prime_factor = pick_random_prime(prime_list, generator);
            if (bit_length(product * prime_factor) <= bit_size - 1) {
                product *= prime_factor;
                factors.push_back(prime_factor);
            }
        }
        factors.push_back(2);

        int candidate = 2 * product + 1;

        if (primality_check(candidate, 6, factors, generator) && 
            miller_rabin_test(candidate, generator)) {
            results.push_back({candidate, primality_check(candidate, 4, factors, generator)});
        }
    }
    return results;
}

vector<pair<int, bool>> poklington_prime_gen(int bit_size, const vector<int>& prime_list, mt19937_64& generator) {
    vector<pair<int, bool>> results;
    uniform_int_distribution<int> distribution(1, 32767);

    while (results.size() < NUMBER_OF_PRIMES) {
        int factor_product = 1;
        vector<int> factors;

        while (bit_length(factor_product) != bit_size / 2 + 1) {
            int prime_factor = pick_random_prime(prime_list, generator);
            if (bit_length(factor_product * prime_factor) <= bit_size / 2 + 1) {
                factor_product *= prime_factor;
                factors.push_back(prime_factor);
            }
        }

        int remainder = 2 * distribution(generator);
        while (bit_length(remainder) != bit_length(factor_product) - 1) {
            remainder = 2 * distribution(generator);
        }
        factors.push_back(remainder);

        int candidate = remainder * factor_product + 1;

        auto max_factor = max_element(factors.begin(), factors.end());
        int R = 1, F = *max_factor;
        for (auto it = factors.begin(); it != factors.end(); ++it) {
            R = (it == max_factor) ? R : R * *it;
        }

        if (find_gcd(R, F) == 1 && poklington_check(candidate, RELIABILITY_LEVEL, {R, F}, generator)) {
            results.push_back({candidate, poklington_check(candidate, 1, {R, F}, generator)});
        }
    }
    return results;
}

vector<pair<int, bool>> gost_prime_gen(int bit_size, const vector<int>& prime_list, mt19937_64& generator) {
    vector<pair<int, bool>> results;
    uniform_real_distribution<double> distribution(0.1, 1.0);

    const int power_2_t1 = 1 << (bit_size - 1);
    const int power_2_t = 1 << bit_size;

    while (results.size() < NUMBER_OF_PRIMES) {
        int prime_q = pick_random_prime(prime_list, generator);
        while (bit_length(prime_q) > ceil_division(bit_size, 2)) {
            prime_q = pick_random_prime(prime_list, generator);
        }

        bool found = false;
        while (!found) {
            double ksi = distribution(generator);
            int N = ceil_division(power_2_t1, prime_q) + ceil_division(power_2_t1 * ksi, prime_q);
            N = (N % 2 == 0) ? N : N + 1;
            int u = 0;

            while (!found) {
                int candidate = (N + u) * prime_q + 1;
                if (candidate > power_2_t) break;
                if (mod_pow(2, candidate - 1, candidate) == 1 && 
                    mod_pow(2, N + u, candidate) != 1) {
                    results.push_back({candidate, 
                        primality_check(candidate, 1, {N + u, prime_q}, generator)});
                    found = true;
                }
                u += 2;
            }
        }
    }
    return results;
}


ostream& operator<<(ostream& os, const vector<int>& data) {
    int count = 1;
    for (const auto& item : data) {
        os << item << "\t";
        if (count++ % 10 == 0) os << "\n";
    }
    return os;
}

ostream& operator<<(ostream& os, const vector<pair<int, bool>>& data) {
    // os << setw(10) << left << "№" << "\t";
    for (int i = 1; i <= data.size(); i++) {
        os << setw(10) << left << i << "\t";
    }
    os << "\n";
    for (const auto& pair : data) {
        os << setw(10) << left << pair.first << "\t";
    }
    os << "\n";
    for (const auto& pair : data) {
        char symbol = pair.second ? '+' : '-';
        os << setw(10) << left << symbol << "\t";
    }
    return os;
}