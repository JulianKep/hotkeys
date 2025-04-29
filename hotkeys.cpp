#include <windows.h>
#include <stdio.h>

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lParam;

        if (p->vkCode == 'P') {
            printf("P key pressed!\n");
        }
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main() {
    HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);
    if (!hook) {
        printf("Failed to install hook.\n");
        return 1;
    }

    printf("Listening for P key...\n");

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(hook);
    return 0;
}
