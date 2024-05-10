#include <iostream>
#include "binaryTree.h"
#include "binaryExpressionTree.h"

int main()
{
    // Create an expression tree object
    binaryExpressionTree exprTree;

    // Build an expression tree from a postfix expression
    std::string postfixExpr = "3 4 + 5 *";
    exprTree.buildFromPostfix(postfixExpr);

    // Evaluate the expression tree
    std::cout << "Evaluation result: ";
    exprTree.evaluateExpressionTree();

    return 0;
}
