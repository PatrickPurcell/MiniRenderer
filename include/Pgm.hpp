
/*
==========================================
    Licensed under the MIT license
    Copyright (c) 2017 Patrick Purcell
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Defines.hpp"
#include "MiniGLM_ex.hpp"

#include<fstream>

/**
 * Writes a grayscale image to a pgm file named "out.pgm".
 * @param [in] w The width of the image
 * @param [in] h The height of the image
 * @param [in] p The image's pixels as an array of floats [0-1]
 */
V pgm(I w,I h,F*p)
{
    ofstream f("out.pgm");
    f<<"P2\n"<<w<<" "<<h<<"\n"<<"255"<<"\n";
    FOR(y,h){
        FOR(x,w)
            f<<(I)round(clmp<F>(p[y*w+x],0,1)*255)<<" ";
        f<<"\n";
    }
}

/**
 * Writes an RGB image to a pgm file named "out.pgm".
 * @param [in] w The width of the image
 * @param [in] h The height of the image
 * @param [in] p The image's pixels as an array of vc3s
 */
V pgm(I w,I h,vc3*p)
{
    ofstream f("out.pgm");
    f<<"P3\n"<<w<<" "<<h<<"\n"<<"255"<<"\n";
    FOR(y,h){
        FOR(x,w)
            FOR(i,3)
                f<<(I)round(clmp<F>(p[y*w+x][i],0,1)*255)<<" ";
        f<<"\n";
    }
}
