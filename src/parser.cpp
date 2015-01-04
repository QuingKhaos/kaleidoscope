#include <ast/expression.h>

/*
 * Kaleidoscope language and compiler
 *
 * Copyright (C) 2015 Patrik Karisch
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <string>
#include <vector>
#include "ast/call.h"
#include "ast/variable.h"
#include "parser.h"

ExpressionAST const* const Parser::error(char const* const str) const {
    std::cerr << "Error:" << str << std::endl;
    return nullptr;
}

PrototypeAST const* const Parser::errorPrototype(char const* const str) const {
    error(str);
    return nullptr;
}

FunctionAST const* const Parser::errorFunction(char const* const str) const {
    error(str);
    return nullptr;
}

/// numberexpression ::= number
NumberExpressionAST const* Parser::parseNumberExpression() {
    NumberExpressionAST const* result = new NumberExpressionAST(lexer->getNumberValue());

    getNextToken(); // consume the number
    return result;
}

/// parenthesisexpression ::= '(' expression ')'
ExpressionAST const* Parser::parseParenthesisExpression() {
    getNextToken(); // eat (

    ExpressionAST const* value = parseExpression();
    if (!value) {
        return nullptr;
    }

    if (currentToken != ')') {
        return error("exprected ')'");
    }

    getNextToken(); // eat )
    return value;
}

/// identifierexpression
///   ::= identifier
///   ::= identifier '(' expression* ')'
ExpressionAST const* Parser::parseIdentifierExpression() {
    std::string identifierName = lexer->getIdentifier();

    getNextToken(); // eat identifier

    // Simple variable reference
    if (currentToken != '(') {
        return new VariableExpressionAST(identifierName);
    }

    // Call
    getNextToken(); // eat (
    std::vector<ExpressionAST*> args;

    if (currentToken != ')') {
        while (1) {
            ExpressionAST* arg = parseExpression();

            if (!arg) {
                return nullptr;
            }
            args.push_back(arg);

            if (currentToken == ')') {
                break;
            }

            if (currentToken != ',') {
                return error("Expected ')' or ',' in argument list");
            }

            getNextToken();
        }
    }

    // Eat the )
    getNextToken();

    return new CallExpressionAST(identifierName, args);
}

/// primary
///   ::= identifierexpression
///   ::= numberexprexpression
///   ::= parenthesisexpression
ExpressionAST const* Parser::parsePrimary() {
    switch (currentToken) {
        case TokenIdentifier:
            return parseIdentifierExpression();
        case TokenNumber:
            return parseNumberExpression();
        case '(':
            return parseParenthesisExpression();
        default:
            return error("unknown token when expecting an expression");
    }
}
