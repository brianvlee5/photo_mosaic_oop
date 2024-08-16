#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "data_loader.h"
#include "photo_data.h"

#define GRID_SIZE 32
#define DIFF_THRESHOLD 30

using namespace std;

class Image{
protected:
    int w, h;
    static Data_Loader data_loader;

public:
    Image();
    ~Image();
    int getW();
    int getH();
    virtual bool LoadImage(string filename) = 0;
    virtual void DumpImage(string filename) = 0;
    virtual void Display_X_Server() = 0;
    virtual void Display_ASCII() = 0;
    virtual void Display_CMD() = 0;
    virtual void boxFilter(int box_size) = 0;
    virtual void sobelGradient() = 0;
    virtual void contrastStretch() = 0;
    virtual void mosaicFilter(int box_size) = 0;
    virtual void getRGBAvg(int &sum_r, int &sum_g, int &sum_b) = 0;
    virtual void replaceGrid(int i, int j, vector<Photo_data> &data_vec, Photo_data &last_used) = 0;
    virtual string findGrid(vector<Photo_data> &data_vec, int big_r, int big_g, int big_b, Photo_data &last_used) = 0;
    virtual void freePixels() = 0;

};

#endif