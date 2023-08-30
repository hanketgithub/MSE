//
//  main.c
//  mse
//
//  Useage: mse [source file] [compare file] [width] [height]
//
//  Created by Hank Lee on 12/21/15.
//  Copyright (c) 2015 Hank Lee. All rights reserved.
//

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

#include "mse.h"
#include "psnr.h"


#define MAX_WIDTH   8192
#define MAX_HEIGHT  4320


static uint8_t img[MAX_WIDTH * MAX_HEIGHT * 3];
static uint8_t cmp[MAX_WIDTH * MAX_HEIGHT * 3];


int main(int argc, const char * argv[]) {
    int fd_src;
    int fd_cmp;
    int fd_mse;
    int fd_psnr;

    ssize_t rd_sz;
    
    uint32_t width;
    uint32_t height;
    uint32_t wxh;
    uint32_t bit_depth;
    uint32_t factor;
    uint32_t cnt;
    double   mse_luma;
    double   mse_cr;
    double   mse_cb;
    double   psnr_luma;
    double   psnr_cr;
    double   psnr_cb;
    double   psnr_luma_accum;
    double   psnr_cr_accum;
    double   psnr_cb_accum;
    double   psnr_luma_avg;
    double   psnr_cr_avg;
    double   psnr_cb_avg;
    double   psnr_avg;
    
    char *cp;
    char output[256] = { 0 };
    
    if (argc < 6)
    {
        fprintf(stderr, "useage: %s [src_file] [cmp_file] [width] [height] [bit_depth]\n", argv[0]);
        
        return -1;
    }
    
    
    rd_sz       = 0;
    width       = 0;
    height      = 0;
    wxh         = 0;
    bit_depth   = 0;
    factor      = 0;
    cnt         = 0;
    mse_luma    = 0;
    mse_cr      = 0;
    mse_cb      = 0;
    psnr_luma   = 0;
    psnr_cr     = 0;
    psnr_cb     = 0;
    psnr_luma_accum = 0;
    psnr_cr_accum = 0;
    psnr_cb_accum = 0;
    cp          = NULL;


    // get src input file name from comand line
    fd_src = open(argv[1], O_RDONLY);
    if (fd_src < 0)
    {
        perror(argv[1]);
        exit(EXIT_FAILURE);
    }
    // get cmp input file name from comand line
    fd_cmp = open(argv[2], O_RDONLY);
    if (fd_cmp < 0)
    {
        perror(argv[2]);
        exit(EXIT_FAILURE);
    }

    // specify output file name
    cp = strrchr(argv[1], '.');
    strncpy(output, argv[1], cp - argv[1]);
    strcat(output, "_mse.csv");
    
    fd_mse = open
            (
             output,
             O_WRONLY | O_CREAT | O_TRUNC,
             S_IRUSR
            );

        
    // specify output file name
    memset(output, 0, sizeof(output));
    cp = strrchr(argv[1], '.');
    strncpy(output, argv[1], cp - argv[1]);
    strcat(output, "_psnr.csv");

    fd_psnr = open
            (
             output,
             O_WRONLY | O_CREAT | O_TRUNC,
             S_IRUSR
            );

    width   = atoi(argv[3]);
    height  = atoi(argv[4]);
    
    wxh = width * height;

    bit_depth = atoi(argv[5]);
    factor = bit_depth == 8 ? 1 : 2;
    
    fprintf(stderr, "Processing: ");

    while (1)
    {
        uint32_t fb_size = wxh * 3 / 2 * factor;
        rd_sz = read(fd_src, img, fb_size);
        rd_sz = read(fd_cmp, cmp, fb_size);
        
        if (rd_sz == fb_size)
        {            
            mse
            (
                wxh,
                bit_depth,
                &mse_luma,
                &mse_cr,
                &mse_cb,
                img,
                cmp
            );
            
            psnr_luma   = psnr(mse_luma, bit_depth);
            psnr_cr     = psnr(mse_cr, bit_depth);
            psnr_cb     = psnr(mse_cb, bit_depth);

            char buf0[200];
            char buf1[200];
            
            sprintf(buf0, "%f,%f,%f\n", mse_luma, mse_cr, mse_cb);
            sprintf(buf1, "%f,%f,%f\n", psnr_luma, psnr_cr, psnr_cb);
            
            write(fd_mse, buf0, strlen(buf0));
            write(fd_psnr, buf1, strlen(buf1));

            cnt++;
            psnr_luma_accum += psnr_luma;
            psnr_cr_accum   += psnr_cr;
            psnr_cb_accum   += psnr_cb;
        }
        else
        {
            break;
        }
        fputc('.', stderr);
        fflush(stderr);
    }

    close(fd_src);
    close(fd_cmp);
    close(fd_mse);
    close(fd_psnr);

    psnr_luma_avg = psnr_luma_accum / cnt;
    psnr_cr_avg = psnr_cr_accum / cnt;
    psnr_cb_avg = psnr_cb_accum / cnt;
    psnr_avg = (6 * psnr_luma_avg + psnr_cr_avg + psnr_cb_avg) / 8;

    fprintf(stderr, "Done\n");
    fprintf(stderr, "Output file: %s\n", output);
    fprintf(stderr, "PSNR Y=%f U=%f V=%f Avg=%f\n", psnr_luma_avg, psnr_cr_avg, psnr_cb_avg, psnr_avg);
    
    return 0;
}

