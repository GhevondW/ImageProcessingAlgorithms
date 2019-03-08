#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

namespace 
{
	const std::string input_path = "Files/HistogramMatching/input.png";
	const std::string target_path = "Files/HistogramMatching/target.png";

	const std::string output_path = "Files/HistogramMatching/Result.png";

	const int GRAY = 256;

	void make_gray(cv::Mat& img) {
		
		for (size_t i = 0; i < img.rows; i++)
		{
			int result = 0;
			for (size_t j = 0; j < img.cols; j++)
			{
				result = 0.21*img.at<cv::Vec3b>(i,j)[0] + 0.72*img.at<cv::Vec3b>(i, j)[1]
					+ 0.07*img.at<cv::Vec3b>(i, j)[2];

				img.at<cv::Vec3b>(i, j)[0] = result;
				img.at<cv::Vec3b>(i, j)[1] = result;
				img.at<cv::Vec3b>(i, j)[2] = result;
			}
		}

	}

	void matching(cv::Mat& input,cv::Mat& target) {
		
		std::vector<double> input_hist(GRAY);
		std::vector<double> target_hist(GRAY);


		for (size_t i = 0; i < input.rows; i++)
		{
			for (size_t j = 0; j < input.cols; j++)
			{
				input_hist[input.at<cv::Vec3b>(i, j)[0]]++;
			}
		}

		for (size_t i = 0; i < target.rows; i++)
		{
			for (size_t j = 0; j < target.cols; j++)
			{
				target_hist[target.at<cv::Vec3b>(i, j)[0]]++;
			}
		}

		int input_total = input.rows * input.cols;
		int target_total = target.rows * target.cols;

		for (int i = 1; i < GRAY; i++) {
			input_hist[i] = input_hist[i - 1] + input_hist[i];
			target_hist[i] = target_hist[i - 1] + target_hist[i];
		}

		for (int i = 0; i < GRAY; i++) {
			input_hist[i] = (input_hist[i] / input_total) * (GRAY - 1);
			input_hist[i] = (int)(input_hist[i] + (0.5));

			target_hist[i] = (target_hist[i] / target_total) * (GRAY - 1);
			target_hist[i] = (int)(target_hist[i] + (0.5));
		}

		for (size_t i = 0; i < GRAY; i++)
		{
			input_hist[i] = *std::lower_bound(target_hist.begin(),target_hist.end(),input_hist[i]);
		}

		for (size_t i = 0; i < input.rows; i++)
		{
			for (size_t j = 0; j < input.cols; j++)
			{
				input.at<cv::Vec3b>(i, j)[0] = input_hist[input.at<cv::Vec3b>(i, j)[0]];
				input.at<cv::Vec3b>(i, j)[1] = input_hist[input.at<cv::Vec3b>(i, j)[1]];
				input.at<cv::Vec3b>(i, j)[2] = input_hist[input.at<cv::Vec3b>(i, j)[2]];
			}
		}


	}

}

int main() {

	cv::Mat input = cv::imread(input_path);
	cv::Mat target = cv::imread(target_path);

	make_gray(input);
	matching(input,target);

	imwrite(output_path, input);
	cv::namedWindow("image", cv::WINDOW_NORMAL);
	cv::imshow("image", input);
	cv::waitKey(0);
	return 0;

}