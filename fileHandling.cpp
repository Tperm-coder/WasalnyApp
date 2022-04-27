#include <bits/stdc++.h>
#include <fstream>
#include "graphStructure/Graph.h"

using namespace std;
const string fixed_file_path = "../dataLayer/UsersInfo/"; // relative to the exe file

class Node;
class Edge;
class Graph;

// camel case 34an 5ater el coach
void splitFromString(unordered_map<int,unordered_map<int,string>>& mp , string& str , char first_splitter , char second_splitter)
{
    string oneD = "";
    int line = 1 , cell;

    cout << "Start Split successfully\n";
    str += first_splitter;
    for (char c : str)
    {
        cell = 1;
        if (c == first_splitter)
        {
            string twoD = "";
            oneD += second_splitter;

            for (char cc : oneD)
            {
                if (cc == second_splitter)
                {
                    mp[line][cell] = twoD;
                    twoD = "";
                    cell++;
                }
                else { twoD += cc; }
            }
            oneD = "";
            line++;
        }
        else { oneD += c; }
    }
    cout << "End Split successfully\n";
}

void csvStringToMap(unordered_map<int,unordered_map<int,string>>& mp , string& csv_string)
{
    splitFromString(mp,csv_string,'\n',',');
}

int charToInt(char c)
{
    return (c - '0');
}

int strToInt(string& str)
{
    if (str.length() == 1) { return charToInt(str[0]); }
    stringstream ans(str);
    int x = 0;
    ans >> x;
    return x;
}


string getRawStringFromFile(string url)
{
    cout <<  "The full file path is : " << url << endl;
    string data_string , temp_input;

    fstream csv_file;
    csv_file.open(url);

    if (!csv_file.fail())
    {
        while (getline(csv_file, temp_input))
        {
            if (temp_input != "") { data_string += temp_input;  data_string += '\n';}
        }
        csv_file.close();

        cout << "The data was read successfully :\n" << data_string <<'\n';
        return data_string;
    }

    else
    {
        /// in case there is an error while opening the file
        cerr << "Error occurred during reading the file , Status : 404\n";
        return "404";
    }
}

string getUrlForGraph(string& user_id , string& graph_id )
{
    return fixed_file_path + user_id + '/' + "savedGraphs/" +graph_id + ".csv";
}

Graph getUserGraph(string user_id , string graph_id )
{

    string graph_string = getRawStringFromFile(getUrlForGraph(user_id, graph_id));
    unordered_map<int,unordered_map<int,string>> splitted_graph;

    csvStringToMap(splitted_graph,graph_string);

    bool isDirected = false, isWeighted = false;
    isDirected = (bool)strToInt(splitted_graph[1][1]);
    isWeighted = (bool)strToInt(splitted_graph[1][2]);

    int nodes_num = strToInt(splitted_graph[2][1]);
    int edges_num = strToInt(splitted_graph[2][2]); //useless


    cout << "Graph data retrieved successfully\nCreating Graph object\n";
    Graph user_graph = Graph(isDirected,isWeighted);

    for (int i = 3 ; i <= 2 + nodes_num ; i++)
    {
        Node * fp = new Node(splitted_graph[i][1]);
        Node * tp = new Node(splitted_graph[i][2]);

        user_graph.addNode(fp);
        user_graph.addNode(tp);

        if (isWeighted)
        {
            Edge curr_edge = Edge(fp,tp,strToInt(splitted_graph[i][3]));
            user_graph.addEdge(curr_edge);
        }
        else
        {
            Edge curr_edge = Edge(fp,tp);
            user_graph.addEdge(curr_edge);
        }
    }
    cout << "Graph object created successfully\n";

    return user_graph;
}

void writeRowStringToFile(string user_id , string graph_id , string dataString)
{
    string url = getUrlForGraph(user_id, graph_id);
    cout <<  "The full file path is : " << url << endl;

    ofstream  csv_file(url);

    cout << "File was opened successfully\n";

    csv_file << dataString;
    csv_file.close();

    cout << "Data was written successfully\n";
}

void createGraphForUser(string user_id , string graph_id , Graph graph)
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

    for (auto i : graph.edges)
    {
        graphCsvString += i.from->label + ',' + i.to->label + ',' + to_string(i.weight) + '\n';
    }

    cout << "Graph csv string created successfully : \n" << graphCsvString << '\n';
    writeRowStringToFile(user_id , graph_id ,graphCsvString );
}
