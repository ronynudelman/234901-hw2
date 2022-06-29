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


#define INF 1e14

// point class which is sorted by X
class PointX {
public:
    double x;
    double y;
    PointX(double _x, double _y) : x(_x), y(_y) {}
    bool operator<(const PointX& p) const {
        if (x == p.x) return y < p.y;
        return x < p.x;
    }
    bool operator==(const PointX& p) const {
        return x == p.x && y == p.y;
    }
};


// point class which is sorted by Y
class PointY {
public:
    double x;
    double y;
    PointY(double _x, double _y) : x(_x), y(_y) {}
    bool operator<(const PointY& p) const {
        if (y == p.y) return x < p.x;
        return y < p.y;
    }
    bool operator==(const PointY& p) const {
        return x == p.x && y == p.y;
    }
};


double dist(PointY p1, PointY p2) {
    return hypot(p1.x - p2.x, p1.y - p2.y);
}


void print_closest_points(pair<double,double> p1, pair<double,double> p2) {
    printf("%0.2f %0.2f %0.2f %0.2f\n", p1.first, p1.second, p2.first, p2.second);
}


// convert PointX to PointY with same values
PointY x_to_y(PointX& p) {
    return PointY(p.x, p.y);
}


void clean_far_cands_from_strip(set<PointY>& strip, double min_dist, PointX& curr_point) {
    PointY curr_point_y = x_to_y(curr_point);
    set<PointY> to_remove;
    for (auto& it : strip) {
        if (curr_point_y.x - it.x >= min_dist) {
            to_remove.insert(it);
        }
    }
    for (auto& it : to_remove) {
        strip.erase(it);
    }
}


void find_min_dist(vector<PointX>& points) {
    pair<pair<double,double>, pair<double,double>> closest_points = {{points[0].x, points[0].y}, {points[1].x, points[1].y}};
    set<PointY> strip;
    double min_dist = INF;
    for (size_t i = 0; i < points.size(); i++) {
        PointX& curr_point = points[i];
        clean_far_cands_from_strip(strip, min_dist, curr_point);
        set<PointY>::iterator low_bound = strip.lower_bound(PointY(0, curr_point.y-min_dist));
        set<PointY>::iterator up_bound = strip.upper_bound(PointY(0, curr_point.y+min_dist));
        PointY curr_point_y = x_to_y(curr_point);
        // check the distance for each of the remaining candidates
        while (low_bound != up_bound) {
            PointY cand = *low_bound;
            double curr_dist = dist(cand, curr_point_y);
            if (curr_dist < min_dist) {
                min_dist = curr_dist;
                closest_points = {{cand.x, cand.y}, {curr_point_y.x, curr_point_y.y}};
            }
            low_bound++;
        }
        strip.insert(x_to_y(curr_point));
    }
    print_closest_points(closest_points.first, closest_points.second);
}


int main() {
    int n;
    while (cin >> n && n != 0) {
        vector<PointX> points;
        while (n--) {
            double x, y;
            cin >> x >> y;
            points.push_back(PointX(x, y));
        }
        sort(points.begin(), points.end());
        find_min_dist(points);
    }
    return 0;
}
