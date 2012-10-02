namespace ir {

struct IR;
struct Literal;
struct Type;

using LetBinding = std::pair<uint64_t, std::shared_ptr<IR>>;

%data IR
  %all% (Type type)
  
  var   (uint64_t id)
  lit   (Literal value)
  tuple (std::vector<std::shared_ptr<IR>> items)
  app   (Exp target, Exp arg)
  let   (std::vector<LetBinding> bindings)
%end

%data Literal
  int (bool sign, uint64_t coef)
  real (bool sign, uint64_t coef, uint64_t exponent)
  bool (bool value)
  string (std::string value)
%end

%data Type
  named (std::string name)
  app (Type target, Type arg)
%end

};

