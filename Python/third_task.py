from typing import Tuple

def gcd(a: int, b: int) -> int:
    while b != 0:
        a, b = b, a % b
    return abs(a)

def add_fractions(a: Tuple[int, int], b: Tuple[int, int]) -> Tuple[int, int]:
    numerator = a[0] * b[1] + b[0] * a[1]
    denominator = a[1] * b[1]
    common_divisor = gcd(numerator, denominator)
    
    return (numerator // common_divisor, denominator // common_divisor)

def factorial(k: int) -> int:
    if k <= 1:
        return 1
    result = 1
    for i in range(2, k + 1):
        result *= i
    return result

def combinations(k: int, n: int) -> int:
    if n < 0 or n > k:
        return 0
    return factorial(k) // (factorial(n) * factorial(k - n))

def stirling_second_kind(n: int, k: int) -> int:
    if k == 0 and n == 0:
        return 1
    if k == 0 or n < k:
        return 0
    
    total = 0
    for i in range(k + 1):
        sign = 1 if (k - i) % 2 == 0 else -1
        term = sign * combinations(k, i)
        term *= i ** n
        total += term
    
    return total // factorial(k)

def calculate_series_sum(a: int, b: int) -> Tuple[int, int]:
    series_sum = (0, 1)
    
    for k in range(a + 1):
        numerator = stirling_second_kind(a, k) * factorial(k) * b
        denominator = (b - 1) ** (k + 1)
        
        term = (numerator, denominator)
        series_sum = add_fractions(series_sum, term)
    
    return series_sum


while (True):
    a, b = map(int, input("Введите a и b: ").split())
    if (a >= 0):
        break
    else:
        print("Неправильно введенные числа\n")

if b <= 1:
    print("infinity")
else:
    numerator, denominator = calculate_series_sum(a, b)
    print(f"Результат: {numerator}/{denominator}")
