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

const int N = 1;

void compute(vector<vector<int>> &hyperEdge, vector<vector<int>> &hyperNode)
{
    for (int k = 0; k < N; k++)
    {
        vector<bool> isInMIS(hyperNode.size(), false);
        vector<bool> isRemovedEdge(hyperEdge.size(), false);
        vector<int> MIS;

        while (true)
        {
            int selectedEdge = -1;
            int selectedVertex = -1;
            int maxDegree = -1;

            for (size_t i = 0; i < hyperEdge.size(); ++i)
            {
                if (isRemovedEdge[i])
                    continue;
                for (size_t j = 0; j < hyperEdge[i].size(); ++j)
                {
                    int vertex = hyperEdge[i][j];
                    int degree = hyperNode[vertex].size();
                    if (!isInMIS[vertex] && degree > maxDegree)
                    {
                        maxDegree = degree;
                        selectedEdge = i;
                        selectedVertex = vertex;
                    }
                }
            }

            if (selectedEdge == -1)
            {
                break;
            }

            isInMIS[selectedVertex] = true;
            MIS.push_back(selectedVertex);

            for (size_t i = 0; i < hyperNode[selectedVertex].size(); ++i)
            {
                isRemovedEdge[hyperNode[selectedVertex][i]] = true;
            }
        }
    }
}