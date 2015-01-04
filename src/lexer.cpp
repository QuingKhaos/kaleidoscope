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

#include "lexer.h"

int const Lexer::getToken() {
    // Skip any whitespace.
    while (isspace(lastChar))
        lastChar = (int) inputStream->get();

    if (isalpha(lastChar)) { // identifier: [a-zA-Z][a-zA-Z0-9]*
        identifier = lastChar;
        while (isalnum((lastChar = (int) inputStream->get())))
            identifier += lastChar;

        if (identifier == "def") return TokenDef;
        if (identifier == "extern") return TokenExtern;
        return TokenIdentifier;
    }

    if (isdigit(lastChar) || lastChar == '.') {   // Number: [0-9.]+
        std::string number;
        do {
            number += lastChar;
            lastChar = (int) inputStream->get();
        } while (isdigit(lastChar) || lastChar == '.');

        numberValue = strtod(number.c_str(), 0);
        return TokenNumber;
    }

    if (lastChar == '#') {
        // Comment until end of line.
        do lastChar = (int) inputStream->get();
        while (lastChar != EOF && lastChar != '\n' && lastChar != '\r');

        if (lastChar != EOF)
            return getToken();
    }

    // Check for end of file.  Don't eat the EOF.
    if (lastChar == EOF)
        return TokenEOF;

    // Otherwise, just return the character as its ascii value.
    int thisChar = lastChar;
    lastChar = (int) inputStream->get();
    return thisChar;
}

std::string Lexer::getIdentifier() {
    return identifier;
}

double Lexer::getNumberValue() {
    return numberValue;
}
