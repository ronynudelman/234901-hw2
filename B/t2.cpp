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


#define POS (1.0)
#define NEG (-1.0)


double eval_exp(string& exp, size_t& from, size_t& to);


string remove_spaces(string& s) {
    string new_s;
    for (auto& c : s) {
        if (c != ' ') {
            new_s.push_back(c);
        }
    }
    return new_s;
}


bool is_digit(char c) {
    return '0' <= c && c <= '9';
}


// given exp, return the first number when starting parsing
// from the left side of exp.
// assume exp does not start with '('.
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


// assume the first char in exp is '('.
// the goal is to find its matching right parenthesis position in exp.
// we do that using balance counter.
size_t find_matching_closing_par_pos(string& exp, const size_t& from, const size_t& to) {
    int balance = 0;
    for (size_t i = from; i < to; i++) {
        if (exp[i] == '(') balance--;
        if (exp[i] == ')') balance++;
        if (balance == 0) return i;
    }
    return 0;
}


// return +1 or -1 according to the sign in the beginning of exp
double get_sign(string& exp, size_t& from) {
    double sign = POS;
    while (exp[from] == '-') {
        sign *= NEG;
        from++;
    }
    return sign;
}


// return the value of the first subexp of exp.
// if the subexp starts with '(' then we need to calculate it recursively.
double get_next_num_val(string& exp, size_t& from, size_t& to) {
    double sign = get_sign(exp, from);
    if (exp[from] == '(') {
        size_t r_par = find_matching_closing_par_pos(exp, from, to);
        from++;
        double res = eval_exp(exp, from, r_par) * sign;
        from = r_par + 1;
        return res;
    }
    else {
        return parse_first_num(exp, from, to) * sign;
    }
}


// calculate "a op b"
double calc_simple_op(double a, char op, double b) {
    if (op == '+') return a + b;
    if (op == '-') return a - b;
    if (op == '*') return a * b;
    if (op == '/') return a / b;
    cout << "ERROR" << endl;
    return 0.0;
}

// the main function as described in the txt file
double eval_exp(string& exp, size_t& from, size_t& to) {
    if (from >= to) {
        return 0.0;
    }
    double first_num = 0.0;
    char first_op = '0';
    double second_num = 0.0;
    char second_op = '0';
    double third_num = 0.0;
    first_num = get_next_num_val(exp, from, to);
    while (from < to) {
        first_op = exp[from++];
        second_num = get_next_num_val(exp, from, to);
        if (first_op == '*' || first_op == '/') {
            first_num = calc_simple_op(first_num, first_op, second_num);
            continue;
        }
        bool revert_from = false;
        while (from < to) {
            second_op = exp[from++];
            if (!(second_op == '*' || second_op == '/')) {
                revert_from = true;
                break;
            }
            third_num = get_next_num_val(exp, from, to);
            second_num = calc_simple_op(second_num, second_op, third_num);
        }
        if (revert_from) {
            from--;
        }
        first_num = calc_simple_op(first_num, first_op, second_num);
    }
    return first_num;
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
