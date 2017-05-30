
#include <cmath>
#include <thread>
#include <cstdint>
#include <cstddef>

#include <iostream>

#if defined(_WIN32) || defined(_WIN64)
#define WIN_32_LEAN_AND_MEAN
#define NOMMINMAX
#define PW (1)
#include<Windows.h>
#endif

#if defined(__linux)
#define PL (1)
#include <X11/Xlib.h>
#endif

#define A auto
#define U uint32_t

#if PW
LRESULT CALLBACK wp(HWND h, UINT message, WPARAM wparam, LPARAM lparam);
#endif

struct W
{
    U w;
    U h;
    bool o { true };

    #if PW
    HDC dc;
    HWND hw;

    W(U w, U h)
        : w { w }
        , h { h }
    {
        U px = 0;
        U py = 0;

        A i = GetModuleHandle(0);
        WNDCLASSEX c { };
        c.cbSize = sizeof(c);
        c.hInstance = i;
        c.style = CS_HREDRAW | CS_VREDRAW;
        c.lpszClassName = "Window Class Name";
        c.lpfnWndProc = wp;
        c.hCursor = LoadCursor(0, IDC_ARROW);
        c.hIconSm = LoadIcon(i, IDI_APPLICATION);
        c.hIcon = LoadIcon(i, IDI_APPLICATION);
        c.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        RegisterClassEx(&c);

        RECT r { 0, 0, (LONG)w, (LONG)h };
        hw = CreateWindowEx(
            NULL,
            "Window Class Name",
            "Window Title",
            // HACK : Removing anything that allows the Window to resize...
            // FUCK : Resizing the Window crashes the app...
            WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME,
            px,
            py,
            r.right - r.left,
            r.bottom - r.top,
            NULL,
            NULL,
            i,
            NULL
        );

        SetWindowLongPtr(hw, GWL_USERDATA, (LONG)this);
        dc = GetDC(hw);

        BOOL b;
        b = ShowWindow(hw, SW_SHOW);
        b = SetForegroundWindow(hw);
        SetFocus(hw);
    }

    void u()
    {
        MSG m;
        if (PeekMessage(&m, hw, 0, 0, PM_REMOVE)) {
            TranslateMessage(&m);
            DispatchMessage(&m);
        }
    }

    void r()
    {

    }

    void c()
    {
        ReleaseDC(hw, dc);
        DeleteDC(dc);
        DestroyWindow(hw);
        o = false;
    }
    #elif PL
    int s;
    GC gc;
    XEvent e;
    Window hw;
    Display* d;
    
    W(U w, U h)
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
    #endif
};

#if PW
LRESULT CALLBACK wp(HWND h, UINT m, WPARAM wp, LPARAM lp)
{
    A w = (W*)GetWindowLongPtr(h, GWL_USERDATA);
    if (w) {
        switch (m) {
            case WM_CLOSE:w->c(); break;
        }
    }

    return DefWindowProc(h, m, wp, lp);
}
#endif

struct vec2
{
    float x;
    float y;
};

float length(vec2 v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}

int main()
{
    W w(640, 480);
    auto p = &w;
    while (w.o) {
        w.u();
        static bool rendered;
        if (!rendered) {
            for (size_t yi = 0; yi < w.h; ++yi) {
                for (size_t xi = 0; xi < w.w; ++xi) {
                    vec2 texcoord { (float)xi / (float)w.w, (float)yi / (float)w.h };
                    {
                        float scale = 2.2f;
                        vec2 center { 0.7f, 0 };
                        size_t iterations = 1000;

                        vec2 z, c;
                        c.x = 1.3333f * (texcoord.x - 0.5f) * scale - center.x;
                        c.y =           (texcoord.y - 0.5f) * scale - center.y;

                        z = c;
                        size_t i = 0;
                        for (; i < iterations; ++i) {
                            float x = (z.x * z.x - z.y * z.y) + c.x;
                            float y = (z.y * z.x + z.x * z.y) + c.y;
                            if ((x * x + y * y) > 4) {
                                break;
                            }

                            z.x = x;
                            z.y = y;
                        }

                        float value = float(i) / 100.0f;
                        
                        #if PW
                        COLORREF color =
                            i == iterations ?
                            RGB(0, 0, 0) :
                            RGB((uint8_t)(value * 255.0f), 1, 1);

                        SetPixel(w.dc, xi, yi, color);
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
            }

            rendered = true;
        }
    }

    return 0;
}

/*

A : auto
B :
C :
D :
E :
F : float
G :
H :
I : int
J :
K :
L :
M :
N :
O :
P :
Q :
R :
S :
T :
U : uint32_t
V :
W : struct Window
X :
Y :
Z : size_t

PW : Platform Windows
PL : Platform Linux

sudo apt-get install libx11-dev
reset; g++ -std=c++11 -Wall Main.cpp -o MiniWindow -lX11; ./MiniWindow

*/
