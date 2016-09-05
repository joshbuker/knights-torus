// #ifdef defined __APPLE__ || defined __MACH__ || defined OSX
#include <curses.h>
#include <iostream>
#include "hal.hpp"

using namespace std;

void playBeep()
{
  cout << "\007";
}

void setCursorPos(int& x, int& y)
{
  x = 0;
  y = 0;
}

void printProgress()
{
  // I'm afraid I can't let you do that, Mac.
}
// #endif
