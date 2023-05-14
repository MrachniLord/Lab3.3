#include "framework.h"  
#include <Windows.h>  

PAINTSTRUCT ps;
RECT WindowRectangle = { 470, 15, 20, 205 };
HBRUSH burstRectangle;

class Vector2D {
public:
    float x, y;

    Vector2D(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}

    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }

    Vector2D& operator+=(const Vector2D& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
};

void DrawEllipse(HDC hdc, const Vector2D& center, const double radius) {
    Ellipse(hdc, static_cast<int>(center.x - radius), static_cast<int>(center.y - radius), static_cast<int>(center.x + radius), static_cast<int>(center.y + radius));
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        const double radius = 30.0;
        const double margin = 40.0;
        const int num_circles = 9;

        FillRect(ps.hdc, &WindowRectangle, CreateSolidBrush(RGB(255, 255, 255)));
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        Vector2D centers[num_circles];
        for (int i = 0; i < num_circles; i++) {
            centers[i] = Vector2D(margin + (i) * (radius + 2 * margin), margin + (i) * (radius + 1 * margin));
        }

        int i = 0;
        while (i < num_circles) {
            DrawEllipse(hdc, centers[i], radius);
            i++;
        }

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"WindowClass";
    RegisterClass(&wc);

    HWND hWnd = CreateWindow(wc.lpszClassName, L"Ellipses", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1240, 780, NULL, NULL, NULL, NULL);
    ShowWindow(hWnd, nCmdShow);

    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return static_cast<int>(msg.wParam);
}
