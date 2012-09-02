import os, shutil
import subprocess

os.chdir(os.path.dirname(os.path.abspath(__file__)))

try:
    os.mkdir('build')
except:
    pass

# Compile grammar.lemon
if subprocess.check_call(['deps/lemon', 'source/grammar.lemon']) == 0:
    shutil.move('source/grammar.c', 'source/grammar.cpp')
    shutil.move('source/grammar.h', 'source/tokentypes.hpp')
    
    # Compile tokenizer.rl
    if subprocess.check_call(['deps/ragel', 'source/tokenizer.rl']) == 0:
        shutil.move('source/tokenizer.c', 'source/tokenizer.cpp')
        
        # Compile all .cpp files
        allcppfiles = ['source/' + p for p in os.listdir('source') if os.path.splitext(p)[1] == '.cpp']
        subprocess.check_call(['clang++', '-Os', '-fno-exceptions', '-fno-rtti', '-Wextra', '-std=c++0x', '-o', 'build/fur'] + allcppfiles)


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
