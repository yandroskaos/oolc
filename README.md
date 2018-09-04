# oolc
Simple and Small Object Oriented Language Compiler targeting .NET

This is a minimal example of how to engineer a simple compiler.
Provides great example on how to use lex + yacc.
But other introductory elements out there stops here and say "yup, now with an AST, everything is easy".
OOLC steps forward and shows how to use visitor pattern effectively, as well as other patterns as
the Builder pattern and tricks such as using virtual parsing nodes to cope with the LALR grammar from yacc in conjuction with the use of a Builder.
Also how to define types and symbols, as well as tables to handle those.
Finally, there is a backend code generator targeting .NET IL (so actually executables produced can be run).
Theres also a beautifier backend for testing purposes.

In the test-files you can see a TicTacToe minimax fully functional program. 

Should work on windows, uses CMake to create project files.

I hope you enjoy hacking it as much as i enjoyed writing it.

