/*Lab6
 * Audaris Blades
 * Maze Solver
 */
#include <vector>
#include <string>
#include <iostream>
#include <cmath>

using namespace std;
//Node structure
class Node{
    //ids are ints
    public:
        //Indexed by (N S W E) (0 1 2 3)
        vector<int> adjList;
        bool visited;
        int id;
		//Set default adj list
		Node(){
			adjList.resize(4, -1);
            visited = false;
		}
};

class Graph{
    //All nodes
    //Indexed by id
    public:
        vector<Node *> graph;
        bool dfs(int node);
        /*g.node(2) gives node at index*/

};
/*param node - current node we're at*/
//have dfs return 1 if it found the path
//Maze end makes code more portable
bool Graph::dfs(int node){

	//Adjecency
	//0- North  1-South 2-East 3-West
	if(graph[node]->visited)
        return 0;

	//Base Case Reached start
	if(graph[node]->id == 0)
		return 1;
	//DFS Base Case
	if(dfs(node)){
        cout << "PATH " << graph[node]->id;
	}

	graph[node]->visited = true;

    if(graph[node]->adjList[0] != -1)
        dfs(graph[node]->adjList[0]);

    if(graph[node]->adjList[1] != -1)
        dfs(graph[node]->adjList[1]);

    if(graph[node]->adjList[2] != -1)
        dfs(graph[node]->adjList[2]);

    if(graph[node]->adjList[3] != -1)
        dfs(graph[node]->adjList[3]);
	//visited return
 //base case first index
    //solve maze backwards
    //recursion is a stack
    //print out in return

    //if at start print Path 0 0
    //return
    //loop through adj list(size 4) four adj nodes
    /*if valid adj node(not -1)
     * call
     * dfs on that node*/
    //print
    //if(dfs  returns 1 on the path to start)
    //return 0
}

int main(){
    //read in rows/ col
    //store in variable
    int rows;
    int cols;
    Graph g;
    cin.ignore();
    cin >> rows;
    cin.ignore();
    cin >> cols;
    //initialize node vector
    for(int i = 0; i < cols; i++){
        for(int j = 0; j < rows; j++){

            int index = i*cols + j;
            Node n;

            //Look North
            if((i*(cols - 1) + j > 0)){
                n.adjList[0] = i*(cols - 1) + j;
            }

            //Look South
            if((i*(cols + 1) + j < rows*cols)){
                n.adjList[1] = i*(cols + 1);
            }

            //Look West
            if(index - 1 >= 0 && j != 0){
                n.adjList[2] = index - 1;
            }

            //Look East
            if(index + 1 < rows*cols && j != cols - 1){
                n.adjList[3] = index + 1;
            }

            //Add node to vector
            g.graph.push_back(&n);
        }
    }
    string s;
    while(cin >> s){
        //
        int w1,w2;
        cin >> s;
        //First location of wall
        cin >> w1;
        //Second location of wall
        cin >> w2;

        //Wall Detection
        int adj = abs(w2 - w1);
        //Wall is vertical
        if(adj == 1){
            //Adjust Respective Adj List
            if(w2 > w1){
                g.graph[w2]->adjList[3] = -1;
                g.graph[w1]->adjList[4] = -1;
            }
            else if(w1 > w2){
                g.graph[w1]->adjList[3] = -1;
                g.graph[w2]->adjList[4] = -1;
            }

        }
        //Horizontal wall
        if(adj == cols){
            if(w2 > w1){
                //Remove Upper Wall from W2
                g.graph[w2]->adjList[0] = -1;
                g.graph[w1]->adjList[1] = -1;
            }
            else if(w2 < w1){
                g.graph[w2]->adjList[1] = -1;
                g.graph[w1]->adjList[0] = -1;
            }

        }


    }
    //store in variable
    //Make instance of graph
    //Make rxc nodes
    //push into g.nodes
    //initialize nodes
    //(can fill in vectors we can fill in graph)
    //fix each nodes adj list
    //initialize adj -1
    //make each index in adj list represent a direction [_ _ _ _] (N S W E)
    //print back out rows and cols
    g.dfs(rows*cols -1);
}
