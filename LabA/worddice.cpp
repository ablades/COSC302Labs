/*Audaris Blades
 * Lab A
 * Network Flow with words
 */
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Edge{
    class Node* from;
    class Node* to;
    //Opposite direction edge
    Edge* reverse;
    //Network Flow Fields
    int original;
    int residual;
};

class Node{
    int id;
    enum type{
        SOURCE, DICE, LETTER, SINK
    };
    vector<bool> letters (26, false);
    vector<Edge *> adj;
    //Network Flow
    Edge* backEdge;
    int visited;
};

class Graph{
    vector<Node*> nodes;
    //Node id for words
    vector<int> spellingIDs;
    int minNodes;
    bool bfs();
    bool canSpell();
    //Removes half of graph
    void deleteLetterNode();
};


bool Graph::dfs(){

}

bool Graph::canSpell(){

}

void Graph::deleteLetterNode(){

}

int main(){
    Graph graph;
    String dice;
    Node* n;
    int id = 0;

    //Read in data create graph
    //Read in Dice
    while(!cin.eof){
        n = new Node;
        id++;
        getline(cin, dice);
        n->id = id;

        //set letters vector
        for(int i = 0; i < dice.size(); i++){
            int pos = dice[i] - 'A';
            n->letters[pos] = true;
        }


    }

    //Create Nodes and adj list
    Node n;
    n.SOURCE;


}