#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <iostream>
#include <windows.h>
#include "Console.h"
#undef byte

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
