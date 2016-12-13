#define _USE_MATH_DEFINES
#include<iostream>
#include<string>
#include<stdlib.h>
#include<stdio.h>
#include<vector>
#include<math.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#define infilename "edge_res/edgeconfigure(chazhi 20)_f_s5.png"

using namespace std;
using namespace cv;
int main() {
    string name[13] = {
		"easy_pic/d.jpg",
		"easy_pic/e.jpg",
		"easy_pic/f.jpg",
		"easy_pic/g.jpg",
		"easy_pic/h.png",
		"easy_pic/i.png",
		"easy_pic/j.png",
		"easy_pic/k.png",
		"easy_pic/l.png",
		"easy_pic/m.png",
		"easy_pic/n.png",
		"easy_pic/o.png",
		"easy_pic/p.png"
	};
	string sss[13] = { "d","e","f","g","h","i","j","k","l","m","n","o","p" };
	int control = 100;
	//cout << "please input control" << endl;
	//cin >> control;
	Mat image = imread(infilename, 0);
	Mat image_change = imread(infilename, 0);
	int r = image.rows;
	int c = image.cols*image.channels();
	vector<int> col(r, 0);
	vector<vector<int>> copy(c, col);
	for (int j = 0; j<r; j++) {
		uchar *data = image_change.ptr<uchar>(j);
		for (int i = 0; i<c; i++) {
			copy[i][j] = data[i];
		}
	}
	for (int j = 0; j<c; j++) {
		int sum = 0;
		for (int i = 0; i<r; i++) {
			if (copy[j][i] == 255) sum++;
		}
		if (sum < control) {
			for (int i = 0; i < r; i++) {
				copy[j][i] = 0;
			}
		}
	}
	for (int j = 0; j<r; j++) {
		uchar *data = image_change.ptr<uchar>(j);
		for (int i = 0; i<c; i++) {
			data[i]=copy[i][j];
		}
	}
	//construct filename.
	char s[30];
	_itoa_s(control, s, 10);
	String chazhi_str(s);
	String filename = "do_judge/vertical(control " + chazhi_str + ").png";
	imwrite(filename, image_change);
	return 1;
}



