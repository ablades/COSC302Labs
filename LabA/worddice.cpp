/*Audaris Blades
 * Lab A
 * Network Flow with words
 */
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
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
            re->residual = 1;
            //Set Each others reverse edges
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
        //Network Flow
        Edge* backEdge;
        int visited;
        //Constructor
        Node() : letters(26, false), visited(false) {}
};

class Graph{
    public:
        vector<Node*> nodes;
        //Node id for words
        vector<int> spellingIDs;
        int minNodes;
        bool bfs();
        bool canSpell();
        //Removes half of graph
        void deleteLetterNode();
};


bool Graph::bfs(){
    return false;
}

bool Graph::canSpell(){

}

void Graph::deleteLetterNode(){

}

int main(int argc, char *argv[]){

    string diceFile(argv[1]);
    string wordFile(argv[2]);
    Graph graph;
    Node* n;
    Edge * edge;
    int id = 0;

    //Source and Sink Nodes
    Node* source = new Node;
    Node* sink = new Node;

    source->type = SOURCE;
    source->id = 0;
    sink->type = SINK;
   // cout << "Node " << source->id  << endl;
   // graph.nodes.push_front(source);

    //Read in data create graph
    //Read in Dice

    std::ifstream file(diceFile.c_str());
    string dice;
    while(getline(file, dice)){
        //Read in Dice
        n = new Node;
        edge = new Edge(source, n);
        //Add Word t0 source
        source->adj.push_back(edge);
        n->backEdge = edge;
        id++;
        n->id = id;

        //set letters vector
        for(int i = 0; i < dice.size(); i++){
            int pos = dice[i] - 'A';
            n->letters[pos] = true;
        }
        n->type = DICE;
     //   cout << "Node " << n->id << ": " << dice <<endl;
        graph.nodes.push_back(n);
        //Add to graph
    }
    graph.nodes.insert(graph.nodes.begin(), source);
    file.close();
    file.clear();
    //THIS IS THE START OF THE LOOP
    //Read in Words
    cout << id;
    string word;
    file.open(wordFile.c_str());
    while(getline(file, word)){
     //   id++;
        n->id = id;

        //Create node for each letter of the word
        for(int i = 0; i < word.size(); i++){
            n = new Node;
            n->id = id + i  + 1;
            n->type = LETTER;
            int pos = word[i] - 'A';
          //  cout << id;
            n->letters[pos] = true;
            //Loop through and set edges
            for(int j = 1; j <= id; j++){
                if(graph.nodes[j]->letters[pos] == true){
                    //cout <<" found edge for " << word[i] << " at "  << j << endl;
                    //Create Edge from Word Node to Letter Node
                    edge = new Edge(graph.nodes[j], n);
                    //add to adj list
                    graph.nodes[j]->adj.push_back(edge);

                }
            }
            //For each letter create an edge from node to sink
            edge = new Edge(n, sink);
            n->backEdge = edge;
            //Add to adj list
            n->adj.push_back(edge);
            graph.nodes.push_back(n);
        }
        //Add sink to end of graph
        sink->id = graph.nodes.size();
        graph.nodes.push_back(sink);

        for(int i = 0; i < graph.nodes.size(); i++){
            Node * n = graph.nodes[i];
            cout << "Node " << n->id << ": " << n->type << " Edges to ";
            for(int j = 0; j < n->adj.size(); j++){
                cout << " " << n->adj[j]->to->id;
            }
            cout << endl;
        }
        cout << endl;



        //Reset second half of vector for next word
        graph.nodes.erase(graph.nodes.begin() + id + 1, graph.nodes.end());
        //Reset adjList
        for(int i = 1; i <graph.nodes.size(); i++)
            graph.nodes[i]->adj.clear();

    }
    file.close();
    //Create Nodes and adj list


}