
/*
==========================================
    Licensed under the MIT license
    Copyright (c) 2017 Patrick Purcell
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Defines.hpp"
#include "MiniGLM_ex.hpp"
#include "MiniImage.hpp"

#if PW

struct FrmBf
{
    I w,h;
    HDC hdc;
    HBITMAP bmp;
    COLORREF*pxls;
    //Img<vc3> img;

    ~FrmBf()
    {
        if(hdc)
            DeleteDC(hdc);
        if(bmp)
            DeleteObject(bmp);
    }

    V rsz(HDC _hdc,I _w,I _h)
    {
        this->~FrmBf();
        w=_w;
        h=_h;
        hdc=CreateCompatibleDC(_hdc);
        BITMAPINFO i{sizeof(i),int(w),-int(h),1,32,BI_RGB,0,0,0,0,{}};
        bmp=CreateDIBSection(hdc,&i,DIB_RGB_COLORS,(V**)&pxls,0,0);
        SelectObject(hdc,bmp);
    }

    V pxl(I x,I y,vc3 c)
    {
        pxl(y*w+x,c);
    }

    V pxl(I i, vc3 c)
    {
        c=strt(c)*255;
        pxls[i]=RGB((B)round(c[2]),(B)round(c[1]),(B)round(c[0]));
    }

    V clr()
    {
        FOR(y,h)
            FOR(x,w)
                pxl(x,y,{0,0,0});
    }
};

LRESULT CALLBACK wp(HWND h,UINT m,WPARAM wp,LPARAM lp);

struct Wndw
{
    I w,h,o{1};
    HWND _;
    HDC hdc;
    FrmBf frmbf;
    void(*rsz)(F);
    Wndw(I w,I h)
        :w{w}
        ,h{h}
        //:frmbf()
    {
        A i=GetModuleHandle(0);
        WNDCLASSEX c{sizeof(c),0,wp,0,0,i,0,0,0,0,"-",0};
        RegisterClassEx(&c);
        _=CreateWindowEx(0,"-",0,WS_MINIMIZEBOX|WS_MAXIMIZEBOX|WS_SYSMENU|WS_THICKFRAME,0,0,w,h,0,0,i,0);
        RECT wr,cr;
        GetWindowRect(_,&wr);
        GetClientRect(_,&cr);
        MoveWindow(_,wr.left,wr.top,w+wr.right-wr.left-cr.right,h+wr.bottom-wr.top-cr.bottom,0);
        hdc=GetDC(_);
        frmbf.rsz(hdc,w,h);
        SetWindowLongPtr(_,GWLP_USERDATA,(LONG_PTR)this);
        ShowWindow(_,SW_SHOW);
        SetForegroundWindow(_);
        SetFocus(_);
    }

    V tick()
    {
        MSG m;
        while(PeekMessage(&m,_,0,0,PM_REMOVE))
            TranslateMessage(&m),
            DispatchMessage(&m);
        InvalidateRect(_,0,0);
    }

    V cls()
    {
        ReleaseDC(_, hdc);
        DeleteDC(hdc);
        DestroyWindow(_);
        o=0;
    }
};

LRESULT CALLBACK wp(HWND h,UINT m,WPARAM wp,LPARAM lp)
{
    A w=(Wndw*)GetWindowLongPtr(h,GWLP_USERDATA);
    if(w){
        A&_=*w;
        switch(m){
            case WM_CLOSE:_.cls();break;
            case WM_SIZE:{
                _.w=LOWORD(lp);
                _.h=HIWORD(lp);
                _.frmbf.rsz(_.hdc,_.w,_.h);
            }break;
            case WM_MOUSEWHEEL:
                // _.rsz(short(HIWORD(wp)));
                break;
            case WM_PAINT:{
                PAINTSTRUCT s;
                A hdc=BeginPaint(_._,&s);
                BitBlt(hdc,0,0,_.w,_.h,_.frmbf.hdc,0,0,SRCCOPY);
                EndPaint(_._,&s);
            }break;
        }
    }
    R DefWindowProc(h,m,wp,lp);
}

#else

#endif
