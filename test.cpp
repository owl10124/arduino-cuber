#include <iostream>
#include <memory>
#include <array>
#include <vector>
using namespace std;
int i;
vector<string> split(string input, string delimiter)
{
    vector<string> result;
    size_t pos = 0;
    while ((pos = input.find(delimiter))!=string::npos)
    {
        result.push_back(input.substr(0, pos));
        input.erase(0, pos+delimiter.length());
    }
    result.push_back(input);
    return result;
}


string replace (string input, string from, string to)
{
    cout<<"replace \n";
    size_t start;
    start = 0;
    while ((start = input.find(from, start))!=string::npos)
    {
        input.replace(start, from.length(), to);
        start+=to.length();
    }
    return input;
}

int main()
{
        string result = "U D D' B2 F2 L' D";
        result = replace(result, "U2", "U U");
        result = replace(result, "D2", "D D");
        result = replace(result, "L2", "L L");
        result = replace(result, "R2", "R R");
        result = replace(result, "F2", "F F");
        result = replace(result, "B2", "B B");

        cout<<result<<"\n";

        vector<string> moves = split(result, " ");
        char solution[moves.size()+1];
        for (i=0;i<moves.size();i++)
        {
                cout<<moves[i]<<"\n";
                if (moves[i]== "U") solution[i]='A';
                else if (moves[i]== "U'") solution[i]='B';
                else if (moves[i]== "D") solution[i]='C';
                else if (moves[i]== "D'") solution[i]='D';
                else if (moves[i]== "F") solution[i]='E';
                else if (moves[i]== "F'") solution[i]='F';
                else if (moves[i]== "B") solution[i]='G';
                else if (moves[i]== "B'") solution[i]='H';
                else if (moves[i]== "L") solution[i]='I';
                else if (moves[i]== "L'") solution[i]='J';
                else if (moves[i]== "R") solution[i]='K';
                else if (moves[i]== "R'") solution[i]='L';
        }
        solution[moves.size()]='\0';
}