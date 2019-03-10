#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <queue>
#include <math.h>

namespace 
{
	const std::string input_path = "Files/SobelFilter/input.png";
	const std::string output_path = "Files/SobelFilter/Result.png";

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
				auto left_top = img.at<cv::Vec3b>(i - 1,j - 1);
				auto left = img.at<cv::Vec3b>(i,j - 1);
				auto left_bottom = img.at<cv::Vec3b>(i  + 1,j - 1);
				auto top = img.at<cv::Vec3b>(i-1,j);

				auto right_top = img.at<cv::Vec3b>(i - 1,j + 1);
				auto right = img.at<cv::Vec3b>(i,j + 1);
				auto right_bottom = img.at<cv::Vec3b>(i + 1,j + 1);
				auto bottom = img.at<cv::Vec3b>(i + 1, j);

				int gx = (-1)*left_top[0] + (-2)*left[0] + (-1)*left_bottom[0] +
					right_top[0] + (2) * right[0] + right_bottom[0];

				int gy = left_top[0] + (2)*top[0] + right_top[0] +
					(-1)*left_bottom[0] + (-2) * bottom[0] + (-1)*right_bottom[0];

				int g = std::sqrt(gx*gx + gy*gy);
				
				/*if (g < 150) {
					g = 255;
				}
				else {
					g = 0;
				}*/

				if (g > 200) {
					g = 255;
				}

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

	//imwrite(output_path, img);
	cv::namedWindow("image", cv::WINDOW_NORMAL);
	cv::imshow("image", img);
	cv::waitKey(0);
	return 0;
}