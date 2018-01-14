
#if defined _WIN32||defined _WIN64
#define WIN_32_LEAN_AND_MEAN
#define NOMINMAX
#define PW 1
#include<Windows.h>
#endif
#if defined __linux
#define PL 1
#include<X11/Xlib.h>
#endif
#define A auto
#define B uint8_t
#define F float
#define I int
#define O operator
#define R return
#define V void
#define FOR(IT,NM)for(I IT=0;IT<NM;++IT)
#define TMP template
#define TYP typename
using namespace std;
#include<algorithm>
#include<array>
#include<cmath>
#define PI 3.14159265358979f
#define RAD(DEG)(PI/180*DEG)
TMP<TYP T>T clmp(T t,T a=T{0},T b=T{1}){R min(max(a,t),b);}F lrp(F a,F b,F t){R
fma(t,b,fma(-t,a,a));}TMP<I N>using vc=array<F,N>;using vc2=vc<2>;using vc3=vc<3
>;using vc4=vc<4>;
#define VO(OP)TMP<I N>A O OP(vc<N>&l,vc<N>&r){vc<N> rv;FOR(i,N)rv[i]=l[i]OP r[i\
];R rv;}TMP<I N>A&O OP=(vc<N>&l,vc<N>&r){l=l+r;R l;}TMP<I N>A O OP(vc<N>&l,F r)\
{vc<N> rv;FOR(i,N)rv[i]=l[i]OP r;R rv;}TMP<I N>A&O OP=(vc<N>&l,F r){l=l+r;R l;}
VO(+)VO(-)VO(*)VO(/)TMP<I N>F dot(vc<N>&l,vc<N>&r){F rv=0;FOR(i,N)rv+=l[i]*r[i];
R rv;}TMP<I N>A nrmlz(vc<N>v){R v/sqrt(dot(v,v));}vc3 cross(vc3&l,vc3&r){R{l[1]*
r[2]-r[1]*l[2],l[2]*r[0]-r[2]*l[0],l[0]*r[1]-r[0]*l[1]};}TMP<I N>vc<N>strt(vc<N>
v){FOR(i,N)v[i]=clmp<F>(v[i],0,1);R v;}using mtx=array<vc4, 4>;mtx O*(mtx&l,mtx&
r){A sA0=l[0];A sA1=l[1];A sA2=l[2];A sA3=l[3];A sB0=r[0];A sB1=r[1];A sB2=r[2];
A sB3=r[3];R{sA0*sB0[0]+sA1*sB0[1]+sA2*sB0[2]+sA3*sB0[3],sA0*sB1[0]+sA1*sB1[1]+
sA2*sB1[2]+sA3*sB1[3],sA0*sB2[0]+sA1*sB2[1]+sA2*sB2[2]+sA3*sB2[3],sA0*sB3[0]+sA1
*sB3[1]+sA2*sB3[2]+sA3*sB3[3]};}vc4 O*(mtx&m,vc4&v){R{m[0][0]*v[0]+m[1][0]*v[1]+
m[2][0]*v[2]+m[3][0]*v[3],m[0][1]*v[0]+m[1][1]*v[1]+m[2][1]*v[2]+m[3][1]*v[3],m[
0][2]*v[0]+m[1][2]*v[1]+m[2][2]*v[2]+m[3][2]*v[3],m[0][3]*v[0]+m[1][3]*v[1]+m[2]
[3]*v[2]+m[3][3]*v[3]};}mtx mtxIdnty(){R{1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};}A
lookAt(vc3&e,vc3&c,vc3&up){A f=nrmlz(c-e);A s=nrmlz(cross(f,up));A u=cross(s,f);
A rv=mtxIdnty();rv[0][0]=s[0];rv[1][0]=s[1];rv[2][0]=s[2];rv[0][1]=u[0];rv[1][1]
=u[1];rv[2][1]=u[2];rv[0][2]=-f[0];rv[1][2]=-f[1];rv[2][2]=-f[2];rv[3][0]=-dot(s
,e);rv[3][1]=-dot(u,e);rv[3][2]=dot(f,e);R rv;}A prspctv(F fv,F ar,F zn,F zf){F
tnHlfFv=tan(fv/2);A rv=mtxIdnty();rv[0][0]=1/(tnHlfFv*ar);rv[1][1]=1/tnHlfFv;rv[
2][3]=-1;rv[2][2]=zf/(zn-zf);rv[3][2]=-(zf*zn)/(zf-zn);R rv;}A trnslt(mtx&m,vc3&
v){A rv=m;rv[3]=m[0]*v[0]+m[1]*v[1]+m[2]*v[2]+m[3];R rv;}A rotate(mtx&m,F a,vc3&
v){F c=cos(a);F s=sin(a);A axis=nrmlz(v);A temp=axis*(1-c);A r=mtxIdnty();r[0][0
]=c+temp[0]*axis[0];r[0][1]=temp[0]*axis[1]+s*axis[2];r[0][2]=temp[0]*axis[2]-s*
axis[1];r[1][0]=temp[1]*axis[0]-s*axis[2];r[1][1]=c+temp[1]*axis[1];r[1][2]=temp
[1]*axis[2]+s*axis[0];r[2][0]=temp[2]*axis[0]+s*axis[1];r[2][1]=temp[2]*axis[1]-
s*axis[0];r[2][2]=c+temp[2]*axis[2];A rv=mtxIdnty();rv[0]=m[0]*r[0][0]+m[1]*r[0]
[1]+m[2]*r[0][2];rv[1]=m[0]*r[1][0]+m[1]*r[1][1]+m[2]*r[1][2];rv[2]=m[0]*r[2][0]
+m[1]*r[2][1]+m[2]*r[2][2];rv[3]=m[3];R rv;}
#include<string>
#include<utility>
#include<vector>
#include<fstream>
TMP<TYP T>class Img:public vector<T>{public:I w,h;Img(I w,I h){rsz(w,h);}V rsz(I
_w,I _h){w=_w;h=_h;resize(w*h);}T&pxl(I x,I y){static T n;R 0<=x&&x<w&&0<=y&&y<h
?this->O[](y*w+x):n;}TMP<I N>A nrmlz(vc<N>&v){A r=v;r[0]=lrp(w*.5f,(F)w,v[0]);r[
1]=lrp(h*.5f,(F)h,-v[1]);R r;}A prjct(vc4&v){R nrmlz(v/v[3]);}V clr(T c={}){fill
(begin(),end(),c);}};F xWuF(F f){f-=floor(f);R f<0?1-f:f;}F xWuRF(F f){R 1-xWuF(
f);}TMP<TYP T,TYP VT>I xWuE(Img<T>&img,VT&v,I steep,F grdnt,T&c,F*intrcpt=0){I
xe=(I)round(v[0]);F ye=v[1]+grdnt*(xe-v[0]);F gap=xWuRF(v[0]+.5f);I xpxl1=xe;I
ypxl1=(I)ye;if(steep){img.pxl(xpxl1,ypxl1)+=c*xWuRF(ye)*gap;img.pxl(xpxl1,ypxl1+
1)+=c*xWuF(ye)*gap;}else{img.pxl(ypxl1,xpxl1)+=c*xWuRF(ye)*gap;img.pxl(ypxl1,
xpxl1+1)+=c*xWuF(ye)*gap;}if(intrcpt)*intrcpt=ye+grdnt;R xpxl1;}TMP<TYP T,TYP VT
>V xWu(Img<T>&img,VT v0,VT v1,T c){swap(v0[0],v0[1]);swap(v1[0],v1[1]);F x0=v0[0
];F y0=v0[1];F x1=v1[0];F y1=v1[1];I steep=abs(y1-y0)>abs(x1-x0);if(steep){swap(
v0[0],v0[1]);swap(v1[0],v1[1]);}if(v0[0]>v1[0]){swap(v0[0],v1[0]);swap(v0[1],v1[
1]);}F intrcpt=0;A dlt=v1-v0;F grdnt=dlt[0]?dlt[1]/dlt[0]:1;I xpxl1=xWuE(img,v0,
steep,grdnt,c,&intrcpt);I xpxl2=xWuE(img,v1,steep,grdnt,c);if (steep)for(I x=
xpxl1+1;x<xpxl2;++x){img.pxl(x,(I)intrcpt)+=c*xWuRF(intrcpt);img.pxl(x,(I)
intrcpt+1)+=c*xWuF(intrcpt);intrcpt+=grdnt;}else for(I x=xpxl1+1;x<xpxl2;++x){
img.pxl((I)intrcpt,x)+=c*xWuRF(intrcpt);img.pxl((I)intrcpt+1,x)+=c*xWuF(intrcpt)
;intrcpt+=grdnt;}}V pgm(string s,I w,I h,F*p){ofstream f(s+".pgm");f<<"P2\n"<<w
<<" "<<h<<"\n"<<"255"<<"\n";FOR(y,h){FOR(x,w)f<<(I)round(clmp<F>(p[y*w+x],0,1)*
255)<<" ";f<<"\n";}}
#if PW
struct FrmBf{HDC hdc;HBITMAP bmp;BITMAPINFO bi;Img<COLORREF>img;FrmBf(I w,I h):
img(w,h){}~FrmBf(){if(hdc)DeleteDC(hdc);if(bmp)DeleteObject(bmp);}V rsz(HDC _hdc
,I w,I h){this->~FrmBf();img.rsz(w, h);hdc=CreateCompatibleDC(_hdc);bi={sizeof(
bi),w,-h,1,32,BI_RGB,0,0,0,0,{}};bmp=CreateDIBSection(hdc,&bi,DIB_RGB_COLORS,0,0
,0);}V pxl(I x,I y,vc3&c){pxl(y*img.w+x,c);}V pxl(I i,vc3 c){c=strt(c)*255;img[i
]=RGB(0xffffff-(B)round(c[2]),0xffffff-(B)round(c[1]),0xffffff-(B)round(c[0]));}
V blt(HDC dst){SelectObject(hdc,bmp);SetDIBits(hdc,bmp,0,img.h,&img[0],&bi,
DIB_RGB_COLORS);BitBlt(dst,0,0,img.w,img.h,hdc,0,0,SRCCOPY);}};LRESULT CALLBACK
wp(HWND h,UINT m,WPARAM wp,LPARAM lp);struct Wndw{I o{1};HWND _;HDC hdc;FrmBf
frmbf;void(*rsz)(F);Wndw(I w,I h):frmbf(w,h){A i=GetModuleHandle(0);WNDCLASSEX c
{sizeof(c),0,wp,0,0,i,0,0,0,0,"-",0};RegisterClassEx(&c);_=CreateWindowEx(0,"-",
0,WS_MINIMIZEBOX|WS_MAXIMIZEBOX|WS_SYSMENU|WS_THICKFRAME,0,0,w,h,0,0,i,0);RECT
wr,cr;GetWindowRect(_,&wr);GetClientRect(_,&cr);MoveWindow(_,wr.left,wr.top,w+wr
.right-wr.left-cr.right,h+wr.bottom-wr.top-cr.bottom,0);hdc=GetDC(_);frmbf.rsz(
hdc,w,h);SetWindowLongPtr(_,GWLP_USERDATA,(LONG_PTR)this);ShowWindow(_,SW_SHOW);
SetForegroundWindow(_);SetFocus(_);}V tick(){MSG m;while(PeekMessage(&m,_,0,0,
PM_REMOVE))TranslateMessage(&m),DispatchMessage(&m);InvalidateRect(_,0,0);}V cls
(){ReleaseDC(_, hdc);DeleteDC(hdc);DestroyWindow(_);o=0;}};LRESULT CALLBACK wp(
HWND h,UINT m,WPARAM wp,LPARAM lp){A w=(Wndw*)GetWindowLongPtr(h,GWLP_USERDATA);
if(w){switch(m){case WM_KEYDOWN:switch(wp){case VK_ESCAPE:w->cls();break;}break;
case WM_CLOSE:w->cls();break;case WM_PAINT:{PAINTSTRUCT s;A hdc=BeginPaint(h,&s)
;w->frmbf.blt(hdc);EndPaint(h,&s);}break;}}R DefWindowProc(h,m,wp,lp);}
#else
struct FrmBf{V pxl(I,vc3){}};struct Wndw{I o{0};FrmBf frmbf;Wndw(I,I){}V tick(){
}};
#endif
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
        68.0f,               // Field of view (degrees)
        2.4f,                // Near plane
        36.0f,               // Far plane
        vc3 { 9, 4.2f, 6 }, // Camera position (a block is 1 world unit cubed)
        1.4f,                // Camera rotation speed (world units per frame)
        2.8f,                // Camera crane amplitude (world units)
        0.02f,               // Camera crane frequency (per frame)
        true,                // Write image to "blocks.pgm"
        true                 // Render (Windows only)
    );
}
