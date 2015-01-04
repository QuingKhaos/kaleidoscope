#
# Kaleidoscope language and compiler
#
# Copyright (C) 2015 Patrik Karisch
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.

set(SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/src/ast/binary.h
    ${PROJECT_SOURCE_DIR}/src/ast/call.h
    ${PROJECT_SOURCE_DIR}/src/ast/expression.h
    ${PROJECT_SOURCE_DIR}/src/ast/function.h
    ${PROJECT_SOURCE_DIR}/src/ast/number.h
    ${PROJECT_SOURCE_DIR}/src/ast/prototype.h
    ${PROJECT_SOURCE_DIR}/src/ast/variable.h
    ${PROJECT_SOURCE_DIR}/src/lexer.cpp
    ${PROJECT_SOURCE_DIR}/src/parser.cpp
)

set(SOURCE_TEST_FILES ${SOURCE_FILES} PARENT_SCOPE)

add_executable(kaleidoscope main.cpp ${SOURCE_FILES})