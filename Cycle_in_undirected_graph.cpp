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

class Solution {
  public:
  
    vector<vector<int>> adj;
    vector<int> parent;
    vector<bool> visited;
    
    bool bfs(int src){
        queue<int> q;
        q.push(src);
        visited[src] = true;
        
        while(!q.empty()){
            int curr = q.front();
            q.pop();
            for(int nb : adj[curr]){
                if(visited[nb] && parent[nb] != parent[curr]) return true;
                if(!visited[nb]){
                    visited[nb] = true;
                    parent[nb] = curr;
                    q.push(nb);
                }
            }
        }
        
        return false;
    }
    
    bool isCycle(int n, vector<vector<int>>& edges) {
        
        
        int e = edges.size();
        
        adj.assign(n , vector<int>());
        parent.assign(n , -1);
        visited.assign(n , false);
        
        for(int i=0 ; i<e ; i++){
            int u = edges[i][0];
            int v = edges[i][1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        
        for(int i=0 ; i<n ; i++){
            if(!visited[i] && bfs(i)) return true;
        }
        
        return false;
    }
};