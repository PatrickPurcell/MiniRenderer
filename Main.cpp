
#if defined(_WIN32) || defined(_WIN64)
#define WIN_32_LEAN_AND_MEAN
#define NOMMINMAX
#define PW (1)
#include<Windows.h>
#endif

#include <cmath>
#include <cstdint>

#define A auto
#define U uint32_t

#if PW
LRESULT CALLBACK wp(HWND h, UINT message, WPARAM wparam, LPARAM lparam);
#endif

struct W
{
    U w;
    U h;
    bool o;

    #if PW
    HDC dc;
    HWND hw;

    W(U w, U h)
        : w { w }
        , h { h }
    {
        U px = 0;
        U py = 0;

        auto i = GetModuleHandle(nullptr);
        WNDCLASSEX c { };
        c.cbSize = sizeof(c);
        c.hInstance = i;
        c.style = CS_HREDRAW | CS_VREDRAW;
        c.lpszClassName = "Window Class Name";
        c.lpfnWndProc = wp;
        c.hCursor = LoadCursor(nullptr, IDC_ARROW);
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
        o = true;
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
            for (size_t yi = 0; yi < 480; ++yi) {
                for (size_t xi = 0; xi < 640; ++xi) {
                    vec2 texcoord { (float)xi / 640, (float)yi / 480 };

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
                        COLORREF color =
                            i == iterations ?
                            RGB(0, 0, 0) :
                            RGB((uint8_t)(value * 255.0f), 1, 1);

                        SetPixel(w.dc, xi, yi, color);
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

*/
