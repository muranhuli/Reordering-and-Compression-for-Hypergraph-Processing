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
    vector<double> pr(int(vertexSet.size()), 1.0 / int(vertexSet.size()));
    double d = 0.85;
    for (int m = 0; m < N; m++)
    {
        vector<double> updatePr(int(vertexSet.size()), 0.0);
        for (int u = 0; u < int(vertexSet.size()); u++)
        {
            for (int i = vertexSet[u].posStar; i < vertexSet[u].posEnd; i++)
            {
                int e = hyperedgeSet[i];
                for (int j = edgeID[e].posStar; j < edgeID[e].posEnd; j++)
                {
                    int v = edgeSet[j];
                    updatePr[u] += pr[v] * (1.0 / (vertexSet[v].posEnd - vertexSet[v].posStar)) * (1.0 / (edgeID[e].posEnd - edgeID[e].posStar));
                }
            }
        }
        for (int u = 0; u < int(vertexSet.size()); u++)
        {
            pr[u] = (1 - d) / int(vertexSet.size()) + d * updatePr[u];
        }
    }
}