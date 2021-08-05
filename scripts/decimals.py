import re

path = "C:\\Users\\Gebruiker\\Desktop\\temp\\"


def printComp(z) -> str:
    return "$" + str(z.real) + "+" + str(z.imag) + "i$"


for i in range(23):
    with open(path + "segment_" + str(i) + ".txt", 'r') as file:
        lines = file.readlines()
        for j in range(len(lines)):
            D = [round(float(d), 3) for d in re.findall(r'\-?\d+.\d+', lines[j])]
            z = complex(D[0], D[1])
            lines[j] = printComp(z) + "\t\\\\\n"
    with open(path + "segment_" + str(i) + ".txt", 'w') as file:
        for j in range(min(len(lines), 40)):
            file.write(lines[j])
