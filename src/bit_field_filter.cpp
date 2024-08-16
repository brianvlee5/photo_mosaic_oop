#include "bit_field_filter.h"

void loadCase(int8_t option, Image *img){
    if(option & CASE_ONE){
        printf("box filter detected\n");
        img->boxFilter(7);
    }
    if(option & CASE_TWO){
        printf("edge detect detected\n");
        img->sobelGradient();
    }
    if(option & CASE_THREE){
        printf("contrast stretch detected\n");
        img->contrastStretch();
    }
    if(option & CASE_FOUR){
        printf("mosaic filter detected\n");
        img->mosaicFilter(4);
    }
    printf("\n");
}
