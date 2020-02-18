#ifndef FEATURE_DETECTORS_H
#define FEATURE_DETECTORS_H

#endif // FEATURE_DETECTORS_H

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;

class FeatureDetectors
{
public:
    void harris(Mat src_gray, vector<Point2f> corners_global)
    {
        int blockSize = 5, apertureSize = 3, thresh = 130; //2, 75
        double k = 0.04;

        std::vector<cv::Point2f> corners;
        Mat dst = Mat::zeros( src_gray.size(), CV_32FC1 );

        cornerHarris( src_gray, dst, blockSize, apertureSize, k );

        /// Normalizing
        Mat dst_norm, dst_norm_scaled;
        normalize( dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
        convertScaleAbs( dst_norm, dst_norm_scaled );

        for(int i = 0; i < corners_global.size(); i++)
            circle( dst_norm_scaled, corners_global[i], 5,  Scalar(255), 1, LINE_AA, 0 );

        //cout << src_gray.at<int>(0, 0);

        namedWindow( "Corners detected" );
        imshow( "Corners detected", src_gray);
        cvtColor( dst_norm_scaled, dst_norm_scaled, cv::COLOR_GRAY2BGR );
        //video << dst_norm_scaled;
    }
    void hough(Mat src_gray)
    {
        std::vector<Vec2f> lines;
        cv::Mat src_gray_c;
        cv::HoughLines(src_gray, lines, 1, CV_PI/180, 108); //150

        cvtColor(src_gray, src_gray_c, COLOR_GRAY2BGR);
        for( size_t i = 0; i < lines.size(); i++ )
        {
            float rho = lines[i][0], theta = lines[i][1];
            Point pt1, pt2;
            double a = cos(theta), b = sin(theta);
            double x0 = a*rho, y0 = b*rho;
            pt1.x = cvRound(x0 + 1000*(-b));
            pt1.y = cvRound(y0 + 1000*(a));
            pt2.x = cvRound(x0 - 1000*(-b));
            pt2.y = cvRound(y0 - 1000*(a));
            line( src_gray_c, pt1, pt2, Scalar(0,0,255), 3, LINE_AA);

            namedWindow( "Edges detected" );
            imshow( "Edges detected", src_gray_c );


        }
    }

    void rect(Mat canny_output)
    {
        int thresh = 100;
        RNG rng(12345);

        //blur( canny_output, canny_output, Size(7,7) );

        vector<vector<Point> > contours;
        findContours( canny_output, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE );

        for (int i =0; i < contours.size(); i++)
        {
            //cout << "points" << contours.at(i);
        }

        vector<vector<Point> > contours_poly( contours.size() );
        vector<Rect> boundRect( contours.size() );
        vector<Point2f>centers( contours.size() );
        vector<float>radius( contours.size() );

        for( size_t i = 0; i < contours.size(); i++ )
        {
            approxPolyDP( contours[i], contours_poly[i], .3, true );
            boundRect[i] = boundingRect( contours_poly[i] );
        }

        Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
        for( size_t i = 0; i< contours.size(); i++ )
        {
            Scalar color = Scalar( rng.uniform(0, 256), rng.uniform(0,256), rng.uniform(0,256) );
            drawContours( drawing, contours_poly, (int)i, color );
            rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 1 );
        }
        //namedWindow( "Contours" );
        //imshow( "Contours", drawing );

        //char c=(char)waitKey(25);
        //if(c==27)
            //exit(0);
    }
};
