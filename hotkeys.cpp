#include <windows.h>
#include <iostream>

HHOOK hHook = NULL;


//LRESULT is a long in Windows
//CALLBACK is a calling convention
//WPARAM unsigned integer
//LPARAM long pointer sized value
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode == HC_ACTION)
    {
        KBDLLHOOKSTRUCT* pKeyboard = (KBDLLHOOKSTRUCT*)lParam;
        
        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)
        {
            // Check if Ctrl + Alt + H is pressed
            bool ctrlDown = (GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0;
            bool altDown = (GetAsyncKeyState(VK_MENU) & 0x8000) != 0;

            if (ctrlDown && altDown && pKeyboard->vkCode == 'H')
            {
                std::cout << "Hotkey Ctrl+Alt+H pressed!" << std::endl;
            }
        }
    }

    return CallNextHookEx(hHook, nCode, wParam, lParam);
}




int main()
{
    // Set the hook
    hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);

    if (hHook == NULL)
    {
        std::cout << "Failed to install hook!" << std::endl;
        return 1;
    }
    else
    {
        std::cout << "Hook installed. Press Ctrl+Alt+H..." << std::endl;
    }

    // Message loop to keep the application running
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Unhook before exit
    UnhookWindowsHookEx(hHook);

    return 0;
}
