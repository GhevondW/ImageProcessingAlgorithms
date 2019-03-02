#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

namespace
{
	std::string input_path = "Files/HistogramEqualization/Example.png";
	std::string output_path = "Files/HistogramEqualization/Result.png";

	void equalize(cv::Mat& img) {
		//todo
	}

}

int main() {
	cv::Mat img = cv::imread(input_path);

	equalize(img);

	imwrite(output_path, img);
	cv::namedWindow("image", cv::WINDOW_NORMAL);
	cv::imshow("image", img);
	cv::waitKey(0);
	return 0;
}

