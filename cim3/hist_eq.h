#pragma once
#include "CImg.h"
#include <vector>
#include <iostream>
#include <string>

using namespace cimg_library;
using namespace std;

CImg<float> rgb2gray(CImg<float> src, int width, int height)
{
	CImg<float> dst(width, height, 1, 1, 0);
	cimg_forXY(src, x, y)
	{
		dst(x, y) = float(src(x, y, 0)*0.299 + src(x, y, 1)*0.587 + src(x, y, 2)*0.114);
	}
	return dst;
}

CImg<float> hist_eq_gray(string infile)
{
	CImg<float> img(infile.c_str());
	const int width = img._width, height = img._height;
	img = rgb2gray(img, width, height);
	//img.display("img");

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
		img(x, y) = cumu_hist[int(img(x, y))] * 255;
	}

	return img;
}

CImg<float> hist_eq_rgb(string infile)
{
	CImg<float> rgb(infile.c_str());
	const int width = rgb._width, height = rgb._height;
	for (int i = 0; i < 3; i++)
	{
		CImg<float> img=rgb.get_shared_channel(i);
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
			img(x, y) = cumu_hist[int(img(x, y))] * 255;
		}
	}

	return rgb;
}
