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
#include "ast/binary.h"
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
    std::vector<ExpressionAST const*> args;

    if (currentToken != ')') {
        while (1) {
            ExpressionAST const* arg = parseExpression();

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

/// Get the precedence of the pending binary operator token.
int const Parser::getTokenPrecedence() {
    if (!isascii(currentToken)) {
        return -1;
    }

    // Make sure it's a declared binary operator.
    int const tokenPrecedence = binaryOpPrecedence[currentToken];
    if (tokenPrecedence <= 0) {
        return -1;
    }

    return tokenPrecedence;
}

/// expression
///   ::= primary binaryoprhs
ExpressionAST const* Parser::parseExpression() {
    ExpressionAST const* lhs = parsePrimary();
    if (!lhs) {
        return nullptr;
    }

    return parseBinaryOpRHS(0, lhs);
}

/// binaryoprhs
///   ::= ('+' primary)*
ExpressionAST const* Parser::parseBinaryOpRHS(int expressionPrecedence, ExpressionAST const* lhs) {
    // If this is a binaryOp, find its precedence.
    while (1) {
        int const tokenPrecedence = getTokenPrecedence();

        // If this is a binaryOp that binds at least as tightly as the current binaryOp,
        // consume it, otherwise we are done.
        if (tokenPrecedence < expressionPrecedence) {
            return lhs;
        }

        // Okay, we know this is a binaryOp.
        int const binaryOp = currentToken;
        getNextToken(); // eat binaryOp

        // Parse the primary expression after the binary operator.
        ExpressionAST const* rhs = parsePrimary();
        if (!rhs) {
            return nullptr;
        }

        // If binaryOp binds less tightly with RHS than the operator after RHS, let
        // the pending operator take RHS as its LHS.
        int const nextPrecedence = getTokenPrecedence();
        if (tokenPrecedence < nextPrecedence) {
            rhs = parseBinaryOpRHS(tokenPrecedence + 1, rhs);
        }

        // Merge LHS/RHS.
        lhs = new BinaryExpressionAST((char) binaryOp, lhs, rhs);
    }
}

/// prototype
///   ::= id '(' id* ')'
PrototypeAST const* Parser::parsePrototype() {
    if (currentToken != TokenIdentifier) {
        return errorPrototype("Expected function name in prototype");
    }

    std::string const functionName = lexer->getIdentifier();
    getNextToken();

    if (currentToken != '(') {
        return errorPrototype("Expected '(' in prototype");
    }

    // Read the list of argument names.
    std::vector<std::string> argNames;
    while (getNextToken() == TokenIdentifier) {
        argNames.push_back(lexer->getIdentifier());
    }

    if (currentToken != ')') {
        return errorPrototype("Expected ')' in prototype");
    }

    getNextToken(); // eat )

    return new PrototypeAST(functionName, argNames);
}

/// definition ::= 'def' prototype expression
FunctionAST const* Parser::parseDefinition() {
    getNextToken(); // eat def

    PrototypeAST const* prototype = parsePrototype();
    if (!prototype) {
        return nullptr;
    }

    ExpressionAST const* expression = parseExpression();
    if (!expression) {
        return nullptr;
    }

    return new FunctionAST(prototype, expression);
}

/// external ::= 'extern' prototype
PrototypeAST const* Parser::parseExtern() {
    getNextToken(); // eat extern

    return parsePrototype();
}

/// toplevelexpression ::= expression
FunctionAST const* Parser::parseTopLevelExpression() {
    ExpressionAST const* expression = parseExpression();
    if (!expression) {
        return nullptr;
    }

    // Make an anonymous prototype
    PrototypeAST const* prototype = new PrototypeAST("", std::vector<std::string>());
    return new FunctionAST(prototype, expression);
}
