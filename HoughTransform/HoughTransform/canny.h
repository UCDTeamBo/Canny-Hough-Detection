//Canny.h
#ifndef CANNY_H
#define CANNY_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
 
#define MAX_BRIGHTNESS 255

typedef struct { uint8_t magic[2]; } bmpfile_magic_t;
 
typedef struct { uint32_t filesz; uint16_t creator1; uint16_t creator2; uint32_t bmp_offset; } bmpfile_header_t;
 
typedef struct { uint32_t header_sz; int32_t  width; int32_t  height; uint16_t nplanes; uint16_t bitspp; uint32_t compress_type; uint32_t bmp_bytesz; int32_t  hres;
    int32_t  vres; uint32_t ncolors; uint32_t nimpcolors; } bitmap_info_header_t;
 
typedef struct { uint8_t r; uint8_t g; uint8_t b; uint8_t nothing; } rgb_t; 

typedef short int pixel_t;

class canny
{
public: 
	pixel_t *canny_edge_detection(const pixel_t *in, const bitmap_info_header_t *bmp_ih, const int tmin, const int tmax, const float sigma);
	void gaussian_filter(const pixel_t *in, pixel_t *out, const int nx, const int ny, const float sigma);
	void convolution(const pixel_t *in, pixel_t *out, const float *kernel, const int nx, const int ny, const int kn, const bool normalize);
	bool save_bmp(const char *filename, const bitmap_info_header_t *bmp_ih, const pixel_t *data);
	pixel_t *load_bmp(const char *filename, bitmap_info_header_t *bitmapInfoHeader);

protected:

public:
};

#endif //CANNY_H
