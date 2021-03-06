
#include <bits/stdc++.h>
#include <fstream>
#include <stdio.h>
#include "graphStructure/Graph.h"

using namespace std;

const string fixedFilePath = "../dataLayer/UsersInfo/"; // relative to the exe file
string graphNamesFileName = "graphName";

class Node;
class Edge;
class Graph;

void splitFromString(unordered_map<int,unordered_map<int,string>>& mp, string& str, char firstSplitter, char secondSplitter)
{
    string oneD = "";
    int line = 1, cell;

//    cout << "Start Split successfully\n";
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
//    cout << "End Split successfully\n";
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
//    cout <<  "The full file path is : " << url << endl;
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

//        cout << "The data was read successfully :\n" << dataString << '\n';
        return dataString;
    }
    else
    {
        /// in case there is an error while opening the file
        cerr << "Error occurred during reading the file , Status : 404\n";
        return "404";
    }
}

string getUrlForGraph(string& graphId)
{
    return fixedFilePath + "Admin" + '/' + "savedGraphs/" + graphId + ".csv";
}

void splitToString(vector<string>& vec, string& str, char splitter)
{
    string one_word = "";
    for (char c : str)
    {
        if (c == splitter) { vec.push_back(one_word); one_word = ""; }
        else { one_word += c; }
    }
    if(!one_word.empty())
        vec.push_back(one_word);
}

vector<string> getCurrentGraphNames()
{
    string NamesString = getRawStringFromFile(getUrlForGraph(graphNamesFileName));
    vector<string> graphNames;

    splitToString(graphNames , NamesString, '\n');

    return graphNames;
}


Graph getUserGraph(string graphId)
{
    string graphString = getRawStringFromFile(getUrlForGraph(graphId));
    unordered_map<int,unordered_map<int,string>> splittedGraph;
    csvStringToMap(splittedGraph, graphString);

    bool isDirected = false, isWeighted = false;
    isDirected = (bool)strToInt(splittedGraph[1][1]);
    isWeighted = (bool)strToInt(splittedGraph[1][2]);

    int nodesNum = strToInt(splittedGraph[2][1]);
    int edgesNum = strToInt(splittedGraph[2][2]);

//    cout << "Graph data retrieved successfully\nCreating Graph object\n";
    Graph userGraph = Graph(isDirected, isWeighted);
    for (int i = 3; i <= 2 + edgesNum; i++)
    {
        Node * fp = new Node(splittedGraph[i][1]);
        Node * tp = new Node(splittedGraph[i][2]);
        fp = userGraph.addNode(fp);
        tp = userGraph.addNode(tp);

        if (isWeighted)
        {
            Edge* currEdge = new Edge(fp, tp, strToInt(splittedGraph[i][3]));
            userGraph.addEdge(currEdge);
        }
        else
        {
            Edge* currEdge = new Edge(fp, tp);
            userGraph.addEdge(currEdge);

        }
    }
//    cout << "Graph object created successfully\n";
    return userGraph;
}

void writeRowStringToFile(string graphId, string dataString)
{
    string url = getUrlForGraph(graphId);
    ofstream csvFile(url);

    csvFile << dataString;
    csvFile.close();
}
void addNewGraphName(string graphName)
{
    vector<string> graphNames = getCurrentGraphNames();

    graphNames.push_back(graphName);

    string newNamesString = "";
    for (string name : graphNames)
    {
        newNamesString += name;
        newNamesString += '\n';
    }

    writeRowStringToFile(graphNamesFileName, newNamesString);
}
void createGraphForUser(string graphId, Graph graph)
{
//    cout << "Creating graph csv string\n";
    string graphCsvString = "";

    graphCsvString += graph.isDirected ? '1' : '0';
    graphCsvString += ',';
    graphCsvString += graph.isWeighted ? '1' : '0';
    graphCsvString += '\n';

    graphCsvString += to_string(graph.nodeLabels.size());
    graphCsvString += ',';
    graphCsvString += to_string(graph.edges.size() / (graph.isDirected ? 1 : 2));
    graphCsvString += '\n';

    bool turn = !graph.isDirected;
    for(auto i: graph.edges)
    {
        if(!graph.isDirected)
            turn ^= true;
        if(turn)
            continue;
        graphCsvString += i.first.from->label + ',' + i.first.to->label + ',' + to_string(i.first.weight) + '\n';
    }

    //cout << "Graph csv string created successfully : \n" << graphCsvString << '\n';
    writeRowStringToFile(graphId , graphCsvString);
    addNewGraphName(graphId);
}

void deleteGraph(string graphName)
{
    vector<string> graphNames = getCurrentGraphNames();

    vector<string> newNames;
    for (string name : graphNames)
    {
        if (name != graphName)
            newNames.push_back(name);
    }

    string newNamesString = "";
    for (string name : newNames)
    {
        newNamesString += name;
        newNamesString += '\n';
    }

    writeRowStringToFile(graphName, "");
    writeRowStringToFile(graphNamesFileName, newNamesString);
}
