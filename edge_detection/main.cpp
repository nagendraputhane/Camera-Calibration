#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;
std::vector<cv::Point2f> corners_global;
int frame_width, frame_height, val = 0;
int first_black_row_mid, first_black_col_mid;
int second_black_row_mid, second_black_col_mid;

bool sorting (const cv::Point p1, const cv::Point p2) {
    return ((p1.x ) < (p2.x));
}

class FeatureDetectors
{
public:
    void harris(Mat src_gray)
    {
        val ++;
        val = val % 100;
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

        cout << src_gray.at<int>(0, 0);

        /*namedWindow( "Corners detected" );
        imshow( "Corners detected", src_gray);
        cvtColor( dst_norm_scaled, dst_norm_scaled, cv::COLOR_GRAY2BGR );
        //video << dst_norm_scaled;*/
    }

    void edge_points(Mat src_gray)
    {
        int end_loop = 0;
        for (int i = 0; i < 720 && end_loop != 1; i++)
        {
            for (int j = 0; j < 1280 && end_loop != 1; j++)
            {
                if (static_cast<int>(cv::norm(src_gray.row(i).col(j))) == 0)
                {
                    int first_black_r = i;
                    int first_black_c = j;
                    if (first_black_c > 300)
                    {
                        continue;
                    }
                    cout << "first_black_r : " << first_black_r << ", first_black_c : " << first_black_c << endl;
                    int row_to_track = first_black_r + 50;
                    cout << "row_to_track : " << row_to_track << endl;
                    int column_to_track;
                    for ( int coli = first_black_c; coli < 1280; coli++)
                    {
                        if (static_cast<int>(cv::norm(src_gray.row(row_to_track).col(coli))) == 255)
                        {
                            int last_black_c = coli - 1;
                            cout << "last_black_c : " << last_black_c << endl;
                            column_to_track = (first_black_c + last_black_c)/2;
                            cout << "column_to_track : " << column_to_track << endl;
                            break;
                        }
                    }
                    for ( int k = 0; k < 720; k++)
                    {
                        if (static_cast<int>(cv::norm(src_gray.row(k).col(column_to_track))) == 0)
                        {
                            first_black_row_mid = k;
                            second_black_row_mid = row_to_track;
                            cout << "first_black_row_mid : " << first_black_row_mid << endl;
                            first_black_col_mid = column_to_track;
                            second_black_col_mid = first_black_c;
                            cout << "Point to track : " << first_black_row_mid << ", " << first_black_col_mid << endl;
                            cout << "Point to track : " << second_black_row_mid << ", " << second_black_col_mid << endl;
                            cout << "------------------------" << endl;
                            end_loop = 1;
                            //exit(0);
                            break;
                        }
                    }
                }
            }
        }
    }




    void corners()
    {
        std::sort(corners_global.begin(), corners_global.end(), sorting);

        if(corners_global[0].y < corners_global[1].y)
        {
            float x0 = corners_global[0].x;
            float y0 = corners_global[0].y;
            float x1 = corners_global[1].x;
            float y1 = corners_global[1].y;
            corners_global[0].x = x1;
            corners_global[0].y = y1;
            corners_global[1].x = x0;
            corners_global[1].y = y0;
        }
        if(corners_global[2].y < corners_global[3].y)
        {
            float x0 = corners_global[2].x;
            float y0 = corners_global[2].y;
            float x1 = corners_global[3].x;
            float y1 = corners_global[3].y;
            corners_global[2].x = x1;
            corners_global[2].y = y1;
            corners_global[3].x = x0;
            corners_global[3].y = y0;
        }
        //cout << "Corners are : " << corners_global << endl;

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

int main()
{
    FeatureDetectors fd;
    Mat src_gray;
    vector<cv::Vec4f> lines;

    VideoCapture cap("/home/iq9/nagendra/delay/dataset/VID_20200212_140735.mp4");

    frame_width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
    frame_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

    //VideoWriter video("/home/iq9/nagendra/delay/dataset/output_corners.avi", CV_FOURCC('M','J','P','G'),
    //                  30, Size(frame_width,frame_height));
    std::ofstream corner_csv;
    corner_csv.open ("/home/iq9/nagendra/delay/corners.csv");
    std::ofstream points_to_track;
    points_to_track.open ("/home/iq9/nagendra/delay/points_to_track.csv");
    //top left, bottom left, top right, bottom right
    while(1)
    {
        Mat frame, frame_bi;
        cap >> frame;

        if (frame.empty())
          break;

        cvtColor( frame, src_gray, COLOR_BGR2GRAY );

        cv::threshold(src_gray, src_gray, 150, 255, ThresholdTypes::THRESH_BINARY);

        cv::goodFeaturesToTrack(src_gray, corners_global, 4, 0.01, 2, noArray(), 5,true, 0.04);

        fd.harris(src_gray);
        //fd.hough(src_gray);
        //fd.rect(src_gray);

        fd.corners();
        corner_csv << corners_global[0].x << "," << corners_global[0].y << "," <<
                      corners_global[1].x << "," << corners_global[1].y << "," <<
                      corners_global[2].x << "," << corners_global[2].y << "," <<
                      corners_global[3].x << "," << corners_global[3].y << "\n";
        fd.edge_points(src_gray);

        points_to_track << first_black_row_mid << "," << first_black_col_mid << "," <<
                           second_black_row_mid << "," << second_black_col_mid << "\n";

        first_black_row_mid = first_black_col_mid = second_black_row_mid = second_black_col_mid = 0;
        char c=(char)waitKey(25);
        if(c==27)
            break;
    }
    corner_csv.close();
    points_to_track.close();
}
