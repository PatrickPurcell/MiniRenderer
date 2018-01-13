
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
TMP<TYP T>
class Img
    :public vector<T>
{
public:
    I w,h;

    Img(I w,I h)
        :w{w}
        ,h{h}
        ,vector<T>(w*h)
    {
    }

    T&pxl(I x,I y)
    {
        static T n;
        R x<w&&y<h?this->O[](y*w+x):n;
    }

    TMP<I N>
    vc<N>nrmlz(vc<N>&v)
    {
        R{
            lrp(w*.5f,w,v[0]),
            lrp(h*.5f,h,-v[1])
        };
    }
};

/**
 * Xialin Wu's line algorithm fpart().
 * https://en.wikipedia.org/wiki/Xiaolin_Wu%27s_line_algorithm
 */
F xWuF(F f){f-=floor(f);R f<0?1-f:f;}

/**
 * Xialin Wu's line algorithm rfpart().
 * https://en.wikipedia.org/wiki/Xiaolin_Wu%27s_line_algorithm
 */
F xWuRF(F f){R 1-xWuF(f);}

/**
 * Xialin Wu's line algorithm endpoint().
 * https://en.wikipedia.org/wiki/Xiaolin_Wu%27s_line_algorithm
 */
TMP<TYP T>
V xWuE(Img<T>&img)
{

}

/**
 * Xialin Wu's line algorithm.
 * https://en.wikipedia.org/wiki/Xiaolin_Wu%27s_line_algorithm
 * @param [in] img The image to render a line into
 * @param [in] a   The line start point
 * @param [in] b   The line end point
 * @param [in] c   The line color
 */
TMP<TYP T>
V xWu(Img<T>&img,vc<2>&a,vc<2>&b,T&c)
{

}
