#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include "color_seperator.hpp"
#include "camera_painter.hpp"

/// <summary>
/// Camera Painter 
/// </summary>




namespace camera_painter {

	cv::Mat img;
	std::vector<std::vector<int>> newPoints;
	std::vector<cv::Scalar> myColorValues{ {255, 0, 255}, {0, 255, 0} };

	void DrawOnCanvas(std::vector<std::vector<int>> newPoints, std::vector<cv::Scalar> myColorValues) {
		for (int i = 0; i < newPoints.size(); ++i) {

			circle(img, cv::Point(newPoints[i][0], newPoints[i][1]), 10, myColorValues[newPoints[i][2]], cv::FILLED);
		}
	}
	cv::Point GetContours(cv::Mat imgDil) {

		std::vector<std::vector<cv::Point>> contours;
		std::vector<cv::Vec4i> hierarchy;

		findContours(imgDil, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

		cv::Point myPoint(0, 0);

		for (int i = 0; i < contours.size(); ++i) {

			int area = contourArea(contours[i]);
			//cout << area << endl;

			std::vector<std::vector<cv::Point>> conPoly(contours.size());
			std::vector<cv::Rect> boundRect(contours.size());
			std::string objectType;

			if (area > 1000) {
				float peri = arcLength(contours[i], true);
				approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);


				boundRect[i] = boundingRect(conPoly[i]);
				myPoint.x = boundRect[i].x + boundRect[i].width / 2;
				myPoint.y = boundRect[i].y;


				drawContours(img, conPoly, i, cv::Scalar(255, 0, 255), 2);
				rectangle(img, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(0, 255, 0), 5);

			}
		}
		return myPoint;
	}
	std::vector<std::vector<int>> GetMasks() {
		ColorSeperator cp = ColorSeperator();

		std::vector<std::vector<int>> maskHSV = cp.get_mask_hsv();
		return maskHSV;
	}
	void ShowMasks(std::vector<std::vector<int>> maskHSVs) {

		cv::VideoCapture cap(0);

		while (true) {
			cap.read(img);
			cv::Mat imgHSV;

			cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);


			for (int i = 0; i < maskHSVs.size(); ++i)
			{

				cv::Scalar lower(maskHSVs[i][0], maskHSVs[i][1], maskHSVs[i][2]);
				cv::Scalar upper(maskHSVs[i][3], maskHSVs[i][4], maskHSVs[i][5]);
				cv::Mat mask;
				inRange(imgHSV, lower, upper, mask);
				GetContours(mask);
				//imshow(to_string(i), mask);
				cv::Point myPoint = GetContours(mask);
				if (myPoint.x != 0) {
					newPoints.push_back({ myPoint.x, myPoint.y, i });

				}
				std::cout << myPoint.x << std::endl;
			}

			DrawOnCanvas(newPoints, myColorValues);
			imshow("Image", img);

			int k = cv::waitKey(1) & 0xFF;

			if (k == 27) {
				cv::destroyAllWindows();
				break;
			}
		}


	}

}


