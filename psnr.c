//
//  psnr.c
//  mse
//
//  Created by Hank Lee on 12/21/15.
//  Copyright (c) 2015 Hank Lee. All rights reserved.
//

#include <math.h>

/*!
  \def TWENTY_MULTIPLY_LOG_BASE_10_OF_MAX
  Precomputed the value of the formula: 20 * log10(255)
 */
#define TWENTY_MULTIPLY_LOG_BASE_10_OF_MAX		(48.130804)


double psnr
(
    double mse
)
{
#if 0
    return 20 * log10(255) - 10 * log10(mse);
#else
    return TWENTY_MULTIPLY_LOG_BASE_10_OF_MAX - 10 * log10(mse);
#endif
}

