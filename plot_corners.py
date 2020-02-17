import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

datapd = pd.read_csv('/home/iq9/nagendra/delay/dataset/corners.csv')
datanp = datapd.to_numpy()

plt.title('Top Left')
plt.plot(datanp[:, 0], label = 'x')
plt.plot(datanp[:, 1], label = 'y' )
plt.yticks(np.arange(0, 800, 50))
plt.legend()
plt.show()

plt.title('Bottom Left')
plt.plot(datanp[:, 2], label = 'x')
plt.plot(datanp[:, 3], label = 'y' )
plt.yticks(np.arange(0, 800, 50))
plt.legend()
plt.show()

plt.title('Top Right')
plt.plot(datanp[:, 4], label = 'x')
plt.plot(datanp[:, 5], label = 'y' )
plt.yticks(np.arange(0, 1400, 100))
plt.legend()
plt.show()

plt.title('Bottom Right')
plt.plot(datanp[:, 6], label = 'x')
plt.plot(datanp[:, 7], label = 'y' )
plt.yticks(np.arange(0, 1400, 100))
plt.legend()
plt.show()
