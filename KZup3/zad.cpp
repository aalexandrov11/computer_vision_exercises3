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
	Mat ref = imread("objects.jpg");
	Mat tpl = imread("sq.png");

	Mat ref_gray, tpl_gray;
	cvtColor(ref, ref_gray, COLOR_BGR2GRAY);
	cvtColor(tpl, tpl_gray, COLOR_BGR2GRAY);

	Mat res(ref.rows - tpl.rows + 1, ref.cols - tpl.cols + 1, CV_32FC1);
	matchTemplate(ref_gray, tpl_gray, res, TM_CCOEFF_NORMED);
	threshold(res, res, 0.8, 1., THRESH_TOZERO);
	int count = 0;
	while (true)
	{
		double minval, maxval, threshold = 0.8;
		Point minloc, maxloc;
		minMaxLoc(res, &minval, &maxval, &minloc, &maxloc);

		if (maxval >= threshold)
		{
			rectangle(ref, maxloc, Point(maxloc.x + tpl.cols, maxloc.y + tpl.rows), CV_RGB(100, 100, 100), 2);
			count++;
			floodFill(res, maxloc, Scalar(0), 0, Scalar(.1), Scalar(1.));
		}
		else
			break;
	}
	cout << "Count of matches: " << count << endl;
	imshow("", ref);
	waitKey(0);
	return 0;
}
