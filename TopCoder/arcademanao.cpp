#include <string>
#include <vector>

using namespace std;

struct ArcadeManao{
	int shortestLadder(vector<string> level, int coinRow, int coinColumn);
};

struct Node{
	bool visited;
	vector<Node *> adj;//0,1 - left , right  | 2, 3 - down, up
   // adj.resize(4);

};

void dfs(Node *n){

    if(n->visited) return;

    n->visited = true;
    //Left DFS
    if(n->adj[0] != NULL && !n->visited)
        dfs(n->adj[0]);

    //Right DFS
    if(n->adj[1] != NULL && !n->visited)
        dfs(n->adj[1]);

    //Down DFS
    if(n->adj[2] != NULL && !n->visited)
        dfs(n->adj[2]);

    //UP DFS
    if(n->adj[3] != NULL && !n->visited)
        dfs(n->adj[3]);
}


int ArcadeManao::shortestLadder(vector<string> level, int coinRow, int coinColumn){
	int i, j;
    int rows = level.size();
    int cols = level[0].size();

    //graph of nodes
    vector<Node *> graph;

    //Set up graph
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){

            //create node for that platform
            Node n;
            n.visited = false;
            //index
            // is a platform

                //Check Left index
                if(j-1 >= 0 && level[i][j-1] == 'X'){
                    Node lnode;
                    lnode.visited = false;
                    n.adj[0] = &lnode;
                }

                //Check Right index
                if(j+1 > cols && level[i][j+1] == 'X'){
                    Node rnode;
                    rnode.visited = false;
                    n.adj[1] = &rnode;
                }

            graph.push_back(n);
        }
    }


    //Now for reach later from 1 to rows -1

    for(int L = 1; L < rows; L++){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                //ignore empty spaces
                if(level[i][j] == "X")
                //reset visited field
                graph[i][j]->visited = false;
                //Create vertical adj
                if(i+L < rows && level[i + L][j] == 'X'){
                    //Connect nodes
                    //Down
                    graph[i][j]->adj[2]-> graph[i +L][j];
                    //up
                    graph[i + L][j]->adj[3]->graph[i][j];
                }
            }
        }
        dfs(graph[rows-1][cols-1]);

        if(graph[coinRow -1][coinColumn -1]->visited)
            return L;
    }

}
