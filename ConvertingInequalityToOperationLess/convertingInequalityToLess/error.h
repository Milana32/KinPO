#ifndef ERROR_H
#define ERROR_H

#include <QString>

enum ErrorType {
    UNKNOWN_CHARACTER,
    NOT_ENOUGH_ARGUMENTS,
    NOT_ENOUGH_OPERATORS,
    EMPTY_NODE
};

struct Error {
    ErrorType type;
    int position;
    QString symbol;

    Error(ErrorType t, int p, const QString &s) : type(t), position(p), symbol(s) {}

    static QString errorToString(const Error &error) {
        switch (error.type) {
        case UNKNOWN_CHARACTER:
            return "Unknown character";
        case NOT_ENOUGH_ARGUMENTS:
            return "Not enough arguments";
        case NOT_ENOUGH_OPERATORS:
            return "Not enough operators";
        case EMPTY_NODE:
            return "Empty node";
        default:
            return "Unknown error";
        }
    }
};

#endif // ERROR_H
