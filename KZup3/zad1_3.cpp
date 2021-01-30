#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>
using namespace cv;


int main(int argc, char* argv[])
{
	// Read image
	Mat im = imread("blob.jpg", IMREAD_GRAYSCALE);

	// Set up the detector with default parameters.
	SimpleBlobDetector detector;

	// Detect blobs.
	std::vector<KeyPoint> keypoints;
	detector.detect(im, keypoints);

	// Draw detected blobs as red circles.
	// DrawMatchesFlags::DRAW_RICH_KEYPOINTS flag ensures the size of the circle corresponds to the size of blob
	Mat im_with_keypoints;
	drawKeypoints(im, keypoints, im_with_keypoints, Scalar(0, 0, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	// Show blobs
	imshow("keypoints", im_with_keypoints);
	waitKey(0);
}