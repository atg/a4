#import <unordered_map>
#import <unordered_set>

#import "ast/ast.hpp"

struct Scope {
    std::shared_ptr<Scope> parent;
    
    std::unordered_map<std::string, Decl*> symbols;
    std::unordered_map<std::string, Type*> types;
    
    Decl* resolve(const std::string& ident) {
        auto it = symbols.find(ident);
        
        // If we didn't find a symbol, search upwards
        if (it == symbols.end()) {
            if (parent)
                return parent->resolve(ident);
            return NULL;
        }
        
        return it->second;
    }
    Type* resolveType(const std::string& ident) {
        auto it = types.find(ident);
        
        // If we didn't find a symbol, search upwards
        if (it == types.end()) {
            if (parent)
                return parent->resolveType(ident);
            return NULL;
        }
        
        return it->second;
    }
};
