#include "autoaccept.h"

int main() {

    HWND window = findWindow();
    if (window == NULL) {
        printf("Could not attach to League of Legends!");
        return 1;
    }
    COLORREF p = pixel(&window, 5,0);
    if (p == CLR_INVALID) {
        printf("Warning: Outside bounding box!");
    }
    printf("r: %d g: %d b: %d", GetRValue(p), GetGValue(p), GetBValue(p));
    Strip strip;
    int success = calcStrip(&strip, &window);
    int* ptr = &success;
    for (;;) {
        if (shouldAccept(&window, &strip,ptr)) {
            break;
        }
        Sleep(500);
    }
    printf("//accept here");
    clickButton(&window);
    //SetCursorPos(pt.xB, pt.y);
    return 0;
}

/*int WinMain(HINSTANCE h, HINSTANCE g, LPSTR str , int i) {
}*/