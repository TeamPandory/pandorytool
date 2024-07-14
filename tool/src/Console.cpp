#include "Console.h"

void Console::enableEcho()
{
    // tcsetattr( 0, TCSANOW, &save );
}

void Console::disableEcho()
{
    /*
    struct termios term;
    tcgetattr( 0, &save );
    term = save;
    term.c_lflag &= (~ECHO);
    tcsetattr( 0, TCSANOW, &term );
     */
}
