#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#define LONG_LIVED_ACCESS_TOKEN = eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiI3ZDAwNGRiMWRjZTU0Yzg1YmIzM2JiMTFmZTkyMGM4YSIsImlhdCI6MTc0NjExNzI1MiwiZXhwIjoyMDYxNDc3MjUyfQ.K_OI7EAvliHJMx6TA_9FRudMzZkcxZQeRs523KROoH0

int main()
{
    // the function inside the if clause is executed using the parameters, it returns 0 if it executed succesfully
    // NULL beceause there is no window id that the message is sent back to
    // 1 is an id to reference this hotkey inside the programm
    if (!RegisterHotKey(NULL, 1, MOD_CONTROL | MOD_ALT, 0x48))
    {
        printf("Failed to register hotkey. Error code: %d\n", GetLastError());
        // pause to display error message
        getchar();
        return 1;
    }
    if (!RegisterHotKey(NULL, 2, MOD_CONTROL | MOD_ALT, 0x4E))
    {
        printf("Failed to register hotkey. Error code: %d\n", GetLastError());
        // pause to display error message
        getchar();
        return 1;
    }
    if (!RegisterHotKey(NULL, 3, MOD_CONTROL | MOD_ALT, 0x4C))
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
<<<<<<< HEAD
                case 1:
                    ShellExecute(NULL, "open", "http://homeassistant.local:8123/config/hardware", NULL, NULL, SW_SHOWNORMAL);
                    break;
                case 2:
                    ShellExecute(NULL, "open", "notepad.exe", NULL, NULL, SW_SHOWNORMAL);
                    break;
=======
            case 1:
                ShellExecute(NULL, "open", "http://homeassistant.local:8123/config/hardware", NULL, NULL, SW_SHOWNORMAL);
                break;
            case 2:
                ShellExecute(NULL, "open", "notepad.exe", NULL, NULL, SW_SHOWNORMAL);
                break;
            case 3:
                system("curl -X POST -H \"Authorization: Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiI3ZDAwNGRiMWRjZTU0Yzg1YmIzM2JiMTFmZTkyMGM4YSIsImlhdCI6MTc0NjExNzI1MiwiZXhwIjoyMDYxNDc3MjUyfQ.K_OI7EAvliHJMx6TA_9FRudMzZkcxZQeRs523KROoH0\" http://homeassistant.local:8123/api/webhook/-6QDwsBUTH2duVkWPiaNwfdEh");
                break;
>>>>>>> 41ab8ef74efd2b0fc19331d4f9819e105818250f
            }
        }
    }

    UnregisterHotKey(NULL, 1);
    UnregisterHotKey(NULL, 2);
    UnregisterHotKey(NULL, 3);
    return 0;
}

/*
compile using:
gcc main.c my.res -o AAAhotkey -mwindows

compile icon:
id ICON "path/to/my.ico"

*/
