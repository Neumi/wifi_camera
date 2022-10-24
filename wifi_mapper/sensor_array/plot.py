import numpy as np
import matplotlib.pyplot as plt
import matplotlib.tri as tri
import time

def to_matrix(l, n):
    return [l[i:i + n] for i in range(0, len(l), n)]

x = []
y = []
z = []

inputRows = 4
inputData = [62, 63, 60, 61, 59, 70, 57, 59, 57, 67, 58, 60, 51, 66, 65, 57]
dataMatrix = to_matrix(inputData, inputRows)

for xData, line in enumerate(dataMatrix):
    for yData, rssi in enumerate(line):
        x.append(xData)
        y.append(yData)
        z.append(rssi)

Xmin = min(x)
Xmax = max(x)
Ymin = min(y)
Ymax = max(y)

npts = 150
ngridx = 150
ngridy = 150

fig, ax = plt.subplots()

xi = np.linspace(Xmin, Xmax, ngridx)
yi = np.linspace(Ymin, Ymax, ngridy)

triang = tri.Triangulation(x, y)
interpolator = tri.LinearTriInterpolator(triang, z)
Xi, Yi = np.meshgrid(xi, yi)
zi = interpolator(Xi, Yi)

ax.contour(xi, yi, zi, levels=12, linewidths=0.2, colors='k')
cntr1 = ax.contourf(xi, yi, zi, levels=8, cmap="gist_rainbow")  # RdBu_r

fig.colorbar(cntr1, ax=ax, orientation="horizontal").set_label("RSSI")
ax.plot(x, y, 'ko', ms=3)
ax.set(xlim=(Xmin, Xmax), ylim=(Ymin, Ymax))
ax.set_title("WiFi signal strength RSSI")
ax.ticklabel_format(useOffset=False)

ax.set_aspect(1)
#plt.savefig("wifi_map.png", dpi=220)
plt.show()
