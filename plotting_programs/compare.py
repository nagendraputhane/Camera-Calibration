import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

datapd = pd.read_csv('/home/iq9/nagendra/delay/points_to_track.csv')
edge_points = datapd.to_numpy()

plt.subplot(2, 2, 1)
plt.title('Middle-point along width')
plt.plot(edge_points[:, 0], label = 'x')
plt.plot(edge_points[:, 1], label = 'y' )
plt.yticks(np.arange(0, 400, 50))
plt.legend()

plt.subplot(2, 2, 2)
plt.title('Middle-point along height')
plt.plot(edge_points[:, 2], label = 'x')
plt.plot(edge_points[:, 3], label = 'y' )
plt.yticks(np.arange(0, 400, 50))
plt.legend()

plt.subplot(2, 2, 3)
datapd = pd.read_csv('/home/iq9/nagendra/delay/IMU_and_Image_data/Vertical/20-02-19 11:35:41/data_lin_acc.csv')
lin_acc = datapd.to_numpy()

plt.title('Accelerometer (Linear)')
plt.plot(lin_acc[:, 1], label = 'x')
plt.plot(lin_acc[:, 2], label = 'y' )
plt.plot(lin_acc[:, 3], label = 'z')
plt.yticks(np.arange(-0.4, 0.4, 0.05))
plt.legend()

plt.subplot(2, 2, 4)
plt.title('Clubbed data')
plt.plot(edge_points[:, 0], label = 'x along width')
plt.plot(edge_points[:, 1], label = 'y along width' )
plt.plot(edge_points[:, 2], label = 'x along height')
plt.plot(edge_points[:, 3], label = 'y along height' )
plt.plot(lin_acc[:1200, 1], label = 'lin_acc x')
plt.plot(lin_acc[:1200, 2], label = 'lin_acc y' )
plt.plot(lin_acc[:1200, 3], label = 'lin_acc z')
plt.xticks(np.arange(0, 1200, 100))
plt.yticks(np.arange(0, 400, 50))
plt.legend()

plt.show()

plt.title('Clubbed data')
plt.plot((edge_points[:, 0]/np.linalg.norm(edge_points[:, 0])), label = 'x along width')
plt.plot(edge_points[:, 1]/np.linalg.norm(edge_points[:, 1]), label = 'y along width' )
plt.plot(edge_points[:, 2]/np.linalg.norm(edge_points[:, 2]), label = 'x along height')
plt.plot(edge_points[:, 3]/np.linalg.norm(edge_points[:, 3]), label = 'y along height' )
plt.plot(lin_acc[:1200, 1]/np.linalg.norm(lin_acc[:1200, 1]), label = 'lin_acc x')
plt.plot(lin_acc[:1200, 2]/np.linalg.norm(lin_acc[:1200, 2]), label = 'lin_acc y' )
plt.plot(lin_acc[:1200, 3]/np.linalg.norm(lin_acc[:1200, 3]), label = 'lin_acc z')
plt.xticks(np.arange(0, 1200, 100))
plt.yticks(np.arange(-0.15, 0.15, 0.01))
plt.legend()

plt.show()
