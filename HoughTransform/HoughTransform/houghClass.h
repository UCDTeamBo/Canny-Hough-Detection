#ifndef HOUGH_H_
#define HOUGH_H_

#include <vector>

using namespace std;

class Hough {
public:
	Hough();
	virtual ~Hough();
public:
	int Transform(unsigned char* img_data, int w, int h);
	vector<pair<pair<int, int>,pair<int, int>>> GetLines(int threshold);
	const unsigned int* GetAccu(int *w, int *h);
private:
	unsigned int* _accu;
	int _accu_w;
	int _accu_h;
	int _img_w;
	int _img_h;
};

#endif /* HOUGH_H_ */

//Angela was here!!!!!