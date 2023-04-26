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

const int N = 1;

struct Vertex;
struct Edge;

void compute(vector<Vertex> &vertexSet, vector<int> &hyperedgeSet, vector<Edge> &edgeID, vector<int> &edgeSet)
{
    for (int k = 0; k < N; k++)
    {
        vector<bool> isInMIS(vertexSet.size(), false);
        vector<bool> isRemovedEdge(edgeID.size(), false);
        vector<int> MIS;

        while (true)
        {
            int selectedEdge = -1;
            int selectedVertex = -1;
            int maxDegree = -1;

            for (size_t i = 0; i < edgeID.size(); ++i)
            {
                if (isRemovedEdge[i])
                    continue;
                for(size_t j=edgeID[i].posStar;j<edgeID[i].posEnd;++j)
                {
                    int vertex = edgeSet[j];
                    int degree = edgeID[i].posEnd-edgeID[i].posStar;
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

            for(size_t i=vertexSet[selectedVertex].posStar;i<vertexSet[selectedVertex].posEnd;++i)
            {
                isRemovedEdge[hyperedgeSet[i]] = true;
            }
        }
    }
}