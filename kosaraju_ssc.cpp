#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <limits>
#include <numeric>
#include <climits>
#define int long long
using namespace std;

class Solution
{
public:
    vector<vector<int>> revadj;
    vector<bool> visited;
    vector<int> order; // store nodes by fishing time in asc order.

    void findorder(int node, vector<vector<int>> &adj)
    {
        visited[node] = true;
        for (int nb : adj[node])
        {
            if (!visited[nb])
            {
                findorder(nb, adj);
            }
        }
        order.push_back(node); // node has finished exploring.
    }

    void dfs(int node)
    {
        visited[node] = true;
        for (int nb : revadj[node])
        {
            if (!visited[nb])
            {
                dfs(nb);
            }
        }
    }

    int kosaraju(vector<vector<int>> &adj)
    {

        int n = adj.size();

        revadj.assign(n, vector<int>());
        visited.assign(n, false);

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < adj[i].size(); j++)
            {
                revadj[adj[i][j]].push_back(i);
            }
        }

        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
            {
                findorder(i, adj);
            }
        }

        // do dfs in finishing time order.
        int ans = 0;

        for (int i = 0; i < n; i++)
            visited[i] = false;

        for (int i = order.size() - 1; i >= 0; i--)
        {
            int node = order[i];
            if (!visited[node])
            {
                ans++;
                dfs(node); // visit entire scc of the graph
            }
        }

        return ans;
    }
};

/*
tc : o(v+e)
sc : o(v+e)
*/