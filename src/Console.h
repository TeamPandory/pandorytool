#ifndef PANDORY_CONSOLE_H
#define PANDORY_CONSOLE_H


//#include <termios.h>

class Console {
protected:
    //struct termios save;
public:
    void enableEcho();
    void disableEcho();
};


#endif //PANDORY_CONSOLE_H
