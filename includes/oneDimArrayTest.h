#ifndef ONEDIMARRAYTEST_H
#define ONEDIMARRAYTEST_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <chrono>
#include <map>
#include <climits>
#include <algorithm>
#include <random>
#include <thread>
#include <mutex>
#include <omp.h>
using namespace std;

struct Vertex
{
    int ID;
    int posStar;
    int posEnd;
};
struct Edge
{
    int ID;
    int posStar;
    int posEnd;
};


void getGraph(const string &path, const string &str, vector<Vertex> &vertexSet, vector<int> &hyperedgeSet, vector<Edge> &edgeID, vector<int> &edgeSet)
{
    ifstream fin(path + str + "-vertexSet");
    while (true)
    {
        string str;
        getline(fin, str);
        if (str == "")
            break;
        istringstream ss(str);
        int a, b, c;
        ss >> a >> b >> c;
        Vertex tmp;
        tmp.ID = a;
        tmp.posStar = b;
        tmp.posEnd = c;
        vertexSet.push_back(tmp);
    }
    fin.close();

    fin.open(path + str + "-hyperedgeSet");
    int a;
    while (fin >> a)
    {
        hyperedgeSet.push_back(a);
    }
    fin.close();

    fin.open(path + str + "-edgeID");
    while (true)
    {
        string str;
        getline(fin, str);
        if (str == "")
            break;
        istringstream ss(str);
        int a, b, c;
        ss >> a >> b >> c;
        Edge tmp;
        tmp.ID = a;
        tmp.posStar = b;
        tmp.posEnd = c;
        edgeID.push_back(tmp);
    }
    fin.close();

    fin.open(path + str + "-edgeSet");
    while (fin >> a)
    {
        edgeSet.push_back(a);
    }
    fin.close();
}

void compute(vector<Vertex> &vertexSet, vector<int> &hyperedgeSet, vector<Edge> &edgeID, vector<int> &edgeSet);

double solve(const string &path, const string &str)
{
    vector<Vertex> vertexSet;
    vector<int> hyperedgeSet;
    vector<Edge> edgeID;
    vector<int> edgeSet;
    getGraph(path, str, vertexSet, hyperedgeSet, edgeID, edgeSet);
    auto t1 = std::chrono::steady_clock::now();
    compute(vertexSet, hyperedgeSet, edgeID, edgeSet);
    auto t2 = std::chrono::steady_clock::now();
    double dr_ns = std::chrono::duration<double, std::nano>(t2 - t1).count();
    return dr_ns;
}

int main(int argc, char* argv[])
{
    string path = argv[1];
    string fileList = "TaAU MaAn WaTr ThAU ThMS CoMH CoGe CoDB";
    std::vector<std::string> files;
    std::istringstream iss(fileList);
    std::string file;
    while (std::getline(iss, file, ' '))
    {
        files.push_back(file);
    }
    vector<double> time(files.size(),0);
#pragma omp parallel for
    for (int i = 0; i < int(files.size()); i++)
    {
        time[i] = solve(path, files[i]);
    }
    for(auto t:time)
    {
        cout<<t<<endl;
    }
    cout << "All done!" << endl;
}

#endif
