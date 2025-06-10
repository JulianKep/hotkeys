#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "lib/cJSON.h"

#define LONG_LIVED_ACCESS_TOKEN = eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiI3ZDAwNGRiMWRjZTU0Yzg1YmIzM2JiMTFmZTkyMGM4YSIsImlhdCI6MTc0NjExNzI1MiwiZXhwIjoyMDYxNDc3MjUyfQ.K_OI7EAvliHJMx6TA_9FRudMzZkcxZQeRs523KROoH0
#define NUM_OF_HOTKEYS 5


int main()
{

    /* the function inside the if clause is executed using the parameters, it returns 0 if it executed succesfully
    NULL beceause there is no window id that the message is sent back to
    1 is an id to reference this hotkey inside the programm */
    RegisterHotKey(NULL, 1, MOD_CONTROL | MOD_ALT, 0x48);
    RegisterHotKey(NULL, 2, MOD_CONTROL | MOD_ALT, 0x4E);
    RegisterHotKey(NULL, 3, MOD_CONTROL | MOD_ALT, 0x4C);
    RegisterHotKey(NULL, 4, MOD_CONTROL | MOD_ALT, 0x50);
    RegisterHotKey(NULL, 5, MOD_CONTROL | MOD_ALT, 0x4D);
    RegisterHotKey(NULL, 6, MOD_CONTROL | MOD_ALT, 'W');

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
                // H
                ShellExecute(NULL, "open", "http://homeassistant.local:8123/config/hardware", NULL, NULL, SW_SHOWNORMAL);
                break;
            case 2:
                // N
                ShellExecute(NULL, "open", "notepad.exe", NULL, NULL, SW_SHOWNORMAL);
                /* ShellExecute(NULL, "open", "chrome.exe", "--new-window https://github.com/JulianKep?tab=repositories", NULL, SW_SHOWNORMAL); */

                Sleep(500);
                HWND notepad_window = FindWindow(NULL, "Unbenannt - Editor");
                if (notepad_window == NULL)
                {   
                    MessageBox(NULL, "Window not found", "Error", MB_OK);
                    return 1;
                }

                // position x, position y, size x, size y
                MoveWindow(notepad_window, 2560, 0, 600, 600, TRUE);

                break;
            case 3:
                // L
                system("curl -X POST -H \"Authorization: Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiI3ZDAwNGRiMWRjZTU0Yzg1YmIzM2JiMTFmZTkyMGM4YSIsImlhdCI6MTc0NjExNzI1MiwiZXhwIjoyMDYxNDc3MjUyfQ.K_OI7EAvliHJMx6TA_9FRudMzZkcxZQeRs523KROoH0\" http://homeassistant.local:8123/api/webhook/-6QDwsBUTH2duVkWPiaNwfdEh");
                break;
            case 4:
                // P
                ShellExecute(NULL, "open", "C:\\Users\\root\\Documents\\pass.md", NULL, NULL, SW_SHOW);
                break;
            case 5:
                // M
                ShellExecute(NULL, "open", "https://moodle.uni-mainz.de/my/courses.php", NULL, NULL, SW_SHOWNORMAL);
                break;
            case 6:
                // W
                
                ShellExecute(NULL, "open", "C:\\Program Files\\WindowsApps\\5319275A.WhatsAppDesktop_2.2522.2.0_x64__cv1g1gvanyjgm\\WhatsApp.exe", NULL, NULL, SW_SHOWNORMAL);

                Sleep(500);
                HWND whatsapp_window = FindWindow(NULL, "WhatsApp");
                if (whatsapp_window == NULL)
                {   
                    MessageBox(NULL, "Window not found", "Error", MB_OK);
                    return 1;
                }

                // position x, position y, size x, size y
                MoveWindow(whatsapp_window, 2560, 0, 1000, 600, TRUE);
                break;

            }
        }
    }

    for (int i = 1; i <= NUM_OF_HOTKEYS; i++)
    {
        UnregisterHotKey(NULL, i);
    }

    return 0;
}

/*
compile using:
gcc main.c lib/cJSON.c my.res -o AAAhotkey -mwindows

compile icon:
id ICON "path/to/my.ico"

*/
