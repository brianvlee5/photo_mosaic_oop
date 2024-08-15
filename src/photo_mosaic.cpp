#include "photo_mosaic.h"

void PhotoMosaic::runMosaic(){
    string test_dir;
    vector<Photo_data> data_vec;//vector for storing rgb/photo dir datas
    ifstream rgb_rec_file_i;//for reading the rec file
    Photo_data last_used;


    int w = big_pic->getW(), h = big_pic->getH();

    rgb_rec_file_i.open(rgb_rec_file_dir);

    loadDataVec(data_vec, rgb_rec_file_i);
    rgb_rec_file_i.close();
    printf("Done loading data_vec\n");

    for(int i=0; i+GRID_SIZE<w; i+=GRID_SIZE){
        for(int j=0; j+GRID_SIZE<h; j+=GRID_SIZE){
            big_pic->replaceGrid(i, j, data_vec, last_used);
        }
    }

    data_vec.clear();
    //delete []big_pic;
}

void PhotoMosaic::listDirectory(vector<string> &pic_dir_vec, string dir){
    struct dirent *entry;
    DIR *dp;

    dp = opendir(dir.c_str());
    if (dp == NULL) {
        perror("opendir: Path does not exist or could not be read.");
        return ;
    }

    while ((entry = readdir(dp))){
        // store all the .png filename into vector
        if(string(entry->d_name) == "." || string(entry->d_name) == "..") continue;
        pic_dir_vec.push_back(dir+ "/" + string(entry->d_name));
    }

    closedir(dp);
    return ;

}

void PhotoMosaic::getSmallRgb(ofstream &file, vector<string> &pic_dir_vec){
    Image *img;
    img = new RGBImage();
    for(auto &pic : pic_dir_vec){
        img->LoadImage(pic);
        int sum_r = 0, sum_g = 0, sum_b = 0;
        img->getRGBAvg(sum_r, sum_g, sum_b);
        file << pic << " " << sum_r << " " << sum_g << " " << sum_b << '\n';
    }
}

void PhotoMosaic::loadDataVec(vector<Photo_data> &data_vec, ifstream &rgb_rec_file){
    Photo_data data;
    while(rgb_rec_file >> data.dir >> data.sum_r >> data.sum_g >> data.sum_b){
        data_vec.push_back(data);
    }
}