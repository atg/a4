#import <string>
#import <cassert>
#import <cstdio>
#import <cstdlib>
#import "parse/tokenizer.hpp"

enum class TypeType {
    Unspecified = 0,
    Variable,
    Named,
    List,
    Dict,
    Function,
    Tuple,
    Optional,
}
struct Type {
    
};
struct TypeVariable : public Type {

    std::string name;
    TypeVariable(std::string name) : name(name) {
        type = TypeType::Variable;
    }
};
struct NamedType : public Type {
    
    std::string name;
    NamedType(std::string name) : name(name) {
        type = TypeType::Named;
    }
};
struct ListType : public Type {
    
    Type* membertype;
    ListType(Type* membertype) : membertype(membertype) {
        type = TypeType::List;
    }
};
struct DictType : public Type {

    Type* keytype;
    Type* valuetype;
    DictType(Type* keytype, Type* valuetype) : keytype(keytype), valuetype(valuetype) {
        type = TypeType::Dict;
    }
};
struct FunctionType : public Type {

    Type* keytype;
    Type* valuetype;
    FunctionType(Type* keytype, Type* valuetype) : keytype(keytype), valuetype(valuetype) {
        type = TypeType::Function;
    }
};
struct OptionalType : public Type {

    Type* membertype;
    ListType(Type* membertype) : membertype(membertype) {
        type = TypeType::List;
    }
};

