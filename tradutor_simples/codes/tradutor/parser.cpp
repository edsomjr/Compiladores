#include "scanner.h"
#include "parser.h"
#include "table.h"
#include "error.h"

Token lookahead;

namespace parser {

    void expr();
    void termo();
    void fator();

    void reconhecer(const Token& token);
    void print(const Token& token);

    void parse()
    {
        lookahead = scanner::next_token();

        while (lookahead.type != DONE)
        {
            expr();
            reconhecer(Token(';'));
            std::cout << '\n';
        }
    }

    void expr()
    {
        termo();

        while (true)
        {
            if (lookahead.type == '+' or lookahead.type == '-')
            {
                auto t = lookahead;

                reconhecer(lookahead);
                termo();
                print(t);
            } 
            else
                break;
        }
    }

    void termo()
    {
        fator();

        while (true) {
            switch (lookahead.type) {
            case '*':
            case '/':
            case DIV:
            case MOD:
            {
                auto t = lookahead;
                reconhecer(lookahead);
                fator();
                print(t);
                break;
            }

            default:
                return;
            }
        }
    }

    void fator()
    {
        switch (lookahead.type) {
        case '(':
            reconhecer(Token('('));
            expr();
            reconhecer(Token(')'));
            break;

        case NUM:
        case ID:
            print(lookahead);
            reconhecer(lookahead);
            break;

        default:
            erro("Erro de sintaxe em fator");
        }
    }

    void reconhecer(const Token& token)
    {
        if (token.type == lookahead.type)
            lookahead = scanner::next_token();
        else
            erro("Erro de sintaxe em reconhecer");
    }

    void print(const Token& token)
    {
        switch (token.type) {
        case '+':
        case '-':
        case '/':
        case '*':
            std::cout << (char) token.type;
            break;

        case DIV:
        case MOD:
            std::cout << token;
            break;

        case ID:
            std::cout << std::get<std::string>(token.value);
            break;

        case NUM:
            std::cout << std::get<int>(token.value);
            break;

        default:
            std::cout << "token desconhecido = " << token << '\n';
        }
    }
}
