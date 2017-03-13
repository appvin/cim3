#pragma once
#include "CImg.h"

using namespace cimg_library;

CImg<float> rgb2gray(CImg<float> src,int width,int height)
{
	CImg<float> dst(width, height, 1, 1, 0);
	cimg_forXY(src, x, y)
	{
		dst(x, y) = float(src(x, y, 0)*0.299 + src(x, y, 1)*0.587 + src(x, y, 2)*0.114);
	}
	return dst;
}