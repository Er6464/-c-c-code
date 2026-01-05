// C++17 - Tree common utilities for CP (LCA / subtree / Euler / HLD skeleton)
// Compile: g++ -std=c++17 -O2 tree_template.cpp

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 200000;   // ปรับตามข้อจำกัด
const int LOGN = 20;       // ceil(log2(MAXN))

int n;
vector<int> g[MAXN+1];

// Basic arrays
int parentArr[LOGN][MAXN+1]; // parentArr[k][v] = 2^k-th ancestor of v
int depthArr[MAXN+1];
int subsize[MAXN+1];

// Euler tour (time in/out)
int tin[MAXN+1], tout[MAXN+1], timerE = 0;
vector<int> euler; // optionally store order

// HLD arrays
int heavy[MAXN+1];     // heavy child or -1
int head[MAXN+1];      // head of heavy path
int posInBase[MAXN+1]; // position in base array
int curPos = 0;        // current position for HLD
int baseArray[MAXN+1]; // values mapped by posInBase, use for segtree

// ---------- DFS to compute parent, depth, subsize, heavy child, euler ----------
void dfs(int u, int p) {
    parentArr[0][u] = p;
    depthArr[u] = (p == 0 ? 0 : depthArr[p] + 1);
    subsize[u] = 1;
    tin[u] = ++timerE;
    euler.push_back(u);

    int maxSub = 0;
    heavy[u] = -1;

    for (int v : g[u]) if (v != p) {
        dfs(v, u);
        subsize[u] += subsize[v];
        if (subsize[v] > maxSub) {
            maxSub = subsize[v];
            heavy[u] = v;
        }
    }

    tout[u] = ++timerE;
}

// ---------- Build binary lifting table ----------
void build_lca() {
    for (int k = 1; k < LOGN; ++k) {
        for (int v = 1; v <= n; ++v) {
            int mid = parentArr[k-1][v];
            parentArr[k][v] = (mid ? parentArr[k-1][mid] : 0);
        }
    }
}

int lift(int v, int k) {
    for (int i = 0; i < LOGN; ++i)
        if (k & (1<<i))
            v = parentArr[i][v];
    return v;
}

int lca(int a, int b) {
    if (depthArr[a] < depthArr[b]) swap(a,b);
    a = lift(a, depthArr[a] - depthArr[b]);
    if (a == b) return a;
    for (int k = LOGN-1; k >= 0; --k) {
        if (parentArr[k][a] != parentArr[k][b]) {
            a = parentArr[k][a];
            b = parentArr[k][b];
        }
    }
    return parentArr[0][a];
}

int dist(int a, int b) {
    int c = lca(a,b);
    return depthArr[a] + depthArr[b] - 2*depthArr[c];
}

// ---------- HLD: decompose into heavy paths (call after dfs) ----------
void decompose(int u, int h) {
    head[u] = h;
    posInBase[u] = ++curPos;
    // baseArray[curPos] = value[u]; // if nodes have initial values

    if (heavy[u] != -1) {
        decompose(heavy[u], h);
    }
    for (int v : g[u]) {
        if (v == parentArr[0][u] || v == heavy[u]) continue;
        decompose(v, v);
    }
}

// Example query on path using HLD (node values, with segtree/query function placeholders)
// We just show how to break path into segments; implement segtree functions separately.
template<typename F> // F is function to query segtree over interval [l,r]
auto query_path(int a, int b, F querySeg) {
    // accumulate or combine using lambda provided
    // Example returns vector of pairs (l, r) in base positions to query
    vector<pair<int,int>> segments;
    while (head[a] != head[b]) {
        if (depthArr[head[a]] < depthArr[head[b]]) swap(a,b);
        segments.push_back({posInBase[head[a]], posInBase[a]});
        a = parentArr[0][head[a]];
    }
    if (depthArr[a] > depthArr[b]) swap(a,b);
    segments.push_back({posInBase[a], posInBase[b]});
    // User can call querySeg on each segment (note some problems need reverse)
    return segments;
}

// ---------- Example main ----------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Input example:
    // n
    // n-1 edges (u v)
    // q queries: type ... (customize)
    cin >> n;
    for (int i = 0; i < n-1; ++i) {
        int u,v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    // root the tree at 1
    dfs(1, 0);
    build_lca();
    decompose(1, 1);

    // Example usage:
    // read q and answer distance queries
    int q; 
    if (cin >> q) {
        while (q--) {
            int u,v; cin >> u >> v;
            cout << "dist(" << u << "," << v << ") = " << dist(u,v) << "\n";
        }
    } else {
        // no queries: we can output some arrays for debug
        for (int i = 1; i <= n; ++i) {
            cerr << "node " << i << ": depth=" << depthArr[i] 
                 << " parent=" << parentArr[0][i] 
                 << " sub=" << subsize[i] 
                 << " heavy=" << heavy[i] 
                 << " head=" << head[i] 
                 << " pos=" << posInBase[i] << "\n";
        }
    }
    return 0;
}
