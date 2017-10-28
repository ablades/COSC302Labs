#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <queue>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <limits>
#include "arcademanao.cpp"
using namespace std;

int main()
{
  ArcadeManao a;

  vector <int> correct = {2, 1, 4, 0, 2, 6, 9, 9, 17};
  vector <int> rv;
  rv.push_back(a.shortestLadder(
      {"XXXX....",
       "...X.XXX",
       "XXX..X..",
       "......X.",
       "XXXXXXXX"}, 2, 4));
  rv.push_back(a.shortestLadder(
      {"XXXX",
       "...X",
       "XXXX"}, 1, 1));
  rv.push_back(a.shortestLadder(
      {"..X..",
       ".X.X.",
       "X...X",
       ".X.X.",
       "..X..",
       "XXXXX"}, 1, 3));
  rv.push_back(a.shortestLadder(
      {"X"}, 1, 1));
  rv.push_back(a.shortestLadder(
      {"XXXXXXXXXX",
       "...X......",
       "XXX.......",
       "X.....XXXX",
       "..XXXXX..X",
       ".........X",
       ".........X",
       "XXXXXXXXXX"}, 1, 1));
  rv.push_back(a.shortestLadder(
      {"....XX....X.X..................",
       "X......X..X.XX...X......XXX....",
       ".......X..X.....XX..X......X...",
       "...............X...............",
       "..XX....X.X..X..X.........X....",
       ".X..XX.....X..X.X......X.X...X.",
       "....XX.XX.X..X..X.X.....XX..XXX",
       "......X.XXX....XXX....X........",
       ".X.X...XX.X.........X.XX.X.X...",
       ".........X....X...X.........X.X",
       "..X......XXX......X.........X..",
       "......X.X.X.XX..X.....X.XX.....",
       ".....XX.X.......X...X.X...X..X.",
       "..XXX....X..X..X......X...X...X",
       "X...X..X.....X.....X.X.X.....XX",
       ".....X...............X......XX.",
       "X........X.....X.XX...X...X..X.",
       "X.X..........XX....X....X......",
       ".X...X...................X...X.",
       ".X.....X....X...X......X.X.X..X",
       "..........X......XX.X..........",
       "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"}, 7, 17));
  rv.push_back(a.shortestLadder(
      {"X...X.X.X.XX..X..X.......",
       "X..X...............X.....",
       "XXX....X.XXX...XXX...XX..",
       "..X....X........X.......X",
       ".......X.................",
       "..X.....X..XX..X..X...X..",
       ".X...X.....X...X..X.X..X.",
       "..X....X.X.X......X....X.",
       "..X..........X.....X.XX..",
       "X.X...X....XXX.....XXX...",
       ".X.......XX..X.XX..X.....",
       "......X.XX....X..........",
       ".X..X..........X.X.......",
       ".......X.X.X.X....X......",
       "......X.X.X...X..........",
       ".XX......X..X.....X....XX",
       "X..........X..X..........",
       "......X....X..........X..",
       ".XX......X....X..X...X...",
       "XXXXXXXXXXXXXXXXXXXXXXXXX"}, 10, 20));
  rv.push_back(a.shortestLadder(
        {"..",
         ".X",
         "..",
         "..",
         "..",
         "..",
         "..",
         ".X",
         ".X",
         "XX",
         ".X",
         "..",
         "X.",
         ".X",
         ".X",
         ".X",
         "..",
         "..",
         "..",
         "X.",
         ".X",
         "X.",
         "..",
         "X.",
         "..",
         ".X",
         "..",
         "..",
         ".X",
         "..",
         "..",
         "..",
         ".X",
         "X.",
         "..",
         "..",
         "..",
         "X.",
         "..",
         "..",
         "..",
         ".X",
         "XX"}, 22, 1));
  rv.push_back(a.shortestLadder(
      {".........X....XX",
       "...X.X....X.....",
       ".X.X..XX..X.....",
       "....X.....X.X...",
       ".........X...X.X",
       "....X...X.......",
       "..X.......X.....",
       "................",
       "...X.X........X.",
       "X......X..X.....",
       ".X...........X..",
       "................",
       ".XX...X.........",
       "............X...",
       "...X......X.....",
       ".X..............",
       "X..............X",
       "..X.X....X....XX",
       "..X....X.X..X...",
       "...............X",
       "..X....X.XX.....",
       "..........X.XX..",
       ".X....X.........",
       ".X....X..X......",
       ".......X......X.",
       "X..X............",
       "....XXX.......X.",
       "........X.......",
       ".X....X.........",
       ".........X......",
       ".........XXXX.X.",
       "...X............",
       ".....X..XXX.....",
       "..X.............",
       "..........X.....",
       "...X.X..........",
       "...X....X.......",
       "................",
       "...........X....",
       ".X..............",
       "..........X.....",
       ".....XX.........",
       ".......X...X....",
       "......XX...X....",
       "....X.X.........",
       "..........X.....",
       "...X............",
       "..............X.",
       ".........X......",
       "XXXXXXXXXXXXXXXX"}, 18, 15));

  cout << "Your Answer == Correct Answer" << endl;
  for(int i = 0; i < rv.size(); i++)
    cout << rv[i] << " == " << correct[i] << endl;
}
