#include "table.h"

SymbolTable& SymbolTable::get_instance()
{
    static SymbolTable instance;
    return instance;
}

SymbolTable::SymbolTable()
{
    insert("div", Token(DIV));
    insert("mod", Token(MOD));
}

void 
SymbolTable::insert(const std::string& lexema, const Token& token)
{
    table[lexema] = token;
}

std::optional<Token> 
SymbolTable::find(const std::string& lexema) const
{
    if (table.count(lexema))
        return table.at(lexema);

    return { };
}
