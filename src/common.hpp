#include <vector>

#ifndef COMMON_HPP
#define COMMON_HPP
// Define globals
struct position {
  int x;
  int y;
};

// Store solution
extern std::vector< std::vector<int> > solution;
extern std::vector< std::vector<int> > failed_moves;
extern std::vector< std::vector<int> > critical_points;
extern std::vector< std::vector<int> > board_moves;
extern std::vector< std::vector<bool> > board_visited;

extern int board_width, board_height, max_moves;
extern int total_failed_moves;
#endif
