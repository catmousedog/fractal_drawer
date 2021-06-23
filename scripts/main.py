import matplotlib.pyplot as plt
import numpy as np
from scipy.integrate import quad
import math

DIR = []
P = 100
a = 10

coefficients = np.array([
    -0.7862903225806459 + 2.754329004329005j,
    3.487903225806452 + 0.18939393939393967j,
    - 0.7862903225806464 + 2.7543290043290045j
])


def getnearest(z):
    nearest = 0
    distance = 10E99
    for _i in range(len(coefficients)):
        d = abs(z - coefficients[_i])
        if d < distance:
            distance = d
            nearest = _i
    return nearest


pressed = False


def onclick(event):
    global pressed
    pressed = True


def onmotion(event):
    if pressed:
        _i = getnearest(event.xdata + event.ydata * 1j)
        coefficients[_i] = event.xdata + event.ydata * 1j
        for dir in DIR:
            dir.remove()
        DIR.clear()


def onrelease(event):
    global pressed
    pressed = False


def fourier(t):
    sum = 0 + 0j
    for _n in range(len(coefficients)):
        sum += (math.e ** (2 * math.pi * t * (1 - _n) * 1j)) * coefficients[_n]
    return sum


def desired_fourier(t):
    return math.sin(2 * math.pi * t) + \
           60 * (t - t ** 2) * 1j


fig, ax = plt.subplots()
fig.canvas.mpl_connect('button_press_event', onclick)
fig.canvas.mpl_connect('motion_notify_event', onmotion)
fig.canvas.mpl_connect('button_release_event', onrelease)
ax.axis([-a, a, -a, a])

ax.hlines(0, -100, 100, 'g')
ax.vlines(0, -100, 100, 'g')
plt.show()

##
for _n in range(len(coefficients)):
    def Re(t: float):
        return (desired_fourier(t) * (math.e ** (-2 * math.pi * (1 - _n) * 1j * t))).real


    def Im(t: float):
        return (desired_fourier(t) * (math.e ** (-2 * math.pi * (1 - _n) * 1j * t))).imag


    r = quad(Re, 0, 1)[0]
    i = quad(Im, 0, 1)[0]
    coefficients[_n] = r + i * 1j
    # print(des_coefficients[_n] - coefficients[_n])
##


COEF = None
POINTS = None
max = P / 6
_t = 0
while plt.fignum_exists(fig.number):
    if POINTS is not None:
        for p in POINTS:
            p.remove()
    T = np.linspace(0, 1, P)
    points = fourier(T)
    POINTS = ax.plot(points.real, points.imag, 'r')
    if COEF is not None:
        for c in COEF:
            c.remove()
    COEF = ax.plot(coefficients.real, coefficients.imag, 'b+')
    if len(DIR) > max:
        DIR[0].remove()
        DIR.pop(0)
    DIR.append(plt.plot(points[_t].real, points[_t].imag, 'ro')[0])
    plt.pause(0.01)
    _t = (_t + 1) % P

for c in coefficients:
    print(f"fractal.region.AddCoefficient(Complex({c.real}, {c.imag}));")

for c in coefficients:
    print(f"{c.real}+{c.imag}j")
