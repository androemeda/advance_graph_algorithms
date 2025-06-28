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

// path compression
class DSU1{
public:
    vector<int> parent;

    DSU1(int n){
        for(int i=0 ; i<n ; i++){
            parent.push_back(i);
        }
    }

    void unite(int a , int b){
        a = findRoot(a);
        b = findRoot(b);
        if(a == b) return;
        parent[b] = a;
    }

    int findRoot(int a){
        if(a == parent[a]) return a;
        return parent[a] = findRoot(parent[a]); //path compression.
    }
};

// small to large
class DSU2{
public:
    vector<int> parent;
    vector<int> size;

    DSU2(int n){
        for(int i=0 ; i<n ; i++){
            parent.push_back(i);
            size.push_back(1);
        }
    }

    void unite(int a , int b){
        a = findRoot(a);
        b = findRoot(b);
        if(a == b) return;
        if(size[a] < size[b]){
            parent[a] = b;
            size[b] += size[a];
        }
        else{
            parent[b] = a;
            size[a] += size[b];
        }
    }

    int findRoot(int a){
        if(a == parent[a]) return a;
        return findRoot(parent[a]);
    }
};

void solve() {
    int N;
    cin >> N;
    vector<pair<int,int>> edges(N);
    for(int i = 1; i <= N-1; i++){
        cin >> edges[i].first >> edges[i].second;
    }
    int Q;
    cin >> Q;
    vector<pair<char,int>> queries(Q);
    vector<bool> removed(N, false);
    for(int i = 0; i < Q; i++){
        char c;
        cin >> c;
        if(c == 'R'){
            int idx; 
            cin >> idx;
            queries[i] = {c, idx};
            removed[idx] = true;
        } else {
            queries[i] = {c, 0};
        }
    }

    long long total_pairs = (long long)N*(N-1)/2;
    long long disconnected = total_pairs;

    DSU2 dsu(N+1);
    for(int i = 1; i <= N-1; i++){
        if(!removed[i]){
            int u = edges[i].first, v = edges[i].second;
            int ru = dsu.findRoot(u), rv = dsu.findRoot(v);
            if(ru != rv){
                long long a = dsu.size[ru], b = dsu.size[rv];
                disconnected -= a*b;
                dsu.unite(ru, rv);
            }
        }
    }

    vector<long long> answers;
    answers.reserve(Q);
    for(int i = Q-1; i >= 0; i--){
        auto [c, x] = queries[i];
        if(c == 'Q'){
            answers.push_back(disconnected);
        } else {
            auto [u, v] = edges[x];
            int ru = dsu.findRoot(u), rv = dsu.findRoot(v);
            if(ru != rv){
                long long a = dsu.size[ru], b = dsu.size[rv];
                disconnected -= a*b;
                dsu.unite(ru, rv);
            }
        }
    }

    int p = (int)answers.size() - 1;
    for(int i = 0; i < (int)answers.size(); i++){
        cout << answers[p--] << "\n";
    }
    cout << "\n";
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int _t;
    cin >> _t;
    while(_t--){
        solve();
    }
    return 0;
}

/**
 * 
 * 
How it works

We mark every “R x” removal ahead of time and build the DSU over the tree minus all removed edges.

We maintain disconnected = N*(N−1)/2 and whenever we union two components of sizes a and b, we subtract a·b (the number of pairs 
just reconnected).

Then we replay the queries in reverse: each removal becomes an “add that edge back” DSU-union, and each query “Q” we simply 
record the current disconnected.

Finally we reverse the recorded answers to match the original query order. This runs in O((N+Q) α(N)) time and fits N,Q≤2·10⁴ 
comfortably.
 */