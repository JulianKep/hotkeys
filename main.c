#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "lib/cJSON.h"

#define LONG_LIVED_ACCESS_TOKEN = eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiI3ZDAwNGRiMWRjZTU0Yzg1YmIzM2JiMTFmZTkyMGM4YSIsImlhdCI6MTc0NjExNzI1MiwiZXhwIjoyMDYxNDc3MjUyfQ.K_OI7EAvliHJMx6TA_9FRudMzZkcxZQeRs523KROoH0




int parse_config(char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Unable to open file");
        return 1;
    }

    // Determine file size
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the file content
    char *data = (char *)malloc(length + 1);
    if (data == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return 1;
    }

    // Read the file into memory
    fread(data, 1, length, file);
    data[length] = '\0';  // Null-terminate the string
    fclose(file);

    // Parse the JSON data
    cJSON *json = cJSON_Parse(data);
    if (json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        free(data);
        return 1;
    }

    // Extract and print the "name" field
    cJSON *name = cJSON_GetObjectItemCaseSensitive(json, "name");
    if (cJSON_IsString(name) && (name->valuestring != NULL)) {
        printf("Name: %s\n", name->valuestring);
    }


}


int main()
{
    char *filename = "config.json";

    parse_config(filename);

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
            case 1:
                ShellExecute(NULL, "open", "http://homeassistant.local:8123/config/hardware", NULL, NULL, SW_SHOWNORMAL);
                break;
            case 2:
                ShellExecute(NULL, "open", "notepad.exe", NULL, NULL, SW_SHOWNORMAL);
                break;
            case 3:
                system("curl -X POST -H \"Authorization: Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiI3ZDAwNGRiMWRjZTU0Yzg1YmIzM2JiMTFmZTkyMGM4YSIsImlhdCI6MTc0NjExNzI1MiwiZXhwIjoyMDYxNDc3MjUyfQ.K_OI7EAvliHJMx6TA_9FRudMzZkcxZQeRs523KROoH0\" http://homeassistant.local:8123/api/webhook/-6QDwsBUTH2duVkWPiaNwfdEh");
                break;
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
gcc main.c lib/cJSON.c my.res -o AAAhotkey -mwindows

compile icon:
id ICON "path/to/my.ico"

*/
