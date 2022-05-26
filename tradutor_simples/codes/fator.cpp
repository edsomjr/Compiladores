using token_t = std::pair<int, int>;

// NUM deve ter um valor diferente de qualquer caractere da tabela ASCII
const int NUM { 256 };  

void fator()
{
    auto [token, valor] = lookahead;

    if (token == '(') {
        reconhecer('(');
        expr();
        reconhecer(')');
    } else if (token == NUM) {
        reconhecer(NUM);
        std::cout << valor;
    } else
        erro();
}
