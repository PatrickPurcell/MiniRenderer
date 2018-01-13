
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

#include <utility>
#include <vector>

/**
 * TODO : Documentation.
 */
TMP<I W,I H,TYP T>
struct Img
    : public array<T,W*H>
{
    /**
     * TODO : Documentation.
     */
    T&pxl(I x,I y)
    {
        static T n;
        R x<W&&y<H?this->O[](y*W+x):n;
    }

    /**
     * TODO : Documentation.
     */
    TMP<I N>
    vc<N>nrmlz(vc<N>&v)
    {
        F w=(F)W;
        F h=(F)H;
        R{
            lrp(w/2,w,v[0]),
            lrp(h/2,h,-v[1])
        };
    }
};

/**
 * TODO : Documentation.
 * Xialin Wu's line algorithm fpart().
 * https://en.wikipedia.org/wiki/Xiaolin_Wu%27s_line_algorithm
 */
F xWuF(F f){f-=floor(f);R f<0?1-f:f;}

/**
 * TODO : Documentation.
 * Xialin Wu's line algorithm rfpart().
 * https://en.wikipedia.org/wiki/Xiaolin_Wu%27s_line_algorithm
 */
F xWuRF(F f){R 1-xWuF(f);}

/**
 * TODO : Documentation.
 * Xialin Wu's line algorithm endpoint().
 * https://en.wikipedia.org/wiki/Xiaolin_Wu%27s_line_algorithm
 */
TMP<I W,I H,TYP T>
V xWuE_ungolfed(Img<W,H,T>&img)
{

}

/**
 * TODO : Documentation.
 * Xialin Wu's line algorithm.
 * https://en.wikipedia.org/wiki/Xiaolin_Wu%27s_line_algorithm
 * @param [in] img
 * @param [in] a   The point to start the line at
 * @param [in] b   The point to end the line at
 * @param [in] c   The opacity of the line
 */
TMP<I W, I H, TYP T>
V xWu_ungolfed(Img<W,H,T>&img,vc<2>&a,vc<2>&b,F c)
{

}
