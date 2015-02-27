//Extra CV code
//DONE IN OPEN CV, this displays final image with lines drawn on it based on accumulator
for(it=lines.begin();it!=lines.end();it++)
{
	cv::line(img_res, cv::Point(it->first.first, it->first.second), cv::Point(it->second.first, it->second.second), cv::Scalar( 0, 0, 255), 2, 8);
}

//Visualize all
int aw, ah, maxa;
aw = ah = maxa = 0;
const unsigned int* accu = hough.GetAccu(&aw, &ah);

for(int p=0;p<(ah*aw);p++)
{
	if((int)accu[p] > maxa)
		maxa = accu[p];
}
double contrast = 1.0;
double coef = 255.0 / (double)maxa * contrast;

cv::Mat img_accu(ah, aw, CV_8UC3);
for(int p=0;p<(ah*aw);p++)
{
	unsigned char c = (double)accu[p] * coef < 255.0 ? (double)accu[p] * coef : 255.0;
	img_accu.data[(p*3)+0] = 255;
	img_accu.data[(p*3)+1] = 255-c;
	img_accu.data[(p*3)+2] = 255-c;
}


cv::imshow(CW_IMG_ORIGINAL, img_res);
cv::imshow(CW_IMG_EDGE, img_edge);
cv::imshow(CW_ACCUMULATOR, img_accu);

char c = cv::waitKey(360000);
if(c == '+')
	threshold += 5;
if(c == '-')
	threshold -= 5;
if(c == 27)
	break;





//USES OpenCV to blur image, then perform basic Canny Edge on it
cv::Mat img_edge;
cv::Mat img_blur;

cv::Mat img_ori = cv::imread( file_path, 1 );
cv::blur( img_ori, img_blur, cv::Size(5,5) );
cv::Canny(img_blur, img_edge, 100, 150, 3);
	




//OPEN CV USE: Creates dialog windows to display images and allow for better UI
cv::namedWindow(CW_IMG_ORIGINAL, cv::WINDOW_AUTOSIZE);
cv::namedWindow(CW_IMG_EDGE, 	 cv::WINDOW_AUTOSIZE);
cv::namedWindow(CW_ACCUMULATOR,	 cv::WINDOW_AUTOSIZE);

cvMoveWindow(CW_IMG_ORIGINAL, 10, 10);
cvMoveWindow(CW_IMG_EDGE, 680, 10);
cvMoveWindow(CW_ACCUMULATOR, 1350, 10);






//Code Here took care of basic input arguments
	int c;
	while ((c = getopt(argc, argv, "s:t:?")) != -1 )
	{
	    switch (c)
	    {
		    case 's':
		    	img_path = optarg;
		    	break;
		    case 't': 
		    	threshold = atoi(optarg);
		    	break;
		    case '?':
	        default:
				usage(argv[0]);
				return -1;
	    }
	}

	if(img_path.empty())
	{
		usage(argv[0]);
		return -1;
	}


//Usage was here

void usage(char * s)
{

	fprintf( stderr, "\n");
   	fprintf( stderr, "%s -s <source file> [-t <threshold>] - hough transform. build: %s-%s \n", s, __DATE__, __TIME__);
	fprintf( stderr, "   s: path image file\n");
	fprintf( stderr, "   t: hough threshold\n");
	fprintf( stderr, "\nexample:  ./hough -s ./img/russell-crowe-robin-hood-arrow.jpg -t 195\n");
	fprintf( stderr, "\n");
}



