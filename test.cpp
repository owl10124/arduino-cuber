#include <iostream>
#include <memory>
#include <array>
#include <vector>
using namespace std;
vector<string> split(string input, string delimiter)
{
    vector<string> result;
    size_t pos = 0;
    while ((pos = input.find(delimiter))!=string::npos)
    {
        result.push_back(input.substr(0, pos));
        input.erase(0, pos+delimiter.length());
    }
    return result;
}

int main()
{
    vector<string> splitted = split("A B C DE FG", " ");
    for (int i=0;i<splitted.size();i++)
    {
        cout<<splitted[i]<<endl;
    }
    return 0;
}