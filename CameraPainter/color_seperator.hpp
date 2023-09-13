#ifndef COLOR_SEPERATOR_H
#define COLOR_SEPERATOR_H

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

namespace camera_painter
{
	class ColorSeperator
	{
	public:
		ColorSeperator();
		std::vector<std::vector<int>> get_mask_hsv();

	private:
		cv::Mat img, imgHSV, mask;
		cv::VideoCapture cap;
		int hmin, smin, vmin;
		int hmax, smax, vmax;
	};
}
#endif
