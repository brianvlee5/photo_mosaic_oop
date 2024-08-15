#ifndef _GRAY_IMAGE_H_
#define _GRAY_IMAGE_H_

#include "image.h"
#include <cmath>
#include <climits>

class GrayImage : public Image{
private:
    int **pixels;

public:
    GrayImage();
    GrayImage(int width, int height, int **pixels_in);
    ~GrayImage();
    bool LoadImage(string filename);
    void DumpImage(string filename);
    void Display_X_Server();
    void Display_ASCII();
    void Display_CMD();
    void boxFilter(int box_size);
    void sobelGradient();
    void contrastStretch();
    void mosaicFilter(int box_size);

};

#endif