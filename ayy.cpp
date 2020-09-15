#include<bits/stdc++.h>
using namespace std;

int main()
{
    ifstream fin;
    ofstream fout;

    fin.open("input.txt");
    fout.open("output.txt");

    string line;
    while(getline(fin,line))
    {
        string id1,id2,handle;
        stringstream ss(line);

        getline(fin,id1,'|');
        getline(fin,id2,'|');
        getline(fin,handle,'|');

        fout<<";handle set "<<id1<<" "<<handle<<"\n";
    }

    return 0;
}