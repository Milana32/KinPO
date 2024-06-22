#include "error.h"

// //Преобразование ошибки в строку
// QString Error::errorToString(const Error &error) {
//     switch (error.type) {
//     case PATH_NOT_FOUND: return "Path not found";
//     case FILE_NOT_FOUND: return "File not found";
//     case FILE_NOT_OPENED: return "File not opened";
//     case MORE_THAN_ONE_STRING: return "More than one string";
//     case UNKNOWN_CHARACTER: return "Unknown character: " + error.symbol;
//     case NOT_ENOUGH_OPERATORS: return "Not enough operators";
//     case NOT_ENOUGH_ARGUMENTS: return "Not enough arguments";
//     case NO_SPACE_BETWEEN_OPERANDS: return "No space between operands";
//     case EMPTY_TREE: return "Empty tree";
//     case EMPTY_NODE: return "Empty node";
//     case COMPARISON_OPERATOR_NOT_FOUND: return "Comparison operator not found";
//     case INCORRECT_USE_OF_EXCLAMATION_MARK: return "Incorrect use of exclamation mark";
//     case MORE_THAN_ONE_COMPARISON_OPERATOR: return "More than one comparison operator";
//     default: return "UNKNOWN_ERROR: Unknown error";
//     }
// }
