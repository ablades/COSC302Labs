/*Audaris Blades
 * Lab A
 * Network Flow with words
 */

#include <vector>
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
        SINK, SOURCE, DICE, LETTER
    };
    vector<bool> letters;
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