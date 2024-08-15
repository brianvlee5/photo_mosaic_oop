#ifndef _RGB_IMAGE_H_
#define _RGB_IMAGE_H_

#include "image.h"
#include "photo_data.h"

class RGBImage : public Image{
private:

public:
    int ***pixels;
    RGBImage();
    RGBImage(int width, int height, int ***pixels_in);
    ~RGBImage();
    bool LoadImage(string filename);
    void DumpImage(string filename);
    void Display_X_Server();
    void Display_ASCII();
    void Display_CMD();
    void boxFilter(int box_size);
    void sobelGradient();
    void contrastStretch();
    void mosaicFilter(int box_size);
    void getRGBAvg(int &sum_r, int &sum_g, int &sum_b);
    void replaceGrid(int i, int j, vector<Photo_data> &data_vec);
    string findGrid(vector<Photo_data> &data_vec, int big_r, int big_g, int big_b);
    
};

#endif