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

typedef pair<int, int> PII;

struct myCmp
{
    bool operator()(const PII &a, const PII &b) const
    {
        if (a.first == b.first)
            return false;
        else
        {
            if (a.second != b.second)
                return a.second > b.second;
            else
                return a.first < b.first;
        }
    }
};

void getGraph(const string &filename, vector<vector<int>> &hyperEdge, unordered_map<int, vector<int>> &hyperNode)
{
    ifstream fin(filename, ios::in);
    int count = -1;
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
            if (find(e.begin(), e.end(), tmp) == e.end())
                e.push_back(tmp);
        }
        if (e.size() == 1)
            continue;
        count++;
        hyperEdge.push_back(e);
        for (auto &node : e)
            hyperNode[node].push_back(count);
    }
}

void reconstructGraph(const string &str, vector<vector<int>> &hyperEdge, unordered_map<int, vector<int>> &hyperNode, vector<Vertex> &vertexSet, vector<int> &hyperedgeSet, vector<Edge> &edgeID, vector<int> &edgeSet, int w)
{
    set<PII, myCmp> remainSet;
    unordered_map<int, int> key;
    unordered_map<int, bool> visitHyperedge;
    int pos = -1, cardi = -1;
    for (int i = 0; i < int(hyperEdge.size()); ++i)
    {
        remainSet.insert(make_pair(i, 0));
        key[i] = 0;
        visitHyperedge[i] = false;
        if (int(hyperEdge[i].size()) > cardi)
        {
            pos = i;
            cardi = int(hyperEdge[i].size());
        }
    }
    Edge tmp;
    tmp.ID = pos;
    tmp.posStar = 0;
    tmp.posEnd = 0;
    edgeID.push_back(tmp);
    remainSet.erase(make_pair(pos, key[pos]));
    visitHyperedge[pos] = true;
    int i = 1;
    while (i < int(hyperEdge.size()))
    {
        int ve = edgeID[i - 1].ID;
        for (auto &node : hyperEdge[ve])
        {
            for (auto &edge : hyperNode[node])
            {
                if (!visitHyperedge[edge])
                {
                    if (remainSet.erase(make_pair(edge, key[edge])))
                    {
                        ++key[edge];
                        remainSet.insert(make_pair(edge, key[edge]));
                    }
                }
            }
        }
        if (i > w - 1)
        {
            int vs = edgeID[i - w].ID;
            for (auto &node : hyperEdge[vs])
            {
                for (auto &edge : hyperNode[node])
                {
                    if (!visitHyperedge[edge])
                    {
                        if (remainSet.erase(make_pair(edge, key[edge])))
                        {
                            --key[edge];
                            remainSet.insert(make_pair(edge, key[edge]));
                        }
                    }
                }
            }
        }
        PII p = *remainSet.begin();
        remainSet.erase(remainSet.begin());
        Edge tmp;
        tmp.ID = p.first;
        tmp.posStar = 0;
        tmp.posEnd = 0;
        edgeID.push_back(tmp);
        visitHyperedge[p.first] = true;
        ++i;
    }
    // process hyperedges
    for (int i = 0; i < int(edgeID.size()); i++)
    {
        unordered_map<int, int> tmp;
        if (i == int(edgeID.size()) - 1)
        {
            for (auto &node : hyperEdge[edgeID[i].ID])
                tmp[node]++;
            if (i > 0)
            {
                for (int j = edgeID[i].posStar; j < edgeID[i - 1].posEnd; j++)
                    tmp.erase(tmp.find(edgeSet[j]));
            }
            for (auto it = tmp.begin(); it != tmp.end(); it++)
            {
                edgeSet.push_back(it->first);
            }
            edgeID[i].posEnd = int(edgeSet.size());
            break;
        }

        for (auto &node : hyperEdge[edgeID[i].ID])
            tmp[node]++;
        if (i > 0)
        {
            for (int j = edgeID[i].posStar; j < edgeID[i - 1].posEnd; j++)
                tmp.erase(tmp.find(edgeSet[j]));
        }
        for (auto &node : hyperEdge[edgeID[i + 1].ID])
        {
            if (tmp.find(node) != tmp.end())
            {
                tmp[node]++;
            }
        }
        for (auto it = tmp.begin(); it != tmp.end(); it++)
        {
            if (it->second == 1)
            {
                edgeSet.push_back(it->first);
            }
        }
        edgeID[i + 1].posStar = int(edgeSet.size());
        for (auto it = tmp.begin(); it != tmp.end(); it++)
        {
            if (it->second == 2)
            {
                edgeSet.push_back(it->first);
            }
        }
        edgeID[i].posEnd = int(edgeSet.size());
    }
    // process vertices
    vertexSet.resize(int(hyperNode.size()));;
    for (int i = 0; i < int(hyperNode.size()); i++)
    {
        vertexSet[i].ID = i;
        unordered_map<int, int> tmp;
        if (i == int(hyperNode.size()) - 1)
        {
            for (auto &edge : hyperNode[i])
                tmp[edge]++;
            if (i > 0)
            {
                for (int j = vertexSet[i].posStar; j < vertexSet[i - 1].posEnd; j++)
                    tmp.erase(tmp.find(hyperedgeSet[j]));
            }
            for (auto it = tmp.begin(); it != tmp.end(); it++)
            {
                hyperedgeSet.push_back(it->first);
            }
            vertexSet[i].posEnd = int(hyperedgeSet.size());
            break;
        }
        for (auto &edge : hyperNode.at(i))
            tmp[edge]++;
        if (i > 0)
        {
            for (int j = vertexSet[i].posStar; j < vertexSet[i - 1].posEnd; j++)
                tmp.erase(tmp.find(hyperedgeSet[j]));
        }
        for (auto &edge : hyperNode.at(i + 1))
        {
            if (tmp.find(edge) != tmp.end())
            {
                tmp[edge]++;
            }
        }
        for (auto it = tmp.begin(); it != tmp.end(); it++)
        {
            if (it->second == 1)
            {
                hyperedgeSet.push_back(it->first);
            }
        }
        vertexSet[i + 1].posStar = int(hyperedgeSet.size());
        for (auto it = tmp.begin(); it != tmp.end(); it++)
        {
            if (it->second == 2)
            {
                hyperedgeSet.push_back(it->first);
            }
        }
        vertexSet[i].posEnd = int(hyperedgeSet.size());
    }
    vertexSet[0].posStar = 0;
}

void output(const string &str, vector<vector<int>> &hyperEdge, unordered_map<int, vector<int>> &hyperNode, vector<Vertex> &vertexSet, vector<int> &hyperedgeSet, vector<Edge> &edgeID, vector<int> &edgeSet, int w)
{
    unordered_map<int, int> ID;
    // convert ID
    for (int i = 0; i < int(edgeID.size()); i++)
    {
        ID[edgeID[i].ID] = i;
    }
    vector<vector<int>> pairs;
    for (int i = 0; i < int(hyperEdge.size()); i++)
    {
        pairs.push_back(hyperEdge[edgeID[i].ID]);
    }
    for (int i = 0; i < int(hyperEdge.size()); i++)
    {
        hyperEdge[i] = pairs[i];
    }
    for (auto &info : edgeID)
    {
        info.ID = ID[info.ID];
    }
    for (int i = 0; i < int(hyperedgeSet.size()); i++)
    {
        hyperedgeSet[i] = ID[hyperedgeSet[i]];
    }

    ofstream fout("./result/reorderingHyperedges/" + str + "-vertexSet");
    for (auto it : vertexSet)
    {
        fout << it.ID << ' ' << it.posStar << ' ' << it.posEnd << endl;
    }
    fout.close();

    fout.open("./result/reorderingHyperedges/" + str + "-hyperedgeSet");
    for (auto it : hyperedgeSet)
    {
        fout << it << endl;
    }
    fout.close();

    fout.open("./result/reorderingHyperedges/" + str + "-edgeID");
    for (auto it : edgeID)
    {
        fout << it.ID << ' ' << it.posStar << ' ' << it.posEnd << endl;
    }
    fout.close();
    fout.open("./result/reorderingHyperedges/" + str + "-edgeSet");
    for (auto it : edgeSet)
    {
        fout << it << endl;
    }
    fout.close();

    fout.open("./result/reorderingHyperedgesUncompre/" + str);
    for (int i = 0; i < int(hyperEdge.size()); i++)
    {
        for (int j = 0; j < int(hyperEdge[i].size()); j++)
        {
            fout << hyperEdge[i][j] << ' ';
        }
        fout << endl;
    }
    fout.close();
}

void solve(const string &str)
{
    int thread_id = omp_get_thread_num();
    int num_threads = omp_get_num_threads();
#pragma omp critical
    {
        cout << "file:" << str << " thread_id: " << thread_id << " num_threads: " << num_threads << endl;
    }

    string path = "/home/C++Projects/graphData/standardized_hypergraph/";
    string filename = path + str;
    vector<vector<int>> hyperEdge;
    unordered_map<int, vector<int>> hyperNode;
    getGraph(filename, hyperEdge, hyperNode);
    vector<Vertex> vertexSet;
    vector<int> hyperedgeSet;
    vector<Edge> edgeID;
    vector<int> edgeSet;
    int w = 16;
    reconstructGraph(str, hyperEdge, hyperNode, vertexSet, hyperedgeSet, edgeID, edgeSet, w);
    output(str, hyperEdge, hyperNode, vertexSet, hyperedgeSet, edgeID, edgeSet, w);
#pragma omp critical
    {
        cout << "file:" << str << "done!" << endl;
    }
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
#pragma omp parallel for
    for (int i = 0; i < int(files.size()); i++)
    {
        solve(files[i]);
    }
    cout << "All done!" << endl;
}
