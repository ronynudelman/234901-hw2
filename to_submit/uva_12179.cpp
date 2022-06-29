#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#include <numeric>
#include <list>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vll;
typedef pair<int, int> pii;
typedef vector<vll> vvll;
typedef vector<vvll> vvvll;
typedef vector<string> vs;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> ii;
typedef vector<double> vd;
typedef vector<vd> vvd;

// use BFS to find min dist
int find_dist(const vvi& g, int s, int goal) {
    queue<ii> q; q.push({s, 0});
    vector<bool> visible (g.size(), false);
    visible[s] = true;
    while (!q.empty()) {
        int u = q.front().first;
        int curr_dist = q.front().second;
        q.pop();
        if (u == goal) {
            return curr_dist;
        }
        for (int v : g[u]) if (!visible[v]) {
            visible[v] = true;
            q.push({v, curr_dist+1});
        }
    }
    return 0;
}

// the recursive function for calculating DP
double calc_prob(int R, int budget, int dist, vvd& probs) {
    if (budget == 0 && dist > 0) {
        return 0.0;
    }
    if (budget >= 0 && dist == 0) {
        return 1.0;
    }
    if (probs[budget][dist] == -1.0) {
        double total_prob = 0.0;
        for (int curr_price = 1; curr_price <= R; curr_price++) {
            if (budget >= curr_price) {
                total_prob += (calc_prob(R, budget - curr_price, dist - 1, probs) / (double)R);
            }
        }
        probs[budget][dist] = total_prob;
        return total_prob;
    }
    else {
        return probs[budget][dist];
    }
}


void run_test() {
    int N, R;
    cin >> N >> R;
    vs rows_strings;
    for (int i = 0; i < N; i++) {
        string next_row;
        cin >> next_row;
        rows_strings.push_back(next_row);
    }
    vvi matrix(N+1, vi(N+1, 0));
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (rows_strings[i-1][j-1] == 'Y') {
                matrix[i][j] = 1;
            }
        }
    }
    vvi graph(N+1, vi());
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (matrix[i][j] == 1) {
                graph[i].push_back(j);
                graph[j].push_back(i);
            }
        }
    }
    // probs[budget][dist]
    vvd probs(10001, vd(101, -1.0));
    int C;
    cin >> C;
    while (C--) {
        int start, goal, budget;
        cin >> start >> goal >> budget;
        int curr_dist = find_dist(graph, start, goal);
        double prob = calc_prob(R, budget, curr_dist, probs);
        printf("%0.6f\n", prob);
    }
}


int main() {
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        cout << "Case " << i << endl;
        run_test();
        cout << endl;
    }
    return 0;
}
