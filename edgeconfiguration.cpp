#define _USE_MATH_DEFINES
#include<iostream>
#include<string>
#include<stdlib.h>
#include<stdio.h>
#include<vector>
#include<math.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#define square_size 3
#define sigma 1


using namespace cv;
int do_gaussfilter(int row, int col, Mat image, std::vector<std::vector<double> > gauss, double sum);
int do_edgeconfigure(int row, int col, Mat image, int chazhi);
int main() {
	int chazhi = 0;
	double sum = 0.0;
	std::cout << "Please input the \"chazhi\" you want:" << std::endl;
	std::cin >> chazhi;
	std::vector<double> line(square_size, 0.0);
	std::vector<std::vector<double> > gauss(square_size, line);
	for (int i = 0; i<square_size; i++) {
		for (int j = 0; j<square_size; j++) {
			double v = (1 / (2 * sigma*sigma*M_PI))*exp(-((i - square_size / 2)*(i - square_size / 2) + (j - square_size / 2)*(j - square_size / 2)) / (2 * sigma*sigma));
			gauss[i][j] = v;
			sum += gauss[i][j];
		}
	}
	Mat image = imread("lajiao.jpg", 0);
	Mat image_change = imread("lajiao.jpg", 0);
	int r = image.rows;
	int c = image.cols*image.channels();
	for (int j = square_size / 2; j<r - square_size / 2; j++) {
		uchar *data = image_change.ptr<uchar>(j);
		for (int i = square_size / 2; i<c - square_size / 2; i++) {
			data[i] = do_gaussfilter(j, i,  image, gauss, sum);
		}
	}
	Mat image_edge = image_change.clone();
	for (int j = square_size / 2; j<r; j++) {
		uchar *data = image_edge.ptr<uchar>(j);
		for (int i = square_size / 2; i<c; i++) {
			data[i] = do_edgeconfigure(j, i, image_change, chazhi);
		}
	}
	//construct filename.
	char s[30];
	_itoa_s(chazhi, s, 10);
	String chazhi_str(s);
	String filename = "edgeconfigure(chazhi " + chazhi_str + ").png";
	imwrite(filename, image_edge);
	return 1;
}


int do_gaussfilter(int row, int col, Mat image, std::vector<std::vector<double> > gauss, double sum) {
	double value = 0;
	for (int j = row - square_size / 2; j<row + square_size / 2 + 1; j++) {
		uchar *data = image.ptr<uchar>(j);
		for (int i = col - square_size / 2; i<col + square_size / 2 + 1; i++) {
			value += (double)data[i] * gauss[j - row + square_size / 2][i - col + square_size / 2] / sum;
		}
	}
	return (int)value;
}

int do_edgeconfigure(int row, int col, Mat image, int chazhi) {
	uchar *lineup = image.ptr<uchar>(row - 1);
	uchar *linenow = image.ptr<uchar>(row);
	if (hypot(linenow[col] - linenow[col - 1], linenow[col] - lineup[col])>chazhi)
		return 255;
	else
		return 0;
}
