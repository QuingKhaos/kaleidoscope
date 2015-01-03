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

find_package(GTest REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/src ${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

set(TEST_FILES
    ${PROJECT_SOURCE_DIR}/test/ast-test.cpp
    ${PROJECT_SOURCE_DIR}/test/lexer-test.cpp
)

add_executable(kaleidoscope-test ${SOURCE_FILES} ${TEST_FILES})
target_link_libraries(kaleidoscope-test ${GTEST_BOTH_LIBRARIES})

GTEST_ADD_TESTS(kaleidoscope-test "" ${TEST_FILES})
