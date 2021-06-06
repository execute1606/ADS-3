// Copyright 2021 NNTU-CS
#include <string>
#include <stack>
#include <map>

std::string infx2pstfx(std::string inf) {
    std::map<char, int> prior = { {'(', 0}, {')', 1},
        {'+', 2}, {'-', 2}, {'*', 3}, {'/', 3} };
    std::string res, temp;
    std::stack<char> stack;
    for (auto& chr : inf) {
        if (chr >= '0' && chr <= '9') {
            temp += chr;
        }
        else if (chr == '(' || chr == '+' ||
            chr == '-' || chr == '*' || chr == '/') {
            if (temp.length()) {
                res += temp;
                res += ' ';
                temp = "";
            }
            if (!stack.empty()) {
                if (chr == '(') {
                    stack.push(chr);
                }
                else if (prior[chr] > prior[stack.top()]) {
                    stack.push(chr);
                }
                else {
                    res += stack.top();
                    stack.pop();
                    stack.push(chr);
                    res += ' ';
                }
            }
            else {
                stack.push(chr);
            }
        }
        else if (chr == ')') {
            if (temp.length()) {
                res += temp;
                res += ' ';
                temp = "";
            }
            if (!stack.empty()) {
                while (stack.top() != '(') {
                    res += stack.top();
                    stack.pop();
                    res += ' ';
                }
                stack.pop();
            }
        }
    }
    if (temp.length()) {
        res += temp;
        res += ' ';
    }
    for (unsigned int i = stack.size(); i > 0; i--) {
        res += stack.top();
        res += ' ';
        stack.pop();
    }
    res.erase(res.end() - 1, res.end());
    return res;
}

int eval(std::string pst) {
    unsigned int x = 0, y = 0;
    std::stack<unsigned int> stack;
    unsigned int temp = 0;
    for (unsigned int i = 0; i < pst.length() + 1; i++) {
        if (pst[i] >= '0' && pst[i] <= '9') {
            temp *= 10;
            temp += pst[i] - '0';
        }
        else if (pst[i] == ' ') {
            stack.push(temp);
            temp = 0;
        }
        else {
            x = stack.top();
            stack.pop();
            y = stack.top();
            stack.pop();
            if (pst[i] == '+') {
                stack.push(y + x);
            }
            else if (pst[i] == '-') {
                stack.push(y - x);
            }
            else if (pst[i] == '*') {
                stack.push(y * x);
            }
            else {
                stack.push(y / x);
            }
            i++;
        }
    }
    return stack.top();
}
