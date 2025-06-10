import sys

MIN_VALUE = -1e9


try:
    n, m = map(int, input().split())
    
    if n <= 0 or m <= 0:
        print("Вводимые числа должны быть положительными")
        sys.exit(1)
        
    nums = list(map(int, input().split()))
    if len(nums) != n:
        print("Количество чисел не соответствует n")
        sys.exit(1)
        
except ValueError:
    print("Ошибка ввода. Пожалуйста, введите целые числа.")
    sys.exit(1)

prefix = [0] * (n + 1)
for i in range(1, n + 1):
    prefix[i] = prefix[i - 1] + nums[i - 1]

dp = [0] * (n + 1)
dp[n] = 0 

for i in range(n - 1, -1, -1):
    max_diff = MIN_VALUE
    max_k = min(m, n - i)
    
    for k in range(1, max_k + 1):
        current_sum = prefix[i + k] - prefix[i]
        current_diff = current_sum - dp[i + k]
        
        if current_diff > max_diff:
            max_diff = current_diff
            
    dp[i] = max_diff

if dp[0] > 0:
    print("1")
else:
    print("0")