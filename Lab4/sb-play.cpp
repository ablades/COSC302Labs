/*Audaris Blades
 * Lab 5
 * Superball
 *sb-play.cpp
 * Calculate/Output Moves
 */
#include "DJ.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

#define talloc(type, num) (type *) malloc(sizeof(type)*(num))

class Superball {
  public:
    Superball(int argc, char **argv);
    void analyze();
    void play();
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
      DJ = new Disjoint(r*c);
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
void:: Superball::play(){
  int swap1;
  int swap2;
  int maxSpot;
  int maxScore = 0;
  vector<int> spotScore;
  spotScore.resize(r*c, 0);

  //Give each spot a score based on adjecent values
  for(int i = 0; i < board.size();i++){
    if(board[i] != '.' && board[i] != '*'){
      //Right cell
      if(board[i] == board[i+1] && i % c != c - 1){
        spotScore[i]++;
      }
      else if(board[i+1] == '.')
        spotScore[i]--;

      //Left Cell
      if((i-1) > 0 && board[i] == board[i-1] && i % c != c - 1){
        spotScore[i]++;
      }
      else if(board[i-1] == '.')
        spotScore[i]--;
      //Lower adjeceny
      if( i + c < r*c && board[i] == board[i+c]){
        spotScore[i]++;
      }
      else if(board[i+c] == '.')
        spotScore[i]--;

      //Upper Adjeceny
      if(board[i] == board[i-c] && i/c != r-1){
        spotScore[i]++;
      }
      else if(board[i-c] == '.')
        spotScore[i]--;

      //Increase priority of spot if on a goal cell.
      if(goals[i] == 1){
        spotScore[i] *= 2;
      }

      //Save highest score
      if(spotScore[i] > maxScore){
        maxScore = spotScore[i];
        maxSpot = i;
      }
    }
  }

  //Find element with lowest score around he maxSpot or different color
  int minScore = maxScore;
  int minSpot = maxSpot;
  for(int i = 0; i < board.size(); i++){
    //if we find an element with the same color as the maximum element and smaller score store it
    if(board[i] == board[maxSpot]){
      if(spotScore[i] <= minScore){
        minSpot = i;
        minScore = spotScore[i];
      }
    }
  }
  //Test print scores
 /* for(int i = 0; i < spotScore.size();i++){
    if( (i + c) % c == 0)
      cout <<endl;
    cout << spotScore[i];
  }*/

  int closestMinSpot = maxSpot;
  if((maxSpot-1) > 0 && maxSpot % c != c - 1 && spotScore[maxSpot -1] < closestMinSpot)
    closestMinSpot = maxSpot -1;

  if( maxSpot + c < r*c && spotScore[maxSpot + c] < closestMinSpot)
    closestMinSpot = maxSpot + c;

  if(spotScore[maxSpot-c] && maxSpot/c != r-1 && spotScore[maxSpot-c] < closestMinSpot){
    closestMinSpot = maxSpot - c;
  }

  /*if(maxSpot % c != c - 1 && spotScore[maxSpot+1] < closestMinSpot)
    closestMinSpot = maxSpot + 1;*/


  //Now find color of same type with lowest score


  //Call swap
  cout << "SWAP " << closestMinSpot/c <<' '<< closestMinSpot%c << ' '<< minSpot/c << ' '<<  (minSpot%c) << endl;

}
void Superball::analyze(){
  vector<int> ranks;
  vector<bool> printed;
  ranks.resize(r*c, 1);
  printed.resize(r*c, false);

  //Sets all links
  for(int i = 0; i < board.size();i++){
    if(board[i] != '.' && board[i] != '*'){
      //Check adjecent cell
      int s1;
      int s2;
      int s3;

      //Check adjecent cell
      if(board[i] == board[i+1] && i % c != c - 1){
        s1 = DJ->Find(i);
        s2 = DJ->Find(i+1);

        if(s1 != s2){
        s3 = DJ->Union(s1, s2);
        ranks[s3] = ranks[s2] + ranks[s1];
        }
      }

      //Check lower adjecent cell
      if(board[i] == board[i+c] && i/c != r-1){
        s1 = DJ->Find(i);
        s2 = DJ->Find(i+c);

        if(s1 != s2){
          s3 = DJ->Union(s1, s2);  
          ranks[s3] = ranks[s2] + ranks[s1];
        }
      }

    }
  }
  
  cout << "Scoring sets:" << endl;
  //Loop through goals board
  for(int i = 0; i < goals.size();i++){
    if(goals[i] == 1 && board[i] != '.' && board[i] != '*'){
      int root = DJ->Find(i);
      if(ranks[root] >= mss && printed[root] == false){
        printed[root] = true;
        cout << " Size: " << setw(2) << setfill(' ') << ranks[root] << " Char: " << (char)board[i] << " Scoring Cell: " << i/c << "," << i%c << endl;
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
  s->play();
  //s->analyze();
  exit(0);
}