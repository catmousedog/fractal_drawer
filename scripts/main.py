def printComp(z) -> str:
    return str(z.real) + "," + str(z.imag) + "\n"


def file_len(fname):
    with open(fname) as f:
        for i, l in enumerate(f):
            pass
    return i + 1


def leja():
    for _i in range(18):
        with open(path + "data\\leja\\segment_" + str(_i) + ".txt", "r") as file:
            leja = []
            for line in file.readlines():
                coord = [float(s) for s in line.split(',')]
                leja.append(complex(coord[0], coord[1]))

        with open(path + "data\\leja\\segment_" + str(_i) + ".txt", "w") as file:
            for point in leja:
                file.write(printComp(point + offset + offsets[_i]))


def coeff():
    for _i in range(18):
        coeff = []
        C = file_len(path + "data\\coeff\\segment_" + str(_i) + ".txt")

        with open(path + "data\\coeff\\segment_" + str(_i) + ".txt", "r") as file:
            for _j, line in enumerate(file):
                coords = [float(s) for s in line.split(',')]
                c = complex(coords[0], coords[1])
                if _j == C // 2:
                    c += offset + offsets[_i]
                coeff.append(c)

        with open(path + "data\\coeff\\segment_" + str(_i) + ".txt", "w") as file:
            for c in coeff:
                file.write(printComp(c))


if __name__ == '__main__':
    offset = complex(-10, 12)
    offsets = [
        complex(2, 0), complex(2, 0), complex(2, 0), complex(2, 0), complex(2, 0), complex(2, 0),
        complex(10, 0), complex(10, 0), complex(10, 0), complex(10, 0),
        complex(20, 0), complex(20, 0), complex(20, 0), complex(20, 0),
        complex(28.5, 0), complex(28.5, 0), complex(28.5, 0), complex(28.5, 0)]

    # path = "C:\\Users\\lauwe\\source\\repos\\FractalDrawer\\FractalDrawer\\"
    path = "C:\\Users\\Gebruiker\\source\\repos\\FractalDrawer\\FractalDrawer\\"

    # leja()
    # coeff()
