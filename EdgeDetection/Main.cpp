#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

#define PI 3.14

namespace 
{

	const std::string input_path = "Files/EdgeDetection/input1.jpg";
	const std::string output_path = "Files/EdgeDetection/Result.jpg";

	void make_gray(cv::Mat& img) {

		for (size_t i = 0; i < img.rows; i++)
		{
			for (size_t j = 0; j < img.cols; j++)
			{
				int result = 0.299*img.at<cv::Vec3b>(i, j)[0] +
					0.587*img.at<cv::Vec3b>(i, j)[1] +
					0.114*img.at<cv::Vec3b>(i, j)[2];

				img.at<cv::Vec3b>(i, j)[0] = result;
				img.at<cv::Vec3b>(i, j)[1] = result;
				img.at<cv::Vec3b>(i, j)[2] = result;

			}
		}

	}

	void box_blur_filter(cv::Mat& img) {

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

				int box_result = 0;

				auto func = [&](int m, int n, int c) {
					box_result += img.at<cv::Vec3b>(m, n)[0] * c;
				};

				for (size_t k = i - 1; k <= i + 1; k++)
				{
					for (size_t l = j - 1; l <= j + 1; l++)
					{
						if (k == i && l == j) {
							func(k, l, 4);
						}
						else if ((k == i && l == j - 1) || (k == i && l == j + 1) ||
							(k == i + 1 && l == j) || (k == i - 1 && l == j)) {
							func(k, l, 2);
						}
						else {
							func(k, l, 1);
						}
					}
				}

				result_mat[i][j] = box_result / 16;
				

			}
		}

		for (size_t i = 0; i < size_x - 0; i++)
		{
			for (size_t j = 0; j < size_y - 0; j++)
			{
				img.at<cv::Vec3b>(i, j)[0] = result_mat[i][j];
				img.at<cv::Vec3b>(i, j)[1] = result_mat[i][j];
				img.at<cv::Vec3b>(i, j)[2] = result_mat[i][j];
			}
		}

	}

	void sobel_filter(cv::Mat& img) {


		int size_x = img.rows;
		int size_y = img.cols;

		int** result_image = new int*[size_x];
		for (size_t i = 0; i < size_x; i++)
		{
			result_image[i] = new int[size_y];
		}

		std::vector<std::vector<int>> angles(img.rows);
		for (size_t i = 0; i < angles.size(); i++)
		{
			angles[i].resize(img.cols);
		}

		for (size_t i = 1; i < img.rows - 1; i++)
		{
			for (size_t j = 1; j < img.cols - 1; j++)
			{
				auto left_top = img.at<cv::Vec3b>(i - 1, j - 1);
				auto left = img.at<cv::Vec3b>(i, j - 1);
				auto left_bottom = img.at<cv::Vec3b>(i + 1, j - 1);
				auto top = img.at<cv::Vec3b>(i - 1, j);

				auto right_top = img.at<cv::Vec3b>(i - 1, j + 1);
				auto right = img.at<cv::Vec3b>(i, j + 1);
				auto right_bottom = img.at<cv::Vec3b>(i + 1, j + 1);
				auto bottom = img.at<cv::Vec3b>(i + 1, j);

				int gx = (left_top[0] + 2*left[0] + left_bottom[0] +
					(-1)*right_top[0] + (-2) * right[0] + (-1)*right_bottom[0]);

				int gy = (left_top[0] + (2)*top[0] + right_top[0] +
					(-1)*left_bottom[0] + (-2) * bottom[0] + (-1)*right_bottom[0]);
			

				int g = std::sqrt(gx*gx + gy * gy);

				int theta = std::atan2(gy,gx) * 180 / PI;
				theta = theta % 180;

				angles[i][j] = theta;

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

		for (size_t i = 1; i < img.rows - 1; i++)
		{
			for (size_t j = 1; j < img.cols - 1; j++)
			{
				auto pixel_value = img.at<cv::Vec3b>(i,j)[0];

				auto check = [&](int k,int l,int m,int n) {
					auto p1_v = img.at<cv::Vec3b>(k,l)[0];
					auto p2_v = img.at<cv::Vec3b>(m,n)[0];
					if (!(pixel_value > p1_v && pixel_value > p2_v)) {
						result_image[i][j] = 0;
					}					
				};

				if (angles[i][j] <= 22.5 || angles[i][j] >= 157.5) { // 0 degree
					check(i,j+1,i,j-1);
				}
				else if (angles[i][j] <= 67.5) { // 45 degree
					check(i-1,j+1,i+1,j-1);
				}
				else if (angles[i][j] <= 112.5) { // 90 degree
					check(i-1,j,i+1,j);
				}
				else if (angles[i][j] <= 157.5) { // 130 degree
					check(i-1,j-1,i+1,j+1);
				}
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

	void double_threshold(cv::Mat& img) {
	
		std::vector<std::vector<int>> result_mat(img.rows);

		for (size_t i = 0; i < result_mat.size(); i++)
		{
			result_mat[i].resize(img.cols);
		}

		for (size_t i = 1; i < img.rows - 1; i++)
		{
			for (size_t j = 1; j < img.cols - 1; j++)
			{
				if (img.at<cv::Vec3b>(i,j)[0] > 110) {
					img.at<cv::Vec3b>(i, j)[0] = 255;
					img.at<cv::Vec3b>(i, j)[1] = 255;
					img.at<cv::Vec3b>(i, j)[2] = 255;
				}
				else if(img.at<cv::Vec3b>(i, j)[0] < 80) {
					img.at<cv::Vec3b>(i, j)[0] = 0;
					img.at<cv::Vec3b>(i, j)[1] = 0;
					img.at<cv::Vec3b>(i, j)[2] = 0;
				}
			}
		}

		/*for (size_t i = 1; i < img.rows-1; i++)
		{
			for (size_t j = 1; j < img.cols - 1; j++)
			{
				if (img.at<cv::Vec3b>(i, j)[0] > 0 && img.at<cv::Vec3b>(i, j)[0] < 255) {
					auto pixel_value = img.at<cv::Vec3b>(i, j)[0];
					bool f = false;
					for (size_t k = i-1; k <= i+1 ; k++)
					{
						for (size_t l = j-1; l <= j+1; l++)
						{
							if (img.at<cv::Vec3b>(k, l)[0] > 250) {
								result_mat[i][j] = 255;
								break;
							}
							
						}
					}
				}
				else {
					result_mat[i][j] = 255;
				}
			}
		}*/

	}

	void edge_detection(cv::Mat& img) {
		box_blur_filter(img);
		sobel_filter(img);
		double_threshold(img);
	}

}

int main() {
	cv::Mat img = cv::imread(input_path);

	make_gray(img);

	edge_detection(img);

	imwrite(output_path, img);
	cv::namedWindow("image", cv::WINDOW_NORMAL);
	cv::imshow("image", img);
	cv::waitKey(0);
	return 0;
}