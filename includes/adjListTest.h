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

void compute(vector<vector<int>> &hyperEdge, vector<vector<int>> &hyperNode);

double solve(const string &str)
{
    vector<vector<int>> hyperEdge;
    vector<vector<int>> hyperNode;
    getGraph(str, hyperEdge, hyperNode);
    auto t1 = std::chrono::steady_clock::now();
    compute(hyperEdge, hyperNode);
    auto t2 = std::chrono::steady_clock::now();
    double dr_ns = std::chrono::duration<double, std::nano>(t2 - t1).count();
    return dr_ns;
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
    vector<double> time(files.size(),0);
#pragma omp parallel for
    for (int i = 0; i < int(files.size()); i++)
    {
        time[i] = solve(files[i]);
    }
    for(auto t:time)
    {
        cout<<t<<endl;
    }
    cout << "All done!" << endl;
}

#endif

