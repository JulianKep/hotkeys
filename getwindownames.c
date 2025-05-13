#include <windows.h>
#include <stdio.h>

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    char title[256];

    if (GetWindowText(hwnd, title, sizeof(title)) > 0) {
        printf("HWND: %p | Title: %s\n", hwnd, title);
    }

    return TRUE;  // continue enumeration
}

int main() {
    EnumWindows(EnumWindowsProc, 0);
    getchar();
    return 0;
}

/* 
compile
gcc getwindownames.c -o getwindownames */