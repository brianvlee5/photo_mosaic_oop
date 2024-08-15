#include "image.h"
#include "gray_image.h"
#include "rgb_image.h"
#include "photo_mosaic.h"
#include "bit_field_filter.h"

int main(int argc, char *argv[]){
    //Image *img1 = new GrayImage();
    //img1->LoadImage("Image-Folder/mnist/img_100.jpg");
    //img1->LoadImage("Image-Folder/cifar10/airplane_0001.png");
    //img1->LoadImage("Image-Folder/fan.jpg");
    //img1->LoadImage("Image-Folder/moon.jpg");
    

    //Image *img2 = new RGBImage();
    //img2->LoadImage("Image-Folder/lena.jpg");
    //img2->DumpImage("img2.jpg");
    //img2->Display_X_Server();
    //img2->Display_CMD();

    // some bit field filter design driven code here
    //uint8_t option = 0b00000000;

    //loadCase(option, img1);
    //img1->DumpImage("img1.jpg");
    ////img1->Display_X_Server();
    //img1->Display_CMD();

    // some photo mosaic driven code here
    PhotoMosaic test;
    test.runMosaic();

    // more ...
    return 0;
}
