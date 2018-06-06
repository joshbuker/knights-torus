#include "hal.hpp"
#include "common.hpp"

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

chrono::time_point<chrono::system_clock> start_time, end_time;

// Usage: color(BLUE);
void color(string color_code)
{
  cout << "\033[" << color_code << "m";
}

void start_watch()
{
  start_time = chrono::system_clock::now();
}

void stop_watch()
{
  end_time = chrono::system_clock::now();
}

long watch_time()
{
  chrono::duration<double> elapsed_seconds = end_time-start_time;
  return (long)(elapsed_seconds.count()*1000);
}

void play_beep()
{
  cout << "\007";
}

void set_cursor_pos()
{
  cout << "\033[s"; // Save position
  color(LIGHT_GRAY);
}

void reset_cursor()
{
  cout << "\033[u"; // Restore Position
}

void print_progress()
{
  reset_cursor();
  color(LIGHT_GRAY);
  cout << "\rTotal Moves: ";
  color(WHITE);
  cout << max_moves << endl;
  color(LIGHT_GRAY);
  cout << "\rCurrent Move: ";
  color(LIGHT_GREEN);
  cout << solution.size() << endl;
  if(total_failed_moves > 0)
  {
    cout << endl;
    color(LIGHT_GRAY);
    cout << "\r# Total Failed Moves: ";
    color(LIGHT_RED);
    cout << total_failed_moves << endl;
    color(LIGHT_GRAY);
    cout << "\r# Current Failed Moves: ";
    color(LIGHT_RED);
    cout << failed_moves.size() << endl;
    color(LIGHT_GRAY);
    cout << "\r# Critical Points Remaining: ";
    color(WHITE);
    cout << critical_points.size() << endl;
  }
  color(LIGHT_GRAY);
}
