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
    vector<int> dijkstra(int n, vector<vector<int>> &edges, int src) {
        
        vector<int> ans(n , INT_MAX);
        
        vector<vector<pair<int,int>>> adj(n , vector<pair<int,int>>());
        
        for(int i=0 ; i<edges.size() ; i++){
            int u = edges[i][0] , v = edges[i][1] , w = edges[i][2];
            adj[u].push_back({v , w});
            adj[v].push_back({u , w});
        }
        
        priority_queue< pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>> > pq; //dist , node
        
        pq.push({0 , src});
        ans[src] = 0;
        
        while(!pq.empty()){
            int dist = pq.top().first;
            int curr = pq.top().second;
            pq.pop();
            for(pair<int,int> p : adj[curr]){
                int nb = p.first;
                int weight = p.second;
                if(ans[nb] > dist+weight){
                    ans[nb] = dist+weight;
                    pq.push({ans[nb] , nb});
                }
            }
        }
        
        return ans;
        
    }
};