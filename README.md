# I] Camera rolling shutter impact measurement
# II] IMU to camera timestamp measurement

## dataset
* IMU data
```
Each Folder contains:
1) Acclerometer data. (data_acc.csv)
2) Gyroscope data. (data_gyro.csv)
3) Linear Accelerometer data. (data_rvec.csv)
```
* Videos
```
Each Folder contains:
1) The video recording.
2) Targets corners.
3) Targets middle-points of edges.
```

## Ploting
* plot_edge.py - Plot Middle-points of the edges of target.
* plot_corners.py - Plot the corners of the edges of the target.
* plot_imu.py - Plot Gyroscope, Accelerometer and Linear Accelerometer data of the image.

## edge_detection (Feature Detectors)
* Target - black rectangle on a white A4 sheet paper.
### 1) Canny algorithm.
### 2) Harris corner detector.
### 3) HoughLines - Hough transform algorithm for line detection.
### 4) Detect contours and draw bounding rectangle.
### 5) goodFeaturesToTrack() - 4 corners.
### 6) Detect Middle-points of Edges.
