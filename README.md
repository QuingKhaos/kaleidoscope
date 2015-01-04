Kaleidoscope language and compiler
==================================

[![Build Status](https://travis-ci.org/patkar/kaleidoscope.svg?branch=master)](https://travis-ci.org/patkar/kaleidoscope)

This is my work on the Kaleidoscope language and compiler based on the
[Kaleidoscope LLVM Tutorial](http://llvm.org/docs/tutorial/LangImpl1.html) and inspired by the
[tutorial from Loren Segal](http://gnuu.org/2009/09/18/writing-your-own-toy-compiler/). Since the Kaleidoscope LLVM
Tutorial doesn't care about design principles and stuff, I'm trying to recreate the tutorial in a cleaner way. Later
I want to integrate [flexc++](http://flexcpp.sourceforge.net) as a lexer and [bisonc++](http://bisoncpp.sourceforge.net/)
as AST parser instead of the self written lexer and parser from the tutorial.

Why on GitHub
-------------

This is mainly a personal project for learning about lexer, parser and compilers. GitHub acts both as online backup and
to show off my learning experience.

Installation
------------

First you have to compile the kaleidoscope compiler itself. Create a directory outside of the git repo and cd into it.

```
cmake ~/path/to/kaleidoscope/gitrepo && make
```

Usage
-----

The `kaleidoscope` binary is located in the `src` folder. Currently kaleidoscope only parses the input and shows which
expression was parsed.

```
$ ./kaleidoscope
ready> def foo(x y) x+foo(y, 4.0);
Parsed a function definition.
ready> def foo(x y) x+y y;
Parsed a function definition.
Parsed a top-level expr
ready> def foo(x y) x+y );
Parsed a function definition.
Error: unknown token when expecting an expression
ready> extern sin(a);
Parsed an extern
ready> ^D
$
```

License
-------

Copyright (C) 2015 Patrik Karisch

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see http://www.gnu.org/licenses/.
