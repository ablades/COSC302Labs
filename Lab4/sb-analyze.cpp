/*Audaris Blades
 * Lab 5
 * Superball
 */
#include "DJ.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <iostream>
#include <vector>
using namespace std;

#define talloc(type, num) (type *) malloc(sizeof(type)*(num))

class Superball {
  public:
    Superball(int argc, char **argv);
    int r;
    int c;
    int mss;
    int empty;
    vector <int> board;
    vector <int> goals;
    vector <int> colors;
    Disjoint *DJ;
};

void usage(const char *s) 
{
  fprintf(stderr, "usage: sb-read rows cols min-score-size colors\n");
  if (s != NULL) fprintf(stderr, "%s\n", s);
  exit(1);
}

Superball::Superball(int argc, char **argv)
{
  int i, j;
  string s;

  if (argc != 5) usage(NULL);

  if (sscanf(argv[1], "%d", &r) == 0 || r <= 0) usage("Bad rows");
  if (sscanf(argv[2], "%d", &c) == 0 || c <= 0) usage("Bad cols");
  if (sscanf(argv[3], "%d", &mss) == 0 || mss <= 0) usage("Bad min-score-size");

  colors.resize(256, 0);

  for (i = 0; i < strlen(argv[4]); i++) {
    if (!isalpha(argv[4][i])) usage("Colors must be distinct letters");
    if (!islower(argv[4][i])) usage("Colors must be lowercase letters");
    if (colors[argv[4][i]] != 0) usage("Duplicate color");
    colors[argv[4][i]] = 2+i;
    colors[toupper(argv[4][i])] = 2+i;
  }

  board.resize(r*c);
  goals.resize(r*c, 0);

  empty = 0;

  for (i = 0; i < r; i++) {
    if (!(cin >> s)) {
      fprintf(stderr, "Bad board: not enough rows on standard input\n");
      exit(1);
    }
    if (s.size() != c) {
      fprintf(stderr, "Bad board on row %d - wrong number of characters.\n", i);
      exit(1);
    }
    for (j = 0; j < c; j++) {
      if (s[j] != '*' && s[j] != '.' && colors[s[j]] == 0) {
        fprintf(stderr, "Bad board row %d - bad character %c.\n", i, s[j]);
        exit(1);
      }
      board[i*c+j] = s[j];
      if (board[i*c+j] == '.') empty++;
      if (board[i*c+j] == '*') empty++;
      if (isupper(board[i*c+j]) || board[i*c+j] == '*') {
        goals[i*c+j] = 1;
        board[i*c+j] = tolower(board[i*c+j]);
      }
    }
  }
}

sb-analyze(){
	//Disjoint set that is the size of the board
	DJ = new Disjoint(r*c);
	//Stores size of unioned colors at color index
	vector<int> ranks;
	ranks.resize(r*c, 0);

	for(int i = 0; i < r; i++){
		for(int j = 0; j < c; j++){
			int index = i*c + j;
			//Right Column
			int rCol = i*c + j + 1;
			//Lower Column
			int dCol = i*r*c + j;
			//dont forget first cell
			if((rCol % c-1 != 0 || j == 0) && board[rCol] == board[index]){
				DJ.Union(DJ.Find(index), DJ.Find(rCol));
				ranks[DJ.Find(index)]++; 
			}

			if((dCol % r-1 != 0 || i == 0) && board[dCol] == board[index]){
				DJ.Union(DJ.Find(index), DJ.Find(dCol));
			}

		}
	}
}

main(int argc, char **argv)
{
  Superball *s;
  int i, j;
  int ngoal, tgoal;
 
  s = new Superball(argc, argv);

  tgoal = 0;
  ngoal = 0;
  for (i = 0; i < s->r*s->c; i++) {
    if (s->goals[i] && s->board[i] != '*') {
      tgoal += s->colors[s->board[i]];
      ngoal++;
    }
  }

  printf("Empty cells:                    %2d\n", s->empty);
  printf("Non-Empty cells:                %2d\n", s->r*s->c - s->empty);
  printf("Number of pieces in goal cells: %2d\n", ngoal);
  printf("Sum of their values:            %2d\n", tgoal);
  exit(0);
}