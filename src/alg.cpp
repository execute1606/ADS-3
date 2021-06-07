// Copyright 2021 NNTU-CS
#include <string>
#include "tstack.h"

int math(int first, int second, char symbol) {
    switch (symbol) {
    case '*':
    {
        second *= first;
        return second;
    }
    case '/':
    {
        second /= first;
        return second;
    }
    case '+':
    {
        second += first;
        return second;
    }
    case '-':
    {
        second -= first;
        return second;
    }
    default:
        break;
    }
    return second;
}
int priority(char chr) {
    int prior = 0;
    if (chr == '(')
        prior = 0;
    if (chr == ')')
        prior = 1;
    if (chr == '+' || chr == '-')
        prior = 2;
    if (chr == '*' || chr == '/')
        prior = 3;
    return prior;
}
std::string infx2pstfx(std::string inf) {
    // добавьте сюда нужный код
    TStack<char> stack1;
    std::string res;
    int prior = -1;
    int priorTop = 0;
    char chr = ' ';
    char chrPrv = ' ';
    bool firstNumber = 0;
    for (int i = 0; i < inf.length(); i++) {
        chr = inf[i];
        chrPrv = stack1.get();
        if (chr >= '0' && chr <= '9') {
            if (!firstNumber) {
                firstNumber = true;
            }
            else {
                res.push_back(' ');
            }
            res.push_back(chr);
        }
        else {
            prior = priority(chr);
            priorTop = priority(chrPrv);
            if ((stack1.isEmpty() || prior > priorTop || !prior)
                && prior != 1) {
                stack1.push(chr);
            }
            else {
                if (prior == 1) {
                    while (stack1.get() != '(') {
                        res.push_back(' ');
                        res.push_back(stack1.get());
                        stack1.pop();
                    }
                    stack1.pop();
                }
                else {
                    if (prior <= priorTop && prior > 1) {
                        while (!stack1.isEmpty() && stack1.get() != '(') {
                            res.push_back(' ');
                            res.push_back(stack1.get());
                            stack1.pop();
                        }
                        stack1.push(chr);
                    }
                }
            }
        }
    }
    while (!stack1.isEmpty()) {
        res.push_back(' ');
        res.push_back(stack1.get());
        stack1.pop();
    }
    return res;
}

int eval(std::string pst) {
    int result = 0;
    TStack<char> stack1;
    TStack<int> stack2;
    int prior = 0, priorPrv = 0;
    int first = 0, second = 0;
    char chr = ' ';
    char chrPrv = ' ';
    for (int i = 0; i < pst.length(); i++) {
        chr = pst[i];
        if (chr != ' ') {
            if (chr >= '0' && chr <= '9') {
                stack2.push(chr - 48);
            } else {
                first = stack2.get();
                stack2.pop();
                second = stack2.get();
                stack2.pop();
                second = math(first, second, chr);
                stack2.push(second);
            }
        }
    }
    return stack2.get();
}
return 0;
