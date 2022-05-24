#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include "Bfs.cpp"
#include "Bellman.cpp"
#include "Dijkstra.cpp"
#include "../fileHandling.cpp"
#include <bits/stdc++.h>
using namespace std;

int nodes, edges;
bool isDirected, isWeighted;

string question, graphName;
Graph g = Graph(0, 0);

bool isNumeric(const string& response)
{
    return all_of(response.begin(), response.end(), [](char c) {
        return isdigit(c);
    });
}

string getOrder(int order)
{
    if (order == 1)
        return "1st";
    else if (order == 2)
        return "2nd";
    else if (order == 3)
        return "3rd";
    else
        return to_string(order) + "th";
}

string ask(const string& Question)
{
    cout << Question;
    string response;
    cin >> response;
    return response;
}

int yesNoQuestion(const string& Question)
{
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

int numberQuestion(const string& Question)
{
    string response = "*";
    while (!isNumeric(response) || response.empty())
        response = ask(Question + ' ');
    return stoi(response);
}

Node* findNode(string label)
{
    if (!g.ids.count(label))
    {
        cout << "Please enter a valid node" << endl;
        return NULL;
    }
    return g.nodes[g.ids[label]];
}

Node* getNode(const string& Question)
{
    string label = "";
    while (label == "" || findNode(label) == NULL)
        label = ask(Question);
    return findNode(label);
}

void loadGraph(string name)
{
    graphName = name;
    g = getUserGraph(graphName);
    nodes = g.nodeCount;
    edges = g.edges.size();
    isDirected = g.isDirected;
    isWeighted = g.isWeighted;
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
void updateGraph()
{
    question = "How would you like to update the graph?\n"
               "(1) Display graph\n"
               "(2) Add a node\n"
               "(3) Add an edge\n"
               "(4) Update a node's name\n";

    if(isWeighted)
        question += "(5) Update an edge's weight\n";

    int response = 0, limit = 4 + isWeighted;
    while (response < 1 || response > limit)
        response = numberQuestion(question);
    if(response == 4)
    {
        cout << "Choose which node to update its name:\n";
        for(int i = 0; i < g.nodeLabels.size(); i++)
            cout << i + 1 << ": " << g.nodeLabels[i] << '\n';

        cin >> response;
        response--;
        string newName = ask("Enter the new name: ");
        for(auto& it : g.nodes)
        {
            if(it->label == g.nodeLabels[response])
            {
                it->label = newName;
                break;
            }
        }
        g.ids[newName] = g.ids[g.nodeLabels[response]];
        g.ids.erase(g.nodeLabels[response]);
        g.nodeLabels[response] = newName;
    }
    else if(response == 5)
    {
        cout << "Choose which edge to update its weight:\n";
        for(int i = 0; i < g.edges.size(); i += (!isDirected) + 1)
        {
            auto edge = g.edges[i].first;
            cout << i + 1 << ": " << edge.from << ' ' << edge.to;
            if(isWeighted)
                cout << ' ' << edge.weight;
            cout << '\n';
        }

        cin >> response;
        response--;
        int newWeight = numberQuestion("Enter the new weight: ");

        if(!isDirected)
        {
            g.edges[response].first.weight = g.edges[response + 1].first.weight = newWeight;
            g.edges[response].second->weight = g.edges[response + 1].second->weight = newWeight;
        }
        else
        {
            g.edges[response].first.weight = newWeight;
            g.edges[response].second->weight = newWeight;
        }
    }
    else if(response == 2)
    {
        string label;
        label = ask("Enter the new node's label: ");
        Node* node = new Node(label);
        g.addNode(node);
    }
    else if(response == 3)
    {
        int weight = 1;
        string from, to;

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
    else if(response == 1)
    {
        for(auto i : g.nodeLabels)
            cout << i << ' ';
        cout << endl;
    }
    deleteGraph(graphName);
    createGraphForUser(graphName, g);
}
void createGraph()
{
    isDirected = yesNoQuestion("Are the edges directed?");
    isWeighted = yesNoQuestion("Are the edges weighted?");

    nodes = numberQuestion("Enter the number of nodes:");
    edges = numberQuestion("Enter the number of edges:");

    g = Graph(isDirected, isWeighted);

    for (int i = 0; i < nodes; i++)
    {
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

    createGraphForUser(graphName, g);
}

int main()
{
    auto graphNames = getCurrentGraphNames();

    int loadExistingGraph = -1;
    while (loadExistingGraph == -1 && !graphNames.empty())
        loadExistingGraph = yesNoQuestion("Load existing graph?");

    if (loadExistingGraph == 1)
    {
        int response;
        cout << "Choose one of the following graphs: \n";
        for(int i = 0; i < graphNames.size(); i++)
            cout << i + 1 << ": " << graphNames[i] << '\n';

        cin >> response;
        loadGraph(graphNames[response - 1]);
    }
    else
    {
        graphName = ask("Enter the graph name: ");
        createGraph();
    }
    while (1)
    {
        question = "What do you want to do with the current graph?\n"
                   "(1)Delete current graph\n"
                   "(2)Update current graph\n"
                   "(3)Get shortest path between two nodes\n";
        int ans = numberQuestion(question);
        if(ans == 1)
            deleteGraph(graphName);
        else if(ans == 2)
            updateGraph();
        else if(ans == 3)
            getShortestPath();
    }
}