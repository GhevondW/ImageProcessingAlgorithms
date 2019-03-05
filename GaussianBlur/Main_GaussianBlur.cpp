#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include "Color.h"

namespace {
	const std::string input_path = "Files/GaussianBlur/input2.jpg";
	const std::string output_path = "Files/GaussianBlur/Result2.jpg";

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
				
				auto func = [&](int m,int n,int c) {
					box_result_red += img.at<cv::Vec3b>(m, n)[0] * c;
					box_result_green += img.at<cv::Vec3b>(m, n)[1] * c;
					box_result_blue += img.at<cv::Vec3b>(m, n)[2] * c;
				};

				for (size_t k = i-1;  k <= i + 1;  k++)
				{
					for (size_t l = j - 1; l <= j + 1; l++)
					{
						if (k == i && l == j) {
							func(k,l,4);
						}
						else if ((k == i && l == j - 1) || (k == i && l == j  + 1) ||
							(k == i + 1 && l == j) || (k == i - 1 && l == j)) {
							func(k, l, 2);
						}
						else {
							func(k, l, 1);
						}
					}
				}

				result_mat[i][j].set_r(box_result_red/16);
				result_mat[i][j].set_g(box_result_green/16);
				result_mat[i][j].set_b(box_result_blue/16);

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