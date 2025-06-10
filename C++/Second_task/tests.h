#include <iostream>
#include <algorithm>
#include <iomanip>
#include <random>
#include <vector>
#include <cmath>
#include <set>

#define NUMBER_OF_PRIMES 10
#define RELIABILITY_LEVEL 10
#define SIEVE 500

using namespace std;

int bit_length(int x);
int find_gcd(int a, int b);
int mod_pow(int base, int exp, int modulus);
int ceil_division(double numerator, double denominator);
int pick_random_prime(const vector<int>& primes, mt19937_64& gen);
vector<int> generate_primes(int limit);

bool miller_rabin_test(int number, mt19937_64& gen);
bool primality_check(int number, int iterations, const vector<int>& factors, mt19937_64& gen);
bool poklington_check(int number, int iterations, const vector<int>& factors, mt19937_64& gen);

vector<pair<int, bool>> miller_prime_gen(int bit_size, const vector<int>& primes, mt19937_64& gen);
vector<pair<int, bool>> poklington_prime_gen(int bit_size, const vector<int>& primes, mt19937_64& gen);
vector<pair<int, bool>> gost_prime_gen(int bit_size, const vector<int>& primes, mt19937_64& gen);

ostream& operator<<(ostream& os, const vector<int>& data);
ostream& operator<<(ostream& os, const vector<pair<int, bool>>& data);