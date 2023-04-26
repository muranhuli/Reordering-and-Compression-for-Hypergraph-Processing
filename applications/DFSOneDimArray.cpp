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


void compute(vector<Vertex> &vertexSet, vector<int> &hyperedgeSet, vector<Edge> &edgeID, vector<int> &edgeSet)
{
    default_random_engine seed(time(NULL));
    mt19937_64 gen(seed());
    int max = int(vertexSet.size()) - 1;
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
            auto start = vertexSet[u].posStar;
            auto end = vertexSet[u].posEnd;
            for (auto i = start; i < end; i++)
            {
                int edge = hyperedgeSet[i];
                if (!visitEdge[edge])
                {
                    visitEdge[edge] = true;
                    int s1 = edgeID[edge].posStar;
                    int e1 = edgeID[edge].posEnd;
                    for (int j = s1; j < e1; j++)
                    {
                        int node = edgeSet[j];
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