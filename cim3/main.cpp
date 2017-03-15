#include <iostream>
#include "hist_eq.h"

using namespace std;

int main()
{
	string infile = "image\\1.bmp";
	hist_eq_rgb(infile).display("o");
	return 0;
}