#import <string>
#import <vector>

#import "ast/ast.hpp"

#ifndef fmt
#define fmt(streamexpr) ({ std::ostringstream oss; oss << streamexpr; oss.str(); })
#endif

struct Diagnostic {
    enum class Kind {
        // For something to be an Error, it MUST prevent the compiler from generating code.
        // This is an objective and mandatory requirement for classifying errors vs warnings.
        // Down with this sort of thing! http://ridiculousfish.com/blog/posts/go_bloviations.html#go_damnableuse
        Error,
        
        // A Warning does not prevent the compiler from generating code.
        Warning,
    };
    
    Kind kind;
    std::string file;
    long indexStart;
    long indexEnd;
    
    void populateFrom(Expr& expr) {
        // TODO
    }
    
    // long line;
    // long column;
    
    // void resolve();
};

struct DiagnosticContext {
    std::vector<Diagnostic> diagnostics;
    
    void push(Diagnostic d) {
        diagnostics.push_back(d);
    }
};

