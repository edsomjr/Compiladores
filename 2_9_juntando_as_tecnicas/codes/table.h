#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <bits/stdc++.h>
#include "token.h"

class SymbolTable {
public:
    static SymbolTable& get_instance(); 

    void insert(const std::string& lexema, const Token& token);
    std::optional<Token> find(const std::string& lexema) const;

private:
    SymbolTable();
    std::map<std::string, Token> table;    
};

#endif
