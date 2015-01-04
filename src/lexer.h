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

#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <string>

// The lexer returns tokens [0-255] if it is an unknown character, otherwise one
// of these for known things.
enum Token {
    TokenEOF = -1,

    // commands
            TokenDef = -2, TokenExtern = -3,

    // primary
            TokenIdentifier = -4, TokenNumber = -5,
};

class Lexer {
    std::istream* inputStream;
    int lastChar = ' ';

protected:
    std::string identifier; // Filled in if TokenIdentifier
    double numberValue;     // Filled in if TokenNumber

public:
    Lexer() { }

    Lexer(std::istream* inputStream) :
            inputStream(inputStream) { }

    virtual int const getToken();
    std::string getIdentifier();
    double getNumberValue();
};

#endif
