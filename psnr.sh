#!/bin/bash

SOURCE_FILE=$1
WIDTH=$2
HEIGHT=$3

if [ $# -lt 3 ]; then
    echo "useage: $0 [test.yuv] [width] [height]" 
    exit 1
fi

echo "Source: ${SOURCE_FILE}_nv12.yuv width=$WIDTH height=$HEIGHT"
echo "Resolution: ${WIDTH}x${HEIGHT}"

echo 'Step 1: Encode'
m30_encode ${SOURCE_FILE}_nv12.yuv

echo 'Step 2: Start decode process'
mv *.avc test.264
ldecod.exe

echo 'Step 3: Start VQ benchmark'
mse ${SOURCE_FILE}.yuv test_dec.yuv $WIDTH $HEIGHT