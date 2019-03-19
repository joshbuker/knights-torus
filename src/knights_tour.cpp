#include "parameters.hpp"
#include "solver.hpp"
#include <unordered_map>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
  unordered_map<string, int> params = parse_arguments(argc, argv);
  if(params.empty()) return -1;
  return solve(params);
}
