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

void compute(vector<vector<int>> &hyperEdge, vector<vector<int>> &hyperNode)
{
    default_random_engine seed(time(NULL));
    mt19937_64 gen(seed());
    int max = int(hyperNode.size()) - 1;
    uniform_int_distribution<int> dist(0, max);

    for (int k = 0; k < N; k++)
    {
        int v = dist(gen);
        stack<int> q;
        q.push(v);
        unordered_map<int, bool> visitVertex;
        unordered_map<int, bool> visitEdge;
        visitVertex[v] = true;
        while (!q.empty())
        {
            int u = q.top();
            q.pop();
            int e = int(hyperNode[u].size());
            for (auto i = 0; i < e; i++)
            {
                int edge = hyperNode[u][i];
                if (!visitEdge[edge])
                {
                    visitEdge[edge] = true;
                    int e1 = int(hyperEdge[edge].size());
                    for (auto j = 0; j < e1; j++)
                    {
                        int node = hyperEdge[edge][j];
                        if (!visitVertex[node])
                        {
                            visitVertex[node] = true;
                            q.push(node);
                        }
                    }
                }
            }
        }
    }
}