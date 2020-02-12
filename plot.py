import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

datapd = pd.read_csv('/home/iq9/nagendra/delay/dataset/20-02-12 11:33:26/data_rvec.csv')
datanp = datapd.to_numpy()

plt.title('Accelerometer (Linear)')
plt.plot(datanp[:, 1], label = 'x')
plt.plot(datanp[:, 2], label = 'y' )
plt.plot(datanp[:, 3], label = 'z')
plt.yticks(np.arange(-1, 1, 0.1))
plt.legend()
plt.show()

datapd = pd.read_csv('/home/iq9/nagendra/delay/dataset/20-02-12 11:33:26/data_gyro.csv')
datanp = datapd.to_numpy()

plt.title('Gyroscope')
plt.plot(datanp[:, 1], label = 'x')
plt.plot(datanp[:, 2], label = 'y' )
plt.plot(datanp[:, 3], label = 'z')
plt.yticks(np.arange(-1, 1, 0.1))
plt.legend()
plt.show()

datapd = pd.read_csv('/home/iq9/nagendra/delay/dataset/20-02-12 11:33:26/data_acc.csv')
datanp = datapd.to_numpy()

plt.title('Accelerometer')
plt.plot(datanp[:, 1], label = 'x')
plt.plot(datanp[:, 2], label = 'y' )
plt.plot(datanp[:, 3], label = 'z')
plt.yticks(np.arange(-0.5, 11, 0.5))
plt.legend()
plt.show()
