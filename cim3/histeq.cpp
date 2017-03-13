#include "CImg.h"
#include "rgb2gray.h"
#include <vector>
#include <iostream>
#include <string>

using namespace cimg_library;
using namespace std;

int main()
{
	CImg<float> img("image\\1.bmp");
	const int width = img._width, height = img._height;
	img = rgb2gray(img, width, height);
	img.display("img");

	vector<float> num_hist;
	num_hist.resize(256);
	cimg_forXY(img, x, y)
	{
		num_hist[int(img(x, y))]++;
	}

	vector<float> prob_hist;
	prob_hist.resize(256);
	for (int i = 0; i < 256; i++)
	{
		prob_hist[i] = num_hist[i] / (width*height);
	}

	vector<float> cumu_hist;
	cumu_hist.resize(256);
	cumu_hist[0] = prob_hist[0];
	for (int i = 1; i < 256; i++)
	{
		cumu_hist[i] = cumu_hist[i - 1] + prob_hist[i];
	}

	cimg_forXY(img, x, y)
	{
		img(x, y) = cumu_hist[int(img(x, y))];
	}

	img.display("result");

	return 0;
}