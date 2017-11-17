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
    class Node* from;
    class Node* to;
    //Opposite direction edge
    Edge* reverse;
    //Network Flow Fields
    int original;
    int residual;
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
    int id = 0;

    Node* source = new Node;
    Node* sink = new Node;

    source->type = SOURCE;
    source->id = id;
    sink->type = SINK;
    cout << "Node " << source->id << endl;
    graph.nodes.push_back(source);

    //Read in data create graph
    //Read in Dice

    std::ifstream file(diceFile.c_str());
    string dice;
    while(getline(file, dice)){
        //Read in Dice
        n = new Node;
        id++;
        n->id = id;

        //set letters vector
        for(int i = 0; i < dice.size(); i++){
            int pos = dice[i] - 'A';
            n->letters[pos] = true;
        }
        n->type = DICE;
        cout << "Node " << n->id << ": " << dice <<endl;
        graph.nodes.push_back(n);
        //Add to graph

    }
    file.close();
    file.clear();
    //THIS IS THE START OF THE LOOP
    //Read in Words
    string word;
    file.open(wordFile.c_str());
    while(getline(file, word)){
     //   id++;
        n->id = id;

        //Create node for each letter of the word
        for(int i = 0; i < word.size(); i++){
            n = new Node;
            n->id = id + i + 1;
            n->type = LETTER;
            int pos = word[i] - 'A';
            cout << (int)word[i] - 'A';
            n->letters[pos] = true;
            //Loop through and set edges
            for(int j = 1; j < id; j++){
                if(graph.nodes[j]->letters[pos] == true)
                     cout <<" found edge for " << word[i] << " at "  << j+1 << endl;
            }
            graph.nodes.push_back(n);
        }
        //Add sink to end of graph
        sink->id = graph.nodes.size();
        graph.nodes.push_back(sink);
        //Reset second half of vector for next word
        graph.nodes.erase(graph.nodes.begin() + id, graph.nodes.end());
    }
    file.close();
    //Create Nodes and adj list


}