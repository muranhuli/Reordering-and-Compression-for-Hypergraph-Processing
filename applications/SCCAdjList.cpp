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


int find(int x, const vector<int> &fa)
{
    if (fa.at(x) == x)
        return x;
    else
        return find(fa.at(x), fa);
}

void merge(int i, int j, vector<int> &fa)
{
    if (i < j)
        fa[i] = find(j, fa);
    else
        fa[j] = find(i, fa);
}


void compute(vector<vector<int>> &hyperEdge, vector<vector<int>> &hyperNode)
{
    for (int k = 0; k < N; k++)
    {
        vector<int> fa(int(hyperNode.size()), 0);
        for (int i = 0; i < int(fa.size()); i++)
            fa[i] = i;
        for (int i = 0; i < int(hyperEdge.size()); i++)
        {
            for (int j = 0; j < int(hyperEdge[i].size()) - 1; j++)
            {
                merge(fa[hyperEdge[i][j]], fa[hyperEdge[i][j + 1]], fa);
            }
        }
    }
}