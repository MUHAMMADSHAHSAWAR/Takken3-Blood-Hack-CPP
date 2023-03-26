// Created by Muhamamd Shahsawar.
// Company: Muhammad Technology.

#include <Windows.h>
#include <iostream>

#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "user32.lib")

bool ReadValue(HANDLE hHandle)
{
    DWORD dAddress = 0x0066D5E0;
    DWORD dAddress1 = 0x006606F6;
    short nBlood;
    SIZE_T bytesRead;
    ReadProcessMemory(hHandle, (LPVOID)dAddress, &nBlood, sizeof(nBlood), &bytesRead);

    if (nBlood < 152)
    {
        return true;
    }

    ReadProcessMemory(hHandle, (LPVOID)dAddress1, &nBlood, sizeof(nBlood), &bytesRead);

    if (nBlood < 152)
    {
        return true;
    }

    return nBlood;
}

void WriteValue(HANDLE hHandle)
{
    DWORD dAddress = 0x0066D5E0;
    DWORD dAddress1 = 0x006606F6;
    int nBlood = 152;
    SIZE_T bytesRead;
    WriteProcessMemory(hHandle, (LPVOID)dAddress, &nBlood, sizeof(nBlood), &bytesRead);
    WriteProcessMemory(hHandle, (LPVOID)dAddress1, &nBlood, sizeof(nBlood), &bytesRead);
}

bool bUnlimitedBlood = false;
HANDLE hHandle;

void Conditions()
{
    while (true)
    {
        if (GetAsyncKeyState(VK_SPACE))
        {
            if (!bUnlimitedBlood)
            {
                bUnlimitedBlood = true;
                MessageBeep(MB_OKCANCEL);

                HWND windowHandle = FindWindowA("EPSX", "ePSXe - Enhanced PSX emulator");
                // std::cout << "WindowHandle: " << windowHandle << std::endl;

                DWORD processID;
                GetWindowThreadProcessId(windowHandle, &processID);
                // std::cout << "ProcessID: " << processID << std::endl;

                hHandle = OpenProcess(PROCESS_ALL_ACCESS, false, processID);
            }
        }
        else if (GetAsyncKeyState(VK_RETURN))
        {
            if (bUnlimitedBlood)
            {
                bUnlimitedBlood = false;
                MessageBeep(MB_RETRYCANCEL);
            }
        }

        Sleep(100);
    }
}

int main()
{
    HWND consoleWindow = GetConsoleWindow();
    SetWindowTextA(consoleWindow, "Takken 3 Hack by Muhammad Technology");

    HWND windowHandle = FindWindowA("EPSX", "ePSXe - Enhanced PSX emulator");
    // std::cout << "WindowHandle: " << windowHandle << std::endl;

    DWORD processID;
    GetWindowThreadProcessId(windowHandle, &processID);
    // std::cout << "ProcessID: " << processID << std::endl;

    hHandle = OpenProcess(PROCESS_ALL_ACCESS, false, processID);

    std::cout << "Hack Started...." << std::endl
              << "Press SPACE to apply hack and Press ENTER to stop hack." << std::endl;

    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Conditions, NULL, 0, 0);

    while (true)
    {
        if (bUnlimitedBlood)
        {
            if (ReadValue(hHandle))
            {
                WriteValue(hHandle);
            }
        }

        Sleep(100);
    }

    CloseHandle(hHandle);

    return 0;
}
