#include <bits/stdc++.h>
#include <fstream>
#include "graphStructure/Graph.h"

using namespace std;
const string fixedFilePath = "../dataLayer/UsersInfo/"; // relative to the exe file

class Node;
class Edge;
class Graph;

void splitFromString(unordered_map<int,unordered_map<int,string>>& mp, string& str, char firstSplitter, char secondSplitter)
{
    string oneD = "";
    int line = 1, cell;

    cout << "Start Split successfully\n";
    str += firstSplitter;
    for (char c: str)
    {
        cell = 1;
        if (c == firstSplitter)
        {
            string twoD = "";
            oneD += secondSplitter;

            for (char cc: oneD)
            {
                if (cc == secondSplitter)
                {
                    mp[line][cell] = twoD;
                    twoD = "";
                    cell++;
                }
                else
                    twoD += cc;
            }
            oneD = "";
            line++;
        }
        else
            oneD += c;
    }
    cout << "End Split successfully\n";
}

void csvStringToMap(unordered_map<int,unordered_map<int,string>>& mp, string& csvString)
{
    splitFromString(mp, csvString, '\n', ',');
}

int charToInt(char c)
{
    return (c - '0');
}

int strToInt(string& str)
{
    if (str.length() == 1)
        return charToInt(str[0]);
    stringstream ans(str);
    int x = 0;
    ans >> x;
    return x;
}


string getRawStringFromFile(string url)
{
    cout <<  "The full file path is : " << url << endl;
    string dataString, tempInput;

    fstream csvFile;
    csvFile.open(url);

    if (!csvFile.fail())
    {
        while (getline(csvFile, tempInput))
        {
            if (tempInput != "") {
                dataString += tempInput;
                dataString += '\n';
            }
        }
        csvFile.close();

        cout << "The data was read successfully :\n" << dataString << '\n';
        return dataString;
    }
    else
    {
        /// in case there is an error while opening the file
        cerr << "Error occurred during reading the file , Status : 404\n";
        return "404";
    }
}

string getUrlForGraph(string& userId, string& graphId)
{
    return fixedFilePath + userId + '/' + "savedGraphs/" + graphId + ".csv";
}

Graph getUserGraph(string userId, string graphId)
{

    string graphString = getRawStringFromFile(getUrlForGraph(userId, graphId));
    unordered_map<int,unordered_map<int,string>> splittedGraph;

    csvStringToMap(splittedGraph, graphString);

    bool isDirected = false, isWeighted = false;
    isDirected = (bool)strToInt(splittedGraph[1][1]);
    isWeighted = (bool)strToInt(splittedGraph[1][2]);

    int nodesNum = strToInt(splittedGraph[2][1]);
    int edgesNum = strToInt(splittedGraph[2][2]); //useless


    cout << "Graph data retrieved successfully\nCreating Graph object\n";
    Graph userGraph = Graph(isDirected, isWeighted);

    for (int i = 3; i <= 2 + nodesNum; i++)
    {
        Node * fp = new Node(splittedGraph[i][1]);
        Node * tp = new Node(splittedGraph[i][2]);

        userGraph.addNode(fp);
        userGraph.addNode(tp);

        if (isWeighted)
        {
            Edge currEdge = Edge(fp, tp, strToInt(splittedGraph[i][3]));
            userGraph.addEdge(currEdge);
        }
        else
        {
            Edge currEdge = Edge(fp, tp);
            userGraph.addEdge(currEdge);
        }
    }
    cout << "Graph object created successfully\n";

    return userGraph;
}

void writeRowStringToFile(string userId, string graphId, string dataString)
{
    string url = getUrlForGraph(userId, graphId);
    cout <<  "The full file path is : " << url << endl;

    ofstream csvFile(url);

    cout << "File was opened successfully\n";

    csvFile << dataString;
    csvFile.close();

    cout << "Data was written successfully\n";
}

void createGraphForUser(string userId, string graphId, Graph graph)
{

    cout << "Creating graph csv string\n";
    string graphCsvString = "";

    graphCsvString += graph.isDirected ? '1' : '0';
    graphCsvString += ',';
    graphCsvString += graph.isWeighted ? '1' : '0';
    graphCsvString += '\n';

    graphCsvString += to_string(graph.nodes.size());
    graphCsvString += ',';
    graphCsvString += to_string(graph.edges.size());
    graphCsvString += '\n';

    for (auto i: graph.edges)
    {
        graphCsvString += i.from->label + ',' + i.to->label + ',' + to_string(i.weight) + '\n';
    }

    cout << "Graph csv string created successfully : \n" << graphCsvString << '\n';
    writeRowStringToFile(userId , graphId , graphCsvString );
}
