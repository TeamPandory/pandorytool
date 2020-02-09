#include "ConsoleColour.h"
#if defined(WIN32)
#include <windows.h>
#endif

void ConsoleColour::setConsoleColour(int textcol, int backcol) {
#if defined(WIN32)
    if ((textcol % 16) == (backcol % 16))textcol++;
    textcol %= 16; backcol %= 16;
    unsigned short wAttributes = ((unsigned)backcol << 4) | (unsigned)textcol;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    SetConsoleTextAttribute(hStdOut, wAttributes);
#endif
}
