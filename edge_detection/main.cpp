#include "feature_detectors.h"
#include  "point_detectors.h"

int main()
{
    FeatureDetectors fd;
    PointDetectors pd;

    std::vector<cv::Point2f> corners_global;
    int frame_width, frame_height;
    int first_black_row_mid, first_black_col_mid;
    int second_black_row_mid, second_black_col_mid;

    /*VideoCapture cap("/home/iq9/nagendra/delay/dataset/Videos/4/VID_20200217_134725.mp4");
    frame_width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
    frame_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
    VideoWriter video("/home/iq9/nagendra/delay/dataset/output_corners.avi", CV_FOURCC('M','J','P','G'),
                      30, Size(frame_width,frame_height));*/

    std::ofstream corner_csv;
    corner_csv.open ("/home/iq9/nagendra/delay/corners.csv");
    std::ofstream points_to_track;
    points_to_track.open ("/home/iq9/nagendra/delay/points_to_track.csv");//top left, bottom left, top right, bottom right
    std::ifstream stream ("/home/iq9/nagendra/delay/IMU_and_Image_data/20-02-17_17:50:23/data_image.csv");

    Mat frame, src_gray;

    string line, frame_name;

    while(stream >> line)
    {
        std::istringstream s(line);
        std::string field;
        while (getline(s, field,','))
        {
            frame_name = field;
        }

        string path = "/home/iq9/nagendra/delay/IMU_and_Image_data/20-02-17_17:50:23/";

        path = path + frame_name;

        frame = imread(path, CV_LOAD_IMAGE_COLOR);

        cvtColor( frame, src_gray, COLOR_BGR2GRAY );

        cv::threshold(src_gray, src_gray, 75, 255, ThresholdTypes::THRESH_BINARY);

        cv::goodFeaturesToTrack(src_gray, corners_global, 4, 0.01, 2, noArray(), 5,true, 0.04);

        fd.harris(src_gray, corners_global);
        //fd.hough(src_gray);
        //fd.rect(src_gray);

        pd.corners(corners_global);
        pd.edge_points(src_gray, &first_black_row_mid, &first_black_col_mid,
                                 &second_black_row_mid, &second_black_col_mid);

        corner_csv << corners_global[0].x << "," << corners_global[0].y << "," <<
                      corners_global[1].x << "," << corners_global[1].y << "," <<
                      corners_global[2].x << "," << corners_global[2].y << "," <<
                      corners_global[3].x << "," << corners_global[3].y << "\n";
        points_to_track << first_black_row_mid << "," << first_black_col_mid << "," <<
                               second_black_row_mid << "," << second_black_col_mid << "\n";

        first_black_row_mid = first_black_col_mid = second_black_row_mid = second_black_col_mid = 0;

        char c=(char)waitKey(1);
        if(c==27)
            break;

    }
    corner_csv.close();
    points_to_track.close();
}
