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
        vector<bool> visited(int(vertexSet.size()), false);
        for (int i = vertexSet[v].posStar; i < vertexSet[v].posEnd; i++)
        {
            int e = hyperedgeSet[i];
            for (int j = edgeID[e].posStar; j < edgeID[e].posEnd; j++)
            {
                int u = edgeSet[j];
            }
        }
    }
}
