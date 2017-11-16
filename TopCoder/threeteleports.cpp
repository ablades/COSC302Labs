using namespace std;

struct ThreeTeleports{
    int shortestDistance(int xMe, int yMe, int xHome, int yHome, vector<string>teleports);
};
struct Node{
    long long x;
    long long y;
    bool visited;
    long long cost;
    multimap<long long>::iterator qit;
    Node() : visited(false), cost(-1), qit(nullptr) {}
};

int ThreeTeleports::shortestDistance(int xMe, int yMe, int xHome, int yHome, vector <string> teleports) {
    multimap<int, Node> mm;
    vector
    Node n;
    n = new Node;
    n.x = xMe;
    n.y = yMe;

    for(int i =0; i < teleports.size(); i++){
        stringstream ss(teleports[i]);

        int x1, y1, x2, y2;
        ss >> x1 >> y1 >> x2 >> y2;

        n = new Node;
        n.x = x1;
        n.y = y1;
        mm.insert(n.cost, n);

        n = new Node;
        n.x = x1;
        n.y = y1;
        mm.insert(n.cost, n);
    }

    n = new Node;
    n.x = xHome;
    n.y = yHome;
    mm.insert(n.cost, n);

    vector< vector <int> > adj_mat (locations.size(), vector <int>(locations.size()));



    while(q.size()){
        long long cost = q.begin()->first;
        int index = q.begin()->second;
        Node &n = nodes[index];
        q.erase(q.begin());

        n.visited = true;

        for(int i = 0; i < nodes.size(); i++){

        }

    }
}
