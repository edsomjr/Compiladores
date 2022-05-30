#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <variant>

enum TokenType { NUM = 256, DIV, MOD, ID, DONE };

struct Token {
    int type;
    std::variant<int, std::string> value; 

    Token(int t, int v) : type(t), value(v) { }
    Token(int t = DONE, std::string s = "") : type(t), value(s) { }
};

std::ostream& operator<<(std::ostream& os, const Token& token);

#endif
