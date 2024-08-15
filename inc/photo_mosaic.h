#ifndef _PHOTO_MOSAIC_H_
#define _PHOTO_MOSAIC_H_

#include "rgb_image.h"
#include "image.h"
#include <vector>
#include <fstream>


class PhotoMosaic{
private:

public:
    Image *big_pic;
    vector<string> small_pic_dirs;
    string rgb_rec_file_dir = "rgb_rec.txt";
    void getSmallRgb(ofstream &file, vector<string> &pic_dir_vec);
    void runMosaic();
    void listDirectory(vector<string> &pic_dir_vec, string dir);
    void loadDataVec(vector<Photo_data> &data_vec, ifstream &rgb_rec_file);

};

#endif