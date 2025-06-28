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

    string s;
    int m;

    cin >> s >> m;

    int n = s.size();

    DSU2 dsu(n);

    for(int i=0 ; i<m ; i++){
        int x,y;
        cin >> x >> y;
        dsu.unite(x,y);
    }

    map<int , vector<int>> mp; // <root index , all indices having that root>

    string ans = s;

    for(int i=0 ; i<n ; i++){
        int root = dsu.findRoot(i);
        mp[root].push_back(i);
    }

    for(auto [root , indices] : mp){
        vector<char> chars;
        for(int index : indices){
            chars.push_back(s[index]);
        }
        sort(indices.begin() , indices.end());
        sort(chars.begin() , chars.end());

        for(int i=0 ; i<indices.size() ; i++){
            ans[indices[i]] = chars[i];
        }
    }

    cout << ans << endl;
}

signed main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int _t = 1;

    cin >> _t;

    while(_t--){
        solve();
    }

    return 0;
}