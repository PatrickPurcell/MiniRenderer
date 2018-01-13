
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
#include "MiniWindow.hpp"

#include<vector>

auto createGrid(F dim,I res,F sd)
{
    F d=dim/2;
    F dlt=1.f/res;
    vector<vc4>r(res*res);
    for(I z=0;z<res;++z){
        F zc=lrp(-d,d,z*dlt);
        for(I x=0;x<res;++x){
            F xc=lrp(-d,d,x*dlt);
            F yc=exp(-(pow(xc,2)+pow(zc,2))/(2*pow(sd,2)));
            r[z*res+x]={xc,yc,zc,1};
        }
    }
    R r;
}

auto drawLine(Img<F>&img,vc4&p0,vc4 p1)
{
    p1=img.prjct(p1);
    F c=(p0[2]+p1[2])/2;
    if(0<p0[2]&&p0[2]<1&&0<p1[2]&&p1[2]<1)
        xWu(img,p0,p1,1-c+0.08f);
}

V main()
{
    I w=1024;
    I h=1024;
    Img<F>img(w,h);
    A p=prspctv(RAD(60),(F)w/(F)h,3.7f,11.4f);
    A v=lookAt(vc3{4.8f,3,4.8f},vc3{},vc3{0,1,0});
    A mvp=p*v;
    F gridDim=6;
    I gridRes=48;
    auto grid=createGrid(gridDim,gridRes,0.8f);
    FOR(y,gridRes)
        FOR(x,gridRes){
            I i=y*gridRes+x;
            A p0=img.prjct(mvp*grid[i]);
            if(x<gridRes-1)
                drawLine(img,p0,mvp*grid[i+1]);
            if(y<gridRes-1)
                drawLine(img,p0,mvp*grid[i+gridRes]);
        }
    pgm("gd",w,h,&img[0]);
    Wndw wndw(w,h);
    F angle=0;
    while(wndw.o){
        wndw.tick();
        // img.clear();
        //// angle+=0.001f;
        //// A r = rotate(mtxIdnty(),angle,vc3{0,1,0});
        //// mvp=p*v*r;
        //// FOR(y,gridRes)
        ////     FOR(x,gridRes){
        ////         I i=y*gridRes+x;
        ////         A p0=img.prjct(mvp*grid[i]);
        ////         if(x<gridRes-1)
        ////             drawLine(img,p0,mvp*grid[i+1]);
        ////         if(y<gridRes-1)
        ////             drawLine(img,p0,mvp*grid[i+gridRes]);
        ////     }
        // wndw.frmbf.clr();
        FOR(i,img.size()){
            wndw.frmbf.pxl(i,vc3{1,1,1}-img[i]);
        }
    }
}
