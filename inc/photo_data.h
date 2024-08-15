#ifndef _PHOTO_DATA_H_
#define _PHOTO_DATA_H_

#include <stdio.h>
#include <string>

class Photo_data{
public:
    int sum_r, sum_g, sum_b;
    std::string dir;
    void print();

};


#endif