
/*
==========================================
    Licensed under the MIT license
    Copyright (c) 2017 Patrick Purcell
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include"Defines.hpp"
#include"MiniGLM_ex.hpp"
#include"MiniImage.hpp"
#include<array>

#include <iostream>

#if PW

struct FrmBf
{
    HDC hdc;
    HBITMAP bmp;
    BITMAPINFO bi;
    Img<COLORREF>img;

    FrmBf(I w,I h)
        :img(w,h)
    {
    }

    ~FrmBf()
    {
        if(hdc)
            DeleteDC(hdc);
        if(bmp)
            DeleteObject(bmp);
    }

    V rsz(HDC _hdc,I w,I h)
    {
        this->~FrmBf();
        img.rsz(w, h);
        hdc=CreateCompatibleDC(_hdc);
        bi={sizeof(bi),w,-h,1,32,BI_RGB,0,0,0,0,{}};
        bmp=CreateDIBSection(hdc,&bi,DIB_RGB_COLORS,0,0,0);
    }

    V pxl(I x,I y,vc3&c)
    {
        pxl(y*img.w+x,c);
    }

    V pxl(I i,vc3 c)
    {
        c=strt(c)*255;
        img[i]=RGB((B)round(c[2]),(B)round(c[1]),(B)round(c[0]));
    }

    V blt(HDC dst)
    {
        SelectObject(hdc,bmp);
        SetDIBits(hdc,bmp,0,img.h,&img[0],&bi,DIB_RGB_COLORS);
        BitBlt(dst,0,0,img.w,img.h,hdc,0,0,SRCCOPY);
    }
};

LRESULT CALLBACK wp(HWND h,UINT m,WPARAM wp,LPARAM lp);

struct Wndw
{
    I o{1};
    HWND _;
    HDC hdc;
    FrmBf frmbf;
    void(*rsz)(F);
    Wndw(I w,I h)
        :frmbf(w,h)
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
        switch(m){
            case WM_KEYDOWN:
                switch(wp){
                    case VK_ESCAPE:w->cls();break;
                }
            break;
            case WM_CLOSE:w->cls();break;
            // case WM_SIZE:w->frmbf.rsz(w->hdc,LOWORD(lp),HIWORD(lp));break;
            case WM_MOUSEWHEEL:
                // _.rsz(short(HIWORD(wp)));
                break;
            case WM_PAINT:{
                PAINTSTRUCT s;
                A hdc=BeginPaint(h,&s);
                w->frmbf.blt(hdc);
                EndPaint(h,&s);
            }break;
        }
    }
    R DefWindowProc(h,m,wp,lp);
}

#else

#endif
