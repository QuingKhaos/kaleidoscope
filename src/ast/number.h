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

#ifndef AST_NUMBER_H
#define AST_NUMBER_H

#include "expression.h"

// NumberExpressionAST - Expression class for numeric literals like "1.0".
class NumberExpressionAST : public ExpressionAST {
    double const value;
public:
    NumberExpressionAST(double const value) : value(value) { }

    double const getValue() const { return value; }
};

#endif
