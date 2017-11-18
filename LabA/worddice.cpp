/*Audaris Blades
 * Lab A
 * Network Flow with words
 */
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>

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
    //What edge got me here
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
        void deleteLetterNodes();
};


bool Graph::bfs(){
    //follow paths with an original equal to 1
    queue<int> q;
    q.push(SOURCE);
    while(q.size()){
        //pop off queue
        int node = q.front();
        q.pop();
        nodes[node]->visited = true;

        //if not the sink and not visited add to queue dd adj edges to queue
        if(nodes[node]->type != SINK){
            Edge* e;
            Node* nextNode;
            //loop through nodes adj list
            for(int i = 0; i < nodes[node]->adj.size(); i++){
                nextNode = nodes[node]->adj[i]->to;
                e = nodes[node]->adj[i];
                //Add next node to queue
                if(!nextNode->visited){
                    //Set its backedge
                    nextNode->backEdge = e->reverse;
                    q.push(nextNode->id);
                }
            }
        }
        else
            return true;//path found

    }
    return false;
}

bool Graph::canSpell(){
    //Reset BackEdges
    for(int i = 0; i < nodes.size(); i++)
        nodes[i]->backEdge = NULL;
    //Call BFS
    //When the bfs find a path
    while(bfs()){
        //follow back edges
        Node* n = nodes.back();
        //Traverse Backedges till source
        while(n->type != SOURCE){
            n->backEdge->original = 0;
            n->backEdge->residual = 1;
            n->backEdge->reverse->residual = 0;
            n->backEdge->reverse->residual = 1;
            n = n->backEdge->from;
        }
    }

    //Loop through letters and look at residual value
    for(int i = minNodes + 1; i < nodes.size(); i++){
        for(int j = 0; j < nodes[i]->adj.size(); j++){
            //Look at edge connected to sink
            if(nodes[i]->adj[j]->to->type == SINK){
                if(nodes[i]->adj[j]->residual != 1)
                    return false;
            }
        }
    }
    return true;

}

void Graph::deleteLetterNodes(){
    //Print out Node Structure
    for(int i = 0; i < nodes.size(); i++){
        Node * n = nodes[i];
        cout << "Node " << n->id << ": " << n->type << " Edges to ";
        for(int j = 0; j < n->adj.size(); j++){
            cout << " " << n->adj[j]->to->id;
        }
        cout << endl;
    }
    cout << endl;

    //Reset second half of vector for next word
    nodes.erase(nodes.begin() + minNodes + 1, nodes.end());
    //Reset adjList
    for(int i = 1; i <= minNodes; i++)
        nodes[i]->adj.clear();
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
        //SET WORD BACK EDGE
       // n->backEdge = edge->reverse;
        //Add Word t0 source
        source->adj.push_back(edge);
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
    graph.minNodes = id;
    string word;
    file.open(wordFile.c_str());
    while(getline(file, word)){
     //   id++;
        n->id = graph.minNodes;

        //Create node for each letter of the word
        for(int i = 0; i < word.size(); i++){
            n = new Node;
            n->id = id + i  + 1;
            n->type = LETTER;
            int pos = word[i] - 'A';
          //  cout << id;
            n->letters[pos] = true;
            //Loop through words and set edges
            for(int j = 1; j <= graph.minNodes; j++){
                if(graph.nodes[j]->letters[pos] == true){
                    //cout <<" found edge for " << word[i] << " at "  << j << endl;
                    //Create Edge from Word Node to Letter Node
                    edge = new Edge(graph.nodes[j], n);
                    //add to adj list
                    graph.nodes[j]->adj.push_back(edge);
                    //Add reverse edge to letters adj list
                    n->adj.push_back(edge->reverse);

                }
            }
            //For each letter create an edge from node to sink
            edge = new Edge(n, sink);
            //SET SINK BACK EDGE
           // sink->backEdge = edge->reverse;
            //Add to adj list
            n->adj.push_back(edge);
            graph.nodes.push_back(n);
        }
        //Add sink to end of graph
        sink->id = graph.nodes.size();
        graph.nodes.push_back(sink);

        //can spell check
        graph.canSpell();
        //Reset Letters
        graph.deleteLetterNodes();

    }
    file.close();
    //Create Nodes and adj list


}