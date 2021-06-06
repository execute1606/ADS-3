// Copyright 2021 NNTU-CS
#include <string>
#include "tstack.h"

int prior(char pri) {
    if (pri == '(')
        return 0;
    else if (pri == ')')
        return 1;
    else if (pri == '+' || pri == '-')
        return 2;
    else if (pri == '*' || pri == '/')
        return 3;
    else
        return -1;
}

int calс(int num1, int num2, char op) {
    if (op == '+')
        return num1 + num2;
    else if (op == '-')
        return num1 - num2;
    else if (op == '*')
        return num1 * num2;
    else if (op = '/')
        return num1 / num2;
}
std::string infx2pstfx(std::string inf) {
    Tstack<char> infWrite;
    chat top = 0;
    std::string pst;
    for (int i = 0; i < inf.length(); i++) {
        char ch = inf[i];
        int pri;
        pri = prior(ch);
        if (pri > -1) {
            if ((pri == 0 || pri > prior(top) ||
                infWrite.isEmpty()) && ch != ')') {
                if (infWrite.isEmpty())
                    top = ch;
                infWrite.push(ch);
            }
            else if (ch == ')') {
                while (infWrite.get() != '(') {
                    pst.push_back(infWrite.get());
                    pst.push_back(' ');
                    infWrite.pop();
                }
                infWrite.pop();
                if (infWrite.isEmpty())
                    top = 0;
            }
            else {
                while (!infWrite.isEmpty() &&
                    prior(infWrite.get()) >= pri)
                {
                    pst.push_back(infWrite.get());
                    pst.push_back(' ');
                    infWrite.pop();
                }
                if (infWrite.isEmpty())
                    top = inf[i];
                infWrite.push(inf[i]);
            }
        }
        else {
            pst.push_back(ch);
            pst.push_back(' ');
        }
    }
    while (!infWrite.isEmpty()) {
        pst.push_back(infWrite.get());
        pst.push_back(' ');
        infWrite.pop();
    }
    pst.erase(pst.end() - 1, pst.end());
    return pst;
}

int eval(std::string pst) {
    TStack <int> pst;
    for (int i = 0; i < pst.size(); i++) {
        char ch = pst[i];
        int pri = prior(ch);
        if (pri == -1)
            pst.push(ch - 48);
        else {
            int num1 = pst.get();
            pstStack.pop();
            int num2 = pst.get();
            pst.pop();
            int res = calс(num1, num2, ch);
            pst.push(res);
        }
    }
    return pst.get();
}
