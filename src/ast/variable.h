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

#ifndef AST_VARIABLE_H
#define AST_VARIABLE_H

#include <string>
#include "expression.h"

// VariableExpressionAST - Expression class for referencing a variable, like "a".
class VariableExpressionAST : public ExpressionAST {
    std::string const name;
public:
    VariableExpressionAST(std::string const& name) : name(name) {}
};

#endif
