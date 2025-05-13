#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "lib/cJSON.h"

#define LONG_LIVED_ACCESS_TOKEN = eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiI3ZDAwNGRiMWRjZTU0Yzg1YmIzM2JiMTFmZTkyMGM4YSIsImlhdCI6MTc0NjExNzI1MiwiZXhwIjoyMDYxNDc3MjUyfQ.K_OI7EAvliHJMx6TA_9FRudMzZkcxZQeRs523KROoH0

typedef struct
{
    char first_key[8];
    char second_key[8];
    char third_key;
    char command[10];
    char modifier[300];

} Hotkey;

int main()
{

    FILE *file;
    // fopen returns a pointer to  a file
    file = fopen("config.txt", "r");

    if (file == NULL)
    {
        printf("Error opening file");
        return 1;
    }

    Hotkey hotkeys[100];

    // used to verify that the correct number of values where read from each line
    int read = 0;

    // keeps track of number of hotkey combinations
    int combo_number = 0;

    do
    {
        // fscanf returns numbers of read values
        read = fscanf(file, "%8[^,],%8[^,],%c,%10[^,],%100[^\n]",
                      hotkeys[combo_number].first_key,
                      hotkeys[combo_number].second_key,
                      &hotkeys[combo_number].third_key,
                      hotkeys[combo_number].command,
                      hotkeys[combo_number].modifier);

        if (read == 5)
        {
            combo_number++;
        }
        if (read != 5 && !feof(file))
        {
            printf("File formatting issue");
            return 1;
        }

        // feof returns true if end of file is reached
    } while (!feof(file));

    fclose(file);

    for (int i = 0; i < combo_number; i++)
    {
        printf("%s, %s, %c, %s, %s\n",
               hotkeys[i].first_key,
               hotkeys[i].second_key,
               hotkeys[i].third_key,
               hotkeys[i].command,
               hotkeys[i].modifier);
    }
    getchar();

    /* the function inside the if clause is executed using the parameters, it returns 0 if it executed succesfully
    NULL beceause there is no window id that the message is sent back to
    1 is an id to reference this hotkey inside the programm */
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
    if (!RegisterHotKey(NULL, 4, MOD_CONTROL | MOD_ALT, 0x50))
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
                ShellExecute(NULL, "open", "http://homeassistant.local:8123/config/hardware", NULL, NULL, SW_SHOWNORMAL);
                break;
            case 2:
                ShellExecute(NULL, "open", "notepad.exe", NULL, NULL, SW_SHOWNORMAL);
                ShellExecute(NULL, "open", "chrome.exe", "--new-window https://github.com/JulianKep?tab=repositories", NULL, SW_SHOWNORMAL);

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
                system("curl -X POST -H \"Authorization: Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiI3ZDAwNGRiMWRjZTU0Yzg1YmIzM2JiMTFmZTkyMGM4YSIsImlhdCI6MTc0NjExNzI1MiwiZXhwIjoyMDYxNDc3MjUyfQ.K_OI7EAvliHJMx6TA_9FRudMzZkcxZQeRs523KROoH0\" http://homeassistant.local:8123/api/webhook/-6QDwsBUTH2duVkWPiaNwfdEh");
                break;
            case 4:
                ShellExecute(NULL, "open", "C:\\Users\\root\\Meine Ablage\\DOKUMENTE\\pass.txt", NULL, NULL, SW_SHOWNORMAL);
                break;
            }
        }
    }

    UnregisterHotKey(NULL, 1);
    UnregisterHotKey(NULL, 2);
    UnregisterHotKey(NULL, 3);
    UnregisterHotKey(NULL, 4);
    return 0;
}

/*
compile using:
gcc main.c lib/cJSON.c my.res -o AAAhotkey -mwindows

compile icon:
id ICON "path/to/my.ico"

*/
