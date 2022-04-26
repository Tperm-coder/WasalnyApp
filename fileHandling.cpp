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

int charToInt_to_int(char c)
{
    return (c - '0');
}

int strToInt(string& str)
{
    if (str.length() == 1) { return charToInt_to_int(str[0]); }
    stringstream ans(str);
    int x = 0;
    ans >> x;
    return x;
}


string getRawString(string url)
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
string updateUserData(string new_data , string user_id)
{
    string full_path = fixed_file_path + user_id + ".csv";
    cout <<  "The full file path is :\n" << full_path << endl;

    fstream csv_file;
    csv_file.open(full_path);

    if (!csv_file.fail())
    {
        csv_file << user_id;
        csv_file.close();
    }
    else
    {
        /// in case there is an error while opening the file
        cerr << "Error occurred during writing in the file , Status : 404\n";
        return "404";
    }

}

string getUrlForGraph(string& user_id , string& graph_id )
{
    return fixed_file_path + user_id + '/' + "savedGraphs/" +graph_id + ".csv";
}

Graph getUserGraph(string user_id , string graph_id )
{

    string graph_string =  getRawString(getUrlForGraph(user_id, graph_id));
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
        Node fromNode = Node(splitted_graph[i][1]);
        Node toNode = Node(splitted_graph[i][2]);
        user_graph.addNode(fromNode);
        user_graph.addNode(toNode);
        if (isWeighted)
        {
            Edge curr_edge = Edge(&fromNode,&toNode,strToInt(splitted_graph[i][3]));
            user_graph.addEdge(curr_edge);
        }
        else
        {
            Edge curr_edge = Edge(&fromNode,&toNode);
            user_graph.addEdge(curr_edge);
        }
    }
    cout << "Graph object created successfully\n";

    return user_graph;
}

