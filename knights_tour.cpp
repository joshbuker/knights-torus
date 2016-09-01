#include <vector>
#include <time.h>
#include <math.h>
// IMPORT ALLLLL THE STREAMS
#include <iostream>
#include <fstream>
#include <sstream>
// Platform Specific Includes
#ifdef defined __linux__
// Linux Headers
#error "Linux not supported (yet)"
// End Linux Headers
#elif defined __APPLE__ || defined __MACH__
// Mac OS X Headers
#include <curses.h>
#ifndef POSIX
#define POSIX
#endif
// End Mac OS X Headers
#elif defined _WIN32 || defined _WIN64
// Windows Headers
#include <Windows.h>
#include <conio.h>
#ifndef WINDOWS
#define WINDOWS
#endif
// End Windows Headers
#else
#error "Unknown Platform"
#endif

// I'm lazy
using namespace std;

// Define globals
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

// Store solution
vector< vector<int> > solution;
vector< vector<int> > failedMoves;
vector< vector<int> > multipleMoves;
vector< vector<int> > boardMoves;
vector< vector<bool> > boardVisited;

int boardWidth,boardHeight,currentMove,maxMoves;
int mouseX,mouseY;
bool escape = false;

bool done()
{
	if(escape||solution.size()==0)
	{
		return true;
	}
	for(int x=0;x<boardWidth;x++)
	{
		for(int y=0;y<boardHeight;y++)
		{
			if(boardMoves[x][y]>0)
			{
				return false;
			}
		}
	}
	return true;
}

bool visited(int x,int y)
{
	if(x<1 || x>boardWidth || y<1 || y>boardHeight)
	{
		return true;
	}
	for(unsigned int z=0;z<solution.size();z++)
	{
		if(x==solution[z][0] && y==solution[z][1])
		{
			return true;
		}
	}
	return false;
}

bool visited(int x,int y,int move)
{
	if(x<1 || x>boardWidth || y<1 || y>boardHeight)
	{
		return true;
	}
	for(unsigned int z=0;z<solution.size();z++)
	{
		if(x==solution[z][0] && y==solution[z][1])
		{
			return true;
		}
	}
	for(unsigned int z=0;z<failedMoves.size();z++)
	{
		if(move==failedMoves[z][0])
		{
			if(x==failedMoves[z][1] && y==failedMoves[z][2])
			{
				if(solution[solution.size()-1][0]==failedMoves[z][3] && solution[solution.size()-1][1]==failedMoves[z][4])
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool wasVisited(int x,int y)
{
	if(x<1 || x>boardWidth || y<1 || y>boardHeight)
		return true;
	else
	{
		return boardVisited[x-1][y-1];
	}
}

void calculatePos(int x,int y)
{
	if(x<1 || x>boardWidth || y<1 || y>boardHeight)
		return;
	int count=0;
	for(int z=0;z<8;z++)
	{
		if(!wasVisited(x+directions[z][0],y+directions[z][1]))
		{
			count++;
		}
	}
	boardMoves[x-1][y-1]=count;
}

void recalculateVisited()
{
	for(int x=1;x<=boardWidth;x++)
	{
		for(int y=1;y<=boardHeight;y++)
		{
			boardVisited[x-1][y-1]=visited(x,y);
		}
	}
}

void recalculateVisited(int x,int y)
{
	boardVisited[x-1][y-1]=visited(x,y);
}

void recalculateBoard()
{
	for(int x=1;x<=boardWidth;x++)
	{
		for(int y=1;y<=boardHeight;y++)
		{
			calculatePos(x,y);
		}
	}
}

void recalculateBoard(int x,int y)
{
	int tempX,tempY;
	for(int z=0;z<8;z++)
	{
		tempX=x+directions[z][0];
		tempY=y+directions[z][1];
		calculatePos(tempX,tempY);
	}
}

void backUp()
{
	vector<int> temp;
	temp.resize(5);
	temp[0]=solution.size();
	temp[1]=solution[solution.size()-1][0];
	temp[2]=solution[solution.size()-1][1];
	if(solution.size()>1)
	{
		temp[3]=solution[solution.size()-2][0];
		temp[4]=solution[solution.size()-2][1];
	}
	failedMoves.push_back(temp);
	solution.pop_back();
	recalculateVisited(temp[1],temp[2]);
}

void move()
{
	vector< vector<int> > possibleMoves;
	vector<int> temp;
	temp.resize(3);

	int currentX=solution[solution.size()-1][0];
	int currentY=solution[solution.size()-1][1];
	recalculateBoard(currentX,currentY);
	//recalculateBoard();
	for(int z=0;z<8;z++)
	{
		if(!visited(currentX+directions[z][0],currentY+directions[z][1],solution.size()+1))
		{
			temp[0]=boardMoves[(currentX+directions[z][0])-1][(currentY+directions[z][1])-1];
			temp[1]=currentX+directions[z][0];
			temp[2]=currentY+directions[z][1];
			possibleMoves.push_back(temp);
		}
	}
	if(!possibleMoves.empty())
	{
		if(possibleMoves.size()==1)
		{
			vector<int> temp2;
			temp2.resize(2);
			temp2[0]=possibleMoves[0][1];
			temp2[1]=possibleMoves[0][2];

			solution.push_back(temp2);

			recalculateVisited(temp2[0],temp2[1]);
		}
		else
		{
			for(unsigned int x = 0;x<=possibleMoves.size();x++)
			{
				for(int y = possibleMoves.size()-1;y>0;y--)
				{
					if(possibleMoves[y-1][0]>possibleMoves[y][0])
					{
						swap(possibleMoves.at(y-1),possibleMoves.at(y));
					}
				}
			}
			vector<int> temp2;
			temp2.resize(2);
			temp2[0]=possibleMoves[0][1];
			temp2[1]=possibleMoves[0][2];

			solution.push_back(temp2);

			recalculateVisited(temp2[0],temp2[1]);
		}
	}
	else
	{
		if(done())
		{
			return;
		}
		else
		{
			if(solution.empty()/*||failedMoves.size()==128*/) // Exits early because reasons: remove failedMoves check when done messing with things
			{
				escape=true;
			}
			else
			{
				backUp();
			}
		}
	}
}

#ifdef WINDOWS
// Found on the internets

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

// Provided by Richard Navas
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
#endif

void print_progress()
{
#ifdef WINDOWS
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
#else
  cout << "POSIX Implementation Coming Soon" << endl;
#endif
}

void start(int x,int y,int boardX,int boardY)
{
	// Push starting position into solution list as first element.
	vector<int> temp;
	temp.push_back(x);
	temp.push_back(y);
	solution.push_back(temp);
	// Set the board size to the size provided. (Remember to add bounds checking later)
	boardMoves.resize(boardX);
	for(int x=0;x<boardX;x++)
	{
		boardMoves[x].resize(boardY);
	}
	boardVisited.resize(boardX);
	for(int x=0;x<boardX;x++)
	{
		boardVisited[x].resize(boardY);
	}
	// Set some globals for other functions to use
	boardWidth=boardX;
	boardHeight=boardY;
	maxMoves=boardWidth*boardHeight;
	recalculateVisited();
	recalculateBoard();
	//print_progress();
	while(!done())
	{
		move();
#ifdef WINDOWS
		print_progress();
#endif
		//Sleep(20);
	}
}

void print_solution()
{
	for(unsigned int x=0;x<solution.size();x++)
	{
		cout << "X: ";
		cout << solution[x][0];
		cout << "\tY: ";
		cout << solution[x][1] << endl;
	}
}

void print_path()
{
	for(int x=1;x<=boardWidth;x++)
	{
		for(int y=1;y<=boardHeight;y++)
		{
			for(unsigned int z=0;z<solution.size();z++)
			{
				if(x==solution[z][0] && y==solution[z][1])
				{
					cout << (z+1);
					cout << "\t";
				}
			}
		}
		cout << endl;
	}
}
// Will ensure that provided solution is a real solution (completely foolproof assuming the user doesn't intentionally fudge width/height)
bool validTour(vector< vector<int> > input,int width,int height,bool fromZero)
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
	if(input.size()!=(width*height))
	{
		cout << "Wrong Number of Moves" << endl;
		return false;
	}
	// If any moves are out of bounds
	if(fromZero)
	{
		for(unsigned int x=0;x<input.size();x++)
		{
			if(input[x][0]<0 || input[x][1]<0 || input[x][0]>=width || input[x][1]>=height)
			{
				cout << "Move Out of Bounds" << endl;
				return false;
			}
		}
	}
	else
	{
		for(unsigned int x=0;x<input.size();x++)
		{
			if(input[x][0]<1 || input[x][1]<1 || input[x][0]>width || input[x][1]>height)
			{
				cout << "Move Out of Bounds" << endl;
				return false;
			}
		}
	}
	// If any moves are duplicated
	for(unsigned int x=0;x<input.size()-1;x++)
	{
		for(unsigned int y=x+1;y<input.size();y++)
		{
			if(input[x][0]==input[y][0] && input[x][1]==input[y][1])
			{
				cout << "Duplicate Move" << endl;
				return false;
			}
		}
	}

	// If any move is not a valid Knight's Move
	for(unsigned int x=0;x<input.size()-1;x++)
	{
		bool isValidMove = false;
		for(int y=0;y<8;y++)
		{
			if(input[x][0]+dirs[y][0]==input[x+1][0] && input[x][1]+dirs[y][1]==input[x+1][1])
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

void save(string loc)
{
	ofstream myfile (loc.c_str());
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
		cout << "Unable to open file: " << loc << endl;
	}
}

int main(int argc, char *argv[])
{
	if(argc!=5)
	{
		cout << "This application requires exactly 4 arguments!" << endl;
		cout << "You supplied: ";
		cout << argc-1;
		cout << " arguments." << endl;
		return -2;
	}
	/* Argument Debugging Code
	cout << "Number of arguments: ";
	cout << argc << endl;
	for(int i=0; i<argc; i++)
	{
		cout << "Argv[";
		cout << i;
		cout << "]: ";
		cout << argv[i] << endl;
	}
	*/

	istringstream ssX(argv[1]);
	istringstream ssY(argv[2]);
	istringstream sbX(argv[3]);
	istringstream sbY(argv[4]);
	int sX,sY,bX,bY;
	if (!(ssX >> sX))
	{
		cerr << "Invalid number " << argv[1] << '\n';
		return -1;
	}
	if (!(ssY >> sY))
	{
		cerr << "Invalid number " << argv[2] << '\n';
		return -1;
	}
	if (!(sbX >> bX))
	{
		cerr << "Invalid number " << argv[3] << '\n';
		return -1;
	}
	if (!(sbY >> bY))
	{
		cerr << "Invalid number " << argv[4] << '\n';
		return -1;
	}

	if(sX < 1 || sX > bX)
	{
		cout << "Starting X position was invalid: ";
		cout << sX << endl;
		return -3;
	}
	if(sY < 1 || sY > bY)
	{
		cout << "Starting Y position was invalid: ";
		cout << sY << endl;
		return -3;
	}
	if(bX < 4)
	{
		cout << "Board width was too small: ";
		cout << bX << endl;
		return -3;
	}
	if(bY < 4)
	{
		cout << "Board height was too small: ";
		cout << bY << endl;
		return -3;
	}

	clock_t begin = clock(); // Get starting time.
#ifdef WINDOWS
	CurPos mousePos = getCursorPos();
	mouseX = mousePos.x;
	mouseY = mousePos.y;
#endif
	cout << "Calculating..." << endl;
	start(sX,sY, bX,bY); // Starting position followed by board size.
	cout << endl;
	clock_t end=clock(); // Get ending time.
	long runningTime=end-begin; // Set total time
	//print_solution();
	cout << endl;
	//print_path();
	if(solution.size()==0)
	{
		cout << boardWidth;
		cout << "x";
		cout << boardHeight << endl;
		cout << "Total Running Time (Sec): ";
		cout << (runningTime/1000) << endl;
		cout << "Total Running Time (MilliSec): ";
		cout << runningTime << endl;
		cout << "Average Time per Move (MilliSec): N/A" << endl;
	}
	else
	{
		cout << boardWidth;
		cout << "x";
		cout << boardHeight << endl;
		cout << "Total Running Time (Sec): ";
		cout << (runningTime/1000) << endl;
		cout << "Total Running Time (MilliSec): ";
		cout << runningTime << endl;
		cout << "Average Time per Move (MilliSec): ";
		cout << (runningTime/(long)solution.size()) << endl;
	}
	cout << "Verifying tour..." << endl;
	if(validTour(solution,boardWidth,boardHeight,false))
	{
		cout << "Success!" << endl;
		stringstream ss;
        ss << "Tour Solution " << boardWidth << "x" << boardHeight << ".txt";
        string tourFileName = ss.str();
		save(tourFileName);
	}
	else
	{
		cout << "Failed!" << endl;
	}
#ifdef WINDOWS
	Beep(261,1000);
#else
	cout << "\007";
#endif
	return 0;
}