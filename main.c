#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    //the function inside the if clause is executed using the parameters, it returns 0 if it executed succesfully
    //NULL beceause there is no window id that the message is sent back to
    //1 is an id to reference this hotkey inside the programm
    if (!RegisterHotKey(NULL, 1, MOD_CONTROL | MOD_ALT, 0x48)) {
        printf("Failed to register hotkey. Error code: %d\n", GetLastError());
        //pause to display error message
        getchar();
        return 1;
    }
    if (!RegisterHotKey(NULL, 2, MOD_CONTROL | MOD_ALT, 0x4E)) {
        printf("Failed to register hotkey. Error code: %d\n", GetLastError());
        //pause to display error message
        getchar();
        return 1;
    }

    printf("Hotkey registered. Press Ctrl+Alt+H...\n");

    MSG msg = {0};
    //gebe pointer von msg
    while (GetMessage(&msg, NULL, 0, 0)) {
        //is the received message of type hotkey
        if (msg.message == WM_HOTKEY) {
            //is the id of the received hotkey 1?
            if (msg.wParam == 1) {
                printf("Hotkey pressed!\n");

                ShellExecute(NULL, "open", "http://homeassistant.local:8123/config/hardware", NULL, NULL, SW_SHOWNORMAL);
            }
            if (msg.wParam == 2) {
                ShellExecute(NULL, "open", "notepad.exe", NULL, NULL, SW_SHOWNORMAL);
            }
        }
    }

    UnregisterHotKey(NULL, 1);
    return 0;
}

//compile using:
//gcc main.c -o main -mwindows   
