
/*

PW : Platform Windows
PL : Platform Linux

sudo apt-get install libx11-dev
reset; g++ -std=c++11 -Wall Main.cpp -o MiniWindow -lX11; ./MiniWindow

*/

#include "MiniDefines.hpp"
#include "MiniGLM.hpp"

#include <cmath>
#include <thread>
#include <cstdint>
#include <cstddef>
#include <cstdint>
#include <cstddef>
#include <iostream>

#include <array>
#include <vector>

using namespace std;
using namespace glm;

#define GOLF

#if PW
#ifndef GOLF
struct FB
{
    U w,h;
    HDC d{0};
    HBITMAP b{0};
    COLORREF*c;

    ~FB()
    {
        if(d)DeleteDC(d);
        if(b)DeleteObject(b);
    }

    V s(HDC g,U x,U y)
    {
        this->~FB();
        w=x;
        h=y;
        d=CreateCompatibleDC(g);
        BITMAPINFO i{sizeof(i),int(w),-int(h),1,32,BI_RGB,0,0,0,0,{}};
        b=CreateDIBSection(g,&i,DIB_RGB_COLORS,(V**)&c,0,0);
        SelectObject(d,b);
    }

    V p(U x,U y,vec3 v)
    {
        v=saturate(v);
        v=v*255;
        c[y*w+x]=RGB(B(v[2]),B(v[1]),B(v[0]));
    }
};

LRESULT CALLBACK wp(HWND h,UINT message,WPARAM wparam,LPARAM lparam);

struct WN
{
    U w,h,o{1};
    HWND _;
    HDC d;
    FB f;
    MSG m;
    void(*s)(float);
    WN(U w,U h)
        :w{w}
        ,h{h}
    {
        A i=GetModuleHandle(0);
        WNDCLASSEX c{sizeof(WNDCLASSEX),0,wp,0,0,i,0,0,0,0,"-",0};
        RegisterClassEx(&c);
        _=CreateWindowEx(0,"-",0,WS_MINIMIZEBOX|WS_MAXIMIZEBOX|WS_SYSMENU|WS_THICKFRAME,0,0,w,h,0,0,i,0);
        RECT wr,cr;
        GetWindowRect(_,&wr);
        GetClientRect(_,&cr);
        MoveWindow(_,wr.left,wr.top,w+wr.right-wr.left-cr.right,h+wr.bottom-wr.top-cr.bottom,0);
        d=GetDC(_);
        f.s(d,w,h);
        SetWindowLongPtr(_,GWLP_USERDATA,(LONG_PTR)this);
        ShowWindow(_,SW_SHOW);
        SetForegroundWindow(_);
        SetFocus(_);
    }

    V u()
    {
        while(PeekMessage(&m,_,0,0,PM_REMOVE))
            TranslateMessage(&m),
            DispatchMessage(&m);
        InvalidateRect(_, 0, 0);
    }

    V c()
    {
        ReleaseDC(_,d);
        DeleteDC(d);
        DestroyWindow(_);
        o=0;
    }
};

LRESULT CALLBACK wp(HWND h,UINT m,WPARAM wp,LPARAM lp)
{
    A w=(WN*)GetWindowLongPtr(h,GWLP_USERDATA);
    if(w){
        A&_=*w;
        switch(m){
            case WM_CLOSE:_.c();break;
            case WM_SIZE:{
                _.w=LOWORD(lp);
                _.h=HIWORD(lp);
                _.f.s(_.d,_.w,_.h);
            }break;
            case WM_MOUSEWHEEL:_.s(short(HIWORD(wp)));break;
            case WM_PAINT:{
                PAINTSTRUCT s;
                A hdc=BeginPaint(_._,&s);
                BitBlt(hdc,0,0,_.w,_.h,_.f.d,0,0,SRCCOPY);
                EndPaint(_._,&s);
            }break;
        }
    }
    R DefWindowProc(h,m,wp,lp);
}
#else
/////////////////////////////////////////////////////////////////////////////////////////
struct FB{U w,h;HDC d{0};HBITMAP b{0};COLORREF*c;~FB(){if(d)DeleteDC(d);if(b)
DeleteObject(b);}V s(HDC g,U x,U y){this->~FB();w=x;h=y;d=CreateCompatibleDC(g);
BITMAPINFO i{sizeof(i),int(w),-int(h),1,32,BI_RGB,0,0,0,0,{}};b=CreateDIBSection(g,&i,
DIB_RGB_COLORS,(V**)&c,0,0);SelectObject(d,b);}V p(U x,U y,vec3 v){v=saturate(v);v=v*255;
c[y*w+x]=RGB(B(v[2]),B(v[1]),B(v[0]));}};LRESULT CALLBACK wp(HWND h,UINT message,WPARAM
wparam,LPARAM lparam);struct WN{U w,h,o{1};HWND _;HDC d;FB f;MSG m;void(*s)(float);WN(U w
,U h):w{w},h{h}{A i=GetModuleHandle(0);WNDCLASSEX c{sizeof(WNDCLASSEX),0,wp,0,0,i,0,0,0,0
,"-",0};RegisterClassEx(&c);_=CreateWindowEx(0,"-",0,WS_MINIMIZEBOX|WS_MAXIMIZEBOX|
WS_SYSMENU|WS_THICKFRAME,0,0,w,h,0,0,i,0);RECT wr,cr;GetWindowRect(_,&wr);GetClientRect(_
,&cr);MoveWindow(_,wr.left,wr.top,w+wr.right-wr.left-cr.right,h+wr.bottom-wr.top-cr.
bottom,0);d=GetDC(_);f.s(d,w,h);SetWindowLongPtr(_,GWLP_USERDATA,(LONG_PTR)this);
ShowWindow(_,SW_SHOW);SetForegroundWindow(_);SetFocus(_);}V u(){while(PeekMessage(&m,_,0,
0,PM_REMOVE))TranslateMessage(&m),DispatchMessage(&m);InvalidateRect(_, 0, 0);}V c(){
ReleaseDC(_,d);DeleteDC(d);DestroyWindow(_);o=0;}};LRESULT CALLBACK wp(HWND h,UINT m,
WPARAM wp,LPARAM lp){A w=(WN*)GetWindowLongPtr(h,GWLP_USERDATA);if(w){A&_=*w;switch(m){
case WM_CLOSE:_.c();break;case WM_SIZE:{_.w=LOWORD(lp);_.h=HIWORD(lp);_.f.s(_.d,_.w,_.h);
}break;case WM_MOUSEWHEEL:_.s(short(HIWORD(wp)));break;case WM_PAINT:{PAINTSTRUCT s;A hdc
=BeginPaint(_._,&s);BitBlt(hdc,0,0,_.w,_.h,_.f.d,0,0,SRCCOPY);EndPaint(_._,&s);}break;}}R
DefWindowProc(h,m,wp,lp);}
/////////////////////////////////////////////////////////////////////////////////////////
#endif
#endif

#if PL
struct WN
{
    U w,h,o{1};
    int s;
    GC gc;
    XEvent e;
    Window hw;
    Display* d;
    
    WN(U w, U h)
        : w { w }
        , h { h }
    {
        d = XOpenDisplay(0);
        s = XDefaultScreen(d);
        hw = XCreateSimpleWindow(
            d,
            XRootWindow(d, s),
            0,
            0,
            w,
            h,
            0,
            XBlackPixel(d, s),
            XWhitePixel(d, s)
        );
        
        // XSetStandardProperties(d, hw, "My Window", "Hi!", None, 0, 0, 0);
        XSelectInput(d, hw, ExposureMask | ButtonPressMask | KeyPressMask);
        gc = XCreateGC(d, hw, 0, 0);
        XMapWindow(d, hw);
        XFlush(d);
    }

    void u()
    {
        XNextEvent(d, &e);
        switch (e.type) {
            case ButtonPress: c(); break;
        }
    }

    void r()
    {

    }

    void c()
    {
        XFreeGC(d, gc);
        XDestroyWindow(d, hw);
        XCloseDisplay(d);
        o = false;
    }
};
#endif

static float scale = 2.2f;
void onmouse(float d)
{
    scale -= d * 0.001f;
}

int main()
{
    WN w(1024,1024);
    w.s = onmouse;
    while(w.o){
        w.u();
        //Sleep(32);
        for(U yi=0;yi<w.h;++yi)
            for(U xi=0;xi<w.w;++xi){
                vec2 t{xi/F(w.w),yi/F(w.h)};

                // F scale = 2.2f;
                vec2 center { 0.7f, 0 };
                U iterations = 64;

                vec2 z, c;
                c[0] = 1.3333f * (t[0] - 0.5f) * scale - center[0];
                c[1] =           (t[1] - 0.5f) * scale - center[1];

                z = c;
                U i = 0;
                for (; i < iterations; ++i) {
                    F x = (z[0] * z[0] - z[1] * z[1]) + c[0];
                    F y = (z[1] * z[0] + z[0] * z[1]) + c[1];
                    if ((x * x + y * y) > 4) {
                        break;
                    }

                    z[0] = x;
                    z[1] = y;
                }

                F value = F(i) / 100.0f;
                        
                #if PW
                w.f.p(xi,yi,i==iterations?vec3{0,0,0}:vec3{value,0,0});
                #endif

                #if PL
                uint8_t r =
                    i == iterations ?
                    0 :
                    (uint8_t)(value * 255.0f);
                uint8_t g = 0;
                uint8_t b = 0;
                unsigned long color = ((r& 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
                XSetForeground(w.d, w.gc, color);
                XDrawPoint(w.d, w.hw, w.gc, xi, yi);
                #endif

            }
    }

    R 0;
}
