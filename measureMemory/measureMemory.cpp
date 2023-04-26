#ifndef ADJLISTTEST_H
#define ADJLISTTEST_H
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

void getGraph(const string &str, vector<vector<int>> &hyperEdge, vector<vector<int>> &hyperNode)
{
    string filename = "/home/C++Projects/graphData/standardized_hypergraph/" + str;
    ifstream fin(filename, ios::in);
    int count = -1;
    unordered_map<int, vector<int>> tmpnode;
    int maxID = INT_MIN;
    while (true)
    {
        string str;
        getline(fin, str);
        if (str == "")
            break;
        istringstream ss(str);
        int tmp;
        vector<int> e;
        while (ss >> tmp)
        {
            e.push_back(tmp);
        }
        count++;
        hyperEdge.push_back(e);
        for (auto &node : e)
        {
            tmpnode[node].push_back(count);
            maxID = max(maxID, node);
        }
    }
    hyperNode.resize(maxID + 1);
    for (auto &info : tmpnode)
    {
        hyperNode[info.first] = info.second;
    }
}

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

void solve(const string &str)
{
    string path = "../result/compressUnordering/";
    // string path = "../result/reorderingHyperedges/";
    // string path = "../result/reorderingVertices/";
    // string path = "../result/reorderingVerticesHyperedges/";
    vector<Vertex> vertexSet;
    vector<int> hyperedgeSet;
    vector<Edge> edgeID;
    vector<int> edgeSet;
    getGraph(path, str, vertexSet, hyperedgeSet, edgeID, edgeSet);
    cout<<vertexSet.size()<<" "<<hyperedgeSet.size()<<" "<<edgeID.size()<<" "<<edgeSet.size()<<endl;
    int cnt = vertexSet.size() * 2 + hyperedgeSet.size() + edgeID.size() * 2 + edgeSet.size();
    cout << cnt << endl;
}

int main()
{
    string fileList = "TaAU MaAn WaTr ThAU ThMS CoMH CoGe CoDB";
    std::vector<std::string> files;
    std::istringstream iss(fileList);
    std::string file;
    while (std::getline(iss, file, ' '))
    {
        files.push_back(file);
    }
// #pragma omp parallel for
    for (int i = 0; i < int(files.size()); i++)
    {
        solve(files[i]);
    }
    cout << "All done!" << endl;
}

#endif
