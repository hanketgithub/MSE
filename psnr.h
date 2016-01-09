//
//  psnr.h
//  mse
//
//  Created by Hank Lee on  12/21/15.
//  Copyright (c) 2015 Hank Lee. All rights reserved.
//

#ifndef ___MSE_PSNR___
#define ___MSE_PSNR___

/**
@brief Compute Peak signal-to-noise ratio.

The \b psnr function computes peak signal-to-noise ratio.

@param mse      mean square error
@return psnr
*/
double psnr(double mse);

#endif

