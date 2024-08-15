#ifndef _PHOTO_MOSAIC_H_
#define _PHOTO_MOSAIC_H_

#include "rgb_image.h"
#include "image.h"
#include <vector>
#include <fstream>


class PhotoMosaic{
private:
    Image *big_pic;
    vector<string> small_pic_dirs;

public:
    void getSmallRgb(ofstream &file, vector<string> &pic_list);
    void runMosaic();
    void listDirectory(vector<string> &pic_vec, string dir);
    void loadDataVec(vector<Photo_data> &data_vec, ifstream &rgb_rec_file);

};

#endif