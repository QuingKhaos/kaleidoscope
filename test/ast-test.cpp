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

#include <stdio.h>
#include <string>
#include <vector>
#include "ast/binary.h"
#include "ast/call.h"
#include "ast/function.h"
#include "ast/number.h"
#include "ast/variable.h"
#include "gtest/gtest.h"

#pragma clang diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-variable"

TEST(ASTTest, BinaryConstruction) {
    char op = '+';
    ExpressionAST lhs, rhs;

    BinaryExpressionAST binary(op, &lhs, &rhs);
    EXPECT_EQ(op, binary.getOp());
    EXPECT_EQ(&lhs, binary.getLHS());
    EXPECT_EQ(&rhs, binary.getRHS());
}

TEST(ASTTest, CallConstruction) {
    std::string callee("foo");
    std::vector<ExpressionAST const*> args;

    ExpressionAST arg;
    args.push_back(&arg);

    CallExpressionAST call(callee, args);

    EXPECT_EQ(callee, call.getCallee());
    EXPECT_STREQ(callee.c_str(), call.getCallee().c_str());

    EXPECT_EQ(args, call.getArgs());
    EXPECT_EQ(&arg, call.getArgs().at(0));
}

TEST(ASTTest, PrototypeAndFunctionConstruction) {
    std::string name("foo");
    std::vector<std::string> args;

    std::string arg("bar");
    args.push_back(arg);

    PrototypeAST prototype(name, args);

    EXPECT_EQ(name, prototype.getName());
    EXPECT_STREQ(name.c_str(), prototype.getName().c_str());

    EXPECT_EQ(args, prototype.getArgs());
    EXPECT_EQ(arg, prototype.getArgs().at(0));
    EXPECT_STREQ(arg.c_str(), prototype.getArgs().at(0).c_str());

    ExpressionAST body;

    FunctionAST function(&prototype, &body);
    EXPECT_EQ(&prototype, function.getPrototype());
    EXPECT_EQ(&body, function.getBody());
}

TEST(ASTTest, NumberConstruction) {
    double value = 1.2;

    NumberExpressionAST number(value);
    EXPECT_DOUBLE_EQ(value, number.getValue());
}

TEST(ASTTest, VariableConstruction) {
    std::string name("foo");

    VariableExpressionAST variable(name);
    EXPECT_EQ(name, variable.getName());
    EXPECT_STREQ(name.c_str(), variable.getName().c_str());
}
