#pragma once
#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include "binaryTree.h"

class binaryExpressionTree : public binaryTreeType<std::string> {
public:
    binaryExpressionTree(); // constructor
    void evaluateExpressionTree(); // public function to evaluate expression tree
    void buildFromPostfix(const std::string& postfixExpr); // public function to build expression tree from postfix expression

    // Implementing the pure virtual functions from the base class
    bool search(const std::string& searchItem) const override;
    void insert(const std::string& insertItem) override;
    void deleteNode(const std::string& deleteItem) override;

private:
    void evaluateExpressionTree(nodeType<std::string>* p); // private recursive function
    void buildExpressionTree(const std::string& postfixExpr); // helper function to build expression tree
    bool isOperator(const std::string& token); // helper function to check if token is an operator
};

binaryExpressionTree::binaryExpressionTree() : binaryTreeType<std::string>() {}

void binaryExpressionTree::evaluateExpressionTree() {
    if (root != nullptr) {
        evaluateExpressionTree(root);
    }
}

void binaryExpressionTree::evaluateExpressionTree(nodeType<std::string>* p) {
    if (p == nullptr)
        return;

    if (p->lLink == nullptr && p->rLink == nullptr) { // leaf node
        // Assuming the info field stores numbers
        try {
            double operand = std::stod(p->info); // Convert the string to double
            std::cout << operand << std::endl;
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Error: Invalid operand encountered." << std::endl;
        }
        catch (const std::out_of_range& e) {
            std::cerr << "Error: Operand out of range." << std::endl;
        }
    }
    else {
        // Operator node, evaluate left and right subtrees first
        evaluateExpressionTree(p->lLink);
        evaluateExpressionTree(p->rLink);

        // Once the subtrees are evaluated, perform the operation
        if (!isOperator(p->info)) {
            std::cerr << "Error: Invalid operator." << std::endl;
            return;
        }

        // Get the operands after evaluating the subtrees
        double x = std::stod(p->lLink->info); // Convert left operand to double
        double y = std::stod(p->rLink->info); // Convert right operand to double

        // Print the expression and the result of the operation
        std::cout << x << " " << p->info << " " << y << " = ";

        // Evaluate the expression based on the operator
        if (p->info == "+")
            std::cout << x + y << std::endl;
        else if (p->info == "-")
            std::cout << x - y << std::endl;
        else if (p->info == "*")
            std::cout << x * y << std::endl;
        else if (p->info == "/") {
            if (y != 0)
                std::cout << x / y << std::endl;
            else
                std::cerr << "Error: Division by zero." << std::endl;
        }
    }
}






void binaryExpressionTree::buildFromPostfix(const std::string& postfixExpr) {
    buildExpressionTree(postfixExpr);
}

void binaryExpressionTree::buildExpressionTree(const std::string& postfixExpr) {
    std::stack<nodeType<std::string>*> nodeStack;
    std::istringstream iss(postfixExpr);

    std::string token;
    while (std::getline(iss, token, ' ')) {
        if (!token.empty()) {
            if (isdigit(token[0])) { // If token is a number
                nodeType<std::string>* newNode = new nodeType<std::string>;
                newNode->info = token;
                newNode->lLink = nullptr;
                newNode->rLink = nullptr;
                nodeStack.push(newNode);
            }
            else if (isOperator(token)) { // If token is an operator
                if (nodeStack.size() < 2) {
                    std::cerr << "Error: Invalid expression." << std::endl;
                    return;
                }
                nodeType<std::string>* newNode = new nodeType<std::string>;
                newNode->info = token;
                newNode->rLink = nodeStack.top();
                nodeStack.pop();
                newNode->lLink = nodeStack.top();
                nodeStack.pop();
                nodeStack.push(newNode);
            }
            else {
                std::cerr << "Error: Unsupported token." << std::endl;
                return;
            }
        }
    }

    if (nodeStack.size() != 1) {
        std::cerr << "Error: Invalid expression." << std::endl;
        root = nullptr;
    }
    else {
        root = nodeStack.top();
        nodeStack.pop();
    }
}


bool binaryExpressionTree::isOperator(const std::string& token) {
    return (token == "+" || token == "-" || token == "*" || token == "/");
}

bool binaryExpressionTree::search(const std::string& searchItem) const {
    // Implementing a search function may not be straightforward for an expression tree
    // If you don't need search functionality, you can simply return false
    return false;
}

void binaryExpressionTree::insert(const std::string& insertItem) {
    // Inserting into an expression tree may not be meaningful
    // If you don't need insertion functionality, you can leave this function empty
}

void binaryExpressionTree::deleteNode(const std::string& deleteItem) {
    // Deleting from an expression tree may not be meaningful
    // If you don't need deletion functionality, you can leave this function empty
}