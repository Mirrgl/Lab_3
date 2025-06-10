import math

DX = 0.1

def print_vector(v):
    for i in range(0, len(v)):
        print(f"{v[i]:7.4f}", end=" ")
        if ((i + 1) % 10 == 0): 
            print()

def solve_circle(dx, x_start, x_end):
    y = []
    while x_start < x_end:
        y.append(math.sqrt(4 - (x_start + 8)**2) - 2)
        x_start += dx
    return y

def solve_line(dx, x_start, x_end):
    y = []
    while x_start < x_end:
        y.append(0.5 * (x_start + 2))
        x_start += dx
    return y

def solve_flat_line(dx, x_start, x_end):
    y = []
    while x_start < x_end:
        y.append(0)
        x_start += dx
    return y

def solve_parabola(dx, x_start, x_end):
    y = []
    while x_start < x_end:
        y.append((x_start - 6)**2)
        x_start += dx
    return y

print("y:")

out = solve_circle(DX, -10, -6)
print_vector(out)
print("\n")

out = solve_line(DX, -6, 2)
print_vector(out)
print("\n") 

out = solve_flat_line(DX, 2, 6)
print_vector(out)
print("\n")

out = solve_parabola(DX, 6, 8 + DX)
print_vector(out)