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
#include "canny.h"

using namespace std;

char * img_path = "C:/Users/Chris/Desktop/Canny-Hough-Detection/HoughTransform/HoughTransform/image.bmp"; //this will be replaced by output of Canny code
int threshold = 0;
int cols = 1920;
int rows = 1080;
unsigned char* pixData;

void doTransform(char *, int threshold);

unsigned char* readBMP(char* filename)
{
	int i;
	FILE* f = fopen(filename, "rb");
	unsigned char info[54];
	fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

	// extract image height and width from header
	int width = *(int*)&info[18];
	int height = *(int*)&info[22];

	int size = 3 * width * height;
	unsigned char* data = new unsigned char[size]; // allocate 3 bytes per pixel
	fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
	fclose(f);

	for (i = 0; i < size; i += 3)
	{
		unsigned char tmp = data[i];
		data[i] = data[i + 2];
		data[i + 2] = tmp;
	}

	return data;
}

int main(const int argc, const char ** const argv)
{
    /*if (argc < 2) {
        printf("Usage: %s image.bmp\n", argv[0]);
        return 1;
    }*/
 
    canny CANNY;
    static bitmap_info_header_t ih;
    const pixel_t *in_bitmap_data = CANNY.load_bmp(img_path, &ih);
    if (in_bitmap_data == NULL) {
        fprintf(stderr, "main: BMP image not loaded.\n");
        return 1;
    }
 
    printf("Info: %d x %d x %d\n", ih.width, ih.height, ih.bitspp);
 
    const pixel_t *out_bitmap_data = CANNY.canny_edge_detection(in_bitmap_data, &ih, 45, 50, 3.0f);
    /*if (out_bitmap_data == NULL) {
        fprintf(stderr, "main: failed canny_edge_detection.\n");
        return 1;
    }*/
 
    if (CANNY.save_bmp("out.bmp", &ih, out_bitmap_data)) {
        fprintf(stderr, "main: BMP image not saved.\n");
        return 1;
    }

	//Canny code goes here, read/stored into img_path
	//Code Here took care of basic input arguments

	//OPEN CV USE: Creates dialog windows to display images and allow for better UI

	doTransform("C:/Users/Chris/Desktop/Canny-Hough-Detection/HoughTransform/HoughTransform/out.bmp", threshold);

	free((pixel_t*)in_bitmap_data);
	free((pixel_t*)out_bitmap_data);

	return 0;
}



void doTransform(char* file_path, int threshold)
{

	//READ IN FILE
	int w = cols;
	int h = rows;

	//Transform
	Hough hough;
	hough.Transform(readBMP(file_path), w, h);

	if (threshold == 0)
		threshold = w>h ? w / 4 : h / 4;

	while (1)
	{
		//Creating output
		//Search the accumulator
		vector<pair<pair<int, int>, pair<int, int>>> lines = hough.GetLines(threshold);
		cout << "I love you so much" << endl;
		
		char input;
		cin >> input;

		if (input == 'c')
			return;
		//use accumulator to determine which lines are important based on threshold
		//draw these lines on original image to show that it worked
		//display the image (maybe just write file and open it manually)

		//DONE IN OPEN CV, this displays final image with lines drawn on it based on accumulator
	}
}


/*Ideas and step by step

1: Read in image from source
	a: webcam will be used in final implementation to continuously capture images
	b: Read image from file for now, replace with webcam later
2: Apply Canny Edge Detection on it to get BW image with white edges
	a: Create greyscale version of input image
	b: Smooth out the lines
	c: Apply gradient along X and Y directions
	d: Suppress noise/width of line
	e: Edge thresholding
3: Apply Hough Transform on this image to determine which ones are most likely lines
	a: Go through image, pixel by pixel, if white go to next step
		1: Determine r for every Theta at that pixel
		2: Increment correct bin for this line (will update 180 bins)
	b: Go through each bin of accumulator
		1: If above certain threshold determine if local maxima
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