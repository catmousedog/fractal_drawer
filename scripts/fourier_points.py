import matplotlib.pyplot as plt
from matplotlib.backend_bases import MouseButton
import numpy as np
import leja
from math import pi, e
import re

tau = 2 * pi * 1j

#
a = 10
P = 0
poles = np.empty(0, dtype=complex)
C = 1
coeff = np.zeros(C, dtype=complex)
T = np.linspace(0, 1, 200)
PLOT = None
COEFF = None
POLES = None


#

def printComp(z) -> str:
    return str(z.real) + "," + str(z.imag) + "\n"


def k(_k):
    return C // 2 - _k  # [C/2, -C/2[
    # return 2 - _k # [a, a-C[
    # return 1 - _k  # [1, 1-C[


def f(t) -> complex:
    sum = complex(0, 0)
    for _k in range(C):
        sum += coeff[_k] * e ** (tau * k(_k) * t)
    return sum


def integrate():
    for _k in range(C):
        sum = complex(0, 0)
        for _n in range(P):
            sum += poles[_n] * e ** -(tau * _n * k(_k) / P)
        coeff[_k] = sum / P


def get_nearest(z: complex) -> int:
    D = 10E9
    nearest = 0
    for _i in range(len(poles)):
        d = (poles[_i] - z).__abs__()
        if d < D:
            D = d
            nearest = _i
    return nearest


def clear():
    global PLOT
    if PLOT is not None:
        for point in PLOT:
            point.remove()
    global POLES
    if POLES is not None:
        for point in POLES:
            point.remove()
    global COEFF
    if COEFF is not None:
        for point in COEFF:
            point.remove()


def draw(event):
    clear()
    integrate()
    points = f(T)
    global PLOT, COEFF, POLES
    PLOT = ax.plot(points.real, points.imag, 'black')
    COEFF = ax.plot(coeff.real, coeff.imag, 'b+')
    POLES = ax.plot(poles.real, poles.imag, 'yx')
    event.canvas.draw()


drag = False


def on_click(event):
    global C, P, poles, coeff, drag
    if toggle:
        return
    if event.xdata is None or event.ydata is None:
        return
    if event.button == MouseButton.LEFT:
        poles = np.append(poles, [complex(event.xdata, event.ydata)])
        P = len(poles)
        # C += 1
        coeff = np.zeros(C, dtype=complex)
    if event.button == MouseButton.RIGHT:
        if P > 0:
            nearest = get_nearest(complex(event.xdata, event.ydata))
            poles = np.delete(poles, [nearest])
            P = len(poles)
            C = min(C, P)
    if event.button == MouseButton.MIDDLE:
        drag = True
    draw(event)


def on_release(event):
    global drag
    if event.button == MouseButton.MIDDLE:
        drag = False


def on_move(event):
    if event.xdata is None or event.ydata is None:
        return
    if drag:
        z = complex(event.xdata, event.ydata)
        nearest = get_nearest(z)
        poles[nearest] = z
        draw(event)


def on_scroll(event):
    global C, coeff
    C = max(C + round(event.step), 1)
    C = min(C, P)
    coeff = np.zeros(C, dtype=complex)
    draw(event)


toggle = False


def on_key(event):
    global toggle
    if event.key == 't':
        toggle = not toggle
    if event.key == ' ':
        file = open("C:\\Users\\Gebruiker\\Desktop\\CPP\\data\\coeff\\segment_.txt", "w")
        for c in coeff:
            file.write(printComp(c))
        file.close()

        leja.set_boundary(f)
        leja.set_points(200)
        file = open("C:\\Users\\Gebruiker\\Desktop\\CPP\\data\\leja\\segment_.txt", "w")
        for l in leja.leja:
            file.write(printComp(l))
        file.close()


if __name__ == '__main__':
    img = plt.imread("name2.png")
    fig, ax = plt.subplots()
    fig.canvas.mpl_connect('button_press_event', on_click)
    fig.canvas.mpl_connect('button_release_event', on_release)
    fig.canvas.mpl_connect('motion_notify_event', on_move)
    fig.canvas.mpl_connect('scroll_event', on_scroll)
    fig.canvas.mpl_connect('key_press_event', on_key)

    ax.axis([-a, a, -a, a])
    ax.hlines(0, -100, 100, 'g')
    ax.vlines(0, -100, 100, 'g')
    offset = 2
    ax.imshow(img, extent=[offset - 2.1818 * a, offset + 2.1818 * a, -a, a])

    plt.show()
