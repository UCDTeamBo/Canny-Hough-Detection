// HoughTransform.cpp : Main code for software implementation of Senior Design Project
//UC Davis: Class of 2015
//Students: Angela Tobin, Lindsey Raven, Christopher Bird
//Functionality: Read in an image from live feed camera, detect objects using Canny Edge Detection and Hough Transform, then steer to avoid
//Extra Libraries: None at the moment, but may use classes later for streamlining


#include "stdafx.h"				//Precompiled Header for Faster Compilation
#include "stdio.h"
#include <iostream>
#include <math.h>

using namespace std;


int main(int argc, _TCHAR* argv[])
{
	//Read Image

	//Canny Edge Detection

	//Hough Transform

	//Output

	//Extra Notes:
	return 0;
}

/*Ideas and step by step

1: Read in image from source
	a: webcam will be used in final implementation to contuniously capture images
	b: Read image from file for now, replace with webcam later
2: Apply Canny Edge Detection on it to get BW image with white edges
	a: Create greyscale version of input image
	b: Smooth out the lines
	c: Apply gradient along X and Y directions
	d: Suppress noise/width of line
	e: Edge threshholding
3: Apply Hough Transform on this image to determine which ones are most likely lines
	a: Go through image, pixel by pixel, if white go to next step
		1: Determine r for every Theta at that pixel
		2: Increment correct bin for this line (will update 180 bins)
	b: Go through each bin of accumulator
		1: If above certain threshhold determine if local maxima
		2: If above is met, save line for later
4: Draw these lines either on image or on new image
	a: Drawing on new image allows to map directly to coordinate system <- This is probably better
	b: Drawing on old image is good for showing correct output to user
5: Determine where is safe to fly (Requires Sensor)
	a: Use radar to determine distance from objects/walls found
	b: Fly where is available
6: Repeat for every image in stream

XXX: At end of it all, possibly create 3D image
*/