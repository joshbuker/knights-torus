#include "common.hpp"
#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#ifndef SOLVER_HPP
#define SOLVER_HPP
void back_up();
void calculate_moves();
void calculate_moves(int x, int y);
void calculate_pos(int x, int y);
void calculate_visited();
void calculate_visited(int x, int y);
position current_pos();
bool done();
std::vector< std::vector<int> > get_possible_moves(int x, int y);
void init_solution(int x, int y);
void move();
bool out_of_bounds(int x, int y);
void print_results();
void resize_board(int width, int height);
void save(std::string file_location);
int save_results();
int solve(std::unordered_map<std::string, int> params);
void solve(int x, int y, int width, int height);
bool visited(int x, int y);
bool visited(int x, int y, int move);
bool visited_cache(int x, int y);
#endif
