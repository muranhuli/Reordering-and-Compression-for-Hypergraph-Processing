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
#include <stack>
#include <thread>
#include <mutex>
#include "oneDimArrayTest.h"
using namespace std;

const int N = 10;

struct Vertex;
struct Edge;

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

void compute(vector<Vertex> &vertexSet, vector<int> &hyperedgeSet, vector<Edge> &edgeID, vector<int> &edgeSet)
{
    for (int k = 0; k < N; k++)
    {
        vector<int> core(int(vertexSet.size()), 0);
        set<pair<int, int>, myCmp> node_count;
        vector<int> deg(int(vertexSet.size()), 0);
        vector<bool> visitEdge(int(edgeID.size()), false);
        vector<bool> visitNode(int(vertexSet.size()), false);
        for (int i = 0; i < int(vertexSet.size()); i++)
        {
            deg[i] = vertexSet[i].posEnd - vertexSet[i].posStar;
            node_count.insert(make_pair(i, deg[i]));
            visitNode[i] = false;
        }
        int K = 0;
        while (!node_count.empty())
        {
            pair<int, int> p = *node_count.begin();
            node_count.erase(node_count.begin());
            K = max(K, p.second);
            core[p.first] = K;
            visitNode[p.first] = true;
            for (int i = vertexSet[p.first].posStar; i < vertexSet[p.first].posEnd; i++)
            {
                int edge = hyperedgeSet[i];
                if (visitEdge[edge])
                    continue;
                visitEdge[edge] = true;
                for (int j = edgeID[edge].posStar; j < edgeID[edge].posEnd; j++)
                {
                    int node = edgeSet[j];
                    if (node == p.first)
                        continue;
                    if (node_count.erase(make_pair(node, deg[node])))
                    {
                        deg[node]--;
                        node_count.insert(make_pair(node, deg[node]));
                    }
                }
            }
        }
    }
}