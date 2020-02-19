#ifndef POINT_DETECTORS_H
#define POINT_DETECTORS_H

#endif // POINT_DETECTORS_H

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace cv;
using namespace std;

bool sorting (const cv::Point p1, const cv::Point p2) {
    return ((p1.x ) < (p2.x));
}

class PointDetectors
{
public:
    void edge_points(Mat src_gray, int *first_black_row_mid, int *first_black_col_mid,
                                   int *second_black_row_mid, int *second_black_col_mid)
    {
        int end_loop = 0;
        for (int i = 0; i < 480 && end_loop != 1; i++)
        {
            for (int j = 277; j < 390 && end_loop != 1; j++)
            {
                if (static_cast<int>(cv::norm(src_gray.row(i).col(j))) == 0)
                {
                    int first_black_r = i;
                    int first_black_c = j;
                    if (first_black_c > 315)
                    {
                        continue;
                    }
                    int row_to_track = first_black_r + 50;
                    int column_to_track;
                    for ( int coli = first_black_c; coli < 390; coli++)
                    {
                        if (static_cast<int>(cv::norm(src_gray.row(row_to_track).col(coli))) == 255)
                        {
                            int last_black_c = coli - 1;
                            column_to_track = (first_black_c + last_black_c)/2;
                            break;
                        }
                    }
                    for ( int k = 0; k < 480; k++)
                    {
                        if (static_cast<int>(cv::norm(src_gray.row(k).col(column_to_track))) == 0)
                        {
                            *first_black_row_mid = k;
                            *second_black_row_mid = row_to_track;
                            *first_black_col_mid = column_to_track;
                            *second_black_col_mid = first_black_c;
                            cout << "Point to track : " << *first_black_row_mid << ", " << *first_black_col_mid << endl;
                            cout << "Point to track : " << *second_black_row_mid << ", " << *second_black_col_mid << endl;
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

    void corners(vector<Point2f> corners_global)
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
        cout << "Corners are : " << corners_global << endl;

    }
};
