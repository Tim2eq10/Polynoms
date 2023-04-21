#ifndef ARITHMETICALEXPRESSION_H
#define ARITHMETICALEXPRESSION_H

#include "Polynom.h"
#include "include/tables/connector.h"
#include <vector>
#include <map>
#include <stack>

class ArithmeticalExpression
{
private:
    std::string infix;
    std::vector<std::string> postfix;
    std::vector<std::string> lexems;
    static inline std::map<char, int> priority = { {'+', 1}, {'-', 1}, {'*', 2} };

    void Tokenize();
    void ToPostfix();

public:
    ArithmeticalExpression(const std::string& ar_expr);
    ~ArithmeticalExpression() = default;

    std::string GetInfix() const { return infix; }
    std::string GetPostfix() const;
    Polynom getExpr(all_tables<std::string, Polynom>& table);
};


#endif // ARITHMETICALEXPRESSION_H
