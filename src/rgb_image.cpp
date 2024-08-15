#include "rgb_image.h"

RGBImage::RGBImage(){
    ;
}
RGBImage::RGBImage(int width, int height, int ***pixels_in){
    w = width, h = height;
    pixels = pixels_in;
}
RGBImage::~RGBImage(){
    ;
}
bool RGBImage::LoadImage(string filename){
    pixels = data_loader.Load_RGB(filename, &w, &h);
    if(pixels == nullptr){
        return false;
    }
    else
        return true;
}

void RGBImage::DumpImage(string filename){
    data_loader.Dump_RGB(w, h, pixels, filename);
}

void RGBImage::Display_X_Server(){
    data_loader.Display_RGB_X_Server(w, h, pixels);
}

void RGBImage::Display_ASCII(){
    data_loader.Display_RGB_ASCII(w, h, pixels);
}

void RGBImage::Display_CMD(){
    string tmp = "tmp.jpg";
    DumpImage(tmp);
    data_loader.Display_RGB_CMD(tmp);
}

void RGBImage::boxFilter(int box_size){
    for(int i=0; i+box_size<w; i+=box_size){
        for(int j=0; j+box_size<h; j+=box_size){
            int sum_r = 0, sum_g = 0, sum_b = 0;
            for(int k=i; k<i+box_size; k++){
                for(int l=j; l<j+box_size; l++){
                    sum_r += pixels[l][k][0];
                    sum_g += pixels[l][k][1];
                    sum_b += pixels[l][k][2];
                }

            }
            sum_r /= box_size*box_size;
            sum_g /= box_size*box_size;
            sum_b /= box_size*box_size;
            for(int k=i; k<i+box_size; k++){
                for(int l=j; l<j+box_size; l++){
                    pixels[l][k][0] = sum_r;
                    pixels[l][k][1] = sum_g;
                    pixels[l][k][2] = sum_b;
                }
            }
        }
    }
}

void RGBImage::sobelGradient(){

}
void RGBImage::contrastStretch(){

}

void RGBImage::mosaicFilter(int box_size){

}

void RGBImage::getRGBAvg(int &sum_r, int &sum_g, int &sum_b){
    sum_r = 0, sum_g = 0, sum_b = 0; 
    for(int i=0; i<GRID_SIZE; i++){
        for(int j=0; j<GRID_SIZE; j++){
            sum_r += pixels[j][i][0];
            sum_g += pixels[j][i][1];
            sum_b += pixels[j][i][2];
        }
    }
    sum_r /= GRID_SIZE*GRID_SIZE;
    sum_g /= GRID_SIZE*GRID_SIZE;
    sum_b /= GRID_SIZE*GRID_SIZE;
}


void RGBImage::replaceGrid(int i, int j, vector<Photo_data> &data_vec, Photo_data &last_used){
    int sum_r = 0, sum_g = 0, sum_b = 0;
    RGBImage small_img;
    string dir;//dir for the small picture to replace the grid

    for(int k=0; k<GRID_SIZE; k++){
        for(int l=0; l<GRID_SIZE; l++){
            sum_r += pixels[j+l][i+k][0];
            sum_g += pixels[j+l][i+k][1];
            sum_b += pixels[j+l][i+k][2];
        }
    }
    sum_r /= GRID_SIZE*GRID_SIZE;
    sum_g /= GRID_SIZE*GRID_SIZE;
    sum_b /= GRID_SIZE*GRID_SIZE;

    //if the last one used is near, then use it
    string small_dir;
    int small_r, small_g, small_b;
    int diff, r_diff, b_diff, g_diff;
    small_dir = last_used.dir, small_r = last_used.sum_r, small_b = last_used.sum_b, small_g = last_used.sum_g;
    r_diff = sum_r-small_r, g_diff = sum_g-small_g, b_diff = sum_b-small_b;
    diff = sqrt(r_diff*r_diff + g_diff*g_diff + b_diff*b_diff);
    if(diff < DIFF_THRESHOLD){
        small_img.LoadImage(small_dir);
        for(int k=0; k<GRID_SIZE; k++){
            for(int l=0; l<GRID_SIZE; l++){
                pixels[j+l][i+k][0] = small_img.pixels[l][k][0];
                pixels[j+l][i+k][1] = small_img.pixels[l][k][1];
                pixels[j+l][i+k][2] = small_img.pixels[l][k][2];
            }
        }
        return;
    }

    //if last used is not near, find a new one
    dir = findGrid(data_vec, sum_r, sum_g, sum_b, last_used);
    small_img.LoadImage(dir);
    for(int k=0; k<GRID_SIZE; k++){
        for(int l=0; l<GRID_SIZE; l++){
            pixels[j+l][i+k][0] = small_img.pixels[l][k][0];
            pixels[j+l][i+k][1] = small_img.pixels[l][k][1];
            pixels[j+l][i+k][2] = small_img.pixels[l][k][2];
        }
    }

}

string RGBImage::findGrid(vector<Photo_data> &data_vec, int big_r, int big_g, int big_b, Photo_data &last_used){
    string small_dir;
    int small_r, small_g, small_b, r_diff, g_diff, b_diff, diff;
    for(auto &d : data_vec){
        last_used = d;
        small_dir = d.dir, small_r = d.sum_r, small_b = d.sum_b, small_g = d.sum_g;
        r_diff = big_r-small_r, g_diff = big_g-small_g, b_diff = big_b-small_b;
        diff = sqrt(r_diff*r_diff + g_diff*g_diff + b_diff*b_diff);
        if(diff < DIFF_THRESHOLD){
            break;
        }
    }
    return small_dir;
}