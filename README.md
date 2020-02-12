# Camera rolling shutter impact measurement
# IMU to camera timestamp measurement

## dataset
* The dataset has CSV files that contain 
```
1) Linear acceleration.
2) Gyroscope readings.
3) Acclerometer reading.
over a period of time along with their timestamps
```
* They are used to interpret the acceleration and rotation along X, Y and Z axes.
* The dataset also has video files that contains the oscillatory recording of the target image.

## Ploting
* plot.py is used to plot the X, Y and Z axes readings of each of the CSV files.

## Feature Detectors
* From the video file which contains a black rectangle in a white A4 target, we try to extract edges and corners. They are,
### Canny algorithm
### Harris corner detector
### HoughLines - Hough transform algorithm for line detection
### Detect contours and draw bounding rectangle
