#pragma once
#include <iostream>
#include "CImg.h"
#include <string>

using namespace std;
using namespace cimg_library;

CImg<float> hist_tr(string filea, string fileb)
{
	CImg<float> src(filea.c_str());
	CImg<float> dst(fileb.c_str());


}