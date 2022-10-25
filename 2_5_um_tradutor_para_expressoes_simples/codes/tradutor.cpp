#include <iostream>

using token = char;

token proximo_token()
{
    auto t = std::cin.get();

    return (token) t;
}

token lookahead;

void erro()
{
    std::cerr << "\nErro de sintaxe! lookahead = " << lookahead << '\n';
    exit(-1);
}

void reconhecer(token t)
{
    if (lookahead == t)
        lookahead = proximo_token();
    else
        erro();
}

void digito()
{
    if (isdigit(lookahead))
    {
        std::cout.put(lookahead);
        reconhecer(lookahead);
    } else
    {
        erro();
    }
}

void resto()
{
    if (lookahead == '+' or lookahead == '-')
    {
        auto c = lookahead;
        reconhecer(c);
        digito();
        std::cout.put(c);
        resto();
    }
}

void expr()
{
    digito();
    resto();
}

int main()
{
    lookahead = proximo_token(); 

    expr();

    std::cout.put('\n');

    return 0;
}
