
/*
==========================================
    Licensed under the MIT license
    Copyright (c) 2017 Patrick Purcell
    http://opensource.org/licenses/MIT
==========================================
*/

#include"MiniRenderer.hpp"

/**
 * Vertex buffer containing all of the vertices that we need to render a cube.
 *  0-----------1
 *  |\          |\
 *  | \         | \
 *  |  3-----------2
 *  |  |        |  |
 *  7..|........6  |
 *   \ |         \ |
 *    \|          \|
 *     4-----------5
 */
#define D .5f
vector<vc4>vb{
{-D,D,-D,1},
{D,D,-D,1},
{ D,D,D,1},
{-D,D,D,1},
{-D,-D,D,1},
{D,-D,D,1},
{D,-D,-D,1},
{-D,-D,-D,1}
};

/**
 * Index buffer for rendering faces of a cube from our vertex buffer.
 */
vector<I>ib{
0,1,2,3, // Top    (0)
4,5,6,7, // Bottom (4)
3,2,5,4, // Front  (8)
2,1,6,5, // Right  (12)
1,0,7,6, // Back   (16)
0,3,4,7  // Left   (20)
};

/**
 * Renders a line.
 * @param [in] img The Img<> to render into
 * @param [in] v0  The start point of the line
 * @param [in] v1  The end point of the line
 */
V ln(Img<F>&img,vc4&v0,vc4&v1)
{
    F c=1-(v0[2]+v1[2])/2+0.08f;
    if(0<v0[2]&&v0[2]<1&&0<v1[2]&&v1[2]<1)
        xWu(img,v0,v1,c-0.08f);
}

/**
 * Renders the quad starting at the given index.
 * @param [in] img The Img<> to render into
 * @param [in] m   The mtx to transform each vertex by
 * @param [in] i   The index of the first element in the index buffer
 */
V rq(Img<F>&img,mtx&m,I i)
{
    A v0=img.prjct(m*vb[ib[i]]);
    A v1=img.prjct(m*vb[ib[i+1]]);
    A v2=img.prjct(m*vb[ib[i+2]]);
    A v3=img.prjct(m*vb[ib[i+3]]);
    A e0=v0-v1;
    A e1=v1-v2;
    A c0=vc3{e0[0],e0[1],e0[2]};
    A c1=vc3{e1[0],e1[1],e1[2]};
    A c=cross(c0,c1);
    if(dot(c,vc3{0,0,1})>0){
        ln(img,v0,v1);
        ln(img,v1,v2);
        ln(img,v2,v3);
        ln(img,v3,v0);
    }
}

/**
 * Checks a neighbor's height for one face of the current block.
 * @param [in] h The height of the block that we're currently working on
 * @param [in] n The height of the neighbor that we're checking
 * @return Whether or not we have a neighbor at the face in question
 */
I cn(I h, I n)
{
    R n&&(h<=n-1||h==abs(n)-1);
}

V blocks(I*in,I inW,I inH)
{
    Img<I>in_ex(inW,inH);
    memcpy(&in_ex[0],in,in_ex.size()*sizeof(I));

    I w=840;
    I h=840;
    Img<F>img(w,h);
    Wndw wndw(w,h);
    while(wndw.o){
        wndw.tick();
        img.clr();
        A m=prspctv(RAD(75),(F)w/(F)h,6.4f,24.4f)*lookAt(vc3{-7,8,8},vc3{},vc3{0,1,0});
        FOR(y,inH)
            FOR(x,inW){
                I t=in_ex.pxl(x,y);
                I i=t>=0?0:abs(t)-1; // Jump to the top if we've got a negative value
                t=abs(t);
                for(;i<t;++i){
                    A mvp=m*trnslt(mtxIdnty(),vc3{(F)x-in_ex.w*.5f,(F)i,(F)y-in_ex.h*.5f});
                    if(i==t-1) // Every column needs a top
                        rq(img,mvp,0);
                    if(!cn(i,in_ex.pxl(x,y-1))) // If no neighber N render back face
                        rq(img,mvp,16);
                    if(!cn(i,in_ex.pxl(x+1,y))) // If no neighber E render right face
                        rq(img,mvp,12);
                    if(!cn(i,in_ex.pxl(x,y+1))) // If no neighber S render front face
                        rq(img,mvp,8);
                    if(!cn(i,in_ex.pxl(x-1,y))) // If no neighber W render left face
                        rq(img,mvp,20);
                }
            }
        FOR(i,img.size())
            wndw.frmbf.pxl(i,vc3{1,1,1}-img[i]);
    }
}

void main()
{
    int input[]{
        3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 0, 0, 7,-7,-7,-7,-7, 7, 0, 0,
        0, 0, 0, 7,-7,-7,-7,-7, 7, 0, 0,
        0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0,
        1, 0, 0, 4, 3, 2, 1, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1
    };
    blocks(input,11,11);
}
