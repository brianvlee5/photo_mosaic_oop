#include "photo_mosaic.h"

void PhotoMosaic::runMosaic(){
    string dir = "Image-Folder/cifar10", big_pic_dir = "Image-Folder/oldman.jpg", rgb_rec_file_dir= "rgb_rec.txt";
    string test_dir;
    vector<string> pic_dir_vec;//for storing all the small pics' directory
    vector<Photo_data> data_vec;//vector for storing rgb/photo dir datas
    ofstream rgb_rec_file_o;//storing the dir and rgb averages from small pic
    ifstream rgb_rec_file_i;//for reading the rec file

    //rgb_rec_file.open(rgb_rec_file_dir);
    big_pic = new RGBImage();//newing the pointer in PhotoMosaic class
    big_pic->LoadImage(big_pic_dir);

    int w = big_pic->getW(), h = big_pic->getH();
    listDirectory(pic_dir_vec, dir);
    //getSmallRgb(rgb_rec_file, pic_dir_vec);
    printf("Done calculating materials\n");

    rgb_rec_file_i.open(rgb_rec_file_dir);

    loadDataVec(data_vec, rgb_rec_file_i);
    rgb_rec_file_i.close();
    printf("Done loading data_vec\n");

    for(int i=0; i+GRID_SIZE<w; i+=GRID_SIZE){
        for(int j=0; j+GRID_SIZE<h; j+=GRID_SIZE){
            big_pic->replaceGrid(i, j, data_vec);
        }
    }

    big_pic->Display_CMD();
    data_vec.clear();
    //small_pic_file.close();
    //delete []big_pic;
    //for(int i=0; i<)
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