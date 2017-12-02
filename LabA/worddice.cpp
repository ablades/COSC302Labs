/*Audaris Blades
 * Lab A
 * Network Flow with words
 */
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <map>

using namespace std;

class Edge{
    public:
        class Node* from;
        class Node* to;
        //Opposite direction edge
        Edge* reverse;
        //Network Flow Fields
        int original;
        int residual;
        //Default constructor
        Edge(){};
        //param f - from, t - to
        //Creates edge and reverse edge
        Edge(class Node * f,class Node * t){
            from = f;
            to = t;
            original = 1;
            residual = 0;
            //Reverse edge init
            Edge* re = new Edge();
            re->from = t;
            re->to = from;
            re->original = 0;
            re->residual = 1    ;

            re->reverse = this;
            reverse = re;
        }
};

//Node type
enum Type{ SOURCE, DICE, LETTER, SINK };

class Node{
    public:
        int id;
        vector<bool> letters ;
        vector<Edge *> adj;
        Type type;
        Edge* backEdge;
        int visited;
        //Constructor
        Node() : letters(26, false), visited(false) {}
};

class Graph{
    public:
        vector<Node*> nodes;
        //Stores Node ids
        map<int, int> sid;
        int minNodes;
        bool bfs();
        bool canSpell();
        //Removes half of graph
        void resetNodes();
};

bool Graph::bfs(){
    //Reset Backedges
     for(int i = 0; i < nodes.size(); i++){
        nodes[i]->visited = false;
         nodes[i]->backEdge = NULL;
    }
    //bfs
    queue<int> q;
    q.push(SOURCE);
    while(q.size()){
        int node = q.front();
        q.pop();

        nodes[node]->visited = true;
        Node* nextNode;
        Edge* e;

        //loop through nodes adj list
        for(int i = 0; i < nodes[node]->adj.size(); i++){
            nextNode = nodes[node]->adj[i]->to;
            e = nodes[node]->adj[i];

            //Add Unvisited node to queue
            if(!nextNode->visited && e->original == 1){
                //Set its backEdge
                nextNode->backEdge = e->reverse;
                q.push(nextNode->id);
                //Path Found
                if(nextNode->type == SINK)
                    return true;
            }
        }
    }
    return false;
}

bool Graph::canSpell(){

    Node* n = nodes.back();
    //Found Path
    while(bfs() == true){

        Node* n = nodes.back();
        int letter;

        //Traverse BackEdges
        while(n->type != SOURCE){

            //Change flow for each edge
            n->backEdge->original = 1;
            n->backEdge->residual = 0;
            n->backEdge->reverse->residual = 1;
            n->backEdge->reverse->original = 0;

            //Store letter
            if(n->type == LETTER)
                letter = n->id;

            //Add Letter/Dice to solution
            if(n->type == DICE)
                sid[letter] = n->id;

            n = n->backEdge->to;
        }
    }

    for(int i = minNodes + 1; i < nodes.size(); i++){
        for(int j = 0; j < nodes[i]->adj.size(); j++){

            //Look at edges residual connected to sink
            if(nodes[i]->adj[j]->to->type == SINK)
                if(nodes[i]->adj[j]->residual != 1)
                    return false;
        }
    }
    return true;
}

//Reset Node, residual/original and adj list
void Graph::resetNodes(){
    nodes.back()->adj.clear();

    for(int i = 0; i < nodes[0]->adj.size();i++){
        nodes[0]->adj[i]->original = 1;
        nodes[0]->adj[i]->residual = 0;
        nodes[0]->adj[i]->reverse->original = 0;
        nodes[0]->adj[i]->reverse->residual = 1;
    }
    sid.clear();
    //Reset second half of vector for next word
    nodes.erase(nodes.begin() + minNodes + 1, nodes.end());
    //Reset adjList
    for(int i = 1; i <= minNodes; i++)
        nodes[i]->adj.clear();
}

int main(int argc, char *argv[]){
    //Parse Arguments
    string diceFile(argv[1]);
    string wordFile(argv[2]);
    Graph graph;
    Node* n;
    Edge * edge;
    int id = 0;

    //Source and Sink Nodes
    Node* source = new Node;
    source->type = SOURCE;
    source->id = 0;
    Node* sink = new Node;

    std::ifstream file(diceFile.c_str());
    string dice;

    //Read in dice
    while(getline(file, dice)){
        n = new Node;
        edge = new Edge(source, n);
        source->adj.push_back(edge);
        id++;
        n->id = id;

        //set letters vector
        for(int i = 0; i < dice.size(); i++){
            int pos = dice[i] - 'A';
            n->letters[pos] = true;
        }
        n->type = DICE;
        graph.nodes.push_back(n);
    }
    
    graph.nodes.insert(graph.nodes.begin(), source);
    file.close();
    file.clear();

    graph.minNodes = id;
    string word;
    file.open(wordFile.c_str());

    //Read in words
    while(getline(file, word)){
        n->id = graph.minNodes;

        //Create node for each letter of the word
        for(int i = 0; i < word.size(); i++){
            n = new Node;
            n->id = id + i  + 1;
            n->type = LETTER;
            int pos = word[i] - 'A';
            n->letters[pos] = true;

            //Set Edges for each letter
            for(int j = 1; j <= graph.minNodes; j++){
                if(graph.nodes[j]->letters[pos] == true){
                    edge = new Edge(graph.nodes[j], n);
                    graph.nodes[j]->adj.push_back(edge);
                    n->adj.push_back(edge->reverse);
                }
            }
            //Create an edge from node to sink
            edge = new Edge(n, sink);
            //Add to adj list
            n->adj.push_back(edge);
            graph.nodes.push_back(n);
        }

        //Add sink to end of graph
        sink->type = SINK;
        sink->id = graph.nodes.size();
        graph.nodes.push_back(sink);

        //Print
        if(graph.canSpell() == true){
            for (std::map<int,int>::iterator it=graph.sid.begin(); it!=graph.sid.end(); ++it){
                if(it == graph.sid.begin())
                    cout << it->second - 1;
                else
                    cout << "," << it->second - 1;
            }
            cout << ": "  << word ;
        }else
            cout << "Cannot spell " << word;

        cout << endl;

        graph.resetNodes();

    }
    file.close();
}