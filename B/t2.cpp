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
typedef double d;

#define POS (1.0)
#define NEG (-1.0)

double eval_exp(string& exp, size_t& from, size_t& to);

string remove_spaces(string& input_line) {
    string exp;
    for (auto& c : input_line) {
        if (c != ' ') {
            exp.push_back(c);
        }
    }
    return exp;
}

bool is_digit(char c) {
    return '0' <= c && c <= '9';
}

double parse_first_num(string& exp, size_t& from, size_t& to) {
    string num;
    while (from < to) {
        char next_c = exp[from];
        if (!is_digit(next_c)) {
            return stod(num);
        }
        num.push_back(next_c);
        from++;
    }
    return stod(num);
}

size_t find_matching_r_par_pos(string& exp, const size_t& from, const size_t& to) {
    int balance = 0;
    for (size_t i = from; i < to; i++) {
        if (exp[i] == '(') balance--;
        if (exp[i] == ')') balance++;
        if (balance == 0) return i;
    }
    cout << "ERROR" << endl;
    return 0;
}

double get_next_num_val(string& exp, size_t& from, size_t& to, double curr_num_sign) {
    if (exp[from] == '(') {
        size_t r_par = find_matching_r_par_pos(exp, from, to);
        from++;
        double res = eval_exp(exp, from, r_par) * curr_num_sign;
        from = r_par + 1;
        return res;
    }
    else {
        return parse_first_num(exp, from, to) * curr_num_sign;
    }
}

double simple_eval(double a, double b, char op) {
    if (op == '+') return a + b;
    if (op == '-') return a - b;
    if (op == '*') return a * b;
    if (op == '/') return a / b;
    cout << "ERROR" << endl;
    return 0.0;
}

double eval_exp(string& exp, size_t& from, size_t& to) {
    if (from >= to) {
        return 0.0;
    }
    bool is_first_number = true;
    double res = 0.0;
    double first_num_sign = POS;
    double first_num = 0.0;
    char first_op = '0';
    double second_num_sign = POS;
    double second_num = 0.0;
    char second_op = '0';
    double third_num_sign = POS;
    double third_num = 0.0;
    char third_op = '0';
    while (exp[from] == '-') {
        first_num_sign *= NEG;
        from++;
    }
    res = get_next_num_val(exp, from, to, first_num_sign);
    while (from < to - 1) {
        first_op = exp[from];
        from++;
        while (exp[from] == '-') {
            second_num_sign *= NEG;
            from++;
        }
        second_num = get_next_num_val(exp, from, to, second_num_sign);
        if (first_op == '*' || first_op == '/') {
            res = simple_eval(res, second_num, first_op);
            continue;
        }
        second_op = exp[from];
        from++;
        while (from < to && (second_op == '*' || second_op == '/')) {
            while (exp[from] == '-') {
                third_num_sign *= NEG;
                from++;
            }
            third_num = get_next_num_val(exp, from, to, third_num_sign);
            second_num = simple_eval(second_num, third_num, second_op);
            if (from < to) {
                second_op = exp[from];
                from++;
            }
        }
        if (second_op == '+' || second_op == '-') {
            from--;
        }
        res = simple_eval(res, second_num, first_op);
    }
    return res;
}


int main() {
    string input_line;
    getline(cin, input_line);
    while (!input_line.empty()) {
        string exp = remove_spaces(input_line);
        size_t from = 0;
        size_t to = exp.size();
        printf("%.2f\n", eval_exp(exp, from, to));
        getline(cin, input_line);
    }
    return 0;
}
