#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Example: Register Ctrl + Alt + H (Virtual-Key 0x48)
    if (!RegisterHotKey(NULL, 1, MOD_CONTROL | MOD_ALT, 0x48)) {
        printf("Failed to register hotkey. Error code: %d\n", GetLastError());
        getchar();
        return 1;
    }

    printf("Hotkey registered. Press Ctrl+Alt+H...\n");

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        if (msg.message == WM_HOTKEY) {
            if (msg.wParam == 1) {
                printf("Hotkey pressed!\n");
                ShellExecute(NULL, "open", "http://homeassistant.local:8123/config/hardware", NULL, NULL, SW_SHOWNORMAL);
            }
        }
    }

    UnregisterHotKey(NULL, 1);
    return 0;
}

//compile using:
//gcc main.c -o main -mwindows   
