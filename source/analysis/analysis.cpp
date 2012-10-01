#import <unordered_map>

#import "ast/ast.hpp"

struct Scope {
    Scope* global;
    Scope* parent;
    
    std::unordered_map<std::string, Decl*> symbols;
    
    Decl* find(const std::string& ident) {
        auto it = symbols.find(ident);
        
        // If we didn't find a symbol, search upwards
        if (it == symbols.end()) {
            if (parent) {
                return parent->find(ident);
            return NULL;
        }
        
        return *it;
    }
};

Type* type_of(Expr*) {
    
}
Type* common_type_of(std::deque<Expr*> exprs) {
    
}

Type* type_of(BinaryExpr* expr) {
    switch (expr->type) {
        case OperatorType::LogicalAnd:
        case OperatorType::LogicalOr:
            return new NamedType("Bool");

        case OperatorType::In:
            // Check that this even makes sense
            return new NamedType("Bool");
        
        case OperatorType::Equals:
        case OperatorType::NotEqual:
            // Check that the objects are of compatiable type
            return new NamedType("Bool");
        
        case OperatorType::LessThan:
        case OperatorType::GreaterThan:
        case OperatorType::LessOrEqual:
        case OperatorType::GreaterOrEqual:
            // Check that the objects are comparable
            return new NamedType("Bool");
        
        case OperatorType::Add:
            // Check that the objects are addable
                // Real, Int, String, 
            /*
                          42   3.14   "abc"   [yes, no]
                       42 Int  Real   String  x
                     3.14 Real Real   String  x
                    "abc" Str  Str    String  x
                [yes, no] x    x      x       List...
                
                The type of a list is as follows
                          List [Any] [T]
                     List List List  List
                    [Any] List [Any] List
                      [T] List List  [T]
            */
            
            Type* lt = type_of(expr->left);
            Type* rt = type_of(expr->right);
            if (!lt || !rt)
                return NULL;
            
            if (type_is_named(lt, "Int"))
                
            
            return  || type_is_string(expr.type) || type_is_list(expr.type);
        case OperatorType::Subtract:
            // Check that the objects are subtractable
            return type_is_number(expr.type) || type_is_string(expr.type) || type_is_list(expr.type);
        
        case OperatorType::Multiply:
            // Check that the objects can be multiplied
            return ...;
        case OperatorType::Divide:
            // Check that the objects can be divided
            return ...;
        case OperatorType::Mod:
            // Check that the objects can be modulo'd
            return ...;
        
        case OperatorType::Power:
            // Check that the objects can be taken to a power
            return ...;
        
        default:
            assert(0 && "Unknown BinaryExpr type in type_of");
    }
}
bool check_signature(FunctionDecl* decl) {
    // Make sure that binary operators overloads have the right number of arguments
    
    static std::unordered_set<std::string> binaryops({ "&&", "||", "in", "==", "+", "-", "*", "/", "mod", "**" });
    static std::unordered_set<std::string> unary({ "negate", "||", "in", "==", "+", "-", "*", "/", "mod", "**" });
    
    // Other special functions
    "compare" // (T, T) -> 
    "negate" // T -> T
    
    if (decl)
}
Type* type_of(UnaryExpr* expr) {
    if (expr.type == OperatorType::Negate) {
        // Check that the argument is negatable
        
        // This is obviously of the same type
        return type_of(expr.expr);
    }
    else if (expr.type == OperatorType::LogicalNot) {
        // Logical not can be applied to any type
        return new NamedType("Bool");
    }
    else {
        assert(0 && "Unknown UnaryExpr type in type_of");
    }
}
Type* type_of(CallExpr* call) {
    Scope* scope = call->scope;
    
    // Find the relevant call for target
    std::deque<std::pair<FunctionDecl*, std::deque<Type*> > > candidates;
    
    bool hasArgumentTypes = false;
    std::deque<Decl*> argumentTypes;
    
    // 1. Find all functions with call->name
    for (Decl* decl : scope.find(call->name)) {
        if (decl.type != DeclType::Function)
            continue;
        
        FunctionDecl* fdecl = static_cast<FunctionDecl*>(decl);
        
        // 2. Ignore any functions with the wrong number of arguments
        // TODO: make this work properly with tuples
        // if (call->arguments.size() != fdecl->parameters.size())
            // continue;

        // 3. Find the types of the arguments given to the call
        if (!hasArgumentTypes) {
            for (Expr* arg : call->arguments) {
                argumentTypes.push_back(type_of(arg, scope->global));
            }
        }
        
        // 4. Find functions whose arguments match the call
        std::deque<Type*> parameterTypes;
        if (fdecl->signature->keytype->type == TypeType:Tuple) {
            for (Type* itemtype : static_cast<TupleTuple*>(fdecl->signature->keytype)->items) {
                parameterTypes.push_back(itemtype);
            }
        }
        else {
            parameterTypes.push_back(fdecl->signature->keytype);
        }
        
        // So, is each argument a subtype of each parameter?
        for (std::deque<Type*>::iterator
               arg_it = argumentTypes.begin(),
               arg_et = parameterTypes.end(),
               par_it = argumentTypes.begin(),
               par_et = parameterTypes.end();
            arg_it != arg_et && par_it != par_et;
            ++arg_it, ++par_it) {
                
                if (!is_subtype_of(*arg_it, *par_it))
                    continue; // Nope!
            }
        
        candidates.push_back(std::make_pair(fdecl, parameterTypes));
    }
    
    // 5. Remove any functions whose argument types differ from another candidate only by being more generic (e.g. (A, B, Int) vs (A, String, Int) )
    for (auto candidate : candidates) {
        for (auto target : candidates) {
            if (candidate.first == target.first)
                continue;
            
            int generic_pairs = 0;
            int equal_pairs = 0;
            for (std::deque<Type*>::iterator
               can_it = candidate.second.begin(),
               can_et = candidate.second.end(),
               tar_it = against_candidate.second.begin(),
               tar_et = against_candidate.second.end();
            can_it != can_et && tar_it != tar_et;
            ++can_it, ++tar_it) {
                
                if (is_generic(*can_it) && !is_generic(*tar_it)) {
                    generic_pairs++;
                }
                else if (is_equal(*can_it, *tar_it)) {
                    equal_pairs++;
                }
            }
            
            if (generic_pairs + equal_pairs == candidate.second.size()) {
                // Remove candidate
                ...
            }
        }
    }
    
    
    // 6. If there is not EXACTLY ONE candidate at this point, then error.
    if (candidates.size() != 1) {
        // Oopsie
        return ...;
    }
    
    return candidates[0]->signature->valuetype;
}
Type* type_of(SubscriptExpr* subscript) {
    Type* target_type = type_of(target);
    Type* value_type = type_of(value);
    
    // If target_type is a list
    if (type_is_list(target_type)) {
        // Make sure that the value_type is an int
        if (!type_is_int(value_type, true, true)) {
            // Error!
        }
        // If the type is optional or any then mark the SubscriptExpr as needing a test
        // if (type_is_optional(value_type) || type_is_any(value_type)) {
            // subscript->uses_slow_path(true);
        // }
        
        return static_cast<ListType*>(target_type)->
    }
}
Type* type_of(NumberLiteral* num) {
    if (num.exponent == 0)
        return new NamedType("Int");
    else
        return new NamedType("Real");
}
Type* type_of(StringLiteral* unused) {
    return new NamedType("String");
}
Type* type_of(ListLiteral* list) {
    return new ListType(common_type_of(list.items));
}
Type* type_of(DictLiteral* dict) {
    
}
Type* type_of(FunctionLiteral* function) {
    
}
Type* type_of(TupleLiteral* tuple) {
    std::deque types;
    for (Expr* e : tuple.items) {
        types.push_back(copy_pointer(type_of(e)));
    }
    return types;
}
Type* type_of(BoolLiteral* unused) {
    return new NamedType("Bool"); // That was easy
}

bool type_is_list(Type* t, bool allow_optional=true, bool allow_any=true) {
    // Either equal to NamedType("List") or is of TypeType::List
}
bool type_is_generic(Type* t) {
    // Generic types are either variables or Any
}
bool type_is_number(Type* t) {
    
}
bool type_is_string(Type* t) {

}
bool type_is_convertable_to(Type* source, Type* destination) {
    
    // We have conversions for
    //   Dict   --> Function
    //   T      --> T?
    //   Int    --> Real
    //   ...    --> Any
    //   Tuple <--> data
    //   Tuple  --> Dict, Function
    //   data   --> Dict, Function
    //   List   --> Dict, Function
    //   [Int]    --> [A]
    //   (A, A, A) --> [A]
    // TODO: Work out covariance of functions
}
