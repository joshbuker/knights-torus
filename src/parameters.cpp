#include "parameters.hpp"

using namespace std;

unordered_map<string, int> parse_arguments(int argc, char *argv[])
{
  unordered_map<string, int> params;
  // TODO: Refactor to use flags
  if(argc!=5)
  {
    cout << "This application requires exactly 4 arguments!" << endl;
    cout << "You supplied: ";
    cout << argc-1;
    cout << " arguments." << endl;
    params.clear();
    return params;
  }

  istringstream ssX(argv[1]);
  istringstream ssY(argv[2]);
  istringstream ssW(argv[3]);
  istringstream ssH(argv[4]);

  int x, y, width, height;

  if (!(ssX >> x))
  {
    cout << "Invalid number ";
    cout << argv[1] << endl;
    params.clear();
    return params;
  }
  if (!(ssY >> y))
  {
    cout << "Invalid number ";
    cout << argv[2] << endl;
    params.clear();
    return params;
  }
  if (!(ssW >> width))
  {
    cout << "Invalid number ";
    cout << argv[3] << endl;
    params.clear();
    return params;
  }
  if (!(ssH >> height))
  {
    cout << "Invalid number ";
    cout << argv[4] << endl;
    params.clear();
    return params;
  }
  if(x < 1 || x > width)
  {
    cout << "Starting X position was invalid: ";
    cout << x << endl;
    params.clear();
    return params;
  }
  if(y < 1 || y > height)
  {
    cout << "Starting Y position was invalid: ";
    cout << y << endl;
    params.clear();
    return params;
  }
  if(width < 3)
  {
    cout << "Board width was too small: ";
    cout << width << endl;
    params.clear();
    return params;
  }
  if(height < 3)
  {
    cout << "Board height was too small: ";
    cout << height << endl;
    params.clear();
    return params;
  }

  params["x"] = x;
  params["y"] = y;
  params["width"] = width;
  params["height"] = height;
  return params;
}
