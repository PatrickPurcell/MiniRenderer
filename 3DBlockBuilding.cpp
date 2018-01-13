
#include <iostream>

#include "Defines.hpp"
#include "MiniGLM_ex.hpp"
#include "MiniRenderer.hpp"
#include "Pgm.hpp"

Img<1024,1024,vc3>img;
int main()
{
    FOR(y,1024)
        FOR(x,1024){
            F r=x/1024.f;
            F g=y/1024.f;
            F b=(r+g)/2;
            img.pxl(x,y)={r,g,b};
    }

    pgm(1024,1024,&img[0]);
    return 0;
}
