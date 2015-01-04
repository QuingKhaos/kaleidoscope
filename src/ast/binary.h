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

#ifndef AST_BINARY_H
#define AST_BINARY_H

#include "expression.h"

// BinaryExpressionAST - Expression class for a binary operator.
class BinaryExpressionAST : public ExpressionAST {
    char const op;
    ExpressionAST const* const lhs;
    ExpressionAST const* const rhs;
public:
    BinaryExpressionAST(char op, ExpressionAST const* const lhs, ExpressionAST const* const rhs)
            : op(op), lhs(lhs), rhs(rhs) { }

    char const getOp() const { return op; }
    ExpressionAST const* const getLHS() const { return lhs; }
    ExpressionAST const* const getRHS() const { return rhs; }
};

#endif
