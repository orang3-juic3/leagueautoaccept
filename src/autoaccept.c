#include "autoaccept.h"
//
// Created by Alex on 01/10/2022.
//

HWND findWindow() {
    HWND handle = FindWindowA(NULL, "League of Legends");
    return handle;
}

COLORREF pixel(HWND* hwnd, int x, int y) {
    HDC dc = GetDC(*hwnd);
    COLORREF colour = GetPixel(dc, x,y);
    ReleaseDC(*hwnd, dc);
    return colour;
}

int shouldAccept(HWND* hwnd, Strip* p, int* shouldRegen) {
    if (*shouldRegen) {
        *shouldRegen = !calcStrip(p, hwnd);
        printf("Regenned strip: shouldRegen: %d",*shouldRegen);

        if (*shouldRegen) return 0;
    }
    HDC dc = GetDC(*hwnd);
    for (int i = p->begin; i < p->end;i++) {
        if (i <= 0) {
            printf("Invalid");
            *shouldRegen = 1;
            return 0;
        }
        COLORREF clr = GetPixel(dc, 0,i);
        if (clr == CLR_INVALID) {
            calcStrip(p, hwnd);
            clr = GetPixel(dc, 0,i);
        }
        const int rgb[6] = {GetRValue(clr), GetGValue(clr), GetBValue(clr),
                            GetRValue(TARGET),GetGValue(TARGET), GetBValue(TARGET)};
        for (int j = 0; j < 3; ++j) {
            if (!((rgb[j+3] -5) < rgb[j] && rgb[j] < (rgb[j+3] + 5))) {
                printf("No:  r: %d g: %d b: %d||| x: %d y: %d\n", GetRValue(clr), GetGValue(clr), GetBValue(clr),0,i);
                goto skip;
            }
        }
        return 1;
        skip: ;
    }
    ReleaseDC(*hwnd, dc);
    return 0;
}

int calcStrip(Strip* pt, HWND* hwnd) {
    RECT r;
    int xCode= GetWindowRect(*hwnd, &r);

    LONG mid = r.top + (r.bottom - r.top) / 2l;
    *pt= (Strip) {mid -15, mid+15};
    return xCode;
}

void clickButton(HWND* hwnd) {
    RECT r;
    GetWindowRect(*hwnd, &r);
    LONG midX = r.left + (r.right - r.left) / 2;
    LONG ratio = (LONG)(DOUBLE)floor((r.bottom - r.top) * 700/900.0);
    LONG y = r.top + ratio;
    SetCursorPos(midX,y);
    lClick();
}
void lClick() {
    INPUT* inputs = (LPINPUT)calloc(2, sizeof(INPUT)); // need zero so data isnt misread
    inputs[0].type = INPUT_MOUSE;
    inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    inputs[1].type = INPUT_MOUSE;
    inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(2, inputs, sizeof(INPUT));
    free(inputs);
}
