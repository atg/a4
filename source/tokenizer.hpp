#import <deque>
#import <string>
#import "tokentypes.hpp"

struct Token {
    int type;
    int location;
    const char* payloadStart;
    const char* payloadEnd;
};

std::deque<Token> tokenize(const std::string& content);
