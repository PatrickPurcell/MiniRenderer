
/*
==========================================
    Licensed under the MIT license
    Copyright (c) 2017 Patrick Purcell
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Defines.hpp"
#include "MiniGLM_ex.hpp"
#include "MiniImage.hpp"
#include "MiniPgm.hpp"

int main()
{
    I w=1024;
    I h=512;
    Img<vc3>rgbImg(w,h);
    FOR(y,h)
        FOR(x,w){
            F r=x/(F)w;
            F g=y/(F)h;
            F b=(r+g)/2;
            rgbImg.pxl(x,y)={r,g,b};
        }
    pgm("rgb",w,h,&rgbImg[0]);

    Img<F>gscImg(w,h);
    FOR(y,h)
        FOR(x,w)
            gscImg.pxl(x,y)=(x/(F)w+y/(F)h)/2;
    pgm("gsc",w,h,&gscImg[0]);

    return 0;
}
