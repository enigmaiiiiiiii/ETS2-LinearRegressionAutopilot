#ifndef __ets_self_driving_h__
#define __ets_self_driving_h__

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
//#include <Windows.h>
#include <iostream>
#include <string>
#include <chrono>

#define PI 3.1415926


using namespace cv;
using namespace std;

class LineFinder{

private:
	cv::Mat image;
	std::vector<cv::Vec4i> lines; 
	double deltaRho;
	double deltaTheta; 
	int minVote; 
	double minLength; 
	double maxGap; 

public:
	LineFinder() : deltaRho(1), deltaTheta(PI / 180), minVote(50), minLength(50), maxGap(10) {}
	void setAccResolution(double dRho, double dTheta);
	void setMinVote(int minv);
	void setLineLengthAndGap(double length, double gap);
	std::vector<cv::Vec4i> findLines(cv::Mat& binary);
	void drawDetectedLines(cv::Mat &image, cv::Scalar color = cv::Scalar(112, 112, 0));
};

void cudaf();

#endif
