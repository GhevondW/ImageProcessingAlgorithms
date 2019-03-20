#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

namespace 
{
	const std::string input_path = "Files/HoughTransform/input.png";
	const std::string output_path = "Files/HoughTransform/Result.png";

	struct AngleRadiusPair{
		double angle;
		double radius;
	};

	void binary(cv::Mat& img) {

		for (size_t i = 0; i < img.rows; i++)
		{
			for (size_t j = 0; j < img.cols; j++)
			{
				if (img.at<cv::Vec3b>(i,j)[0] > 50) {
					img.at<cv::Vec3b>(i, j)[0] = 255;
					img.at<cv::Vec3b>(i, j)[1] = 255;
					img.at<cv::Vec3b>(i, j)[2] = 255;
				}
				else {
					img.at<cv::Vec3b>(i, j)[0] = 0;
					img.at<cv::Vec3b>(i, j)[1] = 0;
					img.at<cv::Vec3b>(i, j)[2] = 0;
				}
			}
		}

	}

}

int main() {
	cv::Mat img = cv::imread(input_path);

	binary(img);

	//imwrite(output_path, img);
	cv::namedWindow("image", cv::WINDOW_NORMAL);
	cv::imshow("image", img);
	cv::waitKey(0);
	return 0;
}