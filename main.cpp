#include "image.h"
#include "gray_image.h"
#include "rgb_image.h"
#include "photo_mosaic.h"
#include "bit_field_filter.h"
#include <stdlib.h>

#define MENU 1
#define BIG_PIC 2
#define SMALL_PIC 3

int main(int argc, char *argv[]){
    Image *img1 = new GrayImage();
    //img1->LoadImage("Image-Folder/mnist/img_100.jpg");
    //img2->DumpImage("img2.jpg");
    //img2->Display_X_Server();
    //img2->Display_CMD();
    ////img1->LoadImage("Image-Folder/cifar10/airplane_0001.png");
    ////img1->LoadImage("Image-Folder/fan.jpg");
    

    //Image *img2 = new RGBImage();
    //img2->LoadImage("Image-Folder/lena.jpg");
    //img2->DumpImage("img2.jpg");
    //img2->Display_X_Server();
    //img2->Display_CMD();

    // some bit field filter design driven code here
    img1->LoadImage("Image-Folder/lena.jpg");
    img1->DumpImage("img1.jpg");
    img1->freePixels();

    printf("step 3\n");
    uint8_t option = 0b00000001;
    img1->LoadImage("Image-Folder/lena.jpg");
    loadCase(option, img1);
    img1->DumpImage("img1_case1.jpg");
    img1->freePixels();

    option = 0b00000010;
    img1->LoadImage("Image-Folder/lena.jpg");
    loadCase(option, img1);
    img1->DumpImage("img1_case2.jpg");
    img1->freePixels();

    option = 0b00000100;
    img1->LoadImage("Image-Folder/moon.jpg");
    loadCase(option, img1);
    img1->DumpImage("img1_case3.jpg");
    img1->freePixels();

    option = 0b00001000;
    img1->LoadImage("Image-Folder/lena.jpg");
    loadCase(option, img1);
    img1->DumpImage("img1_case4.jpg");
    img1->freePixels();


    // some photo mosaic driven code here
    PhotoMosaic pm_obj;
    pm_obj.big_pic = new RGBImage();

    //initialize for testing
    pm_obj.big_pic->LoadImage("Image-Folder/oldman.jpg");
    pm_obj.small_pic_dirs.push_back("Image-Folder/cifar10");

    bool finish = false;
    int state = MENU;
    string keyboard;
    while(!finish){
        switch(state){
            case MENU:
                printf("******************************************************************\n");
                printf("<menu>\n");
                printf("enter s  to show big picture\n");
                printf("enter d  to dump big picture\n");
                printf("enter q  to quit stage 4\n");
                printf("enter bp to move to <big_pic>(load, mosaic)\n");
                printf("enter sp to move to <small_pic>(calculate rgb, update dir)\n");
                printf("******************************************************************\n");
                printf("please enter the command: ");
                cin >> keyboard;
                if(keyboard == "s"){
                    pm_obj.big_pic->Display_CMD();                
                }
                else if(keyboard == "d"){
                    printf("input the directory you want to dump the file:\n");
                    string filename;
                    cin >> filename;
                    pm_obj.big_pic->DumpImage(filename);
                }
                else if(keyboard == "q"){
                    finish = true;
                }
                else if(keyboard == "bp"){
                    state = BIG_PIC;
                }
                else if(keyboard == "sp"){
                    state = SMALL_PIC;
                }
                else{
                    printf("command illegal!\n");
                    string tmp;
                    printf("press any key to continue:\n");
                    cin >> tmp;
                }
                break;
            case BIG_PIC:
                printf("******************************************************************\n");
                printf("<big pic>\n");
                printf("enter b  to return to menu\n");
                printf("enter l  to load big picture\n");
                printf("enter pm to do photo mosaic to big picture\n");
                printf("******************************************************************\n");
                printf("please enter the command: ");
                cin >> keyboard;
                if(keyboard == "l"){
                    printf("input the directory you want to load the file from:\n");
                    string filename;
                    cin >> filename;
                    pm_obj.big_pic->LoadImage(filename);
                }
                else if(keyboard == "pm"){
                    pm_obj.runMosaic();
                }
                else if(keyboard == "b"){
                    state = MENU;
                }
                else{
                    printf("command illegal!\n");
                    string tmp;
                    printf("press any key to continue\n");
                    cin >> tmp;
                }
                break;
            case SMALL_PIC:
                printf("******************************************************************\n");
                printf("<small pic>\n");
                printf("enter b  to return to menu\n");
                printf("enter p  to print directories now\n");
                printf("enter c  to calculate rgb average of small pictures and store\n");
                printf("enter u  to update the directories of finding small pictures\n");
                printf("******************************************************************\n");
                printf("please enter the command: ");
                cin >> keyboard;
                if(keyboard == "c"){
                    vector<string> pic_dir_vec;
                    for(auto &dir : pm_obj.small_pic_dirs)
                        pm_obj.listDirectory(pic_dir_vec, dir);
                    ofstream rgb_rec_file_o;
                    rgb_rec_file_o.open(pm_obj.rgb_rec_file_dir);
                    pm_obj.getSmallRgb(rgb_rec_file_o, pic_dir_vec);
                }
                else if(keyboard == "p"){
                    for(auto &dir : pm_obj.small_pic_dirs)
                        printf("%s\n", dir.c_str());
                    string tmp;
                    printf("press any key to continue\n");
                    cin >> tmp;
                }
                else if(keyboard == "u"){
                    printf("enter the directory you want to update\n");
                    string new_dir;
                    cin >> new_dir;
                    pm_obj.small_pic_dirs.push_back(new_dir);
                }
                else if(keyboard == "b"){
                    state = MENU;
                }
                else{
                    printf("command illegal!\n");
                    string tmp;
                    printf("press any key to continue\n");
                    cin >> tmp;
                }
                break;
        }
        system("clear");
    }

    // more ...
    return 0;
}
