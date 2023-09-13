#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "color_seperator.hpp"
#include <iostream>


camera_painter::ColorSeperator::ColorSeperator() {
	hmin = 0, smin = 0, vmin = 0;
	hmax = 179, smax = 255, vmax = 255;
	cap = cv::VideoCapture(0);
}

std::vector<std::vector<int>> camera_painter::ColorSeperator::get_mask_hsv() {
	int colorCount = 0;
	std::vector<std::vector<int>> maskHSV;
	cv::namedWindow("Trackbars", (640, 200));
	cv::createTrackbar("Hue Min", "Trackbars", &hmin, 179);
	cv::createTrackbar("Hue Max", "Trackbars", &hmax, 179);
	cv::createTrackbar("Sat Min", "Trackbars", &smin, 255);
	cv::createTrackbar("Sat Max", "Trackbars", &smax, 255);
	cv::createTrackbar("Val Min", "Trackbars", &vmin, 255);
	cv::createTrackbar("Val Max", "Trackbars", &vmax, 255);

	while (true) {
		cap.read(img);

		cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);

		cv::Scalar lower(hmin, smin, vmin);
		cv::Scalar upper(hmax, smax, vmax);
		inRange(imgHSV, lower, upper, mask);

		imshow("Image", img);
		imshow("Image Mask", mask);

		int k = cv::waitKey(1) & 0xFF;

		if (k == 13) {



			std::vector<int> tempVec;
			maskHSV.push_back(tempVec);
			maskHSV[colorCount].push_back(hmin);
			maskHSV[colorCount].push_back(smin);
			maskHSV[colorCount].push_back(vmin);
			maskHSV[colorCount].push_back(hmax);
			maskHSV[colorCount].push_back(smax);
			maskHSV[colorCount].push_back(vmax);
			++colorCount;

			hmin = 0, smin = 0, vmin = 0;
			hmax = 179, smax = 255, vmax = 255;
			cv::destroyWindow("Trackbars");

			cv::namedWindow("Trackbars", (640, 200));
			cv::createTrackbar("Hue Min", "Trackbars", &hmin, 179);
			cv::createTrackbar("Hue Max", "Trackbars", &hmax, 179);
			cv::createTrackbar("Sat Min", "Trackbars", &smin, 255);
			cv::createTrackbar("Sat Max", "Trackbars", &smax, 255);
			cv::createTrackbar("Val Min", "Trackbars", &vmin, 255);
			cv::createTrackbar("Val Max", "Trackbars", &vmax, 255);
		}
		if (k == 27) {
			cv::destroyAllWindows();
			break;
		}
	}

	return maskHSV;
}
