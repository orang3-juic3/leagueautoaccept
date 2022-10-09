
//
// Created by Alex on 01/10/2022.
//
#ifndef AUTOACCEPT_AUTOACCEPT_H
#define AUTOACCEPT_AUTOACCEPT_H
#include <stdio.h>
#include "windows.h"
#include <math.h>
#define TARGET RGB(8,11,13) //#0a0e0f
struct Strip {
    LONG begin, end;
};
typedef struct Strip Strip;
int calcStrip(Strip *pt, HWND* hwnd);
HWND findWindow();
COLORREF pixel(HWND* hwnd, int x, int y);
int shouldAccept(HWND* hwnd, Strip* p, int* regenRect);
void clickButton(HWND* hwnd);
void lClick();
#endif //AUTOACCEPT_AUTOACCEPT_H
