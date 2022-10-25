#include <ostream>
#include "token.h"

std::ostream&
operator<<(std::ostream& os, const Token& token)
{
    switch (token.type) {
    case NUM:
        os << "NUM (" << std::get<int>(token.value) << ")";
        break;

    case ID:
        os << "ID (" << std::get<std::string>(token.value) << ")";
        break;

    case DIV:
        os << "DIV";
        break;

    case MOD:
        os << "MOD";
        break;

    case DONE:
        os << "DONE";
        break;

    default:
        os << (char) token.type;
    }

    return os;
}
