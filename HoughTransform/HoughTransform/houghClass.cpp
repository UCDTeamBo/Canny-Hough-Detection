#include "houghClass.h"
#include <cmath>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>

#define DEG2RAD 0.017453293f
#define RAD2DEG 57.2957795f
#define PI 3.14159265359f

Hough::Hough():_accu(0), _accu_w(0), _accu_h(0), _img_w(0), _img_h(0)
{
	//Constructor
}

Hough::~Hough() {
	//Destructor
	if(_accu)
		free(_accu);
}

int Hough::Transform(unsigned char* img_data, int w, int h)
{
	//Performs transform on image data matrix which is input from openCV (Need to correctly input from file with this format)
	_img_w = w;
	_img_h = h;

	//Create the accu
	double hough_h = ((sqrt(2.0) * (double)(h>w?h:w)) / 2.0);
	_accu_h = hough_h * 2.0; // -r -> +r
	_accu_w = 180;

	_accu = (unsigned int*)calloc(_accu_h * _accu_w, sizeof(unsigned int));

	double center_x = w/2;
	double center_y = h/2;

	ofstream outFile("Copy_Image.csv");
	for(int y=0;y<h;y++)
	{
		for(int x=0;x<w;x++)
		{
			if( img_data[(y * w) + x] > 250 )
			{
				//cout << "White Pixel At: " << x << " " << y << endl;
				outFile << x << "," << y << "\n";
				for(int t=0; t < 180; t++)
				{
					double r = ( ((double)x - center_x) * cos((double)t * DEG2RAD)) + (((double)y - center_y) * sin((double)t * DEG2RAD));
					_accu[ (int)((round(r + hough_h) * 180.0)) + t]++;
				}
			}
		}
	}
	outFile.close();

	return 0;
}

vector< pair< pair<int, int>, pair<int, int> > > Hough::GetLines(int threshold)
{
	vector< pair< pair<int, int>, pair<int, int> > > lines;

	if(_accu == 0)
		return lines;

	for(int r=0;r<_accu_h;r++)
	{
		for(int t=0;t<_accu_w;t++)
		{
			if((int)_accu[(r*_accu_w) + t] >= threshold)
			{
				//Is this point a local maxima (9x9)
				int max = _accu[(r*_accu_w) + t];
				for(int ly=-4;ly<=4;ly++)
				{
					for(int lx=-4;lx<=4;lx++)
					{
						if( (ly+r>=0 && ly+r<_accu_h) && (lx+t>=0 && lx+t<_accu_w)  )
						{
							if( (int)_accu[( (r+ly)*_accu_w) + (t+lx)] > max )
							{
								max = _accu[( (r+ly)*_accu_w) + (t+lx)];
								ly = lx = 5;
							}
						}
					}
				}
				if(max > (int)_accu[(r*_accu_w) + t])
					continue;


				int x1, y1, x2, y2;
				x1 = y1 = x2 = y2 = 0;
				
				int angle_to_top_right = RAD2DEG * atan(((_img_h/2) / (_img_w/2)) * DEG2RAD);
				int angle_to_top_left = 180 - angle_to_top_right;
				



				//cout << angle_to_top_right << "to" << angle_to_top_left << endl;
				if(t <= 45 || t >= 135)
				//if(t<=angle_to_top_right || t>=angle_to_top_left)
					//these angles for lines that hit the top and bottom
					//HEY SHOULDN'T IT BE <45 AND >35 IF WE'RE SETTING X? X corresponds to width, yes?
					//these angles may need to change since these angles only apply to a square
					// I think atan((h/2) / (w/2))
				{ 

					//we are currently under the impression that the original code first moves the origin 
						//and then computes y from x (if) or x from y (else)
				
				
					//y = (r - x cos(t)) / sin(t)
					x1 = 0;	//First revision(-_img_w/2)
					//y1 = ((double)(r-(_accu_h/2)) - ((x1 - (_img_w/2) ) * cos(t * DEG2RAD))) / sin(t * DEG2RAD) + (_img_h / 2);	//WE THINK THIS IS ORIGINAL
					//y1 = ((double)(r) - (x1 * cos(t * DEG2RAD))) / sin(t * DEG2RAD);	//First revision
					//y1 = (double)(r-(accu_h/2)) - (double)(r * sin(t *DEG2RAD));	//this should give a negative value = -(w/2)*tan(t*DEG2RAD)
						//I feel like this should only be used when straight line to corner
					y1 = -(_img_w/2)*tan(t*DEG2RAD); //MOST RECENTLY COMMENTED OUT
					x2 = _img_w - 0;	//First revision 0
					//y2 = ((double)(r-(_accu_h/2)) - ((x2 - (_img_w/2) ) * cos(t * DEG2RAD))) / sin(t * DEG2RAD) + (_img_h / 2); //WE THINK ORIG
					//y2 = ((double)(r) - (x2 * cos(t * DEG2RAD))) / sin(t * DEG2RAD);	//First revision
					//y2 = (double)(r+(accu_h/2)) - (double)(r * sin(t *DEG2RAD));	//this should give a positive value = (w/2)*tan(t*DEG2RAD)
					y2 = (_img_w/2)*tan(t*DEG2RAD); //MOST RECENTLY COMMENTED OUT
				
					y1 = -1 * (y1 - (_img_h/2));	//Part of First Revision
					y2 = -1 * (y2 - (_img_h/2));
				
				}
				else
				{
					//x = (r - y sin(t)) / cos(t);
					y1 = 0;		//First revision (-_img_h/2)	//Assuming this is the bottom of the image
					//x1 = ((double)(r-(_accu_h/2)) - ((y1 - (_img_h/2) ) * sin(t * DEG2RAD))) / cos(t * DEG2RAD) + (_img_w / 2); // WE THINK ORIG
					//x1 = ((double)(r) - (y1 * sin(t * DEG2RAD))) / cos(t * DEG2RAD);	//First revision
					x1 = (-_img_h/2) * atan((90-t)*DEG2RAD); //MOST RECENTLY COMMENTED OUT
					y2 = _img_h - 0;	//First revision to 0	//Assuming this is the top of the image
					//x2 = ((double)(r-(_accu_h/2)) - ((y2 - (_img_h/2) ) * sin(t * DEG2RAD))) / cos(t * DEG2RAD) + (_img_w / 2); //WE THINK ORIG
					//x2 = ((double)(r) - (y2 * sin(t * DEG2RAD))) / cos(t * DEG2RAD);	//First revision
					x2 = (_img_h/2) * atan((90-t)*DEG2RAD); //MOST RECENTLY COMMENTED OUT
				
					x1 = x1 + (_img_w/2);	//Part of First Revision
					x2 = x2 + (_img_w/2);
					
				}
				
				//if ((x1 == 0 || x2 == 1920) && ((y1 < -1280 || y1 > 1280) || (y2 < -1280 || y2 > 1280)))
				if ((y1>2560 || y1<0) || (y2>2560||y2<0))
					cout << "error in y" << endl;
				//if ((y1 == 0 || y2 == 2560) && ((x1 < -960 || x2>960) || (x2 < -960 || x2>960)))
				if ((x1>1960 || x1<0) || (x2>1960 || x2<0))
					cout << "error in x" << endl;
				//cout << "X1: " << x1 << " Y1: " << y1 << " " << " X2: " << x2 << " Y2: " << y2 << endl;
					
				lines.push_back(pair< pair<int, int>, pair<int, int> >(pair<int, int>(x1,y1), pair<int, int>(x2,y2)));
				
			}
		}
	}
	
	//cout << "lines: " << lines.size() << " " << threshold << endl;
	return lines;
}

const unsigned int* Hough::GetAccu(int *w, int *h)
{
	*w = _accu_w;
	*h = _accu_h;

	return _accu;
}




