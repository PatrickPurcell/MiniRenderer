
/*
==========================================
    Licensed under the MIT license
    Copyright (c) 2017 Patrick Purcell
    http://opensource.org/licenses/MIT
==========================================
*/

#include"Defines.hpp"
#include"MiniGLM_ex.hpp"
#include"MiniImage.hpp"
#include"MiniPgm.hpp"
#include"MiniWindow.hpp"
#include<array>
#include<thread>
#include<vector>

V ln(Img<F>&img,vc4&v0,vc4&v1)
{
    F c=1-(v0[2]+v1[2])/2+0.08f;
    if(0<v0[2]&&v0[2]<1&&0<v1[2]&&v1[2]<1)
        xWu(img,v0,v1,1-c+0.08f);
}

V quad(Img<F>&img,mtx&m,vc4 v0,vc4 v1,vc4 v2,vc4 v3)
{
    v0=img.prjct(m*v0);
    v1=img.prjct(m*v1);
    v2=img.prjct(m*v2);
    v3=img.prjct(m*v3);
    if(true){
        ln(img,v0,v1);
        ln(img,v1,v2);
        ln(img,v2,v3);
        ln(img,v3,v0);
    }
}

V main()
{
    /*
        0-----------1
        |\          |\
        | \         | \
        |  3-----------2
        |  |        |  |
        7..|........6  |
         \ |         \ |
          \|          \|
           4-----------5
    */

    F d=.5f;
    vector<vc4>vb{
        {-d,d,-d,1},
        {d,d,-d,1},
        {d,d,d,1},
        {-d,d,d,1},
        {-d,-d,d,1},
        {d,-d,d,1},
        {d,-d,-d,1},
        {-d,-d,-d,1}
    };
    vector<I>ib{
        0,1,2,3,
        4,5,6,7,
        3,2,5,4,
        2,1,6,5,
        1,0,7,6,
        0,3,4,7
    };
    F a=0;
    I w=960;
    I h=960;
    Img<F>img(w,h);
    Wndw wndw(w,h);
    while(wndw.o){
        wndw.tick();
        img.clr();
        a+=4.4f;
        A m=rotate(mtxIdnty(),RAD(a),vc3{0,1,0});
        A p=prspctv(RAD(16),(F)w/(F)h,3.4f,11.4f);
        A v=lookAt(vc3{4.8f,3,4.8f},vc3{},vc3{0,1,0});
        m=p*v*m;
        for(I i=0;i<(I)ib.size();i+=4){
            quad(img,m,vb[ib[i]],vb[ib[i+1]],vb[ib[i+2]],vb[ib[i+3]]);
        }
        FOR(i,img.size())
            wndw.frmbf.pxl(i,vc3{1,1,1}*img[i]);
        //this_thread::sleep_for(16ms);
    }
}
