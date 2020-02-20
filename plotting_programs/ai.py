import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

def normalize(data):
	data = data - data.mean() #subtract the mean to centre it around 0
	data = data / data.max() #divide by max to scale it to [-1, 1]
	return data

datapd = pd.read_csv('/home/iq9/nagendra/delay/IMU_and_Image_data/Vertical/20-02-19 11:35:41/data_acc.csv') #read accelerometer data
data1 = datapd.to_numpy()
datapd = pd.read_csv('/home/iq9/nagendra/delay/IMU_and_Image_data/Vertical/20-02-19 11:35:41/data_gravity.csv') #read gravity vector
grav = datapd.to_numpy()
data1 = np.subtract(data1, grav) #subtract gravity vector from accelerometer data
data1 = data1[:, 2] #[0] - timeline, [1] - x, [2] - y, [3] - z
data1 = normalize(data1)

datapd = pd.read_csv('/home/iq9/nagendra/delay/points_to_track.csv') #read middle points of edges
data1 = datapd.to_numpy()
#Middle-point along width -> [0] - x , [1] - y; Middle-point along height -> [2] - x, [3] - y
data1 = data1[:, 2] #read X along height
data1 = normalize(data1)

datapd = pd.read_csv('/home/iq9/nagendra/delay/IMU_and_Image_data/Vertical/20-02-19 11:35:41/data_lin_acc.csv') #read linear acceleration vector
data2 = datapd.to_numpy()
data2 = data2[:, 2] #linear acceleration along Y axis
data2 = normalize(data2) #normalize the data around 0

fig, ax1 = plt.subplots()

plt.grid()
color = 'tab:red'
ax1.set_ylabel('normalized')
ax1.set_xlabel('Edge Point', color=color)
ax1.plot(data1, color=color)
ax1.tick_params(axis='x', labelcolor=color)

ax2 = ax1.twiny()  # instantiate a second axes that shares the same y-axis
#fig2, ax2 = plt.subplots()
plt.grid() 
color = 'tab:blue'
ax2.set_xlabel('Y axis Linear Accelerometer', color=color)  # we already handled the y-label with ax1
ax2.plot(data2, color=color)
ax2.tick_params(axis='x', labelcolor=color)

plt.show()
