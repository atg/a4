#import <string>
#import <cassert>
#import <cstdio>
#import <cstdlib>
#import <vector>
#import "parse/tokenizer.hpp"

struct Type {
    enum class Kind {
        Named,
        Variable,
        List,
        Dict,
        Function,
        Tuple,
        Optional,
    };
    Kind kind;
};
struct NamedType : public Type {
    std::string name;
    NamedType(std::string _name) : name(_name) { }
};
struct VariableType : public Type {
    std::string name;
    VariableType(std::string _name) : name(_name) { }
};
struct ListType : public Type {
    std::shared_ptr<Type> of_ptr;
    Type& of() { return *of_ptr; }
    ListType(Type* _of) : of_ptr(_of) { }
};
struct DictType : public Type {
    std::shared_ptr<Type> key_ptr;
    Type& key() { return *key_ptr; }
    std::shared_ptr<Type> value_ptr;
    Type& value() { return *value_ptr; }
    DictType(Type* _key, Type* _value) : key_ptr(_key), value_ptr(_value) { }
};
struct FunctionType : public Type {
    std::shared_ptr<Type> from_ptr;
    Type& from() { return *from_ptr; }
    std::shared_ptr<Type> to_ptr;
    Type& to() { return *to_ptr; }
    FunctionType(Type* _from, Type* _to) : from_ptr(_from), to_ptr(_to) { }
};
struct TupleType : public Type {
    std::vector<std::shared_ptr<Type>> items;
    TupleType(std::vector<std::shared_ptr<Type>> _items) : items(_items) { }
};
struct OptionalType : public Type {
    std::shared_ptr<Type> of_ptr;
    Type& of() { return *of_ptr; }
    OptionalType(Type* _of) : of_ptr(_of) { }
};
