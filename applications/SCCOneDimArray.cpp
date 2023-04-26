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

int find(int x, const vector<int> &fa)
{
    if (fa.at(x) == x)
        return x;
    else
        return find(fa.at(x), fa);
}

// merge to bigger ID
void merge(int i, int j, vector<int> &fa)
{
    if (i < j)
        fa[i] = find(j, fa);
    else
        fa[j] = find(i, fa);
}

void compute(vector<Vertex> &vertexSet, vector<int> &hyperedgeSet, vector<Edge> &edgeID, vector<int> &edgeSet)
{
    for (int k = 0; k < N; k++)
    {
        vector<int> fa(int(vertexSet.size()), 0);
        for (int i = 0; i < int(fa.size()); i++)
            fa[i] = i;
        for (int i = 0; i < int(edgeID.size()); i++)
        {
            for (int j = edgeID[i].posStar; j < edgeID[i].posEnd - 1; j++)
            {
                merge(fa[edgeSet[j]], fa[edgeSet[j + 1]], fa);
            }
        }
    }
}