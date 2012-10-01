import os, shutil
import subprocess

os.chdir(os.path.dirname(os.path.abspath(__file__)))

try:
    os.mkdir('build')
except:
    pass

# Compile grammar.lemon
if subprocess.check_call(['deps/lemon', 'source/parse/grammar.lemon']) == 0:
    shutil.move('source/parse/grammar.c', 'source/parse/grammar.cpp')
    shutil.move('source/parse/grammar.h', 'source/parse/tokentypes.hpp')
    
    # Compile tokenizer.rl
    if subprocess.check_call(['deps/ragel', 'source/parse/tokenizer.rl']) == 0:
        shutil.move('source/parse/tokenizer.c', 'source/parse/tokenizer.cpp')
        
        # Compile all .cpp files
        allcppfiles = ['source/' + p for p in os.listdir('source') if os.path.splitext(p)[1] == '.cpp']
        for p in os.listdir('source'):
            if p[0] != '.':
                for subp in os.listdir('source/' + p):
                    if os.path.splitext(subp)[1] == '.cpp':
                        allcppfiles.append('source/' + p + "/" + subp)
        
        print allcppfiles
        subprocess.check_call(['clang++', '-Isource', '-Os', '-fno-exceptions', '-fno-rtti', '-Wextra', '-std=c++0x', '-stdlib=libc++', '-o', 'build/fur'] + allcppfiles)
