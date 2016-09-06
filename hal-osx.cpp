#include <iostream>
#include "hal.hpp"

using namespace std;

// Define terminal colors
#define BLACK "0;30"
#define WHITE "1;37"
#define YELLOW "1;33"
#define BLUE "0;34"
#define GREEN "0;32"
#define CYAN "0;36"
#define RED "0;31"
#define PURPLE "0;35"
#define BROWN "0;33"
#define DARK_GRAY "1;30"
#define LIGHT_GRAY "0;37"
#define LIGHT_BLUE "1;34"
#define LIGHT_GREEN "1;32"
#define LIGHT_CYAN "1;36"
#define LIGHT_RED "1;31"
#define LIGHT_PURPLE "1;35"

// Usage: color(BLUE);
void color(string colorCode)
{
  cout << "\033[" << colorCode << "m";
}

void playBeep()
{
  cout << "\007";
}

void setCursorPos()
{
  cout << "\033[s"; // Save position
  color(LIGHT_GRAY);
}

void resetCursor()
{
  cout << "\033[u"; // Restore Position
}

void printProgress(int totalMoves, int currentMove, int failedMoves)
{
  resetCursor();
  color(LIGHT_GRAY);
  cout << "\rTotal Moves: ";
  color(WHITE);
  cout << totalMoves << endl;
  color(LIGHT_GRAY);
  cout << "\rCurrent Move: ";
  color(LIGHT_GREEN);
  cout << currentMove << endl;
  if(failedMoves > 0)
  {
    cout << endl;
    color(LIGHT_GRAY);
    cout << "\r# Failed Moves: ";
    color(LIGHT_RED);
    cout << failedMoves << endl;
  }
  color(LIGHT_GRAY);
}
