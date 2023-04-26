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

const int N = 5;

void compute(vector<vector<int>> &hyperEdge, vector<vector<int>> &hyperNode)
{
    default_random_engine seed(time(NULL));
    mt19937_64 gen(seed());
    int max = int(hyperNode.size()) - 1;
    uniform_int_distribution<int> dist(0, max);

    for (int k = 0; k < N; k++)
    { 
        int u = dist(gen);
        int v = dist(gen);
        // u和v的最短路长度
        vector<int> dist(int(hyperNode.size()), INT_MAX);
        vector<bool> visitVertex(int(hyperNode.size()), false);
        vector<bool> visitEdge(int(hyperEdge.size()), false);
        dist[u] = 0;
        while (!visitVertex[v])
        {
            int minDist = INT_MAX;
            int minVertex = -1;
            for (int i = 0; i < int(hyperNode.size()); i++)
            {
                if (!visitVertex[i] && dist[i] < minDist)
                {
                    minDist = dist[i];
                    minVertex = i;
                }
            }
            if (minVertex == -1)
            {
                break;
            }
            visitVertex[minVertex] = true;
            for (int i = 0; i < int(hyperNode[minVertex].size()); i++)
            {
                int e = hyperNode[minVertex][i];
                if (!visitEdge[e])
                {
                    visitEdge[e] = true;
                    for (int j = 0; j < int(hyperEdge[e].size()); j++)
                    {
                        int w = hyperEdge[e][j];
                        if (dist[w] > dist[minVertex] + int(hyperEdge[e].size()))
                        {
                            dist[w] = dist[minVertex] + int(hyperEdge[e].size());
                        }
                    }
                }
            }
        }
        
    }
}