import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

#np.subtract(x1, x2)

datapd = pd.read_csv('/home/iq9/nagendra/delay/IMU_and_Image_data/20-02-18 18:53:41/data_acc.csv')
data1 = datapd.to_numpy()
datapd = pd.read_csv('/home/iq9/nagendra/delay/IMU_and_Image_data/20-02-18 18:53:41/data_gravity.csv')
grav = datapd.to_numpy()
#data1 = np.subtract(data1, grav)
data1 = data1[:, 1]
data1 = data1 - data1.mean()
data1 = data1 / data1.max()

#datapd = pd.read_csv('/home/iq9/nagendra/delay/points_to_track.csv')
#data1 = datapd.to_numpy()
#data1 = data1[:, 2]
#data1 = data1[:, 2]/np.linalg.norm(data1[:, 2])


datapd = pd.read_csv('/home/iq9/nagendra/delay/IMU_and_Image_data/20-02-18 18:53:41/data_lin_acc.csv')
data2 = datapd.to_numpy()
data2 = data2[:, 1]
#data2 = data2[:, 1]/np.linalg.norm(data2[:, 1])
data2 = data2 - data2.mean()
data2 = data2 / data2.max()

fig, ax1 = plt.subplots()

plt.grid()
color = 'tab:red'
ax1.set_ylabel('normalized')
ax1.set_xlabel('X axis Accelerometer', color=color)
ax1.plot(data1, color=color)
ax1.tick_params(axis='x', labelcolor=color)

ax2 = ax1.twiny()  # instantiate a second axes that shares the same x-axis

color = 'tab:blue'
ax2.set_xlabel('X axis Linear Accelerometer', color=color)  # we already handled the x-label with ax1
ax2.plot(data2, color=color)
ax2.tick_params(axis='x', labelcolor=color)

plt.show()
