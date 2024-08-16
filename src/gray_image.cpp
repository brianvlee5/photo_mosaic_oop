#include "gray_image.h"


GrayImage::GrayImage(){
    ;
}

GrayImage::GrayImage(int width, int height, int **pixels_in){
    w = width, h = height;
    pixels = pixels_in;
}

GrayImage::~GrayImage(){
    ;
}

bool GrayImage::LoadImage(string filename){
    pixels = data_loader.Load_Gray(filename, &w, &h);
    if(pixels == nullptr){
        return false;
    }
    else
        return true;
}

void GrayImage::DumpImage(string filename){
    data_loader.Dump_Gray(w, h, pixels, filename);
}

void GrayImage::Display_X_Server(){
    data_loader.Display_Gray_X_Server(w, h, pixels);
}

void GrayImage::Display_ASCII(){
    data_loader.Display_Gray_ASCII(w, h, pixels); 
}

void GrayImage::Display_CMD(){
    string tmp = "tmp.jpg";
    printf("w:%d h:%d\n", w, h);
    DumpImage(tmp);
    data_loader.Display_Gray_CMD(tmp);
}

void GrayImage::boxFilter(int box_size){
    //printf("w:%d h:%d\n", w, h);
    for(int i=0; i<w; i++){
        for(int j=0; j<h; j++){
            int sum = 0;
            for(int k=i-box_size/2; k<=i+box_size/2; k++){
                for(int l=j-box_size/2; l<j+box_size/2; l++){
                    int pix;
                    if(k<0 || k>=w || l<0 || l>=h)
                        pix = 0;
                    else
                        pix = pixels[l][k];
                    sum += pix;
                }
            }
            //normalize
            sum /= box_size*box_size;
            pixels[j][i] = sum;
        }
    }
}

void GrayImage::sobelGradient(){
    int **pixels_cp;
    pixels_cp = new int*[h];
    for(int i=0; i<h; i++){
        pixels_cp[i] = new int[w];
    }

    int sobel_x[3][3] = {0}, sobel_y[3][3] = {0};//setting the sobel filters
    sobel_x[0][0] = 1, sobel_x[0][2] = -1, sobel_x[1][0] = 2, sobel_x[1][2] = -2, sobel_x[2][0] = 1, sobel_x[2][2] = -1;
    sobel_y[0][0] = 1, sobel_y[0][1] = 2, sobel_y[0][2] = 1, sobel_y[2][0] = -1, sobel_y[2][1] = -2, sobel_y[2][2] = -1;
    for(int i=0; i<w; i++){
        for(int j=0; j<h; j++){
            int grad = 0, grad_x = 0, grad_y = 0;
            for(int k=i-1; k<i+2; k++){
                for(int l=j-1; l<j+2; l++){
                    int pix;
                    if(k<0 || k>=w || l<0 || l>=h)
                        pix = 0;
                    else
                        pix = pixels[l][k];
                    grad_x += sobel_x[l-j+1][k-i+1] * pix;
                    grad_y += sobel_y[l-j+1][k-i+1] * pix;
                }
            }
            //normalize
            grad = sqrt(pow(grad_x, 2)+pow(grad_y, 2));
            grad = (double)grad/360*255;
            if(grad > 255)
                pixels_cp[j][i] = 255;
            else if(grad < 0)
                pixels_cp[j][i] = 0;
            else
                pixels_cp[j][i] = grad;
        }
    }

    for(int i=0; i<w; i++){
        for(int j=0; j<h; j++){
            pixels[j][i] = pixels_cp[j][i];
        }
    }
}


void GrayImage::contrastStretch(){
    int min = INT_MAX, max = INT_MIN;
    for(int i=0; i<w; i++){
        for(int j=0; j<h; j++){
            if(pixels[j][i] > max)
                max = pixels[j][i];
            if(pixels[j][i] < min)
                min = pixels[j][i];
        }
    }
    //printf("min:%d max:%d\n", min, max);
    for(int i=0; i<w; i++)
        for(int j=0; j<h; j++)
            pixels[j][i] = (pixels[j][i]-min)*255/(max-min);
    for(int i=0; i<w; i++){
        for(int j=0; j<h; j++){
            if(pixels[j][i] > max)
                max = pixels[j][i];
            if(pixels[j][i] < min)
                min = pixels[j][i];
        }
    }
    //printf("min:%d max:%d\n", min, max);
}

void GrayImage::mosaicFilter(int box_size){
    //printf("w:%d h:%d\n", w, h);
    for(int i=0; i+box_size<w; i+=box_size){
        for(int j=0; j+box_size<h; j+=box_size){
            int sum = 0;
            for(int k=i; k<i+box_size; k++)
                for(int l=j; l<j+box_size; l++)
                    sum += pixels[l][k];
            
            sum /= box_size*box_size;
            for(int k=i; k<i+box_size; k++)
                for(int l=j; l<j+box_size; l++)
                    pixels[l][k] = sum;
        }
    }
}

void GrayImage::getRGBAvg(int &sum_r, int &sum_g, int &sum_b){

}
void GrayImage::replaceGrid(int i, int j, vector<Photo_data> &data_vec, Photo_data &last_used){

}
string GrayImage::findGrid(vector<Photo_data> &data_vec, int big_r, int big_g, int big_b, Photo_data &last_used){

}