#ifndef _BIT_FIELD_FILTER_H
#define _BIT_FIELD_FILTER_H

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdint.h>

#include "gray_image.h"
#include "rgb_image.h"

#define CASE_ONE    0b00000001
#define CASE_TWO    0b00000010
#define CASE_THREE  0b00000100
#define CASE_FOUR   0b00001000


void loadCase(int8_t option, Image *img);

//using bitwise and to track whtat is the user's option
#endif