import numpy as np
import matplotlib.pyplot as plt
import matplotlib.tri as tri
import time
import random
import serial


def to_matrix(l, n):
    return [l[i:i + n] for i in range(0, len(l), n)]


ser = serial.Serial("/dev/cu.usbserial-0001", 115200)

fig, ax = plt.subplots()
inputData = []
inputRows = 4

Xmin = 0
Xmax = inputRows - 1
Ymin = 0
Ymax = inputRows - 1

while True:
    dataLine = ser.readline().decode()
    data = dataLine.split(',')
    del data[-1]

    if len(data) == 16:
        print(data)
        inputData = data

    x = []
    y = []
    z = []



    dataMatrix = to_matrix(inputData, inputRows)

    for xData, line in enumerate(dataMatrix):
        for yData, rssi in enumerate(line):
            x.append(xData)
            y.append(yData)
            z.append(int(rssi))



    ngridx = 16
    ngridy = 16

    xi = np.linspace(Xmin, Xmax, ngridx)
    yi = np.linspace(Ymin, Ymax, ngridy)

    triang = tri.Triangulation(x, y)
    interpolator = tri.LinearTriInterpolator(triang, z)
    Xi, Yi = np.meshgrid(xi, yi)
    zi = interpolator(Xi, Yi)

    ax.contour(xi, yi, zi, levels=8, linewidths=0.2, colors='k')
    cntr1 = ax.contourf(xi, yi, zi, levels=8, cmap="gist_rainbow")  # RdBu_r
    # fig.colorbar(cntr1, ax=ax, orientation="horizontal").set_label("RSSI")

    ax.plot(x, y, 'ko', ms=3)
    ax.set(xlim=(Xmin, Xmax), ylim=(Ymin, Ymax))
    ax.set_title("WiFi signal strength RSSI")
    ax.ticklabel_format(useOffset=False)
    ax.set_aspect(1)

    plt.pause(0.5)
    # fig.clf()
    ax.cla()

# plt.savefig("wifi_map.png", dpi=220)

plt.show()

ser.close()

exit()
