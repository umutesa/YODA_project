#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macros.h"
#include "sobel.h"
#include "file_operations.h"

#include <time.h>
#define ARGS_NEEDED 4

int main(int argc, char *argv[]) {
    char *file_in,
         *file_out,
         *file_out_h,
         *file_out_v,
         *file_gray;

    byte *rgb,
         *gray,
         *sobel_h_res,
         *sobel_v_res,
         *contour_img;

    int rgb_size,
        width,
        height;
    int inter_files = 0,
        gray_file = 0;

    // Get arguments
    if(argc < ARGS_NEEDED) {
        printf("Usage: TODO\n");
        return 1;
    }

    // File names
    file_in = argv[1];
    file_out = argv[2];
  
  
  
