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
#include "ast/function.h"
#include "ast/number.h"
#include "ast/variable.h"
#include "gtest/gtest.h"

TEST(ASTTest, BinaryConstruction) {
    char op = '+';
    ExpressionAST lhs, rhs;

    BinaryExpressionAST binary(op, &lhs, &rhs);
}

TEST(ASTTest, CallConstruction) {
    std::string callee("foo");
    std::vector<ExpressionAST*> args;

    ExpressionAST arg;
    args.push_back(&arg);

    CallExpressionAST call(callee, args);
}

TEST(ASTTest, PrototypeAndFunctionConstruction) {
    std::string name("foo");
    std::vector<std::string> args;

    std::string arg("bar");
    args.push_back(arg);

    PrototypeAST prototype(name, args);
    ExpressionAST body;

    FunctionAST function(&prototype, &body);
}

TEST(ASTTest, NumberConstruction) {
    double value = 1.2;

    NumberExpressionAST number(value);
}

TEST(ASTTest, VariableConstruction) {
    std::string name("foo");

    VariableExpressionAST variable(name);
}
