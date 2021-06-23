import numpy as np

B = 10000
T = np.linspace(0, 1, B)
leja = None
boundary = None


def set_boundary(f):
    global boundary
    boundary = np.empty(B, dtype=complex)
    boundary = f(T)


def set_points(N: int):
    global leja
    leja = np.empty(0, dtype=complex)

    if len(leja) > N:
        leja = leja[0:N]
    else:
        for _i in range(N - len(leja)):
            max = -1
            out = complex(0, 0)
            for b in boundary:
                m = leja_distance(b)
                if m > max:
                    max = m
                    out = b
            leja = np.append(leja, out)
            if _i % 10 == 0:
                print(_i)


def leja_distance(z: complex):
    prod = 1.0
    for c in leja:
        prod *= (z - c).__abs__()
    return prod
