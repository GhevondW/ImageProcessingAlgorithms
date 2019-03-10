#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <queue>
#include <math.h>

namespace 
{
	const std::string input_path = "Files/ScharrEdgeDetection/input.png";
	const std::string output_path = "Files/ScharrEdgeDetection/Result.png";

	void make_gray(cv::Mat& img) {
	
		for (size_t i = 0; i < img.rows; i++)
		{
			for (size_t j = 0; j < img.cols; j++)
			{
				int result = 0.21*img.at<cv::Vec3b>(i, j)[0] + 
					0.72*img.at<cv::Vec3b>(i, j)[1] + 
					0.07*img.at<cv::Vec3b>(i, j)[2];

				img.at<cv::Vec3b>(i, j)[0] = result;
				img.at<cv::Vec3b>(i, j)[1] = result;
				img.at<cv::Vec3b>(i, j)[2] = result;

			}
		}

	}

	void filter(cv::Mat& img) {
	

		int size_x = img.rows;
		int size_y = img.cols;

		int** result_image = new int*[size_x];
		for (size_t i = 0; i < size_x; i++)
		{
			result_image[i] = new int[size_y];
		}

		

		for (size_t i = 1; i < img.rows - 1; i++)
		{
			for (size_t j = 1; j < img.cols - 1; j++)
			{
				auto left_top = img.at<cv::Vec3b>(i - 1,j - 1)[0];
				auto left = img.at<cv::Vec3b>(i,j - 1)[0];
				auto left_bottom = img.at<cv::Vec3b>(i  + 1,j - 1)[0];
				auto top = img.at<cv::Vec3b>(i-1,j)[0];

				auto right_top = img.at<cv::Vec3b>(i - 1,j + 1)[0];
				auto right = img.at<cv::Vec3b>(i,j + 1)[0];
				auto right_bottom = img.at<cv::Vec3b>(i + 1,j + 1)[0];
				auto bottom = img.at<cv::Vec3b>(i + 1, j)[0];

				double gx = (left_top*3 + 10*left + 3*left_bottom -
					3*right_top - 10*right - 3*right_bottom)/16;

				double gy = (3 * left_top + 10 * top + 3 * right_top -
					3*left_bottom - 10*bottom  - 3*right_bottom)/16;

				double g = std::sqrt(gx*gx + gy * gy);


				
				result_image[i][j] = g;

			}
		}

		

		

		for (size_t i = 1; i < img.rows - 1; i++)
		{
			for (size_t j = 1; j < img.cols - 1; j++)
			{
				img.at<cv::Vec3b>(i, j)[0] = result_image[i][j];
				img.at<cv::Vec3b>(i, j)[1] = result_image[i][j];
				img.at<cv::Vec3b>(i, j)[2] = result_image[i][j];
			}
		}

	}

}

int main() {
	cv::Mat img = cv::imread(input_path);

	make_gray(img);
	filter(img);

	imwrite(output_path, img);
	cv::namedWindow("image", cv::WINDOW_NORMAL);
	cv::imshow("image", img);
	cv::waitKey(0);
	return 0;
}