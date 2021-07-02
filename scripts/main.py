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

        with open(path + "data\\leja\\segment_" + str(_i) + ".txt", "w") as file
            for point in leja:
                file.write(printComp(point + offset + offsets[_i]))


def coeff():
    for _i in range(18):
        coeff = path + "data\\coeff\\segment_"
        C = file_len(coeff + str(_i) + ".txt")
        with open(coeff + str(_i) + ".txt", "r") as file:
            for i, line in enumerate(file):
                coord = [float(s) for s in line.split(',')]
                leja.append(complex(coord[0], coord[1]))


if __name__ == '__main__':
    offset = complex(-10, 12)
    offsets = [
        complex(2, 0), complex(2, 0), complex(2, 0), complex(2, 0), complex(2, 0), complex(2, 0),
        complex(10, 0), complex(10, 0), complex(10, 0), complex(10, 0),
        complex(20, 0), complex(20, 0), complex(20, 0), complex(20, 0),
        complex(28.5, 0), complex(28.5, 0), complex(28.5, 0), complex(28.5, 0)]

    path = "C:\\Users\\lauwe\\source\\repos\\FractalDrawer\\FractalDrawer\\"

    # leja()
