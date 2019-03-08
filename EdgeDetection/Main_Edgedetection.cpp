#include <iostream>
#include <opencv2/opencv.hpp>
#include "Color.h"

namespace
{
	const std::string input_path = "Files/EdgeDetection/i2.jpg";
	const std::string output_path = "Files/EdgeDetection/Result2.jpg";

	void gray(cv::Mat& img) {
	
		for (size_t i = 0; i < img.rows; i++)
		{
			int avg = 0;
			for (size_t j = 0; j < img.cols; j++)
			{
				//0.21 R + 0.72 G + 0.07 B
				avg = (0.21 * img.at<cv::Vec3b>(i,j)[0]+
					0.72 * img.at<cv::Vec3b>(i, j)[1]+
					0.07 * img.at<cv::Vec3b>(i, j)[2]);

				img.at<cv::Vec3b>(i, j)[0] = avg;
				img.at<cv::Vec3b>(i, j)[1] = avg;
				img.at<cv::Vec3b>(i, j)[2] = avg;
			}
		}

	}

	void edge_detection(cv::Mat& img) {
	
		int size_x = img.rows;
		int size_y = img.cols;

		std::vector<std::vector<int>> result_mat(size_x);
		for (size_t i = 0; i < result_mat.size(); i++)
		{
			result_mat[i].resize(size_y);
		}


		for (size_t i = 1; i < size_x - 1; i++)
		{
			for (size_t j = 1; j < size_y - 1; j++)
			{

				int red = 0;

				for (size_t k = i-1; k <= i+1; k++)
				{
					for (size_t l = j-1; l <= j+1; l++)
					{
						auto pixel = img.at<cv::Vec3b>(k,l);
						if (l == j && k == i) {
							red += 8 * pixel[0];
						}
						else if(l == j + 1){
							red += -1 * pixel[0];
						}						
					}
				}
				
				

				if (red > 200) {
					red = 255;
				}

				result_mat[i][j] = red;

			}
		}

		for (size_t i = 0; i < size_x; i++)
		{
			for (size_t j = 0; j < size_y; j++)
			{
				img.at<cv::Vec3b>(i, j)[0] = result_mat[i][j];
				img.at<cv::Vec3b>(i, j)[1] = result_mat[i][j];
				img.at<cv::Vec3b>(i, j)[2] = result_mat[i][j];
			}
		}

	}

}

int main() {

	cv::Mat img = cv::imread(input_path);

	gray(img);

	edge_detection(img);

	imwrite(output_path, img);
	cv::namedWindow("image", cv::WINDOW_NORMAL);
	cv::imshow("image", img);
	cv::waitKey(0);
	return 0;

}