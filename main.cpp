#include <bits/stdc++.h>
#include <fstream>

using namespace std;

const string fixed_file_path = "";

void split_to_string(vector<string>& vec, string& str, char splitter)
{
    string one_word = " ";
    for (char c : str)
    {
        if (c == splitter) { vec.push_back(one_word); one_word = " "; }
        else { one_word += c; }
    }
    vec.push_back(one_word);
}

int char_to_int(char c)
{
    return (c - '0');
}

int str_to_int(string& str)
{
    if (str.length() == 1) { return char_to_int(str[0]); }
    stringstream ans(str);
    int x = 0;
    ans >> x;
    return x;
}


string get_raw_string(string user_id)
{
    string full_path = fixed_file_path + user_id + ".csv";

    cout <<  "The full file path is : " << full_path << endl;
    string data_string , temp_input;

    fstream csv_file;
    csv_file.open(full_path);

    if (!csv_file.fail())
    {
        while (getline(csv_file, temp_input))
        {
            if (temp_input != "") { data_string += temp_input;  data_string += '\n';}
        }
        csv_file.close();

        return data_string;
    }

    else
    {
        /// in case there is an error while opening the file
        return "404";
    }
}
string update_user_data(string new_data ,  string user_id)
{
    string full_path = fixed_file_path + user_id + ".csv";

    cout <<  "The full file path is : " << full_path << endl;

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
        return "404";
    }

}

string getUserGraphs(string user_id)
{
    // 1-get raw string (done)
    // 2-format raw string (pending)
}


int main()
{
    cout << get_raw_string("data");
    return 0;
}
