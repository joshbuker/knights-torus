#include <Windows.h>
#include <time.h>
#include <conio.h>
#include "hal.hpp"

using namespace std;

int mouseX,mouseY;
clock_t begin,end;

void startWatch()
{
  begin = clock();
}

void stopWatch()
{
  end = clock();
}

long watchTime()
{
  return (end-begin);
}

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

void setCursorPos()
{
  CurPos mousePos = getCursorPos();
  mouseX = mousePos.x;
  mouseY = mousePos.y;
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

void printProgress(int totalMoves, int currentMove, int failedMoves)
{
  gotoxy(mouseX,mouseY);
  cout << "Total Moves: ";
  cout << totalMoves << endl;
  cout << "Current Move: ";
  cout << currentMove << endl;
  /*for(int x=0;x<boardWidth;x++)
  {
    for(int y=0;y<boardHeight;y++)
    {
      cout << boardMoves[x][y];
      cout << " ";
    }
    cout << endl;
  }*/
  if(failedMoves > 0)
  {
    cout << endl;
    cout << "# Failed Moves: ";
    cout << failedMoves << endl;
  }
}
