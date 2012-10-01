# cppadt -- write ADTs in C++

# We want to emulate Haskell, ML and co
#  data Expr = Add (Expr, Expr)
#            | Subtract (Expr, Expr)
#            | Times (Expr, Expr)
#            | Multiply (Expr, Expr)
#            | Negate (Expr)
#            | ListLiteral [Expr]
#            | IntLiteral (Int)
#            | StringLiteral (String)
# ...etc


# Then we want to be able to pattern match on it
#  foo Add (a, b) = ...
#  foo Subtract (a, b) = ...
#  foo Times (a, b) = ...
#  foo Multiply (a, b) = ...
#  foo Negate (a) = ...
# ...etc


# So what is an ADT? For our purposes we just have
#  (name String, [(tag String, types [(type String, )])])

# Then when we want to use it we just want to say
#  "generate functions named X with this return type, and these suffix arguments"

# And we want to write this all in C++ code and be a strict superset of C++

## Language Extensions
# An ADT block is like this
#    %data
#    
#    %end

# When we want to USE a particular ADT, we do this
#    %generate void foo(int bar, $Expr$, float baz)
#    %case Add expr
#      ...
#    %case Subtract expr
#      ...
#    %case Negate expr
#      ...
#    %end


import sys
import os
import re

DATA_END_REGEX = re.compile(r'%data\s+([a-zA-Z0-9_]+)\n([\s\S]+?)\n%end\n')
DATA_INNARDS_REGEX = re.compile(r'\s*([a-zA-Z0-9_]+)\s*\(([^\)]*)\)')


GENERATE_END_REGEX = re.compile(r'%generate\s+([a-zA-Z0-9_]+)\n([\s\S]+?)\n%end\n')
#DATA_INNARDS_REGEX = re.compile(r'\s*([a-zA-Z0-9_]+)\s*\(([^\)]*)\)')

# Step one, walk the given directory to find .adt.cpp and .adt.hpp files
rootdir = sys.argv[1]
os.chdir(rootdir)

filepaths = []
for root, dirs, files in os.walk('.'):
    for filename in files:
        filepath = os.path.join(root, filename)
        if '.adt.' in filename:
            filepaths.append(filepath)

# Step two, find data declarations and convert into C++ declarations
global_datadecls = []

def data_parse_function(m):
    return data_function(m, True)
def data_replace_function(m):
    return data_function(m, False)
def generate_replace_function(m):
    return 'blah'

def data_function(m, shouldadd):
    dataname = m.groups()[0]
    datainner = m.groups()[1]
    
    tags = []
    for matchgroup in DATA_INNARDS_REGEX.findall(datainner):
        args = matchgroup[1].split(',')
        args = [ tuple(arg.strip().split()) for arg in args ]
        args = [ arg for arg in args if arg ]
        
        tags.append({
            'name': matchgroup[0],
            'arguments': args
        })
    
    if shouldadd:
        # add to global_datadecls
        datadecl = {
            'name': dataname,
            'decls': tags
        }
        
        global_datadecls.append(datadecl)
        return src
    
    else:
        # Template it out
        output  = 'struct %s {\n' % dataname
        output += '    enum class Kind {\n'
        for tag in tags:
            output += '        %s,\n' % tag['name'].title()
        output += '    };\n'
        output += '    Kind kind;\n'
        output += '};\n'
        
        for tag in tags:
            output += 'struct %s%s {\n' % (tag['name'].title(), dataname)
            for arg in tag['arguments']:            
                
                argtype = arg[0] # TODO: magically turn this type into a proper reference
                isOwned = False
                for gdd in global_datadecls:
                    if gdd['name'] == argtype:
                        isOwned = True
                        argtype = 'std::unique_ptr<%s>' % argtype
                        break
                
                argname = arg[1]
                output += '    %s %s;\n' % (argtype, argname)
            output += '};\n'
        
        return output

for filepath in filepaths:
    with open(filepath, 'r') as f:
        src = f.read()
        
        # Parse %data -> %end
        DATA_END_REGEX.sub(data_parse_function, src)

# Step three, find all generate/case statements and turn into C++ code
for filepath in filepaths:
    with open(filepath, 'r') as f:
        src = f.read()

        # Replace %data -> %end
        src = DATA_END_REGEX.sub(data_replace_function, src)
        
        # Replace %generate -> %end
        src = GENERATE_END_REGEX.sub(generate_replace_function, src)
        
        # Create a file without the .adt.
        newfilepath = filepath.replace('.adt.', '.')
        
        # Write to it
        # ...
        print src
        


