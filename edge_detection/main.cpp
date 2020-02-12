#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

class FeatureDetectors
{
public:
    void harris(Mat src_gray)
    {
        int blockSize = 2;
        int apertureSize = 3;
        double k = 0.04;
        int thresh = 75;

        std::vector<cv::Point2f> corners;

        Mat dst = Mat::zeros( src_gray.size(), CV_32FC1 );

        cornerHarris( src_gray, dst, blockSize, apertureSize, k );

        cv::TermCriteria criteria = cv::TermCriteria(cv::TermCriteria::EPS || cv::TermCriteria::MAX_ITER, 100, 0.001 );

        /// Normalizing
        Mat dst_norm, dst_norm_scaled;
        normalize( dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
        convertScaleAbs( dst_norm, dst_norm_scaled );

        /// Drawing a circle around corners
        for( int i = 0; i < dst_norm.rows ; i++ )
        {
            for( int j = 0; j < dst_norm.cols; j++ )
            {
                if( (int) dst_norm.at<float>(i,j) > thresh )
                {

                    circle( dst_norm_scaled, cv::Point2f(j,i), 5,  Scalar(255), 2, 8, 0 );
                    corners.emplace_back(cv::Point2f(j,i));
                }
            }
        }

        cv::cornerSubPix(src_gray, corners, cv::Size(5,5), cv::Size(-1,-1), criteria);

        if(corners.size() <= 4)
            cout << "Corners are : " << corners << endl;

        corners.clear();

        namedWindow( "Corners detected" );
        imshow( "Corners detected", dst_norm_scaled);

        char c=(char)waitKey(25);
        if(c==27)
          exit(0);
    }

    void hough(Mat src_gray)
    {
        std::vector<Vec2f> lines;
        cv::Mat src_gray_c;
        cv::HoughLines(src_gray, lines, 1, CV_PI/180, 150);

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

            namedWindow( "Corners detected" );
            imshow( "Corners detected", src_gray_c );

            char c=(char)waitKey(25);
            if(c==27)
                exit(0);
        }
    }

    void rect(Mat canny_output)
    {
        int thresh = 100;
        RNG rng(12345);

        //blur( canny_output, canny_output, Size(7,7) );

        vector<vector<Point> > contours;
        findContours( canny_output, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE );

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
        namedWindow( "Contours" );
        imshow( "Contours", drawing );

        char c=(char)waitKey(25);
        if(c==27)
            exit(0);
    }
};

int main()
{
    FeatureDetectors fd;
    Mat src_gray;
    vector<cv::Vec4f> lines;

    //cv::Ptr<CLAHE> clahe = cv::createCLAHE(0.5);

    VideoCapture cap("/home/iq9/nagendra/delay/dataset/VID_20200212_144723.mp4");
    while(1)
    {
        Mat frame, frame_bi;
        cap >> frame;

        if (frame.empty())
          break;


        cv::Ptr<cv::LineSegmentDetector> lsd = createLineSegmentDetector();

        cvtColor( frame, src_gray, COLOR_BGR2GRAY );

        //lsd->detect(src_gray, lines);

        //cout << "Number of lines : " << lines.size() << endl;

        cv::Canny(src_gray, src_gray, 200, 255, 3, true);

        fd.harris(src_gray);
        //fd.hough(src_gray);
        //fd.rect(src_gray);
    }
}
