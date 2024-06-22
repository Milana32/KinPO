#ifndef TREE_H
#define TREE_H

#include <QString>

enum TreeNodeType {
    VAR,
    OPER_PLUS,
    OPER_MINUS,
    OPER_MULTIPLICATION,
    OPER_DIVISION,
    OPER_REMAINDER_OF_DIVISION,
    OPER_NEGATION,
    OPER_LESS_THAN,
    OPER_LESS_OR_EQUAL,
    OPER_GREATER_THAN,
    OPER_GREATER_OR_EQUAL,
    OPER_UNARY_MINUS,
    OPER_UNARY_PLUS
};

struct TreeNode {
    QString value;
    TreeNodeType type;
    TreeNode *left;
    TreeNode *right;

    TreeNode(const QString &val, TreeNodeType t, TreeNode *l = nullptr, TreeNode *r = nullptr)
        : value(val), type(t), left(l), right(r) {}
};

#endif // TREE_H
