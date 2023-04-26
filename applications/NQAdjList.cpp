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
        vector<bool> visited(int(hyperNode.size()), false);
        for (int i = 0; i < int(hyperNode[v].size()); i++)
        {
            int e = hyperNode[v][i];
            for (int j = 0; j < int(hyperEdge[e].size()); j++)
            {
                int u = hyperEdge[e][j];
            }
        }
    }
}