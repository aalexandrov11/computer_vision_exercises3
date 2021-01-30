//3. Напишете програма, с която да откриете даден шаблон в изображение чрез сравнение с шаблони и / или контури.
//Примерни варианти за шаблони и изображения : шаблон на символ, който се открива в изображение с текст или шаблон на обект, 
//който се открива в изображение от GoogleMaps.

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
	Mat templ = imread("one.jpg");

	Mat img_gray, templ_gray;
	cvtColor(img, img_gray, COLOR_BGR2GRAY);
	cvtColor(templ, templ_gray, COLOR_BGR2GRAY);

	Mat result(img.rows - templ.rows + 1, img.cols - templ.cols + 1, CV_32FC1);
	matchTemplate(img_gray, templ_gray, result, TM_CCOEFF_NORMED);
	threshold(result, result, 0.8, 1., THRESH_TOZERO);
	int count = 0;
	while (true)
	{
		double minval, maxval, threshold = 0.8;
		Point minloc, maxloc;
		minMaxLoc(result, &minval, &maxval, &minloc, &maxloc);

		if (maxval >= threshold)
		{
			rectangle(img, maxloc, Point(maxloc.x + templ.cols, maxloc.y + templ.rows), CV_RGB(255, 0, 200), 2);
			count++;
			floodFill(result, maxloc, Scalar(0), 0, Scalar(.1), Scalar(1.));
		}
		else
			break;
	}
	cout << "Count of matches: " << count << endl;
	imshow("", img);
	waitKey(0);
	return 0;
}
