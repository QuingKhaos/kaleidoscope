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
#include "lexer.h"
#include "parser.h"
#include "gtest/gtest.h"

class DummyLexer : public Lexer {
    int const token;
public:
    DummyLexer(int token) : token(token) { }

    int const getToken() {
        return token;
    }
};

#pragma clang diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-variable"

TEST(ParserTest, NextToken) {
    DummyLexer lexer(TokenDef);

    Parser parser(&lexer);
    EXPECT_EQ(TokenDef, parser.getNextToken());
}