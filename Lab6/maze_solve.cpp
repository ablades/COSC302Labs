/*Lab6
 * Audaris Blades
 * Solve maze using Depth First Search
 */
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <algorithm>
using namespace std;

//Represents a cell in maze
class Node{
    public:
        vector <int> adjList;
        bool visited;
        int id;
};

class Graph{
    public:
        vector<Node *> nodes;
        bool dfs(int node);
};

//Graph Traversal
bool Graph::dfs(int node) {
    Node *n;
    n = nodes[node];

    if (n->visited)
        return false;
    else
        n->visited = true;

    if (node == 0) {
        cout << "PATH " << n->id << endl;
        return true;
    }

    for (int i = 0; i < n->adjList.size(); i++){
        if (dfs(n->adjList[i])) {
            cout << "PATH " << node << endl;
            return true;
        }
    }
}

int main(){

    string s;
    int rows;
    int cols;
    Node * n;
    Graph g;


    cin >> s;
    cout << s << " ";
    cin >> rows;
    cout << rows << " ";
    cin >> s;
    cout << s << " ";
    cin >> cols;
    cout << cols << endl;

    //Create Graph
    for(int i = 0; i < rows*cols;i++){
        n = new Node;
        n->id = i;
        n->visited = false;
        g.nodes.push_back(n);
    }

    //Initialize Node Adjacency list
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            int index = i*cols + j;

            //North
            if((i - 1)*cols + j >= 0)
                g.nodes[index]->adjList.push_back((i - 1)*cols + j);

            //South
            if((i+1)*(cols) + j < rows*cols)
                g.nodes[index]->adjList.push_back((i+1)*cols +j);

            //West
            if(index - 1 >= 0 && j != 0)
                g.nodes[index]->adjList.push_back(index - 1);

            //East
            if(index + 1 < rows*cols && j != cols - 1)
                g.nodes[index]->adjList.push_back(index + 1);
        }
    }

    while(cin >> s){
        //Walls
        int w1,w2;
        cout << s << " ";
        cin >> w1;
        cout << w1 << " ";
        cin >> w2;
        cout << w2 << endl;

        //Remove Walls in respective adjacency List
        vector<int>::iterator it1, it2;

        it2 = find(g.nodes[w2]->adjList.begin(), g.nodes[w2]->adjList.end(), w1);
        if(it2 != g.nodes[w2]->adjList.end())
            g.nodes[w2]->adjList.erase(it2);

        it1 = find(g.nodes[w1]->adjList.begin(), g.nodes[w1]->adjList.end(), w2);
        if(it1 != g.nodes[w1]->adjList.end())
            g.nodes[w1]->adjList.erase(it1);
    }

    //DFS on Last Element
    g.dfs(rows*cols -1);
}
