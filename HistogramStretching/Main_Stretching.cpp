#include <iostream>
#include <opencv2/opencv.hpp>

void stretching(cv::Mat& img,int L,int H);

int main() {

	cv::Mat img = cv::imread("Files/HistogramStretching/Example.png");

	stretching(img,90,170);

	imwrite("Files/HistogramStretching/Result.png", img);
	cv::namedWindow("image", cv::WINDOW_NORMAL);
	cv::imshow("image", img);
	cv::waitKey(0);
	return 0;
}

void stretching(cv::Mat& img,int L,int H)
{
	for (size_t i = 0; i < img.rows; i++)
	{
		int x_old = 0;
		for (size_t j = 0; j < img.cols; j++)
		{
			auto pixel = img.at<cv::Vec3b>(i,j);
			x_old = (pixel[0] +
				pixel[1] +
				pixel[2]) / 3;
			
			int x_new = ((x_old - L) * 255)/ (H - L);

			if (x_new > 255) {
				x_new = 255;
			}

			img.at<cv::Vec3b>(i, j)[0] = (int)x_new;
			img.at<cv::Vec3b>(i, j)[1] = (int)x_new;
			img.at<cv::Vec3b>(i, j)[2] = (int)x_new;
		}
	}
}