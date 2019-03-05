#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include "Color.h"

namespace {
	const std::string input_path = "Files/BoxBlur/input.png";
	const std::string output_path = "Files/BoxBlur/Result.png";

	void box_blur_filter(cv::Mat& img) {
		
		int size_x = img.rows;
		int size_y = img.cols;

		std::vector<std::vector<Color>> result_mat(size_x);
		for (size_t i = 0; i < result_mat.size(); i++)
		{
			result_mat[i].resize(size_y);
		}

		for (size_t i = 1; i < size_x - 1; i++)
		{
			for (size_t j = 1; j < size_y - 1; j++)
			{

				int box_result_red = 0;
				int box_result_green = 0;
				int box_result_blue = 0;
				
				for (size_t k = i-1;  k <= i + 1;  k++)
				{
					for (size_t l = j - 1; l <= j + 1; l++)
					{
						box_result_red += img.at<cv::Vec3b>(k,l)[0];
						box_result_green += img.at<cv::Vec3b>(k,l)[1];
						box_result_blue += img.at<cv::Vec3b>(k,l)[2];
					}
				}

				result_mat[i][j].set_r(box_result_red/9);
				result_mat[i][j].set_g(box_result_green/9);
				result_mat[i][j].set_b(box_result_blue/9);

			}
		}

		for (size_t i = 0; i < size_x - 0; i++)
		{
			for (size_t j = 0; j < size_y - 0; j++)
			{
				img.at<cv::Vec3b>(i, j)[0] = result_mat[i][j].get_r();
				img.at<cv::Vec3b>(i, j)[1] = result_mat[i][j].get_g();
				img.at<cv::Vec3b>(i, j)[2] = result_mat[i][j].get_b();
			}
		}

	}

}



int main() {

	cv::Mat img = cv::imread(input_path);

	box_blur_filter(img);

	imwrite(output_path, img);
	cv::namedWindow("image", cv::WINDOW_NORMAL);
	cv::imshow("image", img);
	cv::waitKey(0);
	return 0;

}