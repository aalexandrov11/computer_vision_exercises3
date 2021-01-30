#include <opencv2\opencv.hpp>
#include <vector>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("many.jpg");
	Mat templ = imread("one.jpg");

	Mat img_gray;
	Mat templ_gray;
	cvtColor(img, img_gray, COLOR_BGR2GRAY);
	cvtColor(templ, templ_gray, COLOR_BGR2GRAY);

	Mat result;
	matchTemplate(img, templ, result, TM_CCOEFF_NORMED);

	double thresh = 0.7;
	threshold(result, result, thresh, 1., THRESH_BINARY);

	Mat resb;
	result.convertTo(resb, CV_8U, 255);

	vector<vector<Point>> contours;
	findContours(resb, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

	for (int i = 0; i < contours.size(); ++i)
	{
		Mat mask(result.rows, result.cols, uchar(0));
		drawContours(mask, contours, i, Scalar(255), -1);

		Point max_point;
		double max_val;
		minMaxLoc(result, NULL, &max_val, NULL, &max_point, mask);

		rectangle(img, Rect(max_point.x, max_point.y, templ.cols, templ.rows), Scalar(0, 255, 0), 2);
	}
	imshow("", img);
	return 0;

}