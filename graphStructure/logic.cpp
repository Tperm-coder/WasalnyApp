#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include "Bfs.cpp"
#include "Bellman.cpp"
#include "Dijkstra.cpp"
#include <bits/stdc++.h>
using namespace std;

int nodes, edges;
bool isDirected, isWeighted;

string question;
Graph g = Graph(0, 0);
bool isNumeric(const string& response) {
    return all_of(response.begin(), response.end(), [](char c) {
        return isdigit(c);
    });
}

string getOrder(int order) {
    if (order == 1)
        return "1st";
    else if (order == 2)
        return "2nd";
    else if (order == 3)
        return "3rd";
    else
        return to_string(order) + "th";
}

string ask(const string& Question) {
    cout << Question;
    string response;
    getline(cin, response);
    return response;
}

int yesNoQuestion(const string& Question) {
    string response = "*";
    while (response != "y" && response != "n")
        response = ask(Question + " (y/n): ");
    if (response == "y")
        return 1;
    else if (response == "n")
        return 0;
    else
        return -1;
}

int numberQuestion(const string& Question) {
    string response = "*";
    while (!isNumeric(response))
        response = ask(Question + ' ');
    return stoi(response);
}

Node* findNode(string label) {
    if (!g.ids.count(label)) {
        cout << "Please enter a valid node" << endl;
        return NULL;
    }
    return g.nodes[g.ids[label]];
}

Node* getNode(const string& Question) {
    string label = "";
    while (label == "" || findNode(label) == NULL)
        label = ask(Question);
    return findNode(label);
}

void loadGraph() {

}
void getShortestPath()
{
    cout << "Choose the source and destination nodes" << endl;
    Node* from = getNode("Enter the source node: ");
    Node* to = getNode("Enter the destination node: ");

    bool algoOptions[] = {0, 1, 1, 0};
    question = "Which algorithm do you want to use?\n(1)Dijkstra\n(2)Bellman\n";

    if (!isWeighted)
        question += "(3)Bfs\n", algoOptions[3] = 1;

    int algo = 0;
    while (algo < 1 || algo > 3 || !algoOptions[algo])
        algo = numberQuestion(question);

    Path *path;
    if (algo == 1)
        path = Dijkstra(from, to);
    else if (algo == 2)
        path = Bellman(from, to, &g);
    else
        path = Bfs(from, to);

    path->Display();
}
void deleteGraph()
{

}
void updateGraph()
{
    question = "How would you like to update the graph?\n(1)Delete a node\n(2)Delete an edge\n(3)Add a node\n(4)Add an edge\n";
    int ans = 0;
    while (ans < 1 || ans > 4)
        ans = numberQuestion(question);
    if(ans == 1)
    {
        string nodeName = ask("Enter the node's name\n");
        Node *node = findNode(nodeName);
        g.nodes.erase(find(g.nodes.begin(), g.nodes.end(), node));
    }
    else if(ans == 2)
    {

    }
    else if(ans == 3)
    {

    }
    else if(ans == 4)
    {

    }
}
void createGraph() {
    isDirected = yesNoQuestion("Are the edges directed?");
    isWeighted = yesNoQuestion("Are the edges weighted?");

    nodes = numberQuestion("Enter the number of nodes:");
    edges = numberQuestion("Enter the number of edges:");

    g = Graph(isDirected, isWeighted);

    for (int i = 0; i < nodes; i++) {
        string label;
        label = ask("Enter the " + getOrder(i + 1) + " node's label: ");
        Node* node = new Node(label);
        g.addNode(node);
    }

    for (int i = 0; i < edges; i++) {
        int weight = 1;
        string from, to;

        cout << getOrder(i + 1) + " edge:" << endl;

        Node *u = NULL;
        while (u == NULL) {
            from = ask("Enter the 1st node: ");
            u = findNode(from);
        }

        Node *v = NULL;
        while (v == NULL) {
            to = ask("Enter the 2nd node: ");
            v = findNode(to);
        }

        if (isWeighted)
            weight = numberQuestion("Enter the weight of the edge: ");

        Edge *e = new Edge(u, v, weight);
        g.addEdge(e);
    }
}

int main()
{
    int loadExistingGraph = -1;
    while (loadExistingGraph == -1)
        loadExistingGraph = yesNoQuestion("Load existing graph?");

    if (loadExistingGraph)
        loadGraph();
    else
        createGraph();

    while (1) {
        question = "What do you want to do with the current graph?\n(1)Delete current graph\n(2)Update current graph\n(3)Get shortest path between two nodes\n";
        int ans = numberQuestion(question);
        if(ans == 1)
        {

        }
        else if(ans == 2)
        {

        }
        else if(ans == 3)
            getShortestPath();
        createGraph();
    }
}