#include <bits/stdc++.h>

using token_t = std::pair<int, int>;
const int NUM = 256, NONE = -1;

token_t scanner()
{
    while (not std::cin.eof())
    {
        auto c = std::cin.get();

        if (isspace(c))
            continue;

        if (isdigit(c))
        {
            int valor = c - '0';

            while (not std::cin.eof() and (c = std::cin.get(), isdigit(c)))
                valor = 10*valor + (c - '0');
            
            std::cin.unget();

            return { NUM, valor };
        } else
            return { c, NONE };
    }

    return { EOF, NONE };
}

int main()
{
    while (true)
    {
        auto [lookahead, valor] = scanner();

        if (lookahead == EOF)
            break;
        else if (lookahead == NUM)
            std::cout << "Número lido: " << valor << '\n';
        else
            std::cout << "Token lido: " << (char) lookahead << '\n';
    }

    return 0;
}
