#import <unordered_map>
#import <unordered_set>

#import "ast/ast.hpp"

struct Scope {
    Scope& global;
    std::unique_ptr<Scope> parent;
    
    std::unordered_map<std::string, Decl*> symbols;
    
    Decl* find(const std::string& ident) {
        auto it = symbols.find(ident);
        
        // If we didn't find a symbol, search upwards
        if (it == symbols.end()) {
            if (parent)
                return parent->find(ident);
            return NULL;
        }
        
        return it->second;
    }
};

