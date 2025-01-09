#include <windows.h>

bool get_console_size(int& width, int& height)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (hConsole == INVALID_HANDLE_VALUE)
        return false;

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
        return false;

    width = csbi.srWindow.Right - csbi.srWindow.Left;
    height = csbi.srWindow.Bottom - csbi.srWindow.Top;

    return true;
}