import matplotlib.pyplot as plt
from matplotlib.backend_bases import MouseButton
import numpy as np
import leja
import os
from math import pi, e

tau = 2 * pi * 1j

#
a = 20
P = 0
poles = np.empty(0, dtype=complex)
C = 1
coeff = np.zeros(C, dtype=complex)
T = np.linspace(0, 1, 200)
offset = 0 + 0j
PLOT = None
COEFF = None
POLES = None

other_coeffs = []
OTHER_PLOTS = []

# path = "C:\\Users\\lauwe\\source\\repos\\FractalDrawer\\FractalDrawer\\"


path = "C:\\Users\\Gebruiker\\source\\repos\\FractalDrawer\\FractalDrawer\\"


def coeffPath(i):
    return path + "data\\coeff\\segment_" + str(i) + ".txt"


def lejaPath(i):
    return path + "data\\leja\\segment_" + str(i) + ".txt"


def printComp(z) -> str:
    return str(z.real) + "," + str(z.imag) + "\n"


def f(c, t) -> complex:
    sum = complex(0, 0)
    for k in range(len(c)):
        sum += c[k] * e ** (tau * (len(c) // 2 - k) * t)
    return sum


def integrate():
    for k in range(C):
        sum = complex(0, 0)
        for n in range(P):
            sum += poles[n] * e ** -(tau * n * (len(coeff) // 2 - k) / P)
        coeff[k] = sum / P


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
    global PLOT, POLES, COEFF, OTHER_PLOTS
    if PLOT is not None:
        for point in PLOT:
            point.remove()
    if POLES is not None:
        for point in POLES:
            point.remove()
    if COEFF is not None:
        for point in COEFF:
            point.remove()
    for plot in OTHER_PLOTS:
        if plot is not None:
            for point in plot:
                point.remove()
    OTHER_PLOTS = []


def draw(event):
    clear()
    integrate()

    points = f(coeff, T)
    global PLOT, COEFF, POLES
    PLOT = ax.plot(points.real, points.imag, 'black')
    COEFF = ax.plot(coeff.real, coeff.imag, 'b+')
    POLES = ax.plot(poles.real, poles.imag, 'yx')

    for c in other_coeffs:
        points = f(c, T)
        OTHER_PLOTS.append(ax.plot(points.real, points.imag, 'green'))

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
    global toggle, other_coeffs
    if event.key == 't':
        toggle = not toggle
    if event.key == ' ':
        i = 0
        while os.path.exists(coeffPath(i)):
            i += 1
        with open(coeffPath(i), "w") as file:
            for i, c in enumerate(coeff):
                if i is len(coeff) // 2:
                    file.write(printComp(c + offset))
                else:
                    file.write(printComp(c))

        # i = 0
        # while not os.path.exists(lejaPath(i)):
        #     i += 1
        # with open(lejaPath(i), "w") as file:
        #     leja.set_boundary(lambda z: f(coeff, z))
        #     leja.set_points(200)
        #     for l in leja.leja:
        #         file.write(printComp(l + offset))

    if event.key == 'i':
        other_coeffs = []
        i = 0
        while os.path.exists(coeffPath(i)):
            other_coeffs.append([])
            with open(coeffPath(i), 'r') as file:
                for line in file:
                    coords = [float(s) for s in line.split(',')]
                    c = complex(coords[0], coords[1])
                    other_coeffs[i].append(c)
            i += 1


if __name__ == '__main__':
    img = plt.imread(path + "scripts\\name2.png")
    fig, ax = plt.subplots()
    fig.canvas.mpl_connect('button_press_event', on_click)
    fig.canvas.mpl_connect('button_release_event', on_release)
    fig.canvas.mpl_connect('motion_notify_event', on_move)
    fig.canvas.mpl_connect('scroll_event', on_scroll)
    fig.canvas.mpl_connect('key_press_event', on_key)

    ax.axis([-a, a, -a, a])
    ax.hlines(0, -100, 100, 'g')
    ax.vlines(0, -100, 100, 'g')
    ax.imshow(img, extent=[offset.real - 2.1818 * a, offset.real + 2.1818 * a, offset.imag - a, offset.imag + a])

    plt.show()
