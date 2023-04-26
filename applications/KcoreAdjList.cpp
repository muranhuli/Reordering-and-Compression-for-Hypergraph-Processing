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
#include "adjListTest.h"
using namespace std;

const int N = 10;

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

void compute(vector<vector<int>> &hyperEdge, vector<vector<int>> &hyperNode)
{
    for (int k = 0; k < N; k++)
    {
        vector<int> core(int(hyperNode.size()), 0);
        set<PII, myCmp> node_count;
        vector<int> deg(int(hyperNode.size()), 0);
        vector<bool> visitEdge(int(hyperEdge.size()), false);
        vector<bool> visitNode(int(hyperNode.size()), false);
        for (int i = 0; i < int(hyperNode.size()); i++)
        {
            deg[i] = int(hyperNode[i].size());
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
            for (int i = 0; i < int(hyperNode[p.first].size()); i++)
            {
                int edge = hyperNode[p.first][i];
                if (visitEdge[edge])
                    continue;
                visitEdge[edge] = true;
                for (int j = 0; j < int(hyperEdge[edge].size()); j++)
                {
                    int node = hyperEdge[edge][j];
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