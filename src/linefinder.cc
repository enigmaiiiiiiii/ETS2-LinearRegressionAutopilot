#include "ets2_self_driving.h"
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
//#include <opencv2/imageproc/imageproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/photo/cuda.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/cudaimgproc.hpp>
//#include <opencv2/cudafilters.hpp>
//#include <opencv2/gpu/gpu.hpp>
#include <iostream>
#include <string>

#define PI 3.1415926

cv::Point prev_point;

using namespace cv;
using namespace std;

void LineFinder::setAccResolution(double dRho, double dTheta) {
	deltaRho = dRho;
	deltaTheta = dTheta;
}

void LineFinder::setMinVote(int minv) {
	minVote = minv;
}

void LineFinder::setLineLengthAndGap(double length, double gap) {
	minLength = length;
	maxGap = gap;
}


std::vector<cv::Vec4i> LineFinder::findLines(cv::Mat& binary) {
	UMat gpuBinary = binary.getUMat(ACCESS_RW);
	lines.clear();
	cv::HoughLinesP(gpuBinary, lines, deltaRho, deltaTheta, minVote, minLength, maxGap);
	return lines;
}
void LineFinder::drawDetectedLines(cv::Mat &image, cv::Scalar color) {

	UMat gpuImage = image.getUMat(ACCESS_RW);
	std::vector<cv::Vec4i>::const_iterator it2 = lines.begin();
	cv::Point endPoint;

	while (it2 != lines.end()) {
		cv::Point startPoint((*it2)[0], (*it2)[1]);
		endPoint = cv::Point((*it2)[2], (*it2)[3]);
		cv::line(gpuImage, startPoint, endPoint, color, 3);
		++it2;
	}
}
