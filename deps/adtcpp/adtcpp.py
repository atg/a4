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
GENERATE_TEMPLATE_REGEX = re.compile(r'%template\s+([^\n]+)\n')
GENERATE_CALL_TEMPLATE_REGEX = re.compile(r'%call\s+([^\n]+)\n')
#GENERATE_CASE_REGEX = re.compile(r'%case\s+([^\s+]+)\s+([^\s+]+)\n([^\n]+)\n%')
GENERATE_CASE_REGEX = re.compile(r'^\s*([a-zA-Z0-9_]+)\s+([a-zA-Z0-9_]+)$')
#DATA_INNARDS_REGEX = re.compile(r'\s*([a-zA-Z0-9_]+)\s*\(([^\)]*)\)')

CASE_END_REGEX = re.compile(r'%case\s+([a-zA-Z0-9_]+)\n([\s\S]+?)\n\s*%end\n')

# Step one, walk the given directory to find .adt.cpp and .adt.hpp files
rootdir = sys.argv[1]
os.chdir(rootdir)

def capitalized(s):
    if not s:
        return s
    return s[0].capitalize() + s[1:]

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
    return generate_function(m, False)

def generate_function(m, isCase):
    genname = m.groups()[0]
    geninner = m.groups()[1]
    print isCase
    # Parse out the template
    if not isCase:
        gentemplate = GENERATE_TEMPLATE_REGEX.findall(geninner)[0]
        gencalltemplate = GENERATE_CALL_TEMPLATE_REGEX.findall(geninner)
        if not gencalltemplate:
            funcname = re.findall(r'\s+([a-zA-Z0-9_]+)\(', gentemplate)[0]
            gencalltemplate = funcname + '($$)'
        else:
            gencalltemplate = gencalltemplate[0]
    
        # Replace the $$
        template_function = lambda tname, aname: gentemplate.replace('$$', tname + '& ' + aname)
    
    # Parse out the cases
    currentcase = None
    gencases = []
    for line in geninner.splitlines():
        matchedcase = GENERATE_CASE_REGEX.findall(line)
        print matchedcase
        if matchedcase:
            currentcase = {}
            gencases.append(currentcase)
            currentcase['type'] = matchedcase[0][0]
            currentcase['name'] = matchedcase[0][1]
            currentcase['body'] = ''
            
        elif currentcase:
            currentcase['body'] += line + '\n'
    
    output = ''
    if isCase:
        # Generate the main function
        output = '\nswitch (%s.kind) {\n' % genname.lower()
        for case in gencases:
            output += '  case %s::Kind::%s: {\n' % (genname, case['type'])
            output += '    %s& %s = static_cast<%s&>(%s);\n' % (case['type'], case['name'], case['type'], genname.lower())
            output += '    %s' % case['body']
            output += '    break;\n'
            output += '  }\n'
        output += '}\n'
        
        return output
    else:
        returner = ''
        if not gentemplate.startswith('void '):
            returner = 'return '
        
        # Generate the main function
        output = template_function(genname, genname.lower()) + '{\n'
        output += '    switch (%s.kind) {\n' % genname.lower()
        for case in gencases:
            output += '      case %s::Kind::%s:\n' % (genname, case['type'])
            
            invocation = gencalltemplate.replace('$$', 'static_cast<%s&>(%s)' % (case['type'] + genname, genname.lower()))
            
            output += '        %s%s;\n' % (returner, invocation)
        output += '    }\n'
        output += '}\n'
        
        # Generate the other functions
        for case in gencases:
            output += template_function(case['type'] + genname, case['name']) + '{\n'
            output += case['body']
            output += '}\n'
    
    return output


def case_replace_function(m):
    return generate_function(m, True)

def data_function(m, shouldadd):
    dataname = m.groups()[0]
    datainner = m.groups()[1]
    
    tags = []
    for matchgroup in DATA_INNARDS_REGEX.findall(datainner):
        args = []
        for arg in matchgroup[1].split(','):
            type_and_name = arg.strip().split()
            if not type_and_name:
                continue
            args.append({
                'type': type_and_name[0],
                'name': type_and_name[1]
            })
        
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
            output += '        %s,\n' % capitalized(tag['name'])
        output += '    };\n'
        output += '    Kind kind;\n'
        output += '};\n'
        
        for tag in tags:
            tagstructname = capitalized(tag['name']) + dataname
            output += 'struct %s : public %s {\n' % (tagstructname, dataname)
            
            # Generate members
            for arg in tag['arguments']:
                argtype = arg['type'] # TODO: magically turn this type into a proper reference
                isref = False
                
                for gdd in global_datadecls:
                    if gdd['name'] == argtype:
                        argtype = 'std::unique_ptr<%s>' % argtype
                        isref = True
                        break
                
                arg['isref'] = isref
                arg['fulltype'] = argtype
                if isref:
                    arg['ptrreftype'] = arg['type'] + '*'
                else:
                    arg['ptrreftype'] = arg['type']
                
                argname = arg['name']
                if isref:
                    # We want to generate TWO members, one is a unique_ptr, the other is a reference to whatever's in the pointer
                    output += '    %s %s_ptr;\n' % (argtype, argname)
                    output += '    %s& %s() { return *%s_ptr; }\n' % (arg['type'], argname, argname)
                    arg['member_name'] = argname + '_ptr'
                else:
                    output += '    %s %s;\n' % (argtype, argname)
                    arg['member_name'] = argname
            
            # Generate constructor
            output += '    %s(' % tagstructname
            output += ', '.join('%s _%s' % (arg['ptrreftype'], arg['name']) for arg in tag['arguments'])
            output += ') : '
            #output += ', '.join('%s_ptr(_%s), %s(*_%s)' % (arg['name'], arg['name'], arg['name'], arg['name']) for arg in tag['arguments'])
            output += ', '.join('%s(_%s)' % (arg['member_name'], arg['name']) for arg in tag['arguments'])
            
            output += ' { }\n'
            
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
        
        # Replace %case -> %end
        src = CASE_END_REGEX.sub(case_replace_function, src)
        
        # Create a file without the .adt.
        newfilepath = filepath.replace('.adt.', '.')
        
        # Write to it
        # ...
        print src
        


