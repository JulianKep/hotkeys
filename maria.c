#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "lib/cJSON.h"

void send_unicode_char(wchar_t ch)
{
    INPUT input[2] = {0};

    // Key down (unicode)
    input[0].type = INPUT_KEYBOARD;
    input[0].ki.dwFlags = KEYEVENTF_UNICODE;
    input[0].ki.wScan = ch;

    // Key up (unicode)
    input[1].type = INPUT_KEYBOARD;
    input[1].ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
    input[1].ki.wScan = ch;

    SendInput(2, input, sizeof(INPUT));
}

int main()
{
    /* the function inside the if clause is executed using the parameters, it returns 0 if it executed succesfully
    NULL beceause there is no window id that the message is sent back to
    1 is an id to reference this hotkey inside the programm */
    if (!RegisterHotKey(NULL, 1, MOD_CONTROL | MOD_ALT, 0x41))
    {
        printf("Failed to register hotkey. Error code: %d\n", GetLastError());
        // pause to display error message
        getchar();
        return 1;
    }
    if (!RegisterHotKey(NULL, 2, MOD_CONTROL | MOD_ALT | MOD_SHIFT, 0x41))
    {
        printf("Failed to register hotkey. Error code: %d\n", GetLastError());
        // pause to display error message
        getchar();
        return 1;
    }
    if (!RegisterHotKey(NULL, 3, MOD_CONTROL | MOD_ALT, 0x4F))
    {
        printf("Failed to register hotkey. Error code: %d\n", GetLastError());
        // pause to display error message
        getchar();
        return 1;
    }
    if (!RegisterHotKey(NULL, 4, MOD_CONTROL | MOD_ALT | MOD_SHIFT, 0x4F))
    {
        printf("Failed to register hotkey. Error code: %d\n", GetLastError());
        // pause to display error message
        getchar();
        return 1;
    }
    if (!RegisterHotKey(NULL, 5, MOD_CONTROL | MOD_ALT, 0x55))
    {
        printf("Failed to register hotkey. Error code: %d\n", GetLastError());
        // pause to display error message
        getchar();
        return 1;
    }
    if (!RegisterHotKey(NULL, 6, MOD_CONTROL | MOD_ALT | MOD_SHIFT, 0x55))
    {
        printf("Failed to register hotkey. Error code: %d\n", GetLastError());
        // pause to display error message
        getchar();
        return 1;
    }

    MSG msg = {0};
    // gebe pointer von msg
    while (GetMessage(&msg, NULL, 0, 0))
    {
        // is the received message of type hotkey
        if (msg.message == WM_HOTKEY)
        {
            switch (msg.wParam)
            {
            case 1:
                send_unicode_char(L'ä');
                printf("sent");
                break;
            case 2:
                send_unicode_char(L'Ä');
                printf("sent");
                break;
            case 3:
                send_unicode_char(L'ö');
                printf("sent");
                break;
            case 4:
                send_unicode_char(L'Ö');
                printf("sent");
                break;
            case 5:
                send_unicode_char(L'ü');
                printf("sent");
                break;
            case 6:
                send_unicode_char(L'Ü');
                printf("sent");
                break;
            }
        }
    }

    UnregisterHotKey(NULL, 1);
    UnregisterHotKey(NULL, 2);
    UnregisterHotKey(NULL, 3);
    UnregisterHotKey(NULL, 4);
    UnregisterHotKey(NULL, 5);
    UnregisterHotKey(NULL, 6);
    return 0;
}

/*
compile using:
gcc main.c lib/cJSON.c my.res -o AAAhotkey -mwindows

compile icon:
id ICON "path/to/my.ico"

*/
