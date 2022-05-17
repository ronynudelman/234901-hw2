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
typedef vector<int> vi;
typedef pair<int, int> pii;


// KMP Init
void KMP_init(const string& KMP_pat, vi& lps){
    int m = KMP_pat.length();
    lps.resize(m+1,0);
    lps[0]=-1;
    int i = 0, j = -1;
    while (i < m) {
        while (j >= 0 && KMP_pat[i] != KMP_pat[j]) j = lps[j];
        i++; j++;
        // cout << i << endl;
        lps[i] = j;
    }
}

// Search a pattern in a string
// Assuming lps is allready initialized with KMP_init
int KMP_search(const string& KMP_str, const string& KMP_pat, vi& lps) {
    int counter = 0;
    int n = KMP_str.length();
    int m = KMP_pat.length();
    int i = 0, j = 0;
    while (i < n) {
        while (j >= 0 && KMP_str[i] != KMP_pat[j]) j = lps[j];
        i++; j++;
        if (j == m) { // Pattern found
            // cout << "The pattern is found at index " << i-j << endl;
            counter++;
            j = lps[j];
        }
    }
    return counter;
}


// no change
int type1_check(const string& KMP_str, const string& KMP_pat) {
    int counter = 0;
    vi lps;
    KMP_init(KMP_pat, lps);
    counter = KMP_search(KMP_str, KMP_pat, lps);
    return counter;
}


// delete one char from pat
int type2_check(const string& KMP_str, const string& KMP_pat) {
    int counter = 0;
    set<string> new_pats;
    for (size_t pos = 0; pos < KMP_pat.size(); pos++) {
        new_pats.insert(KMP_pat.substr(0, pos) + KMP_pat.substr(pos + 1));
    }
    for (auto& new_pat : new_pats) {
        counter += type1_check(KMP_str, new_pat);
    }
    return counter;
}


// insert one char in pat
int type3_check(const string& KMP_str, const string& KMP_pat) {
    int counter = 0;
    set<string> new_pats;
    string new_pat;
    for (size_t pos = 0; pos < KMP_pat.size() + 1; pos++) {
        new_pats.insert(KMP_pat.substr(0, pos) + "A" + KMP_pat.substr(pos));
        new_pats.insert(KMP_pat.substr(0, pos) + "T" + KMP_pat.substr(pos));
        new_pats.insert(KMP_pat.substr(0, pos) + "C" + KMP_pat.substr(pos));
        new_pats.insert(KMP_pat.substr(0, pos) + "G" + KMP_pat.substr(pos));
    }
    for (auto& new_pat : new_pats) {
        counter += type1_check(KMP_str, new_pat);
    }
    return counter;
}


void run(const string& KMP_str, const string& KMP_pat) {
    int type1_num = type1_check(KMP_str, KMP_pat);
    int type2_num = type2_check(KMP_str, KMP_pat);
    int type3_num = type3_check(KMP_str, KMP_pat);
    cout << type1_num << " " << type2_num << " " << type3_num << endl;
}


int main() {
    string S, L;
    while (cin >> S) {
        if (S == "0") break;
        cin >> L;
        string& KMP_str = L; // The string to search in
        string& KMP_pat = S; // The pattern to search
        run(KMP_str, KMP_pat);
    }

    return 0;
}
