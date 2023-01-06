%{
    enum {
        LT, LE, EQ, NE, GT, GE,
        IF, THEN, ELSE, ID, NUM, RELOP, END_OF_FILE
    };

    int yylval;
    int instalar_id();
    int instalar_num();
%}

delim   [ \t\n]
ws      {delim}+
letra   [A-Za-z]
digito  [0-9]
id      {letra}({letra}|{digito})*
num     {digito}+(\.{digito}+)?(E[+-]?{digito}+)?

%%

{ws}    { printf("WS\n"); /* Nenhum valor retornado */ }
if      { return IF; }
then    { return THEN; }
else    { return ELSE; }
{id}    { yylval = instalar_id(); return ID; }
{num}   { yylval = instalar_num(); return NUM; }
"<"     { yylval = LT; return RELOP; }
"<="    { yylval = LE; return RELOP; }
"="     { yylval = EQ; return RELOP; }
"<>"    { yylval = NE; return RELOP; }
">"     { yylval = GT; return RELOP; }
">="    { yylval = GE; return RELOP; }
<<EOF>> { return END_OF_FILE; }

%%

int instalar_id()
{
    // Insere o lexema e o token na tabela de símbolos e retorna o índice da tabela
    // onde o símbolo foi inserido. O lexema fica armazenado na variável yytext
    return -1;
}

int instalar_num()
{
    // Insere o valor do lexema na tabela de números e retorna o índice da tabela
    // onde o número foi inserido. O lexema fica armazenado na variável yytext
    return -2;
}

// Retorno diferente de zero indica que o scanner deve encerrar ao encontrar EOF
int yywrap() { return 1; }  

int main()
{
    while (1)
    {
        int token = yylex();

        if (token == END_OF_FILE)
        {
            printf("Fim da entrada\n");
            return 0;
        }

        printf("Token = %d, yytext = %s, yylval = %d\n", token, yytext, yylval);
    }

    return 0;
}
