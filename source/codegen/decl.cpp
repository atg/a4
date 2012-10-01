#import "codegen/codegen.hpp"

void codegen(ParseTree tree, std::ostream& out) {
    for (Decl* decl : tree.decls) {
        codegen(decl, out);
        out << '\n';
    }
}

void codegen(Decl* decl, std::ostream& out) {
    switch (decl->type) {
        case DeclType::Function:
            codegen(static_cast<FunctionDecl*>(decl), out);
            break;

        case DeclType::Unspecified: break;
    }
}

void codegen(FunctionDecl* decl, std::ostream& out) {    
    out << "static " << "RETURN_TYPE" << ' ' << decl->name << '(';

    // Arguments
    bool isFirst = true;
    for (const std::string& param : decl->parameters) {

        if (!isFirst)
            out << ", ";
        else
            isFirst = false;

        out << "PARAM_TYPE" << ' ' << param;
    }

    out << ") {\n";
    out << "    return ";
    codegen(decl->body, out);
    out << ";\n}";
}
