import math

DX = 0.5

def print_vector(vec):
    for i, element in enumerate(vec):
        print(f"{element:8.4f}", end="")
        if (i + 1) % 10 == 0:
            print()
    return

def solve_circle(dx, x_start, x_end):
    y = []
    x = x_start
    while x < x_end:
        y.append(math.sqrt(4 - pow(x + 8, 2)) - 2)
        x += dx
    return y

def solve_line(dx, x_start, x_end):
    y = []
    x = x_start
    while x < x_end:
        y.append(0.5 * (x + 2))
        x += dx
    return y

def solve_flat_line(dx, x_start, x_end):
    y = []
    x = x_start
    while x < x_end:
        y.append(0.0)
        x += dx
    return y

def solve_parabola(dx, x_start, x_end):
    y = []
    x = x_start
    while x < x_end:
        y.append(pow(x - 6, 2))
        x += dx
    return y

print("x | y:")

out = solve_circle(DX, -10, -6)
x = -10.0
for val in out:
    print(f"{x:.1f}\t{val:.4f}")
    x += DX
print()

out = solve_line(DX, -6, 2)
x = -6.0
for val in out:
    print(f"{x:.1f}\t{val:.4f}")
    x += DX
print()

out = solve_flat_line(DX, 2, 6)
x = 2.0
for val in out:
    print(f"{x:.1f}\t{val:.4f}")
    x += DX
print()

out = solve_parabola(DX, 6, 9)
x = 6.0
for i, val in enumerate(out):
    print(f"{x:.1f}\t{val:.4f}")
    x += DX
    if x == 8.5:
        break
print()