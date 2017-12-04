
#include <bits/stdc++.h>
using namespace std;

struct Point
{
    int x, y;
};

// (i, j) corresponds to tail of the snake
list<Point> findPath(vector<vector <int> > grid, vector<vector <int> > mat, int i, int j) {
    list<Point> path;

    int M, N;
    M = mat.size();
    N = mat[0].size();

    Point pt;
    pt.x = i;
    pt.y = j;
    path.push_front(pt);

    while (grid[i][j] != 0)
    {
        if (i > 0 && grid[i][j] - 1 == grid[i - 1][j])
        {
            pt.x = i - 1;
            pt.y = j;
            path.push_front(pt);
            i--;
        }

        if (j > 0 && grid[i][j] - 1 == grid[i][j - 1])
        {
            pt.x = i;
            pt.y = j - 1;
            path.push_front(pt);
            j--;
        }

        if((j+1 < N && i+1 < M) && grid[i][j] - 1 == grid[i+1][j+1]){
            pt.x = i + 1;
            pt.y = j + 1;
            path.push_front(pt);
            j++;
            i++;
        }
        if((j > 0 && i+1 < M) && grid[i][j] - 1 == grid[i+1][j-1]){
            pt.x = i + 1;
            pt.y = j - 1;
            path.push_front(pt);
            j--;
            i++;
        }

        if((j+1 < N && i > 0) && grid[i][j] - 1 == grid[i-1][j+1]){
            pt.x = i - 1;
            pt.y = j + 1;
            path.push_front(pt);
            j++;
            i--;
        }
        if((j > 0  && i > 0) && grid[i][j] - 1 == grid[i-1][j-1]){
            pt.x = i - 1;
            pt.y = j - 1;
            path.push_front(pt);
            j--;
            i--;
        }
    }

    return path;
}

// Function to find maximum length Snake sequence
void findSequence(vector<vector <int> > mat)
{
    int M, N;
    M = mat.size();
    N = mat[0].size();

    // table to store results of subproblems
    vector<vector <int> > lookup(M, vector<int>(N, 0));
    // initialize by 0
    // memset(lookup, 0, sizeof lookup);

    // stores maximum length of Snake sequence
    int max_len = 0;

    // store cordinates to snake's tail
    int max_row = 0;
    int max_col = 0;

    // fill the table in bottom-up fashion
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            // do except for (0, 0) cell
            if (i || j) {
                // look above
                if (i > 0 && abs(mat[i - 1][j] - mat[i][j]) == 1) {
                    lookup[i][j] = max(lookup[i][j], lookup[i - 1][j] + 1);

                    if (max_len < lookup[i][j])
                    {
                        max_len = lookup[i][j];
                        max_row = i, max_col = j;
                    }
                }

                // look left
                if (j > 0 && abs(mat[i][j - 1] - mat[i][j]) == 1) {
                    lookup[i][j] = max(lookup[i][j], lookup[i][j - 1] + 1);

                    if (max_len < lookup[i][j]) {
                        max_len = lookup[i][j];
                        max_row = i, max_col = j;
                    }
                }

                //Check weird bounds
                //column is even
                if(j % 2 == 0){
                    //check r+1, c+1
                    if((j+1 < N && i+1 < M) && abs(mat[i + 1][j + 1] - mat[i][j]) == 1){
                        lookup[i][j] = max(lookup[i][j], lookup[i+1][j+1] + 1);

                        if (max_len < lookup[i][j]) {
                            max_len = lookup[i][j];
                            max_row = i, max_col = j;
                        }
                    }

                    //check r+1 c -1
                    if((j > 0 && i+1 < M) && abs(mat[i + 1][j - 1] - mat[i][j]) == 1){
                        lookup[i][j] = max(lookup[i][j], lookup[i+1][j-1] + 1);

                        if (max_len < lookup[i][j]) {
                            max_len = lookup[i][j];
                            max_row = i, max_col = j;
                        }
                    }
                }

                //col is odd
                if(j % 2 != 0){
                    //check r-1, c+1
                    if((j+1 < N && i > 0) && abs(mat[i - 1][j + 1] - mat[i][j]) == 1){
                        lookup[i][j] = max(lookup[i][j], lookup[i-1][j+1] + 1);

                        if (max_len < lookup[i][j]) {
                            max_len = lookup[i][j];
                            max_row = i, max_col = j;
                        }
                    }

                    //check r-1 c-1
                    if((j > 0  && i > 0) && abs(mat[i - 1][j - 1] - mat[i][j]) == 1){
                        lookup[i][j] = max(lookup[i][j], lookup[i-1][j-1] + 1);

                        if (max_len < lookup[i][j]) {
                            max_len = lookup[i][j];
                            max_row = i, max_col = j;
                        }
                    }

                }
            }
        }
    }

    //cout << "Maximum length" << max_len << endl;

    // find maximum length Snake sequence path
    list<Point> path = findPath(lookup, mat, max_row, max_col);
    cout << path.size() << endl;
      cout << "PATH";
      for (list<Point>::iterator it = path.begin(); it != path.end(); it++)
          cout << endl  << it->x << " " << it->y ;
}


// Driver code
int main(int argc, char **argv)
{
    string spellFile = (argv[1]);

    std::ifstream file(spellFile.c_str());
    string row = "";
    int i = 0;
    vector< vector <int> > board;

    while(getline(file, row)){


        //set letters vector
        //Add new column
        vector<int> col;
        board.push_back(col);
        for(int j = 0; j < row.size(); j++){
                 cout << row[j];
            board[i].push_back(row[j]);
        }
           cout << endl;

        i++;
    }

    findSequence(board);

    return 0;
}
