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

const int N = 5;

struct Vertex;
struct Edge;

void compute(vector<Vertex> &vertexSet, vector<int> &hyperedgeSet, vector<Edge> &edgeID, vector<int> &edgeSet)
{
    default_random_engine seed(time(NULL));
    mt19937_64 gen(seed());
    int max = int(vertexSet.size()) - 1;
    uniform_int_distribution<int> dist(0, max);

    for (int k = 0; k < N; k++)
    { 
        int u = dist(gen);
        int v = dist(gen);
        // u和v的最短路长度
        vector<int> dist(int(vertexSet.size()), INT_MAX);
        vector<bool> visitVertex(int(vertexSet.size()), false);
        vector<bool> visitEdge(int(edgeID.size()), false);
        dist[u] = 0;
        while (!visitVertex[v])
        {
            int minDist = INT_MAX;
            int minVertex = -1;
            for (int i = 0; i < int(vertexSet.size()); i++)
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
            for(auto i = vertexSet[minVertex].posStar; i < vertexSet[minVertex].posEnd; i++)
            {
                int e = hyperedgeSet[i];
                if (!visitEdge[e])
                {
                    visitEdge[e] = true;
                    for(auto j = edgeID[e].posStar; j < edgeID[e].posEnd; j++)
                    {
                        int w = edgeSet[j];
                        if (dist[w] > dist[minVertex] + int(edgeID[e].posEnd - edgeID[e].posStar))
                        {
                            dist[w] = dist[minVertex] + int(edgeID[e].posEnd - edgeID[e].posStar);
                        }
                    }
                }
            }
        }
    }
}