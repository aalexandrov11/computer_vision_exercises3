#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <list>
#include <iterator>
#include <iostream>
using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat img = imread("many.jpg");
	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	Mat templ = imread("o.jpg");
	Mat result;
	//double thresh = 0.7;
	//threshold(result, result, thresh, 1., THRESH_BINARY);
	int resultCol = img.cols - templ.cols + 1;
	int resultRow = img.rows - templ.rows + 1;
	matchTemplate(img, templ, result, TM_CCOEFF_NORMED);
	//double minVal, maxVal; 
	//Point minLoc, maxLoc;
	//minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
	//double minTresh = (minVal + 1e-6) * 1.5;
	//list <Point> match;
	//for (int i = 0; i <  ; i++)
	//{
	//
	//}
	Mat resb;
	result.convertTo(resb, CV_8U, 255);
	vector<vector<Point>> contours;
	findContours(resb, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

	for (int i = 0; i < contours.size(); ++i)
	{
		Mat mask(result.rows, result.cols, uchar(0));
		drawContours(mask, contours, i, Scalar(255), 1);
		//Mat match = image(Rect(highest_maxLoc.x, highest_maxLoc.y, templateMat.cols, templateMat.rows));
		Point maxLoc;
		double maxVal;
		//minMaxLoc(result, NULL, &max_val, NULL, &max_point, mask);
		//minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, mask);
		minMaxLoc(result, NULL, &maxVal, NULL, &maxLoc, mask);
		rectangle(img, maxLoc, Point(maxLoc.x + templ.cols, maxLoc.y + templ.rows), Scalar::all(0), 2, 8, 0);
	}
	imshow("", img);
	waitKey(0);
	return 0;
}