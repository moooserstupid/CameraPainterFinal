#ifndef CAMERA_PAINTER_H
#define CAMERA_PAINTER_H
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

namespace camera_painter {

	void DrawOnCanvas(std::vector<std::vector<int>>, std::vector<cv::Scalar>);
	cv::Point GetContours(cv::Mat);

	std::vector<std::vector<int>> GetMasks();
	void ShowMasks(std::vector<std::vector<int>>);
}
#endif