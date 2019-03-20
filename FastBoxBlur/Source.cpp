#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>


std::string input_path = "input.jpg";
std::string output_path = "output.jpg";

void make_gray(cv::Mat& img) {

	for (size_t i = 0; i < img.rows; i++)
	{
		for (size_t j = 0; j < img.cols; j++)
		{
			auto pixel = img.at<cv::Vec3b>(i,j);
			int result = 0.299*pixel[0] + 0.57*pixel[1] + 0.131*pixel[2];
			img.at<cv::Vec3b>(i,j)[0] = result;
			img.at<cv::Vec3b>(i,j)[1] = result;
			img.at<cv::Vec3b>(i,j)[2] = result;
		}
	}

}

void h_motion_blur(cv::Mat& img,int radius) {

	radius = radius * 2 + 1;

	for (size_t i = 0; i < img.rows; i++)
	{
		int sum = 0;
		int result_avg = 0;

		for (size_t x = 0;  x < radius;  x++)
		{
			auto pixel = img.at<cv::Vec3b>(i,x);
			sum += pixel[0];
		}

		result_avg = sum / radius;

		for (int j = 0; j < img.cols; j++)
		{
			if (j - radius / 2 >= 0 && j + 1 + radius / 2 < img.cols) {
				auto temp_old_pixel = img.at<cv::Vec3b>(i,j - radius/2);
				sum -= temp_old_pixel[0];
				auto temp_new_pixel = img.at<cv::Vec3b>(i,j+1+radius/2);
				sum += temp_new_pixel[0];

				result_avg = sum  / radius;

			}
			img.at<cv::Vec3b>(i, j)[0] = result_avg;
			img.at<cv::Vec3b>(i, j)[1] = result_avg;
			img.at<cv::Vec3b>(i, j)[2] = result_avg;
		}

	}


}

void v_motion_blur(cv::Mat img,int radius) {
	radius = radius * 2 + 1;

	for (size_t j = 0; j < img.cols; j++)
	{
		int sum = 0;
		int result_avg = 0;

		for (size_t x = 0; x < radius; x++)
		{
			auto pixel = img.at<cv::Vec3b>(x, j);
			sum += pixel[0];
		}

		result_avg = sum / radius;

		for (int i = 0; i < img.rows; i++)
		{
			if (i - radius / 2 >= 0 && i + 1 + radius / 2 < img.rows) {
				auto temp_old_pixel = img.at<cv::Vec3b>(i - radius / 2, j);
				sum -= temp_old_pixel[0];
				auto temp_new_pixel = img.at<cv::Vec3b>(i + 1 + radius / 2, j);
				sum += temp_new_pixel[0];

				result_avg = sum / radius;

			}
			img.at<cv::Vec3b>(i, j)[0] = result_avg;
			img.at<cv::Vec3b>(i, j)[1] = result_avg;
			img.at<cv::Vec3b>(i, j)[2] = result_avg;
		}

	}

}

int main()
{
	cv::Mat img = cv::imread(input_path);

	int r = 5;

	make_gray(img);

	h_motion_blur(img,r);
	v_motion_blur(img,r);

	imwrite(output_path, img);
	cv::namedWindow("image", cv::WINDOW_NORMAL);
	cv::imshow("image", img);
	cv::waitKey(0);
	return 0;
}


