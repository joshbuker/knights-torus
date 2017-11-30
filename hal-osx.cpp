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

chrono::time_point<chrono::system_clock> startTime,endTime;

// Usage: color(BLUE);
void color(string colorCode)
{
  cout << "\033[" << colorCode << "m";
}

void startWatch()
{
  startTime = chrono::system_clock::now();
}

void stopWatch()
{
  endTime = chrono::system_clock::now();
}

long watchTime()
{
  chrono::duration<double> elapsed_seconds = endTime-startTime;
  return (long)(elapsed_seconds.count()*1000);
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

void printProgress(const int & totalMoves, const int & currentMove, const int & totalFailedMoves, const int & currentFailedMoves, const int & criticalPointsRemaining)
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
  if(totalFailedMoves > 0)
  {
    cout << endl;
    color(LIGHT_GRAY);
    cout << "\r# Total Failed Moves: ";
    color(LIGHT_RED);
    cout << totalFailedMoves << endl;
    color(LIGHT_GRAY);
    cout << "\r# Current Failed Moves: ";
    color(LIGHT_RED);
    cout << currentFailedMoves << endl;
    color(LIGHT_GRAY);
    cout << "\r# Critical Points Remaining: ";
    color(WHITE);
    cout << criticalPointsRemaining << endl;
  }
  color(LIGHT_GRAY);
}
