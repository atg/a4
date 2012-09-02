import os
import subprocess

os.chdir(os.path.dirname(os.path.abspath(__file__)))

try:
    os.mkdir('build')
except:
    pass

# Compile grammar.lemon
subprocess.call(['deps/lemon', 'source/grammar.lemon'])
subprocess.call(['mv', 'source/grammar.c' 'source/grammar.cpp'])
subprocess.call(['mv', 'source/grammar.h' 'source/grammar.hpp'])

# Compile tokenizer.rl
subprocess.call(['deps/ragel', 'source/tokenizer.rl'])
subprocess.call(['mv', 'source/tokenizer.c' 'source/tokenizer.cpp'])

# Compile all .cpp files
allcppfiles = [p for p in os.listdir('source') if os.path.splitext(p) == '.cpp']
subprocess.call(['clang++', '-Os', '-fno-exceptions', '-fno-rtti', '-Wextra', '-std=c++11'] + allcppfiles)


'''
cd code/selectors

# Selector Bytecode

../../Tools/lemon/lemon selectorbytecode_parser.lemon
mv selectorbytecode_parser.c selectorbytecode_parser.mm
../../Tools/ragel/ragel selectorbytecode_tokenizer.rl
mv selectorbytecode_tokenizer.c selectorbytecode_tokenizer.mm


cd ../snippets
# Snippet Parser

../../Tools/lemon/lemon CHNewSnippetParser.lemon
mv CHNewSnippetParser.c CHNewSnippetParser.m
../../Tools/ragel/ragel CHNewSnippetLexer.rl
mv CHNewSnippetLexer.c CHNewSnippetLexer.m
'''
