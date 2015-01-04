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

#ifndef PARSER_H
#define PARSER_H

#include <map>
#include "ast/expression.h"
#include "ast/function.h"
#include "ast/number.h"
#include "ast/prototype.h"
#include "lexer.h"

class Parser {
    int currentToken;
    Lexer* const lexer;

protected:
    ExpressionAST const* const error(char const* const str) const;
    PrototypeAST const* const errorPrototype(char const* const str) const;
    FunctionAST const* const errorFunction(char const* const str) const;

public:
    Parser(Lexer* const lexer) : lexer(lexer) { }

    int const getNextToken() { return currentToken = lexer->getToken(); }

    NumberExpressionAST const* parseNumberExpression();
    ExpressionAST const* parseParenthesisExpression();
    ExpressionAST const* parseIdentifierExpression();
    ExpressionAST const* parsePrimary();

    /// This holds the precedence for each binary operator that is defined
    std::map<char, int> binaryOpPrecedence;
    int const getTokenPrecedence();

    ExpressionAST const* parseExpression();
    ExpressionAST const* parseBinaryOpRHS(int expressionPrecedence, ExpressionAST const* lhs);
};

#endif
