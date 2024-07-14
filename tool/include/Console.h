#pragma once

class Console
{
  protected:
    // struct termios save;
  public:
    void enableEcho();
    void disableEcho();
};