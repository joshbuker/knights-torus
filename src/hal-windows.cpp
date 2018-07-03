#include "hal.hpp"
#include "common.hpp"
#include <Windows.h>
#include <ctime>

using namespace std;

int mouse_x, mouse_y;
clock_t start_time, end_time;

void start_watch()
{
  start_time = clock();
}

void stop_watch()
{
  end_time = clock();
}

long watch_time()
{
  return (end_time-start_time);
}

void play_beep()
{
  Beep(261,1000);
}

struct CurPos
{
  CurPos():x(-1),y(-1) {}
  int x, y;
  operator bool() const { return x >= 0 && y >= 0; }
};

CurPos get_cursor_pos()
{
  CurPos pos;
  CONSOLE_SCREEN_BUFFER_INFO con;
  HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
  if (hcon != INVALID_HANDLE_VALUE && GetConsoleScreenBufferInfo(hcon,&con))
  {
    pos.x = con.dwCursorPosition.X;
    pos.y = con.dwCursorPosition.Y;
  }
  return pos;
}

void set_cursor_pos()
{
  CurPos mouse_pos = get_cursor_pos();
  mouse_x = mouse_pos.x;
  mouse_y = mouse_pos.y;
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

void print_backup_progress()
{
  cout << endl;
  cout << "# Total Failed Moves: ";
  cout << total_failed_moves << endl;
  cout << "# Current Failed Moves: ";
  cout << failed_moves.size() << endl;
  cout << "# Critical Points Remaining: ";
  cout << critical_points.size() << endl;
}

void print_progress()
{
  gotoxy(mouse_x,mouse_y);
  cout << "Total Moves: ";
  cout << max_moves << endl;
  cout << "Current Move: ";
  cout << solution.size() << endl;
  if(total_failed_moves > 0)
    print_backup_progress();
}
