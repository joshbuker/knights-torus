#include "validator.hpp"

using namespace std;

// Will ensure that provided solution is a real solution (completely foolproof assuming the user doesn't intentionally fudge width/height)
bool valid_tour(vector< vector<int> > solution, int width, int height, bool from_zero)
{
  const int dirs[8][2] =
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
  // If the amount of moves isn't correct.
  if(solution.size()!=(width*height))
  {
    cout << "Wrong Number of Moves" << endl;
    return false;
  }
  // If any moves are out of bounds
  if(from_zero)
  {
    for(unsigned int x=0;x<solution.size();x++)
    {
      if(solution[x][0]<0 || solution[x][1]<0 || solution[x][0]>=width || solution[x][1]>=height)
      {
        cout << "Move Out of Bounds" << endl;
        return false;
      }
    }
  }
  else
  {
    for(unsigned int x=0;x<solution.size();x++)
    {
      if(solution[x][0]<1 || solution[x][1]<1 || solution[x][0]>width || solution[x][1]>height)
      {
        cout << "Move Out of Bounds" << endl;
        return false;
      }
    }
  }
  // If any moves are duplicated
  for(unsigned int x=0;x<solution.size()-1;x++)
  {
    for(unsigned int y=x+1;y<solution.size();y++)
    {
      if(solution[x][0]==solution[y][0] && solution[x][1]==solution[y][1])
      {
        cout << "Duplicate Move" << endl;
        return false;
      }
    }
  }

  // If any move is not a valid Knight's Move
  for(unsigned int x=0;x<solution.size()-1;x++)
  {
    bool isValidMove = false;
    for(int y=0;y<8;y++)
    {
      if(solution[x][0]+dirs[y][0]==solution[x+1][0] && solution[x][1]+dirs[y][1]==solution[x+1][1])
      {
        isValidMove = true;
        break;
      }
    }
    if(!isValidMove)
    {
      cout << "Invalid Move" << endl;
      return false;
    }
  }
  return true;
}
