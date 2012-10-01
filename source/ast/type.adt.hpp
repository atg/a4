#import <string>
#import <cassert>
#import <cstdio>
#import <cstdlib>
#import <vector>
#import "parse/tokenizer.hpp"

%data Type

named    (std::string name)
variable (std::string name)
list     (Type of)
dict     (Type key, Type value)
function (Type from, Type to)
tuple    (std::vector<std::shared_ptr<Type>> items)
optional (Type of)

%end
