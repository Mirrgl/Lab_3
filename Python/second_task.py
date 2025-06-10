import math
import random
from typing import List, Tuple

NUMBER_OF_PRIMES = 10
RELIABILITY_LEVEL = 10
SIEVE = 500

def bit_length(x: int) -> int:
    return x.bit_length()

def find_gcd(x: int, y: int) -> int:
    while y != 0:
        x, y = y, x % y
    return x

def ceil_division(numerator: float, denominator: float) -> int:
    return math.ceil(numerator / denominator)

def mod_pow(base: int, exp: int, modulus: int) -> int:
    result = 1
    base = base % modulus
    while exp > 0:
        if exp % 2 == 1:
            result = (result * base) % modulus
        base = (base * base) % modulus
        exp = exp >> 1
    return result

def pick_random_prime(prime_list: List[int], generator: random.Random) -> int:
    return generator.choice(prime_list)

def generate_primes(limit: int) -> List[int]:
    if limit < 2:
        return []
    
    sieve = [True] * (limit + 1)
    sieve[0] = sieve[1] = False
    
    for i in range(2, int(math.sqrt(limit)) + 1):
        if sieve[i]:
            sieve[i*i::i] = [False] * len(sieve[i*i::i])
    
    return [i for i, is_prime in enumerate(sieve) if is_prime]

def primality_check(number: int, iterations: int, factors: List[int], generator: random.Random) -> bool:
    if number < 2:
        return False
    if number == 2 or number == 3:
        return True
    
    test_bases = {2}
    while len(test_bases) < iterations:
        test_bases.add(generator.randint(2, number - 1))
    
    for base in test_bases:
        if mod_pow(base, number - 1, number) != 1:
            return False
    
    for factor in factors:
        all_unity = True
        for base in test_bases:
            if mod_pow(base, (number - 1) // factor, number) != 1:
                all_unity = False
                break
        if all_unity:
            return False
    return True

def poklington_check(number: int, iterations: int, factors: List[int], generator: random.Random) -> bool:
    if number < 2:
        return False
    
    test_bases = set()
    while len(test_bases) < iterations:
        test_bases.add(generator.randint(2, number - 1))
    
    for base in test_bases:
        if mod_pow(base, number - 1, number) != 1:
            return False
    
    for base in test_bases:
        all_unity = True
        for factor in factors:
            if mod_pow(base, (number - 1) // factor, number) == 1:
                all_unity = False
                break
        if all_unity:
            return True
    return False

def miller_rabin_test(number: int, generator: random.Random) -> bool:
    if number < 2:
        return False
    if number == 2 or number == 3:
        return True
    if number % 2 == 0:
        return False
    
    s = 0
    t = number - 1
    while t % 2 == 0:
        t //= 2
        s += 1
    
    iterations = math.floor(math.log2(number))
    for _ in range(iterations):
        base = generator.randint(2, number - 2)
        x = mod_pow(base, t, number)
        
        if x == 1 or x == number - 1:
            continue
        
        is_composite = True
        for __ in range(s - 1):
            x = mod_pow(x, 2, number)
            if x == 1:
                return False
            if x == number - 1:
                is_composite = False
                break
        
        if is_composite:
            return False
    return True

def miller_prime_gen(bit_size: int, prime_list: List[int], generator: random.Random) -> List[Tuple[int, bool]]:
    results = []
    
    while len(results) < NUMBER_OF_PRIMES:
        product = 1
        factors = []
        
        while bit_length(product) != bit_size - 1:
            prime_factor = pick_random_prime(prime_list, generator)
            if bit_length(product * prime_factor) <= bit_size - 1:
                product *= prime_factor
                factors.append(prime_factor)
        
        factors.append(2)
        candidate = 2 * product + 1
        
        if (primality_check(candidate, 6, factors, generator) and 
            miller_rabin_test(candidate, generator)):
            results.append((candidate, primality_check(candidate, 4, factors, generator)))
    
    return results

def poklington_prime_gen(bit_size: int, prime_list: List[int], generator: random.Random) -> List[Tuple[int, bool]]:
    results = []
    
    while len(results) < NUMBER_OF_PRIMES:
        factor_product = 1
        factors = []
        
        while bit_length(factor_product) != bit_size // 2 + 1:
            prime_factor = pick_random_prime(prime_list, generator)
            if bit_length(factor_product * prime_factor) <= bit_size // 2 + 1:
                factor_product *= prime_factor
                factors.append(prime_factor)
        
        remainder = 2 * generator.randint(1, 32767)
        while bit_length(remainder) != bit_length(factor_product) - 1:
            remainder = 2 * generator.randint(1, 32767)
        factors.append(remainder)
        
        candidate = remainder * factor_product + 1
        max_factor = max(factors)
        R = 1
        F = max_factor
        
        for factor in factors:
            if factor != max_factor:
                R *= factor
        
        if find_gcd(R, F) == 1 and poklington_check(candidate, RELIABILITY_LEVEL, [R, F], generator):
            results.append((candidate, poklington_check(candidate, 1, [R, F], generator)))
    
    return results

def gost_prime_gen(bit_size: int, prime_list: List[int], generator: random.Random) -> List[Tuple[int, bool]]:
    results = []
    
    power_2_t1 = 1 << (bit_size - 1)
    power_2_t = 1 << bit_size
    
    while len(results) < NUMBER_OF_PRIMES:
        prime_q = pick_random_prime(prime_list, generator)
        while bit_length(prime_q) > ceil_division(bit_size, 2):
            prime_q = pick_random_prime(prime_list, generator)
        
        found = False
        while not found:
            ksi = generator.uniform(0.1, 1.0)
            N = ceil_division(power_2_t1, prime_q) + ceil_division(power_2_t1 * ksi, prime_q)
            N = N if N % 2 == 0 else N + 1
            u = 0
            
            while not found:
                candidate = (N + u) * prime_q + 1
                if candidate > power_2_t:
                    break
                if (mod_pow(2, candidate - 1, candidate) == 1 and 
                    mod_pow(2, N + u, candidate) != 1):
                    results.append((candidate, 
                        primality_check(candidate, 1, [N + u, prime_q], generator)))
                    found = True
                u += 2
    return results

def print_primes(primes: List[Tuple[int, bool]]) -> None:
    print("№\t\t", end="")
    for i in range(1, len(primes)):
        print(f"{i:<10}\t", end="")
    print()
    
    for num, _ in primes:
        print(f"{num:<10}\t", end="")
    print()
    
    for _, is_prime in primes:
        symbol = '+' if is_prime else '-'
        print(f"{symbol:<10}\t", end="")
    print()

generator = random.Random()

prime_numbers = generate_primes(SIEVE)
print("Решето Эратосфена:")
print(*prime_numbers)
print()

bit_size = 0
while True:
    try:
        bit_size = int(input("Ввод количества битов (минимум 6 бит): "))
        if bit_size >= 6:
            break
        print("Неправильный ввод")
    except ValueError:
        print("Неправильный ввод")

print()

miller_primes = miller_prime_gen(bit_size, prime_numbers, generator)
non_prime_count = sum(1 for _, is_prime in miller_primes if not is_prime)
print("Миллер:")
print_primes(miller_primes)
print(f"Количество непростых чисел: {non_prime_count}")
print()

poklington_primes = poklington_prime_gen(bit_size, prime_numbers, generator)
non_prime_count = sum(1 for _, is_prime in poklington_primes if not is_prime)
print("Поклингтон:")
print_primes(poklington_primes)
print(f"Количество непростых чисел: {non_prime_count}")
print()

gost_primes = gost_prime_gen(bit_size, prime_numbers, generator)
non_prime_count = sum(1 for _, is_prime in gost_primes if not is_prime)
print("ГОСТ Р 34.10-94:")
print_primes(gost_primes)
print(f"Количество непростых чисел: {non_prime_count}")
print()