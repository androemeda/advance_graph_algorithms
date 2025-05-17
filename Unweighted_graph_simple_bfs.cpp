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
  
    vector<int> dist;
    vector<int> parent;
    int n;
    
    void printpath(int src , int dest){
        cout << src << "-->" << dest << " : ";
        int d = dest;
        vector<int> path;
        while(parent[dest] != -1){
            path.push_back(parent[dest]);
            dest = parent[dest];
        }
        
        if(path.size() == 0){
            cout << endl;
            return;
        }
        
        reverse(path.begin() , path.end());
        for(int i=0 ; i<path.size() ; i++){
            cout << path[i] << " ";
        }
        cout << d;
        cout << endl;
    }
    
    void bfs(vector<vector<int>>& adj, int src){
        
        queue<int> q;
        q.push(src);
        dist[src] = 0;
        
        while(!q.empty()){
            int curr = q.front();
            q.pop();
            for(int node : adj[curr]){
                if(dist[node] == -1 || dist[node] > 1+dist[curr]){
                    dist[node] = 1+dist[curr];
                    q.push(node);
                    parent[node] = curr;
                }
            }
        }
    }
    
    vector<int> shortestPath(vector<vector<int>>& adj, int src) {
        
        n = adj.size();
        dist.assign(n , -1);
        parent.assign(n , -1);
        
        for(int i=0 ; i<n ; i++){
            if(dist[i] == -1){
                bfs(adj , src);
            }
        }
        
        for(int i=0 ; i<n ; i++){
            printpath(src , i);
        }
        
        return dist;
    }
};