import math

def calculate_temperature(Tk: float, Ts: float, r: float, t: float) -> float:
    return Ts + (Tk - Ts) * math.exp(-r * t)

try:
    Tk = float(input("Введите начальную температуру кофе (Tk, в градусах Цельсия): "))
    Ts = float(input("Введите температуру окружающей среды (Ts, в градусах Цельсия): "))
    r = float(input("Введите коэффициент остывания (r, обычно 0.01-0.1): "))
    time_limit = int(input("Введите конечное время (в минутах): "))

    if time_limit < 0:
        raise ValueError("Время должно быть положительным числом")

    times = list(range(time_limit + 1))
    temperatures = [calculate_temperature(Tk, Ts, r, t) for t in times]

    print("\nВремя (мин)\tТемпература (°C)")
    for t, temp in zip(times, temperatures):
        print(f"{t:<16}{temp:.4f}")

except ValueError as e:
    print(f"Ошибка ввода: {e}")