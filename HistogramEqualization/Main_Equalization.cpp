#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>


const std::string input_path = "Files/HistogramEqualization/Example.png";
const std::string output_path = "Files/HistogramEqualization/Result.png";

const int GrayLevel = 256;

void equalize(cv::Mat& img) {

	double hist[GrayLevel];

	for (size_t i = 0; i < GrayLevel; i++)
	{
		hist[i] = 0;
	}

	for (int i = 0; i < img.rows; i++)
		for (int j = 0; j < img.cols; j++)
			hist[img.at<cv::Vec3b>(i, j)[0]]++;

	int total = img.rows * img.cols;

	for (int i = 1; i < GrayLevel; i++)
		hist[i] = hist[i - 1] + hist[i];

	for (int i = 0; i < GrayLevel; i++) {
		hist[i] = (hist[i] / total) * (GrayLevel - 1);
		hist[i] = (int)(hist[i] + (0.5));
	}

	for (size_t i = 0; i < img.rows; i++)
	{
		for (size_t j = 0; j < img.cols; j++)
		{
			img.at<cv::Vec3b>(i, j)[0] = hist[img.at<cv::Vec3b>(i, j)[0]];
			img.at<cv::Vec3b>(i, j)[1] = hist[img.at<cv::Vec3b>(i, j)[1]];
			img.at<cv::Vec3b>(i, j)[2] = hist[img.at<cv::Vec3b>(i, j)[2]];
		}
	}

}

int main() {
	cv::Mat img = cv::imread(input_path);

	for (size_t i = 0; i < img.rows; i++)
	{
		for (size_t j = 0; j < img.cols; j++)
		{
			int avg = (img.at<cv::Vec3b>()[0] +
				img.at<cv::Vec3b>()[1] +
				img.at<cv::Vec3b>()[2]) / 3;

			img.at<cv::Vec3b>()[0] = avg;
			img.at<cv::Vec3b>()[1] = avg;
			img.at<cv::Vec3b>()[2] = avg;
		}
	}

	equalize(img);

	imwrite(output_path, img);
	cv::namedWindow("image", cv::WINDOW_NORMAL);
	cv::imshow("image", img);
	cv::waitKey(0);
	return 0;
}

