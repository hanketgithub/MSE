//
//  psnr.c
//  mse
//
//  Created by Hank Lee on 12/21/15.
//  Copyright (c) 2015 Hank Lee. All rights reserved.
//

#include <math.h>
#include <stdint.h>


double psnr
(
    double mse,
    uint32_t bit_depth
)
{
    return 20 * log10( (1 << bit_depth) - 1 ) - 10 * log10(mse);
}

