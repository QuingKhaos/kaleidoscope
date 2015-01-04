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

#include <sstream>
#include "lexer.h"
#include "gtest/gtest.h"

#pragma clang diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-variable"

TEST(LexerTest, EndOfFile) {
    std::istringstream input;
    Lexer lexer(&input);

    EXPECT_EQ(TokenEOF, lexer.getToken());
}

TEST(LexerTest, FunctionDefine) {
    std::istringstream input("def");
    Lexer lexer(&input);

    EXPECT_EQ(TokenDef, lexer.getToken());
}

TEST(LexerTest, FunctionExtern) {
    std::istringstream input("extern");
    Lexer lexer(&input);

    EXPECT_EQ(TokenExtern, lexer.getToken());
}

TEST(LexerTest, Identifier) {
    std::istringstream input("foo");
    Lexer lexer(&input);

    EXPECT_EQ(TokenIdentifier, lexer.getToken());
    EXPECT_EQ("foo", lexer.getIdentifier());
}

TEST(LexerTest, Number) {
    std::istringstream input("1.2");
    Lexer lexer(&input);

    EXPECT_EQ(TokenNumber, lexer.getToken());
    EXPECT_EQ(1.2, lexer.getNumberValue());
}
