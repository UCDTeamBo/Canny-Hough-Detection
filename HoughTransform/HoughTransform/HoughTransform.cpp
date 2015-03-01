// HoughTransform.cpp : Main code for software implementation of Senior Design Project
//UC Davis: Class of 2015
//Students: Angela Tobin, Lindsey Raven, Christopher Bird
//Functionality: Read in an image from live feed camera, detect objects using Canny Edge Detection and Hough Transform, then steer to avoid
//Extra Libraries: None at the moment, but may use classes later for streamlining


#include <stdio.h>
#include <string>
#include <map>
#include <iostream>
#include "houghClass.h"

using namespace std;

string img_path = "C:/Users/Chris/Desktop/Canny-Hough-Detection/HoughTransform/HoughTransform/AngelaHeadshot.jpg";
int threshold = 0;
int cols = 1920;
int rows = 1080;
unsigned char* pixData;

void doTransform(string, int threshold);
//Usage was here

int main(int argc, char** argv) {
	
	//Code Here took care of basic input arguments

	//OPEN CV USE: Creates dialog windows to display images and allow for better UI

	doTransform(img_path, threshold);

	return 0;
}



void doTransform(string file_path, int threshold)
{
	//USES OpenCV to blur image, then perform basic Canny Edge on it


	//READ IN FILE
	int w = cols;
	int h = rows;

	//Transform
	Hough hough;
	hough.Transform(pixData, w, h);

	if (threshold == 0)
		threshold = w>h ? w / 4 : h / 4;

	while (1)
	{
		//Creating output
		//Search the accumulator
		vector<pair<pair<int, int>, pair<int, int>>> lines = hough.GetLines(threshold);

		//DONE IN OPEN CV, this displays final image with lines drawn on it based on accumulator
	}
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