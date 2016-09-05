// #ifdef defined _WIN32 || defined _WIN64 || defined WINDOWS
#include <Windows.h>
#include <conio.h>
#include "hal.hpp"

void playBeep()
{
  Beep(261,1000);
}

struct CurPos
{
  CurPos():x(-1),y(-1) {}
  int x, y;
  operator bool() const { return x >= 0 && y >= 0; }
};

CurPos getCursorPos()
{
  CurPos pos;
  CONSOLE_SCREEN_BUFFER_INFO con;
  HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
  if (hcon != INVALID_HANDLE_VALUE &&
      GetConsoleScreenBufferInfo(hcon,&con))
  {
    pos.x = con.dwCursorPosition.X;
    pos.y = con.dwCursorPosition.Y;
  }
  return pos;
}

void gotoxy( int column, int line )
{
  COORD coord;
  coord.X = column;
  coord.Y = line;

  SetConsoleCursorPosition(
    GetStdHandle( STD_OUTPUT_HANDLE ),
    coord
  );
}

void printProgress()
{
  gotoxy(mouseX,mouseY);
  cout << "Total Moves: ";
  cout << maxMoves << endl;
  cout << "Current Move: ";
  cout << solution.size() << endl;
  /*for(int x=0;x<boardWidth;x++)
  {
    for(int y=0;y<boardHeight;y++)
    {
      cout << boardMoves[x][y];
      cout << " ";
    }
    cout << endl;
  }*/
  if(!failedMoves.empty())
  {
    cout << endl;
    cout << "# Failed Moves: ";
    cout << failedMoves.size() << endl;
  }
}
// #endif
