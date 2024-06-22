#include <QCoreApplication>
#include <QString>
#include <QStack>
#include <QList>
#include <QDebug>
#include "tree.h"
#include "error.h"

// Функция для проверки, является ли токен оператором
bool isOperator(const QString &token) {
    static QStringList operators = {">", ">=", "<", "<=", "+", "-", "*", "/", "%", "!", "_-", "_+"};
    return operators.contains(token);
}

// Функция для проверки, является ли токен допустимым операндом
bool isValidOperand(const QString &token) {
    bool ok;
    token.toLongLong(&ok);
    if (ok) return true;

    QRegExp rx("[a-zA-Z][a-zA-Z0-9]{0,19}");
    return rx.exactMatch(token);
}

// Функция для построения логического дерева из неравенства
TreeNode* buildLogicalTree(const QString &inequality, QList<Error>& errors) {
    QStack<TreeNode*> stack;
    QStringList tokens = inequality.split(' ');

    for (const QString &token : tokens) {
        qDebug() << "Processing token:" << token;
        if (isValidOperand(token)) {
            stack.push(new TreeNode(token, VAR));
        } else if (isOperator(token)) {
            TreeNodeType type;
            if (token == "+") type = OPER_PLUS;
            else if (token == "-") type = OPER_MINUS;
            else if (token == "*") type = OPER_MULTIPLICATION;
            else if (token == "/") type = OPER_DIVISION;
            else if (token == "%") type = OPER_REMAINDER_OF_DIVISION;
            else if (token == "!") type = OPER_NEGATION;
            else if (token == "<") type = OPER_LESS_THAN;
            else if (token == "<=") type = OPER_LESS_OR_EQUAL;
            else if (token == ">") type = OPER_GREATER_THAN;
            else if (token == ">=") type = OPER_GREATER_OR_EQUAL;
            else if (token == "_-") type = OPER_UNARY_MINUS;
            else if (token == "_+") type = OPER_UNARY_PLUS;
            else continue;

            if (type == OPER_NEGATION || type == OPER_UNARY_MINUS || type == OPER_UNARY_PLUS) {
                if (stack.isEmpty()) {
                    errors.append(Error{NOT_ENOUGH_ARGUMENTS, -1, token});
                    return nullptr;
                }
                TreeNode *operand = stack.pop();
                stack.push(new TreeNode(token, type, operand, nullptr));
            } else {
                if (stack.size() < 2) {
                    errors.append(Error{NOT_ENOUGH_ARGUMENTS, -1, token});
                    return nullptr;
                }
                TreeNode *right = stack.pop();
                TreeNode *left = stack.pop();
                stack.push(new TreeNode(token, type, left, right));
            }
        } else {
            errors.append(Error{UNKNOWN_CHARACTER, -1, token});
        }
    }

    if (stack.size() != 1) {
        errors.append(Error{NOT_ENOUGH_OPERATORS, -1, ""});
        return nullptr;
    }

    return stack.pop();
}

// Функция для преобразования логического дерева для использования оператора "меньше"
void convertToLess(TreeNode* root, QList<Error>& errors) {
    if (!root) {
        errors.append(Error{EMPTY_NODE, -1, ""});
        return;
    }
    if (root->type == OPER_GREATER_THAN) {
        root->type = OPER_LESS_THAN;
        root->value = "<";  // Обновляем значение узла
        TreeNode *temp = root->left;
        root->left = root->right;
        root->right = temp;
    } else if (root->type == OPER_GREATER_OR_EQUAL) {
        root->type = OPER_LESS_OR_EQUAL;
        root->value = "<=";  // Обновляем значение узла
        TreeNode *temp = root->left;
        root->left = root->right;
        root->right = temp;
    } else if (root->type == OPER_LESS_OR_EQUAL) {
        root->type = OPER_LESS_THAN;
        root->value = "<";  // Обновляем значение узла
        root->right = new TreeNode("!", OPER_NEGATION, root->right, nullptr);
    } else if (root->type == OPER_LESS_THAN) {
    }
}

// Функция для получения приоритета оператора
int getPriority(const QString &node) {
    if (node == "!" || node == "_+" || node == "_-") return 4;
    if (node == "<" || node == ">" || node == "<=" || node == ">=") return 1;
    if (node == "*" || node == "/" || node == "%") return 3;
    if (node == "+" || node == "-") return 2;
    return 0;
}

// Функция для преобразования логического дерева в строку
QString treeToString(TreeNode *root, QList<Error>& errors) {
    if (!root) {
        errors.append(Error{EMPTY_NODE, -1, ""});
        return "";
    }
    QString result;
    if (root->left) {
        if (getPriority(root->value) > getPriority(root->left->value)) {
            result += "(" + treeToString(root->left, errors) + ")";
        } else {
            result += "(" + treeToString(root->left, errors) + ")";
        }
    }
    result += " " + root->value + " ";
    if (root->right) {
        if (getPriority(root->value) > getPriority(root->right->value)) {
            result += "(" + treeToString(root->right, errors) + ")";
        } else {
            result += "(" + treeToString(root->right, errors) + ")";
        }
    }
    return result.trimmed();
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QString inequality = "4 3 >=";
    QList<Error> errors;

    TreeNode *root = buildLogicalTree(inequality, errors);

    QString inequality_result = treeToString(root, errors);

    if (!errors.isEmpty()) {
        for (const Error &error : errors) {
            qDebug() << "Error:" << Error::errorToString(error) << "Token:" << error.symbol;
        }
        return -1;
    }

    convertToLess(root, errors);

    if (!errors.isEmpty()) {
        for (const Error &error : errors) {
            qDebug() << "Error:" << Error::errorToString(error) << "Token:" << error.symbol;
        }
        return -1;
    }

    QString result = treeToString(root, errors);

    if (!errors.isEmpty()) {
        for (const Error &error : errors) {
            qDebug() << "Error:" << Error::errorToString(error) << "Token:" << error.symbol;
        }
        return -1;
    }

    qDebug() << "Original inequality:" << inequality_result;
    qDebug() << "Converted inequality:" << result;

    return a.exec();
}
