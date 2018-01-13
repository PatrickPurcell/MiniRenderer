
/*
==========================================
    Licensed under the MIT license
    Copyright (c) 2017 Patrick Purcell
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Defines.hpp"
#include "MiniGLM_ex.hpp"
#include "MiniPgm.hpp"
#include "MiniRenderer.hpp"

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

int main()
{
    I w=1024;
    I h=1024;
    Img<float> img(w,h);
    mtx m=mtxIdnty();
    mtx v=lookAt(vc3{4.8f,3,4.8f},vc3{},vc3{0,1,0});
    mtx p=prspctv(RAD(60),(F)w/(F)h,3.7f,11.4f);
    mtx mvp=p*v*m;
    F gridDim=6;
    I gridRes=48;
    auto grid=createGrid(gridDim,gridRes,0.8f);
    FOR(y,gridRes)
        FOR(x,gridRes){
            I i=y*gridRes+x;
            vc4 p0=grid[i];
            p0=mvp*p0;
            p0=p0/p0[3];
            p0=img.nrmlz(p0);
            if(x<gridRes-1){
                vc4 p1=grid[i+1];
                p1=mvp*p1;
                p1=p1/p1[3];
                p1=img.nrmlz(p1);
                F c=(p0[2]+p1[2])/2;
                if(0<p0[2]&&p0[2]<1&&0<p1[2]&&p1[2]<1)
                    xWu(img,p0,p1,1-c+0.08f);
            }
            if(y<gridRes-1){
                vc4 p1=grid[i+gridRes];
                p1=mvp*p1;
                p1=p1/p1[3];
                p1=img.nrmlz(p1);
                F c=(p0[2]+p1[2])/2;
                if(0<p0[2]&&p0[2]<1&&0<p1[2]&&p1[2]<1)
                    xWu(img,p0,p1,1-c+0.08f);
            }
        }
    pgm("gd",w,h,&img[0]);
    return 0;
}
