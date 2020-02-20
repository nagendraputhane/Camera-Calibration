import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

#####
datapd = pd.read_csv('/home/iq9/nagendra/delay/IMU_and_Image_data/Vertical/20-02-19 11:46:13/data_acc.csv')
datanp = datapd.to_numpy()

plt.title('Accelerometer')
plt.plot(datanp[:, 1], label = 'x')
plt.plot(datanp[:, 2], label = 'y' )
plt.plot(datanp[:, 3], label = 'z')
plt.yticks(np.arange(-0.5, 11, 0.5))
plt.legend()
plt.show()

#####
datapd = pd.read_csv('/home/iq9/nagendra/delay/IMU_and_Image_data/Vertical/20-02-19 11:46:13/data_gravity.csv')
datanp = datapd.to_numpy()

plt.title('Gravity')
plt.plot(datanp[:, 1], label = 'x')
plt.plot(datanp[:, 2], label = 'y' )
plt.plot(datanp[:, 3], label = 'z')
plt.yticks(np.arange(-0.5, 11, 0.5))
plt.legend()
plt.show()

#####
datapd = pd.read_csv('/home/iq9/nagendra/delay/IMU_and_Image_data/Vertical/20-02-19 11:46:13/data_gyro.csv')
datanp = datapd.to_numpy()


#plt.subplot(3, 1, 1)
plt.title('Gyroscope')
plt.plot(datanp[:, 1], label = 'x')
plt.plot(datanp[:, 2], label = 'y' )
plt.plot(datanp[:, 3], label = 'z')
plt.yticks(np.arange(-0.2, 0.2, 0.05))
plt.legend()
plt.show()

#####
datapd = pd.read_csv('/home/iq9/nagendra/delay/IMU_and_Image_data/Vertical/20-02-19 11:46:13/data_lin_acc.csv')
datanp = datapd.to_numpy()
ax = datanp[:, 1]

plt.title('Accelerometer (Linear)')
plt.plot(datanp[:, 1], label = 'x')
plt.plot(datanp[:, 2], label = 'y' )
plt.plot(datanp[:, 3], label = 'z')
plt.yticks(np.arange(-0.4, 0.4, 0.05))
plt.legend()
plt.show()





'''
def running_mean(x, N):
    cumsum = np.cumsum(np.insert(x, 0, 0)) 
    return (cumsum[N:] - cumsum[:-N]) / float(N)

N = 100

result = running_mean(ax, N)
plt.title('X Accelerometer (Linear)')
plt.plot(result, label = 'x')
plt.yticks(np.arange(-1, 1, 0.1))
plt.legend()
plt.show()
'''
