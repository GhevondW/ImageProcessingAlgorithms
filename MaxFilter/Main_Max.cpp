#include <iostream>
#include <opencv2/opencv.hpp>
#include "Color.h"

namespace
{
	const std::string input_path1 = "Files/MaxFilter/i1.bmp";
	const std::string input_path3 = "Files/MaxFilter/i3.png";

	const std::string output_path1 = "Files/MaxFilter/Result1.bmp";
	const std::string output_path3 = "Files/MaxFilter/Result3.png";

	void max_filter(cv::Mat& img) {
		int size_x = img.rows;
		int size_y = img.cols;

		std::vector<std::vector<Color>> result_img(size_x);
		for (size_t i = 0; i < result_img.size(); i++)
		{
			result_img[i].resize(size_y);
		}

		for (size_t i = 1; i < size_x - 1; i++)
		{
			for (size_t j = 1; j < size_y - 1; j++)
			{
				std::vector<int> temp_red;
				std::vector<int> temp_green;
				std::vector<int> temp_blue;
				for (size_t k = i - 1; k <= i + 1; k++)
				{
					for (size_t l = j - 1; l <= j + 1; l++)
					{
						
						temp_red.push_back(img.at<cv::Vec3b>(k, l)[0]);
						temp_green.push_back(img.at<cv::Vec3b>(k, l)[1]);
						temp_blue.push_back(img.at<cv::Vec3b>(k, l)[2]);
					}
				}

				std::sort(temp_red.begin(), temp_red.end());
				std::sort(temp_green.begin(), temp_green.end());
				std::sort(temp_blue.begin(), temp_blue.end());

				int r = temp_red[temp_red.size()-1];
				int g = temp_green[temp_green.size()-1];
				int b = temp_blue[temp_blue.size()-1];

				Color c(r, g, b);

				result_img[i][j] = std::move(c);

			}
		}

		for (size_t i = 0; i < size_x; i++)
		{
			for (size_t j = 0; j < size_y; j++)
			{
				img.at<cv::Vec3b>(i, j)[0] = result_img[i][j].get_r();
				img.at<cv::Vec3b>(i, j)[1] = result_img[i][j].get_g();
				img.at<cv::Vec3b>(i, j)[2] = result_img[i][j].get_b();
			}
		}
	}

}

int main() {
	cv::Mat img1 = cv::imread(input_path1);
	cv::Mat img3 = cv::imread(input_path3);

	max_filter(img1);
	max_filter(img3);

	imwrite(output_path1, img1);
	imwrite(output_path3, img3);

	cv::namedWindow("image", cv::WINDOW_NORMAL);
	//cv::imshow("image", img1);
	cv::imshow("image", img3);
	cv::waitKey(0);
	return 0;
}