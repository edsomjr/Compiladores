#include <bits/stdc++.h>
#include "buffer.h"

using namespace std;
using pattern = int (*)(int);
using edge = pair<int, pattern>;

template<int c> int match(int x) { return c == x; };
int wildcard(int) { return 1; };

map<int, vector<edge>> diagram {
    { 0, { { 1, match<'<'> }, { 5, match<'='> }, { 6, match<'>'> } } },
    { 1, { { 2, match<'='> }, { 3, match<'>'> }, { 4, wildcard } } },
    { 6, { { 7, match<'='> }, { 8, wildcard } } },
    { 9, { { 10, isalpha } } },
    { 10, { { 10, isalpha }, { 11, wildcard } } },
    { 28, { { 29, isspace } } },
    { 29, { { 29, isspace }, { 30, wildcard } } },
};

enum TokenType { IF, THEN, ELSE, RELOP, ID, DONE  };

struct Token {
    TokenType type;
    variant<int, string> value;

    Token(TokenType t, int v) : type(t), value(v) { }
    Token(TokenType t = DONE, const string& v = "") : type(t), value(v) { }
};

map<string, Token> symbolTable {
    { "if", { IF } },
    { "then", { THEN } },
    { "else", { ELSE } },
};

const string relationalOperatorsNames[] { "LE", "NE", "LT", "EQ", "GE", "GT" };
const string keywordsNames[] { "IF", "THEN", "ELSE" };

Token install(const string& lexema)
{
    if (not symbolTable.count(lexema))
        symbolTable[lexema] = Token(ID, lexema);

    return symbolTable[lexema];
}

using returnToken = function<optional<Token>(string&)>;

enum RelationalOperators { LE, NE, LT, EQ, GE, GT };
auto in = IOBuffer::getInstance();

map<int, returnToken> accept {
    { 2, [](string&) { return Token(RELOP, LE); } },
    { 3, [](string&) { return Token(RELOP, NE); } },
    { 4, [](string&) { in.unget(); return Token(RELOP, LT); } },
    { 5, [](string&) { return Token(RELOP, EQ); } },
    { 7, [](string&) { return Token(RELOP, GE); } },
    { 8, [](string&) { in.unget(); return Token(RELOP, GT); } },
    { 11, [](string& lexema) { in.unget(); lexema.pop_back(); return install(lexema); } },
    { 30, [](string& lexema) { in.unget(); return optional<Token>(); } }
};
    
ostream& operator<<(ostream& os, const Token& token)
{
    switch (token.type) {
    case RELOP:
        os << "RELOP (" << relationalOperatorsNames[get<int>(token.value)] << ")";
        break;

    case ID:
        os << "ID (" << get<string>(token.value) << ")";
        break;

    case IF:
    case THEN:
    case ELSE:
        os << "Keyword (" << keywordsNames[token.type] << ")";
        break;
    }

    return os;
}

optional<int> nextState(int state, int lookahead)
{
    for (auto [next, isMatch] : diagram.at(state))
        if (isMatch(lookahead))
            return next;

    return { };
}

optional<Token> nextToken()
{
    if (in.eof())
        return Token(DONE);
        
    vector<int> beginStates { 0, 9, 28 };
    auto start = in.tell();

    for (auto state : beginStates)
    {
        string lexema;

        while (not accept.count(state))
        {
            auto c = in.get();
            auto next = nextState(state, c);

            if (not next)
                break;

            lexema.push_back((char) c);
            state = next.value();
        } 

        if (accept.count(state))
            return accept[state](lexema);

        in.seek(start);
    }

    cerr << "Lexical error!\n";
    exit(-1);
}

int main()
{
    while (true)
    {
        auto token = nextToken();

        if (token)
        {
            if (token.value().type == DONE)
                break;

            cout << token.value() << '\n'; 
        }
    }
}
