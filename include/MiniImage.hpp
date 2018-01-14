
/*
==========================================
    Licensed under the MIT license
    Copyright (c) 2017 Patrick Purcell
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "MiniDefines.hpp"
#include "MiniGLM_ex.hpp"

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
    {
        rsz(w,h);
    }

    V rsz(I _w,I _h)
    {
        w=_w;
        h=_h;
        resize(w*h);
    }

    T&pxl(I x,I y)
    {
        static T n;
        R x<w&&y<h?this->O[](y*w+x):n;
    }

    TMP<I N>
    A nrmlz(vc<N>&v)
    {
        A r=v;
        r[0]=lrp(w*.5f,(F)w,v[0]);
        r[1]=lrp(h*.5f,(F)h,-v[1]);
        R r;
    }

    A prjct(vc4&v)
    {
        R nrmlz(v/v[3]);
    }

    V clr(T c={})
    {
        fill(begin(),end(),c);
    }
};

/**
 * Xialin Wu's line algorithm fpart().
 */
F xWuF(F f){f-=floor(f);R f<0?1-f:f;}

/**
 * Xialin Wu's line algorithm rfpart().
 */
F xWuRF(F f){R 1-xWuF(f);}

/**
 * Xialin Wu's line algorithm endpoint().
 */
TMP<TYP T,TYP VT>
I xWuE(Img<T>&img,VT&v,bool steep,F grdnt,T&c,F*intrcpt=0)
{
    I xe=(I)round(v[0]);
    F ye=v[1]+grdnt*(xe-v[0]);
    F gap=xWuRF(v[0]+.5f);
    I xpxl1=xe;
    I ypxl1=(I)ye;
    if(steep){
        img.pxl(xpxl1,ypxl1)+=c*xWuRF(ye)*gap;
        img.pxl(xpxl1,ypxl1+1)+=c*xWuF(ye)*gap;
    }else{
        img.pxl(ypxl1,xpxl1)+=c*xWuRF(ye)*gap;
        img.pxl(ypxl1,xpxl1+1)+=c*xWuF(ye)*gap;
    }
    if(intrcpt)
        *intrcpt=ye+grdnt;
    R xpxl1;
}

/**
 * Xialin Wu's line algorithm.
 * https://en.wikipedia.org/wiki/Xiaolin_Wu%27s_line_algorithm
 * @param [in] img The image to render a line into
 * @param [in] v0  The line start point
 * @param [in] v1  The line end point
 * @param [in] c   The line color
 */
TMP<TYP T,TYP VT>
V xWu(Img<T>&img,VT v0,VT v1,T c)
{
    swap(v0[0],v0[1]);
    swap(v1[0],v1[1]);
    F x0=v0[0];
    F y0=v0[1];
    F x1=v1[0];
    F y1=v1[1];
    bool steep=abs(y1-y0)>abs(x1-x0);
    if(steep){
        swap(v0[0],v0[1]);
        swap(v1[0],v1[1]);
    }
    if(v0[0]>v1[0]){
        swap(v0[0],v1[0]);
        swap(v0[1],v1[1]);
    }
    F intrcpt=0;
    A dlt=v1-v0;
    F grdnt=dlt[0]?dlt[1]/dlt[0]:1;
    I xpxl1=xWuE(img,v0,steep,grdnt,c,&intrcpt);
    I xpxl2=xWuE(img,v1,steep,grdnt,c);
    if (steep)
        for(I x=xpxl1+1;x<xpxl2;++x){
            img.pxl(x,(I)intrcpt)+=c*xWuRF(intrcpt);
            img.pxl(x,(I)intrcpt+1)+=c*xWuF(intrcpt);
            intrcpt+=grdnt;
        }
    else
        for(I x=xpxl1+1;x<xpxl2;++x){
            img.pxl((I)intrcpt,x)+=c*xWuRF(intrcpt);
            img.pxl((I)intrcpt+1,x)+=c*xWuF(intrcpt);
            intrcpt+=grdnt;
        }
}
