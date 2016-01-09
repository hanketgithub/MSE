//
//  mse.h
//  mse
//
//  Created by Hank Lee on  12/21/15.
//  Copyright (c) 2015 Hank Lee. All rights reserved.
//

#ifndef ___MSE___
#define ___MSE___

/**
@brief Compute Mean Square Error between two frames.

The \b mse function computes Mean Square Error between source frame and frame to be compared.

@param wxh      width x height
@param mse_luma output address of luma mse
@param mse_cr   output address of cr mse
@param mse_cb   output address of cb mse
@param src      input address of source frame
@param cmp      input address of frame to be compared
@return
- 0: Successful
- 1: Failed
*/
int mse
(
        uint32_t wxh,
        double  *mse_luma,
        double  *mse_cr,
        double  *mse_cb,
  const uint8_t *src,
  const uint8_t *cmp
);

#endif