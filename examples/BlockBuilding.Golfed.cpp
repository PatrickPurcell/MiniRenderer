

#include"MiniRenderer.hpp"

#define D .5f
vector<vc4>vb{{-D,D,-D,1},{D,D,-D,1},{ D,D,D,1},{-D,D,D,1},{-D,-D,D,1},{D,-D,D,1
},{D,-D,-D,1},{-D,-D,-D,1}};vector<I>ib{0,1,2,3,4,5,6,7,3,2,5,4,2,1,6,5,1,0,7,6,
0,3,4,7};V ln(Img<F>&img,vc4&v0,vc4&v1){F c=1.08f-(v0[2]+v1[2])/2;if(0<v0[2]&&v0
[2]<1&&0<v1[2]&&v1[2]<1)xWu(img,v0,v1,c);}V rq(Img<F>&img,mtx&m,I i,I b){A v0=
img.prjct(m*vb[ib[i]]);A v1=img.prjct(m*vb[ib[i+1]]);A v2=img.prjct(m*vb[ib[i+2]
]);A v3=img.prjct(m*vb[ib[i+3]]);A e0=v0-v1;A e1=v1-v2;A c0=vc3{e0[0],e0[1],e0[2
]};A c1=vc3{e1[0],e1[1],e1[2]};A c=cross(c0,c1);if(!b||dot(c,vc3{0,0,1})>0)ln(
img,v0,v1),ln(img,v1,v2),ln(img,v2,v3),ln(img,v3,v0);}I cn(I h, I n){R n&&(h<=n-
1||h==abs(n)-1);}V rf(Img<F>&img,Img<I>&in,mtx&m,I b,I d){FOR(y,in.h)FOR(x,in.w)
{I rb=0;I t=in.pxl(x,y);I i=t>=0?0:abs(t)-1;t=abs(t);for(;i<t;++i){A mvp=m*
trnslt(mtxIdnty(),vc3{(F)x-in.w*.5f,(F)i,(F)y-in.h*.5f});if(i==t-1)rq(img,mvp,0,
b);if(!d||!cn(i,in.pxl(x,y-1)))rq(img,mvp,16,b);if(!d||!cn(i,in.pxl(x+1,y)))rq(
img,mvp,12,b);if(!d||!cn(i,in.pxl(x,y+1)))rq(img,mvp,8,b);if(!d||!cn(i,in.pxl(x-
1,y)))rq(img,mvp,20,b);if(!rb)rq(img,mvp,4,b),rb=1;}}}V blocks(I*inD,I inW,I inH
,I oW,I oH,I b,I d,F fv,F np,F fp,vc3 c,F s,F ca,F cf,I o,I g){F a=0;F ac=c[1];
size_t fc=0;Img<F>img(oW, oH);Img<I>in(inW,inH);memcpy(&in[0],inD,in.size()*
sizeof(I));A wndw=g?new Wndw(oW,oH):0;while(o||g){img.clr();c[1]=ac+ca*sin(cf*fc
);A cr=rotate(mtxIdnty(),RAD(a),vc3{0,1,0})*vc4{c[0],c[1],c[2],1};A m=prspctv(
RAD(fv),(F)oW/(F)oH,np,fp)*lookAt(vc3{cr[0],cr[1],cr[2]},vc3{},vc3{0,1,0});rf(
img,in,m,b,d);g=wndw?wndw->o:0;if(g){wndw->tick();FOR(i,img.size())wndw->frmbf.
pxl(i,vc3{1,1,1}*img[i]);}if(o)pgm("blocks",oW,oH,&img[0]),o=0;a+=s;++fc;}if(
wndw)delete wndw;}

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
    blocks(
        input,               // Input data
        11,                  // Input width
        11,                  // Input height
        840,                 // Ouptut width
        840,                 // Output height
        true,                // Enable back face culling
        true,                // Enable hollow structures
        68.0f,               // Field of view (Degrees)
        2.4f,                // Near plane
        36.0f,               // Far plane
        vc3 { -8, 4.6f, 8 }, // Camera position (a block is 1 world unit cubed)
        1.4f,                // Camera rotation speed (world units per frame)
        2.8f,                // Camera crane amplitude (world units)
        0.02f,               // Camera crane frequency (crane amplitude per frame)
        true,                // Write image to "blocks.pgm"
        true                 // Render (Windows only)
    );
}
