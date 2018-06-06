#include "solver.hpp"
#include "hal.hpp"
#include "validator.hpp"

using namespace std;

int directions[8][2] =
{
  {1,2},
  {2,1},
  {2,-1},
  {1,-2},
  {-1,-2},
  {-2,-1},
  {-2,1},
  {-1,2}
};

std::vector< std::vector<int> > solution;
std::vector< std::vector<int> > failed_moves;
std::vector< std::vector<int> > critical_points;
std::vector< std::vector<int> > board_moves;
std::vector< std::vector<bool> > board_visited;

int board_width, board_height, max_moves;
int total_failed_moves, last_crit = 0;
bool escape = false;

int solve(unordered_map<string, int> params)
{
  int x, y, width, height;
  x = params["x"];
  y = params["y"];
  width = params["width"];
  height = params["height"];
  start_watch();
  set_cursor_pos();
  cout << "Calculating..." << endl;
  solve(x, y, width, height);
  stop_watch();
  print_results();
  int return_value = save_results();
  play_beep();
  return return_value;
}

void solve(int x, int y, int width, int height)
{
  init_solution(x, y);
  resize_board(width, height);
  calculate_visited();
  calculate_moves();

  total_failed_moves = 0;

  while(!done())
  {
    move();
    // TODO: Allow modular progress reporting
    print_progress();
  }
}

void print_results()
{
  long running_time = watch_time();
  cout << endl;
  if(solution.empty())
  {
    cout << board_width;
    cout << "x";
    cout << board_height << endl;
    cout << "Total Running Time (Sec): ";
    cout << (running_time/1000) << endl;
    cout << "Total Running Time (MilliSec): ";
    cout << running_time << endl;
    cout << "Average Time per Move (MilliSec): N/A" << endl;
  }
  else
  {
    cout << board_width;
    cout << "x";
    cout << board_height << endl;
    cout << "Total Running Time (Sec): ";
    cout << (running_time/1000) << endl;
    cout << "Total Running Time (MilliSec): ";
    cout << running_time << endl;
    cout << "Average Time per Move (MilliSec): ";
    cout << (running_time/(long)solution.size()) << endl;
  }
}

int save_results()
{
  cout << "Verifying tour..." << endl;
  if(valid_tour(solution, board_width, board_height, false))
  {
    cout << "Success!" << endl;
    stringstream ss;
    ss << "Tour Solution "
       << board_width << "x" << board_height
       << ".txt";
    string tour_file_name = ss.str();
    save(tour_file_name);
    return 0;
  }
  else
  {
    cout << "Failed!" << endl;
    return -4;
  }
}

void save(string file_location)
{
  ofstream myfile (file_location.c_str());
  if(myfile.is_open())
  {
    for(unsigned int x=0;x<solution.size();x++)
    {
      myfile << "X: ";
      myfile << solution[x][0];
      myfile << "\tY: ";
      myfile << solution[x][1] << endl;
    }
    myfile.close();
  }
  else
  {
    cout << "Unable to open file: " << file_location << endl;
  }
}

void init_solution(int x, int y)
{
  vector<int> temp;
  temp.push_back(x);
  temp.push_back(y);
  solution.push_back(temp);
}

void resize_board(int width, int height)
{
  board_moves.resize(width);
  for(int x=0; x<width; x++)
  {
    board_moves[x].resize(height);
  }

  board_visited.resize(width);
  for(int x=0; x<width; x++)
  {
    board_visited[x].resize(height);
  }

  board_width = width;
  board_height = height;
  max_moves = width * height;
}

void calculate_visited()
{
  for(int x=1; x<=board_width; x++)
  {
    for(int y=1; y<=board_height; y++)
    {
      calculate_visited(x, y);
    }
  }
}

void calculate_visited(int x, int y)
{
  // NOTE: Easier to assume top left of the board is 1,1 instead of 0,0
  board_visited[x-1][y-1] = visited(x, y);
}

bool visited(int x, int y)
{
  // NOTE: Assume visited if outside bounds of the board
  if(out_of_bounds(x, y))
    return true;
  // NOTE: Cache size to improve performance
  unsigned int solution_size = solution.size();
  for(unsigned int move=0; move<solution_size; move++)
  {
    if(x==solution[move][0] && y==solution[move][1])
      return true;
  }
  return false;
}

bool visited(int x, int y, int move)
{
  if(visited(x, y))
    return true;
  unsigned int failed_moves_size = failed_moves.size();
  for(unsigned int i=0; i<failed_moves_size; i++)
  {
    // NOTE: Nesting the if statements saves performance by returning early if a
    // condition isn't met.
    if(move==failed_moves[i][0])
      if(x==failed_moves[i][1] && y==failed_moves[i][2])
        if(solution.back()[0]==failed_moves[i][3] && solution.back()[1]==failed_moves[i][4])
          return true; // Deja vu! I've just been in this place before!
  }
  return false;
}

bool out_of_bounds(int x, int y)
{
  if(x<1 || x>board_width || y<1 || y>board_height)
    return true;
  else
    return false;
}

void calculate_moves()
{
  // NOTE: Calculate remaining moves for entire board
  for(int x=1; x<=board_width; x++)
  {
    for(int y=1; y<=board_height; y++)
    {
      calculate_pos(x, y);
    }
  }
}

void calculate_moves(int x, int y)
{
  // NOTE: Input is a position that was just visited
  // calculates only positions that have been affected by the change
  int affected_x, affected_y;
  for(int dir=0; dir<8; dir++)
  {
    affected_x = x+directions[dir][0];
    affected_y = y+directions[dir][1];
    calculate_pos(affected_x, affected_y);
  }
}

void calculate_pos(int x, int y)
{
  if(out_of_bounds(x, y))
    return;
  int count = 0;
  for(int dir=0; dir<8; dir++)
  {
    // NOTE: Use cache to improve performance of lookups
    if(!visited_cache(x+directions[dir][0], y+directions[dir][1]))
      count++;
  }
  board_moves[x-1][y-1] = count;
}

bool visited_cache(int x, int y)
{
  if(out_of_bounds(x, y))
    return true;
  else
    return board_visited[x-1][y-1];
}

bool done()
{
  if(escape || solution.empty())
    return true;
  // TODO: Try the following to improve performance on larger boards...
  /*
  if(current_move == max_moves)
    return true;
  else
    return false;
  */
  for(int x=1; x<=board_width; x++)
  {
    for(int y=1; y<=board_height; y++)
    {
      if(board_moves[x-1][y-1]>0)
        return false;
    }
  }
  return true;
}

void move()
{
  position current_position = current_pos();
  vector< vector<int> > possible_moves = get_possible_moves(
    current_position.x,
    current_position.y
  );
  vector<int> temp;

  if(!possible_moves.empty())
  {
    if(possible_moves.size()==1)
    {
      temp.resize(2);
      temp[0] = possible_moves[0][1];
      temp[1] = possible_moves[0][2];
      solution.push_back(temp);
      board_visited[temp[0]-1][temp[1]-1] = true;
    }
    else
    {
      // NOTE: Sort possible moves from lowest to highest
      for(unsigned int x=0; x<=possible_moves.size(); x++)
      {
        for(int y=possible_moves.size()-1; y>0; y--)
        {
          if(possible_moves[y-1][0]>possible_moves[y][0])
            swap(possible_moves.at(y-1), possible_moves.at(y));
        }
      }
      // NOTE: Add critical points if they haven't failed previously
      if(failed_moves.empty())
      {
        temp.resize(3);
        for(int x=1; x<possible_moves.size(); x++)
        {
          if(possible_moves[x-1][0]==possible_moves[x][0])
          {
            temp[0] = solution.size();
            temp[1] = possible_moves[x][1];
            temp[2] = possible_moves[x][2];
            critical_points.push_back(temp);
          }
          // TODO: Redundant break, remove?
          else
            break;
        }
      }
      // NOTE: Add move with lowest possible options per Warnsdorf's rule
      temp.resize(2);
      temp[0] = possible_moves[0][1];
      temp[1] = possible_moves[0][2];
      solution.push_back(temp);
      board_visited[temp[0]-1][temp[1]-1] = true;
    }
  }
  else
  {
    if(done())
      return;
    else
    {
      if(solution.empty())
        escape = true;
      else
        back_up();
    }
  }
}

position current_pos()
{
  position temp;
  vector<int> last_move = solution.back();
  temp.x = last_move[0];
  temp.y = last_move[1];
  return temp;
}

vector< vector<int> > get_possible_moves(int x, int y)
{
  calculate_moves(x, y);
  vector< vector<int> > possible_moves;
  vector<int> temp;
  temp.resize(3);
  int possible_x;
  int possible_y;
  int next_move = solution.size()+1;
  for(int dir=0; dir<8; dir++)
  {
    possible_x = x+directions[dir][0];
    possible_y = y+directions[dir][1];

    if(!visited(possible_x, possible_y, next_move))
    {
      temp[0] = board_moves[possible_x-1][possible_y-1];
      temp[1] = possible_x;
      temp[2] = possible_y;
      possible_moves.push_back(temp);
    }
  }
  return possible_moves;
}

void back_up()
{
  if(solution.empty() || critical_points.empty())
  {
    escape = true;
    return;
  }
  int x, y; // To be used for easy position references
  if(last_crit==0)
    last_crit = critical_points.back()[0];
  // NOTE: Rollback to the failing move
  while(solution.size()>critical_points.back()[0]+1)
  {
    x = solution.back()[0];
    y = solution.back()[1];
    solution.pop_back();
    board_visited[x-1][y-1] = false;
    calculate_moves(x, y);
  }
  // NOTE: If this is a new critical point, reset failed moves
  if(last_crit!=critical_points.back()[0])
  {
    failed_moves.clear();
    last_crit = critical_points.back()[0];
  }
  // NOTE: Add current move to failed list
  vector<int> temp;
  temp.resize(5);
  temp[0] = solution.size();
  temp[1] = solution.back()[0];
  temp[2] = solution.back()[1];
  // TODO: If solution isn't >=2, should this return early?
  if(solution.size()>1)
  {
    temp[3] = solution[solution.size()-2][0];
    temp[4] = solution[solution.size()-2][1];
  }
  else
  {
    temp[3] = 0;
    temp[4] = 0;
  }
  failed_moves.push_back(temp);
  total_failed_moves++;
  x = solution.back()[0];
  y = solution.back()[1];
  solution.pop_back();
  board_visited[x-1][y-1] = false;
  calculate_moves(x, y);

  temp.resize(2);
  temp[0] = critical_points.back()[1];
  temp[1] = critical_points.back()[2];
  solution.push_back(temp);
  board_visited[temp[0]-1][temp[1]-1] = true;
  critical_points.pop_back();
}
