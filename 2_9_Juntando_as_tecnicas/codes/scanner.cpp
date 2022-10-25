#include <iostream>
#include "scanner.h"
#include "table.h"

namespace scanner {

    Token next_token()
    {
        auto c = std::cin.get();

        while (isspace(c))
            c = std::cin.get();

        if (c == EOF)
            return { DONE, "" };

        if (isdigit(c))
        {
            std::cin.unget();

            int value;
            std::cin >> value; 

            return { NUM, value };
        }

        if (isalpha(c))
        {
            std::string lexema;

            while (isalpha(c))
            {
                lexema.push_back(c);
                c = std::cin.get();
            }

            std::cin.unget();

            auto table = SymbolTable::get_instance();
            auto token = table.find(lexema);

            if (not token)
            {
                table.insert(lexema, Token(ID, lexema));
                return { ID, lexema };
            } else
                return token.value();
        }

        if (isgraph(c))
            return Token(c);

        return Token(DONE);
    }
}
