#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Функция для проверки, является ли токен оператором
bool isOperator(const QString &token, QList<Error>& errors);

// Функция для проверки, является ли токен допустимым операндом
bool isValidOperand(const QString &token, QList<Error>& errors);

// Функция для построения логического дерева из неравенства
TreeNode* buildLogicalTree(const QString &inequality, QList<Error>& errors);

// Функция для преобразования логического дерева для использования оператора "меньше"
void convertToLess(TreeNode* root, QList<Error>& errors);

// Функция для получения приоритета оператора
int getPriority(const QString &node);


// Функция для преобразования логического дерева в строку
QString treeToString(TreeNode *root, QList<Error>& errors);


#endif // FUNCTIONS_H
