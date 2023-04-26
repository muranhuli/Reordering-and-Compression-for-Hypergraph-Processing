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
    vector<double> pr(int(hyperNode.size()), 1.0 / int(hyperNode.size()));
    double d = 0.85;
    for (int m = 0; m < N; m++)
    {
        vector<double> updatePr(int(hyperNode.size()), 0.0);
        for (int u = 0; u < int(hyperNode.size()); u++)
        {
            for (int i = 0; i < int(hyperNode[u].size()); i++)
            {
                int e = hyperNode[u][i];
                for (int j = 0; j < int(hyperEdge[e].size()); j++)
                {
                    int v = hyperEdge[e][j];
                    updatePr[u] += pr[v] * (1.0 / int(hyperNode[v].size() - 0)) * (1.0 / int(hyperEdge[e].size() - 0));
                }
            }
        }
        for (int u = 0; u < int(hyperNode.size()); u++)
        {
            pr[u] = (1 - d) / int(hyperNode.size()) + d * updatePr[u];
        }
    }
}