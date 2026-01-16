#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <iostream>
#include <windows.h>
#include "Console.h"
#undef byte

void Console::DisableResize()
{
    HWND hwnd = GetConsoleWindow();
    LONG style = GetWindowLong(hwnd, GWL_STYLE);
    style &= ~WS_SIZEBOX;
    style &= ~WS_MAXIMIZEBOX;
    SetWindowLong(hwnd, GWL_STYLE, style);
}

void Console::LockConsoleBuffer(short width, short height)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD bufferSize = { width, height };
    SetConsoleScreenBufferSize(hOut, bufferSize);

    SMALL_RECT windowSize = { 0, 0, width - 1, height - 1 };
    SetConsoleWindowInfo(hOut, TRUE, &windowSize);
}

void Console::InitUtf8()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void Console::SleepMs(int ms)
{
    Sleep(ms);
}

void Console::Clear()
{
    system("cls");
}
