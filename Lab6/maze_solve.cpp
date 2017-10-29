/*Lab6
 * Audaris Blades
 * Maze Solver
 */
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <algorithm>
using namespace std;
//Node structure
class Node{
    public:
        vector <int> adjList;
        bool visited;
        int id;
        //Indexed by (N S W E) (0 1 2 3)
		//Set default adj list
};

class Graph{
    //All nodes
    //Indexed by id
    public:
        vector<Node *> nodes;
        bool dfs(int node);
        /*g.node(2) gives node at index*/

};
/*param node - current node we're at*/
//have dfs return 1 if it found the path
//Maze end makes code more portable
bool Graph::dfs(int node){


        Node *n;
        n = nodes[node];
        if (n->visited)
            return false;

        if (node == nodes.size()) {
            cout << "Path " << node << endl;
        }

    if(true) {
        cout << "PATH " << node << endl;
    }

        n->visited = true;

        //DFS Base Case

        //Adjecency
        //0- North  1-South 2-East 3-West

        //Base Case Reached start


        for (int i = 0; i < nodes[node]->adjList.size(); i++)
            if (!nodes[n->adjList[i]]->visited)
                return dfs(n->adjList[i]);

    return false;
    }
    //return false;

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


int main(){
    //read in rows/ col
    //store in variable
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

    for(int i = 0; i < rows*cols;i++){
        n = new Node;
        n->id = i;
        n->visited = false;
        g.nodes.push_back(n);
    }
    //initialize node vector
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            int index = i*cols + j;
           // n.adjList.resize(4, -1);
            //n->visited = false;
           // cout << "Index: " << index;
            //Look North
            if((i - 1)*cols + j >= 0){
                g.nodes[index]->adjList.push_back((i - 1)*cols + j);
              //  cout << " North: "<< (i-1)*cols + j;
            }

            //Look South
            if((i+1)*(cols) + j < rows*cols){
                g.nodes[index]->adjList.push_back((i+1)*cols +j);
            //    cout << " South: " << (i +1)*cols +j;
            }

            //Look West
            if(index - 1 >= 0 && j != 0){
                g.nodes[index]->adjList.push_back(index - 1);
             //   cout << " West: " << index - 1;
            }

            //Look East
            if(index + 1 < rows*cols && j != cols - 1){
                g.nodes[index]->adjList.push_back(index + 1);
              //  cout << " East: " << index + 1;
            }
           // cout << endl;
        }
    }

    while(cin >> s){
        cin.clear();
        int w1,w2;
        //cin >> s;
        cout << s << " ";
        //First location of wall
        cin >> w1;
        cout << w1 << " ";
        //Second location of wall
        cin >> w2;
        cout << w2 << endl;

        //Wall Detection;
        vector<int>::iterator it1, it2;
        //Look for w1 in w2 and remove it
        it2 = find(g.nodes[w2]->adjList.begin(), g.nodes[w2]->adjList.end(), w1);
        if(it2 != g.nodes[w2]->adjList.end()){
            g.nodes[w2]->adjList.erase(it2);
            cout << "ERASING " << w1 << " FROM " << w2 <<endl;
        }
        //Look for w2 in w1
        it1 = find(g.nodes[w1]->adjList.begin(), g.nodes[w1]->adjList.end(), w2);
        if(it1 != g.nodes[w1]->adjList.end()){
            g.nodes[w1]->adjList.erase(it1);
            cout << "ERASING " << w2 << " FROM " << w1 <<endl;
        }
    }

  /*  for(int i = 0; i < g.nodes.size(); i++){
        cout << "Node: " << i;
        for(int j = 0; j < g.nodes[i]->adjList.size();j++){
            cout<< " adj: " << g.nodes[i]->adjList[j];
        }
        cout << endl;
    }*/

    g.dfs(0);


}
