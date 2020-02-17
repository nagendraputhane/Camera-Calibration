import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

datapd = pd.read_csv('/home/iq9/nagendra/delay/dataset/Videos/4/points_to_track.csv')
datanp = datapd.to_numpy()

plt.title('Middle-point along width')
plt.plot(datanp[:, 0], label = 'x')
plt.plot(datanp[:, 1], label = 'y' )
plt.yticks(np.arange(0, 800, 50))
plt.legend()
plt.show()

plt.title('Middle-point along height')
plt.plot(datanp[:, 2], label = 'x')
plt.plot(datanp[:, 3], label = 'y' )
plt.yticks(np.arange(0, 800, 50))
plt.legend()
plt.show()
