#include "include/polynoms/ArithmeticalExpression.h"

bool isOperator(char c) {
    if (c == '+' || c == '-' || c == '*')
        return true;
    return false;
}
bool isOperator(std::string s) {
    if (s[0] == '+' || s[0] == '-' || s[0] == '*')
        return true;
    return false;
}

ArithmeticalExpression::ArithmeticalExpression(const std::string& ar_expr): infix(ar_expr) {
    Tokenize();
    ToPostfix();
}


void ArithmeticalExpression::Tokenize() {
    std::string curMon = "";

    for (char c : infix) {
        if (c == ' ')
            continue;
        else if (isOperator(c) || c == '(' || c == ')') {
            if (curMon.size() > 0) {

                // check if monom is correct, if not -> exception
                Monom m(curMon);

                lexems.push_back(curMon);
                curMon = "";
            }
            lexems.push_back(std::string(1, c));
        }
        else if (c >= 'A' && c <= 'Z') {
            lexems.push_back(std::string(1,c));
        }
        else {
            curMon += c;
        }
    }

    if (curMon.size() > 0) {
        Monom m(curMon);
        lexems.push_back(curMon);
    }
}

void ArithmeticalExpression::ToPostfix()
{
    std::stack<std::string> s;

    for (std::string lexem : lexems) {
        if (lexem == "(") {
            s.push("(");
        }
        else if (lexem == ")") {
            while (s.top() != "(") {
                postfix.push_back(s.top());
                s.pop();
            }
            s.pop();
        }
        else if (isOperator(lexem)) {
            while ((s.empty() == false && isOperator(s.top()) && priority[lexem[0]] <= priority[s.top()[0]])) {
                postfix.push_back(s.top());
                s.pop();
            }
            s.push(lexem);
        }
        else {
            postfix.push_back(lexem);
        }
    }
    while (s.empty() == false) {
        postfix.push_back(s.top());
        s.pop();
    }
}

Polynom ArithmeticalExpression::getExpr(all_tables<std::string, Polynom>& table) {
    std::stack<Polynom> s;
    Polynom l, r;
    for (std::string lexem : postfix) {
        if (lexem == "+") { r = s.top(); s.pop(); l = s.top(); s.pop(); s.push(l + r); }
        else if (lexem == "-") { r = s.top(); s.pop(); l = s.top(); s.pop(); s.push(l - r); }
        else if (lexem == "*") { r = s.top(); s.pop(); l = s.top(); s.pop(); s.push(l * r); }
        else if (lexem >= "A" && lexem <= "Z") { s.push(table.at(lexem)); }
        else { s.push(Monom(lexem)); }
    }
    return s.top();
}
